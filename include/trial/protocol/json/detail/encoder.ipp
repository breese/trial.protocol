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
// Helpers
//-----------------------------------------------------------------------------

struct outputter
{
    static std::size_t write(encoder::buffer_type& buffer,
                             char character)
    {
        if (buffer.grow(1))
        {
            buffer.write(character);
            return 1;
        }
        return 0;
    }

    static std::size_t write(encoder::buffer_type& buffer,
                             const encoder::view_type& data)
    {
        const encoder::view_type::size_type size = data.size();
        if (buffer.grow(size))
        {
            buffer.write(data);
            return size;
        }
        return 0;
    }
};

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
    static size_type write(encoder& self)
    {
        return outputter::write(*self.buffer, traits<char>::null_text());
    }
};

template <>
struct encoder::overloader<token::begin_array>
{
    static size_type write(encoder& self)
    {
        return outputter::write(*self.buffer, traits<char>::alpha_bracket_open);
    }
};

template <>
struct encoder::overloader<token::end_array>
{
    static size_type write(encoder& self)
    {
        return outputter::write(*self.buffer, traits<char>::alpha_bracket_close);
    }
};

template <>
struct encoder::overloader<token::begin_object>
{
    static size_type write(encoder& self)
    {
        return outputter::write(*self.buffer, traits<char>::alpha_brace_open);
    }
};

template <>
struct encoder::overloader<token::end_object>
{
    static size_type write(encoder& self)
    {
        return outputter::write(*self.buffer, traits<char>::alpha_brace_close);
    }
};

template <>
struct encoder::overloader<token::value_separator>
{
    static size_type write(encoder& self)
    {
        return outputter::write(*self.buffer, traits<char>::alpha_comma);
    }
};

template <>
struct encoder::overloader<token::name_separator>
{
    static size_type write(encoder& self)
    {
        return outputter::write(*self.buffer, traits<char>::alpha_colon);
    }
};

// Integers

template <typename T>
struct encoder::overloader<T,
                           typename boost::enable_if< boost::is_integral<T> >::type>
{
    static size_type write(encoder& self, const T& data)
    {
        typedef boost::array<encoder::value_type, std::numeric_limits<T>::digits10 + 1> array_type;
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

        if (!self.buffer->grow(size))
        {
            return 0;
        }
        if (is_negative)
        {
            self.buffer->write(traits<char>::alpha_minus);
        }
        while (begin != output.end())
        {
            self.buffer->write(*begin);
            ++begin;
        }
        return size;
    }
};

// Floating point numbers

template <typename T>
struct encoder::overloader<T,
                           typename boost::enable_if< boost::is_floating_point<T> >::type>
{
    static size_type write(encoder& self, const T& data)
    {
        switch (boost::math::fpclassify(data))
        {
        case FP_INFINITE:
        case FP_NAN:
            // Infinity and NaN must be encoded as null
            return outputter::write(*self.buffer, traits<char>::null_text());
        default:
            break;
        }

        std::string work = boost::lexical_cast<std::string>(data);
        const std::string::size_type size = work.size();

        if (!self.buffer->grow(size))
        {
            return 0;
        }

        for (std::string::const_iterator it = work.begin();
             it != work.end();
             ++it)
        {
            self.buffer->write(*it);
        }

        return size;
    }
};

// Strings

template <>
struct encoder::overloader<encoder::view_type>
{
    static size_type write(encoder& self, const view_type& data)
    {
        // This is an approximation of the size. Further characters may be
        // added by escaped characters, in which case we grow the buffer
        // per escape character.
        size_type size = sizeof(char) + data.size() + sizeof(char);

        if (!self.buffer->grow(size))
        {
            return 0;
        }

        self.buffer->write(traits<char>::alpha_quote);
        for (typename view_type::const_iterator it = data.begin();
             it != data.end();
             ++it)
        {
            switch (*it)
            {
            case traits<char>::alpha_quote:
            case traits<char>::alpha_reverse_solidus:
            case traits<char>::alpha_solidus:
                if (outputter::write(*self.buffer, traits<char>::alpha_reverse_solidus) == 0)
                    return 0;
                self.buffer->write(*it);
                ++size;
                break;

            case traits<char>::alpha_backspace:
                if (outputter::write(*self.buffer, traits<char>::alpha_reverse_solidus) == 0)
                    return 0;
                self.buffer->write(traits<char>::alpha_b);
                ++size;
                break;

            case traits<char>::alpha_formfeed:
                if (outputter::write(*self.buffer, traits<char>::alpha_reverse_solidus) == 0)
                    return 0;
                self.buffer->write(traits<char>::alpha_f);
                ++size;
                break;

            case traits<char>::alpha_newline:
                if (outputter::write(*self.buffer, traits<char>::alpha_reverse_solidus) == 0)
                    return 0;
                self.buffer->write(traits<char>::alpha_n);
                ++size;
                break;

            case traits<char>::alpha_return:
                if (outputter::write(*self.buffer, traits<char>::alpha_reverse_solidus) == 0)
                    return 0;
                self.buffer->write(traits<char>::alpha_r);
                ++size;
                break;

            case traits<char>::alpha_tab:
                if (outputter::write(*self.buffer, traits<char>::alpha_reverse_solidus) == 0)
                    return 0;
                self.buffer->write(traits<char>::alpha_t);
                ++size;
                break;

            default:
                self.buffer->write(*it);
                break;
            }
        }
        self.buffer->write(traits<char>::alpha_quote);

        return size;
    }
};

template <>
struct encoder::overloader<std::string>
{
    static size_type write(encoder& self, const std::string& data)
    {
        return overloader<encoder::view_type>::write(self, data);
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
        return outputter::write(*buffer, traits<char>::true_text());
    }
    else
    {
        return outputter::write(*buffer, traits<char>::false_text());
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
    return outputter::write(*buffer, data);
};

} // namespace detail
} // namespace json
} // namespace protocol
} // namespace trial

#if defined(TRIAL_PROTOCOL_JSON_DETAIL_LEXICAL_CAST)
#define BOOST_LEXICAL_CAST_ASSUME_C_LOCALE TRIAL_PROTOCOL_JSON_DETAIL_LEXICAL_CAST
#undef TRIAL_PROTOCOL_JSON_DETAIL_LEXICAL_CAST
#endif

#endif // TRIAL_PROTOCOL_JSON_DETAIL_ENCODER_IPP
