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
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/is_integral.hpp>
#include <boost/type_traits/is_floating_point.hpp>
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
// encoder_overloader
//-----------------------------------------------------------------------------

template <typename CharT, typename T, typename Enable = void>
struct encoder_overloader
{
};

// Tags

template <typename CharT, typename T>
struct encoder_overloader<CharT,
                          T,
                          typename boost::enable_if< boost::is_same<T, token::null> >::type>
{
    typedef typename basic_encoder<CharT>::size_type size_type;

    inline static size_type write(basic_encoder<CharT>& self)
    {
        return self.null_value();
    }
};

template <typename CharT, typename T>
struct encoder_overloader<CharT,
                          T,
                          typename boost::enable_if< boost::is_same<T, token::begin_array> >::type>
{
    typedef typename basic_encoder<CharT>::size_type size_type;

    inline static size_type write(basic_encoder<CharT>& self)
    {
        return self.begin_array_value();
    }
};

template <typename CharT, typename T>
struct encoder_overloader<CharT,
                          T,
                          typename boost::enable_if< boost::is_same<T, token::end_array> >::type>
{
    typedef typename basic_encoder<CharT>::size_type size_type;

    inline static size_type write(basic_encoder<CharT>& self)
    {
        return self.end_array_value();
    }
};

template <typename CharT, typename T>
struct encoder_overloader<CharT,
                          T,
                          typename boost::enable_if< boost::is_same<T, token::begin_object> >::type>
{
    typedef typename basic_encoder<CharT>::size_type size_type;

    inline static size_type write(basic_encoder<CharT>& self)
    {
        return self.begin_object_value();
    }
};

template <typename CharT, typename T>
struct encoder_overloader<CharT,
                          T,
                          typename boost::enable_if< boost::is_same<T, token::end_object> >::type>
{
    typedef typename basic_encoder<CharT>::size_type size_type;

    inline static size_type write(basic_encoder<CharT>& self)
    {
        return self.end_object_value();
    }
};

template <typename CharT, typename T>
struct encoder_overloader<CharT,
                          T,
                          typename boost::enable_if< boost::is_same<T, token::value_separator> >::type>
{
    typedef typename basic_encoder<CharT>::size_type size_type;

    static size_type write(basic_encoder<CharT>& self)
    {
        return self.value_separator_value();
    }
};

template <typename CharT, typename T>
struct encoder_overloader<CharT,
                          T,
                          typename boost::enable_if< boost::is_same<T, token::name_separator> >::type>
{
    typedef typename basic_encoder<CharT>::size_type size_type;

    static size_type write(basic_encoder<CharT>& self)
    {
        return self.name_separator_value();
    }
};

// Integers

template <typename CharT, typename T>
struct encoder_overloader<CharT,
                          T,
                          typename boost::enable_if< boost::is_integral<T> >::type>
{
    typedef typename basic_encoder<CharT>::size_type size_type;

    inline static size_type write(basic_encoder<CharT>& self,
                                  const T& data)
    {
        return self.integral_value(data);
    }
};

// Floating point numbers

template <typename CharT, typename T>
struct encoder_overloader<CharT,
                          T,
                          typename boost::enable_if< boost::is_floating_point<T> >::type>
{
    typedef typename basic_encoder<CharT>::size_type size_type;

    inline static size_type write(basic_encoder<CharT>& self,
                                  const T& data)
    {
        return self.floating_value(data);
    }
};

// Strings

template <typename CharT, typename T>
struct encoder_overloader<CharT,
                          T,
                          typename boost::enable_if< boost::is_same<T, typename basic_encoder<CharT>::view_type> >::type>
{
    typedef typename basic_encoder<CharT>::size_type size_type;
    typedef typename basic_encoder<CharT>::view_type view_type;

    static size_type write(basic_encoder<CharT>& self,
                           const view_type& data)
    {
        return self.string_value(data);
    }
};

template <typename CharT, typename T>
struct encoder_overloader<CharT,
                          T,
                          typename boost::enable_if< boost::is_same<T, std::basic_string<CharT> > >::type>
{
    typedef typename basic_encoder<CharT>::size_type size_type;

    static size_type write(basic_encoder<CharT>& self,
                           const std::basic_string<CharT>& data)
    {
        return self.string_value(data);
    }
};

//-----------------------------------------------------------------------------
// basic_encoder<CharT>
//-----------------------------------------------------------------------------

template <typename CharT>
template <typename T>
basic_encoder<CharT>::basic_encoder(T& output)
    : buffer(new typename buffer::traits<T>::buffer_type(output))
{
};

template <typename CharT>
template <typename U>
typename basic_encoder<CharT>::size_type
basic_encoder<CharT>::value(const U& data)
{
    return encoder_overloader<CharT, U>::write(*this, data);
}

template <typename CharT>
typename basic_encoder<CharT>::size_type
basic_encoder<CharT>::value(bool data)
{
    if (data)
    {
        return write(traits<CharT>::true_text());
    }
    else
    {
        return write(traits<CharT>::false_text());
    }
};

template <typename CharT>
typename basic_encoder<CharT>::size_type
basic_encoder<CharT>::value(const value_type *data)
{
    return encoder_overloader<CharT, view_type>::write(*this, data);
};

