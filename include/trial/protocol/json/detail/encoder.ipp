#ifndef TRIAL_PROTOCOL_JSON_DETAIL_ENCODER_IPP
#define TRIAL_PROTOCOL_JSON_DETAIL_ENCODER_IPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2015 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <iterator>
#if defined(BOOST_LEXICAL_CAST_ASSUME_C_LOCALE)
#define TRIAL_PROTOCOL_JSON_DETAIL_LEXICAL_CAST BOOST_LEXICAL_CAST_ASSUME_C_LOCALE
#endif
#define BOOST_LEXICAL_CAST_ASSUME_C_LOCALE 1
#include <boost/lexical_cast.hpp>
#include <boost/static_assert.hpp>
#include <boost/array.hpp>
#include <boost/utility/string_ref.hpp>
#include <boost/math/special_functions/fpclassify.hpp>
#include <trial/protocol/buffer/base.hpp>
#include <trial/protocol/json/detail/traits.hpp>
#include <trial/protocol/json/token.hpp>

namespace trial
{
namespace protocol
{
namespace json
{
namespace detail
{

//-----------------------------------------------------------------------------
// encoder::overloader
//-----------------------------------------------------------------------------

template <typename T, typename Enable>
struct encoder::overloader
{
};

// Tags

template <>
struct encoder::overloader<token::null>
{
    inline static size_type write(encoder& self)
    {
        return self.null_value();
    }
};

template <>
struct encoder::overloader<token::begin_array>
{
    inline static size_type write(encoder& self)
    {
        return self.begin_array_value();
    }
};

template <>
struct encoder::overloader<token::end_array>
{
    inline static size_type write(encoder& self)
    {
        return self.end_array_value();
    }
};

template <>
struct encoder::overloader<token::begin_object>
{
    inline static size_type write(encoder& self)
    {
        return self.begin_object_value();
    }
};

template <>
struct encoder::overloader<token::end_object>
{
    inline static size_type write(encoder& self)
    {
        return self.end_object_value();
    }
};

template <>
struct encoder::overloader<token::value_separator>
{
    static size_type write(encoder& self)
    {
        return self.value_separator_value();
    }
};

template <>
struct encoder::overloader<token::name_separator>
{
    static size_type write(encoder& self)
    {
        return self.name_separator_value();
    }
};

// Integers

template <typename T>
struct encoder::overloader<T,
                           typename boost::enable_if< boost::is_integral<T> >::type>
{
    inline static size_type write(encoder& self, const T& data)
    {
        return self.integral_value(data);
    }
};

// Floating point numbers

template <typename T>
struct encoder::overloader<T,
                           typename boost::enable_if< boost::is_floating_point<T> >::type>
{
    inline static size_type write(encoder& self, const T& data)
    {
        return self.floating_value(data);
    }
};

// Strings

template <>
struct encoder::overloader<encoder::view_type>
{
    static size_type write(encoder& self, const view_type& data)
    {
        return self.string_value(data);
    }
};

template <>
struct encoder::overloader<std::string>
{
    static size_type write(encoder& self, const std::string& data)
    {
        return self.string_value(data);
    }
};

//-----------------------------------------------------------------------------
// encoder
//-----------------------------------------------------------------------------

template <typename T>
encoder::encoder(T& output)
    : buffer(new typename buffer::traits<T>::buffer_type(output))
{
};

template <typename U>
typename encoder::size_type encoder::value(const U& data)
{
    return overloader<U>::write(*this, data);
}

inline encoder::size_type encoder::value(bool data)
{
    if (data)
    {
        return write(traits<char>::true_text());
    }
    else
    {
        return write(traits<char>::false_text());
    }
};

inline encoder::size_type encoder::value(const char *data)
{
    return overloader<view_type>::write(*this, data);
};

template <typename U>
encoder::size_type encoder::value()
{
    return overloader<U>::write(*this);
}

inline encoder::size_type encoder::literal(const view_type& data)
{
    return write(data);
}

template <typename T>
encoder::size_type encoder::integral_value(const T& data)
{
    typedef boost::array<value_type, std::numeric_limits<T>::digits10 + 1> array_type;
    array_type output;

    // Build buffer backwards
    typename array_type::reverse_iterator where = output.rbegin();
    const bool is_negative = data < 0;
    typedef typename boost::make_unsigned<T>::type unsigned_type;
    unsigned_type number = unsigned_type(std::abs(data));
    if (number == 0)
    {
        *where = traits<char>::alpha_0;
        ++where;
    }
    else
    {
        const T base = T(10);
        while (number != 0)
        {
            *where = traits<char>::alpha_0 + (number % base);
            ++where;
            number /= base;
        }
    }
    typename array_type::const_iterator begin = where.base();
    const size_type size = size_type(std::distance(begin, output.cend()) + (is_negative ? 1 : 0));

    if (!buffer->grow(size))
    {
        return 0;
    }
    if (is_negative)
    {
        buffer->write(traits<char>::alpha_minus);
    }
    while (begin != output.end())
    {
        buffer->write(*begin);
        ++begin;
    }
    return size;
}

template <typename T>
encoder::size_type encoder::floating_value(const T& data)
{
    switch (boost::math::fpclassify(data))
    {
    case FP_INFINITE:
    case FP_NAN:
        // Infinity and NaN must be encoded as null
        return write(traits<char>::null_text());
    default:
        break;
    }

    std::string work = boost::lexical_cast<std::string>(data);
    return write(work);
}

template <typename T>
encoder::size_type encoder::string_value(const T& data)
{
    // This is an approximation of the size. Further characters may be
    // added by escaped characters, in which case we grow the buffer
    // per escape character.
    size_type size = sizeof(char) + data.size() + sizeof(char);

    if (!buffer->grow(size))
    {
        return 0;
    }

    buffer->write(traits<char>::alpha_quote);
    for (typename T::const_iterator it = data.begin();
         it != data.end();
         ++it)
    {
        switch (*it)
        {
        case traits<char>::alpha_quote:
        case traits<char>::alpha_reverse_solidus:
        case traits<char>::alpha_solidus:
            if (write(traits<char>::alpha_reverse_solidus) == 0)
                return 0;
            buffer->write(*it);
            ++size;
            break;

        case traits<char>::alpha_backspace:
            if (write(traits<char>::alpha_reverse_solidus) == 0)
                return 0;
            buffer->write(traits<char>::alpha_b);
            ++size;
            break;

        case traits<char>::alpha_formfeed:
            if (write(traits<char>::alpha_reverse_solidus) == 0)
                return 0;
            buffer->write(traits<char>::alpha_f);
            ++size;
            break;

        case traits<char>::alpha_newline:
            if (write(traits<char>::alpha_reverse_solidus) == 0)
                return 0;
            buffer->write(traits<char>::alpha_n);
            ++size;
            break;

        case traits<char>::alpha_return:
            if (write(traits<char>::alpha_reverse_solidus) == 0)
                return 0;
            buffer->write(traits<char>::alpha_r);
            ++size;
            break;

        case traits<char>::alpha_tab:
            if (write(traits<char>::alpha_reverse_solidus) == 0)
                return 0;
            buffer->write(traits<char>::alpha_t);
            ++size;
            break;

        default:
            buffer->write(*it);
            break;
        }
    }
    buffer->write(traits<char>::alpha_quote);

    return size;
}

inline encoder::size_type encoder::null_value()
{
    return write(traits<char>::null_text());
}

inline encoder::size_type encoder::begin_array_value()
{
    return write(traits<char>::alpha_bracket_open);
}

inline encoder::size_type encoder::end_array_value()
{
    return write(traits<char>::alpha_bracket_close);
}

inline encoder::size_type encoder::begin_object_value()
{
    return write(traits<char>::alpha_brace_open);
}

inline encoder::size_type encoder::end_object_value()
{
    return write(traits<char>::alpha_brace_close);
}

inline encoder::size_type encoder::value_separator_value()
{
    return write(traits<char>::alpha_comma);
}

inline encoder::size_type encoder::name_separator_value()
{
    return write(traits<char>::alpha_colon);
}

inline encoder::size_type encoder::write(value_type character)
{
    const size_type size = sizeof(character);
    if (buffer->grow(size))
    {
        buffer->write(character);
        return size;
    }
    return 0;
}

inline encoder::size_type encoder::write(const view_type& data)
{
    const view_type::size_type size = data.size();
    if (buffer->grow(size))
    {
        buffer->write(data);
        return size;
    }
    return 0;
}

} // namespace detail
} // namespace json
} // namespace protocol
} // namespace trial

#if defined(TRIAL_PROTOCOL_JSON_DETAIL_LEXICAL_CAST)
#define BOOST_LEXICAL_CAST_ASSUME_C_LOCALE TRIAL_PROTOCOL_JSON_DETAIL_LEXICAL_CAST
#undef TRIAL_PROTOCOL_JSON_DETAIL_LEXICAL_CAST
#endif

#endif // TRIAL_PROTOCOL_JSON_DETAIL_ENCODER_IPP