template <typename CharT>
template <typename U>
typename basic_encoder<CharT>::size_type
basic_encoder<CharT>::value()
{
    return encoder_overloader<CharT, U>::write(*this);
}

template <typename CharT>
typename basic_encoder<CharT>::size_type
basic_encoder<CharT>::literal(const view_type& data)
{
    return write(data);
}

template <typename CharT>
template <typename T>
typename basic_encoder<CharT>::size_type
basic_encoder<CharT>::integral_value(const T& data)
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
        *where = traits<CharT>::alpha_0;
        ++where;
    }
    else
    {
        const T base = T(10);
        while (number != 0)
        {
            *where = traits<CharT>::alpha_0 + (number % base);
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
        buffer->write(traits<CharT>::alpha_minus);
    }
    while (begin != output.end())
    {
        buffer->write(*begin);
        ++begin;
    }
    return size;
}

template <typename CharT>
template <typename T>
typename basic_encoder<CharT>::size_type
basic_encoder<CharT>::floating_value(const T& data)
{
    switch (boost::math::fpclassify(data))
    {
    case FP_INFINITE:
    case FP_NAN:
        // Infinity and NaN must be encoded as null
        return write(traits<CharT>::null_text());
    default:
        break;
    }

    std::string work = boost::lexical_cast<std::string>(data);
    return write(work);
}

template <typename CharT>
template <typename T>
typename basic_encoder<CharT>::size_type
basic_encoder<CharT>::string_value(const T& data)
{
    // This is an approximation of the size. Further characters may be
    // added by escaped characters, in which case we grow the buffer
    // per escape character.
    size_type size = sizeof(char) + data.size() + sizeof(char);

    if (!buffer->grow(size))
    {
        return 0;
    }

    buffer->write(traits<CharT>::alpha_quote);
    for (typename T::const_iterator it = data.begin();
         it != data.end();
         ++it)
    {
        switch (*it)
        {
        case traits<CharT>::alpha_quote:
        case traits<CharT>::alpha_reverse_solidus:
        case traits<CharT>::alpha_solidus:
            if (write(traits<CharT>::alpha_reverse_solidus) == 0)
                return 0;
            buffer->write(*it);
            ++size;
            break;

        case traits<CharT>::alpha_backspace:
            if (write(traits<CharT>::alpha_reverse_solidus) == 0)
                return 0;
            buffer->write(traits<CharT>::alpha_b);
            ++size;
            break;

        case traits<CharT>::alpha_formfeed:
            if (write(traits<CharT>::alpha_reverse_solidus) == 0)
                return 0;
            buffer->write(traits<CharT>::alpha_f);
            ++size;
            break;

        case traits<CharT>::alpha_newline:
            if (write(traits<CharT>::alpha_reverse_solidus) == 0)
                return 0;
            buffer->write(traits<CharT>::alpha_n);
            ++size;
            break;

        case traits<CharT>::alpha_return:
            if (write(traits<CharT>::alpha_reverse_solidus) == 0)
                return 0;
            buffer->write(traits<CharT>::alpha_r);
            ++size;
            break;

        case traits<CharT>::alpha_tab:
            if (write(traits<CharT>::alpha_reverse_solidus) == 0)
                return 0;
            buffer->write(traits<CharT>::alpha_t);
            ++size;
            break;

        default:
            buffer->write(*it);
            break;
        }
    }
    buffer->write(traits<CharT>::alpha_quote);

    return size;
}

template <typename CharT>
typename basic_encoder<CharT>::size_type
basic_encoder<CharT>::null_value()
{
    return write(traits<CharT>::null_text());
}

template <typename CharT>
typename basic_encoder<CharT>::size_type
basic_encoder<CharT>::begin_array_value()
{
    return write(traits<CharT>::alpha_bracket_open);
}

template <typename CharT>
typename basic_encoder<CharT>::size_type
basic_encoder<CharT>::end_array_value()
{
    return write(traits<CharT>::alpha_bracket_close);
}

template <typename CharT>
typename basic_encoder<CharT>::size_type
basic_encoder<CharT>::begin_object_value()
{
    return write(traits<CharT>::alpha_brace_open);
}

template <typename CharT>
typename basic_encoder<CharT>::size_type
basic_encoder<CharT>::end_object_value()
{
    return write(traits<CharT>::alpha_brace_close);
}

template <typename CharT>
typename basic_encoder<CharT>::size_type
basic_encoder<CharT>::value_separator_value()
{
    return write(traits<CharT>::alpha_comma);
}

template <typename CharT>
typename basic_encoder<CharT>::size_type
basic_encoder<CharT>::name_separator_value()
{
    return write(traits<CharT>::alpha_colon);
}

template <typename CharT>
typename basic_encoder<CharT>::size_type
basic_encoder<CharT>::write(value_type character)
{
    const size_type size = sizeof(character);
    if (buffer->grow(size))
    {
        buffer->write(character);
        return size;
    }
    return 0;
}

template <typename CharT>
typename basic_encoder<CharT>::size_type
basic_encoder<CharT>::write(const view_type& data)
{
    const typename view_type::size_type size = data.size();
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
