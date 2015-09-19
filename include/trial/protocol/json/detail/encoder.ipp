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

template <typename CharT>
struct outputter
{
    static std::size_t write(buffer::base<CharT>& buffer,
                             CharT character)
    {
        if (buffer.grow(1))
        {
            buffer.write(character);
            return 1;
        }
        return 0;
    }

    static std::size_t write(buffer::base<CharT>& buffer,
                             const boost::basic_string_ref<CharT>& data)
    {
        const std::size_t size = data.size();
        if (buffer.grow(size))
        {
            buffer.write(data);
            return size;
        }
        return 0;
    }
};

//-----------------------------------------------------------------------------
// basic_encoder_functor
//-----------------------------------------------------------------------------

template <typename CharT>
template <typename T, typename Enable>
struct basic_encoder<CharT>::type_matcher
{
};

// Tags

template <typename CharT>
template <typename T>
struct basic_encoder<CharT>::type_matcher<T,
                                          typename boost::enable_if< boost::is_same<T, token::null> >::type>
{
    static size_type write(basic_encoder<CharT>& self)
    {
        return outputter<CharT>::write(*self.buffer, traits<CharT>::null_text());
    }
};

template <typename CharT>
template <typename T>
struct basic_encoder<CharT>::type_matcher<T,
                                          typename boost::enable_if< boost::is_same<T, token::begin_array> >::type>
{
    static size_type write(basic_encoder<CharT>& self)
    {
        return outputter<CharT>::write(*self.buffer, traits<CharT>::alpha_bracket_open);
    }
};

template <typename CharT>
template <typename T>
struct basic_encoder<CharT>::type_matcher<T,
                                          typename boost::enable_if< boost::is_same<T, token::end_array> >::type>
{
    static size_type write(basic_encoder<CharT>& self)
    {
        return outputter<CharT>::write(*self.buffer, traits<CharT>::alpha_bracket_close);
    }
};

template <typename CharT>
template <typename T>
struct basic_encoder<CharT>::type_matcher<T,
                                          typename boost::enable_if< boost::is_same<T, token::begin_object> >::type>
{
    static size_type write(basic_encoder<CharT>& self)
    {
        return outputter<CharT>::write(*self.buffer, traits<CharT>::alpha_brace_open);
    }
};

template <typename CharT>
template <typename T>
struct basic_encoder<CharT>::type_matcher<T,
                                          typename boost::enable_if< boost::is_same<T, token::end_object> >::type>
{
    static size_type write(basic_encoder<CharT>& self)
    {
        return outputter<CharT>::write(*self.buffer, traits<CharT>::alpha_brace_close);
    }
};

template <typename CharT>
template <typename T>
struct basic_encoder<CharT>::type_matcher<T,
                                          typename boost::enable_if< boost::is_same<T, token::value_separator> >::type>
{
    static size_type write(basic_encoder<CharT>& self)
    {
        return outputter<CharT>::write(*self.buffer, traits<CharT>::alpha_comma);
    }
};

template <typename CharT>
template <typename T>
struct basic_encoder<CharT>::type_matcher<T,
                                          typename boost::enable_if< boost::is_same<T, token::name_separator> >::type>
{
    static size_type write(basic_encoder<CharT>& self)
    {
        return outputter<CharT>::write(*self.buffer, traits<CharT>::alpha_colon);
    }
};

// Integers

template <typename CharT>
template <typename T>
struct basic_encoder<CharT>::type_matcher<T,
                                          typename boost::enable_if< boost::is_integral<T> >::type>
{
    static size_type write(basic_encoder<CharT>& self, const T& data)
    {
        typedef boost::array<CharT, std::numeric_limits<T>::digits10> array_type;
        array_type output;

        // Build buffer backwards
        typename array_type::reverse_iterator where = output.rbegin();
        const bool is_negative = data < 0;
        typename boost::make_unsigned<T>::type number = std::abs(data);
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
        const size_type size = std::distance(begin, output.cend()) + (is_negative ? 1 : 0);

        if (!self.buffer->grow(size))
        {
            return 0;
        }
        if (is_negative)
        {
            self.buffer->write(traits<CharT>::alpha_minus);
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

template <typename CharT>
template <typename T>
struct basic_encoder<CharT>::type_matcher<T,
                                          typename boost::enable_if< boost::is_floating_point<T> >::type>
{
    static size_type write(basic_encoder<CharT>& self, const T& data)
    {
        switch (boost::math::fpclassify(data))
        {
        case FP_INFINITE:
        case FP_NAN:
            // Infinity and NaN must be encoded as null
            return outputter<CharT>::write(*self.buffer, traits<CharT>::null_text());
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

// Floating point numbers

template <typename CharT>
template <typename T>
struct basic_encoder<CharT>::type_matcher<T,
                                          typename boost::enable_if< boost::is_same<T, boost::basic_string_ref<CharT> > >::type>
{
    static size_type write(basic_encoder<CharT>& self, const T& data)
    {
        // This is an approximation of the size. Further characters may be
        // added by escaped characters, in which case we grow the buffer
        // per escape character.
        size_type size = sizeof(CharT) + data.size() + sizeof(CharT);

        if (!self.buffer->grow(size))
        {
            return 0;
        }

        self.buffer->write(traits<CharT>::alpha_quote);
        for (typename view_type::const_iterator it = data.begin();
             it != data.end();
             ++it)
        {
            switch (*it)
            {
            case traits<CharT>::alpha_quote:
            case traits<CharT>::alpha_reverse_solidus:
            case traits<CharT>::alpha_solidus:
                if (outputter<CharT>::write(*self.buffer, traits<CharT>::alpha_reverse_solidus) == 0)
                    return 0;
                self.buffer->write(*it);
                ++size;
                break;

            case traits<CharT>::alpha_backspace:
                if (outputter<CharT>::write(*self.buffer, traits<CharT>::alpha_reverse_solidus) == 0)
                    return 0;
                self.buffer->write(traits<CharT>::alpha_b);
                ++size;
                break;

            case traits<CharT>::alpha_formfeed:
                if (outputter<CharT>::write(*self.buffer, traits<CharT>::alpha_reverse_solidus) == 0)
                    return 0;
                self.buffer->write(traits<CharT>::alpha_f);
                ++size;
                break;

            case traits<CharT>::alpha_newline:
                if (outputter<CharT>::write(*self.buffer, traits<CharT>::alpha_reverse_solidus) == 0)
                    return 0;
                self.buffer->write(traits<CharT>::alpha_n);
                ++size;
                break;

            case traits<CharT>::alpha_return:
                if (outputter<CharT>::write(*self.buffer, traits<CharT>::alpha_reverse_solidus) == 0)
                    return 0;
                self.buffer->write(traits<CharT>::alpha_r);
                ++size;
                break;

            case traits<CharT>::alpha_tab:
                if (outputter<CharT>::write(*self.buffer, traits<CharT>::alpha_reverse_solidus) == 0)
                    return 0;
                self.buffer->write(traits<CharT>::alpha_t);
                ++size;
                break;

            default:
                self.buffer->write(*it);
                break;
            }
        }
        self.buffer->write(traits<CharT>::alpha_quote);

        return size;
    }
};

template <typename CharT>
template <typename T>
struct basic_encoder<CharT>::type_matcher<T,
                                          typename boost::enable_if< boost::is_same<T, std::basic_string<CharT> > >::type>
{
    static size_type write(basic_encoder<CharT>& self, const T& data)
    {
        return type_matcher< typename boost::basic_string_ref<CharT> >::write(self, data);
    }
};

//-----------------------------------------------------------------------------
// basic_encoder
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
    return type_matcher<U>::write(*this, data);
}

template <typename CharT>
typename basic_encoder<CharT>::size_type
basic_encoder<CharT>::value(bool data)
{
    if (data)
    {
        return outputter<CharT>::write(*buffer, traits<CharT>::true_text());
    }
    else
    {
        return outputter<CharT>::write(*buffer, traits<CharT>::false_text());
    }
};

template <typename CharT>
typename basic_encoder<CharT>::size_type
basic_encoder<CharT>::value(const CharT *data)
{
    return type_matcher< typename boost::basic_string_ref<CharT> >::write(*this, data);
};

template <typename CharT>
template <typename U>
typename basic_encoder<CharT>::size_type basic_encoder<CharT>::value()
{
    return type_matcher<U>::write(*this);
}

template <typename CharT>
typename basic_encoder<CharT>::size_type
basic_encoder<CharT>::literal(const view_type& data)
{
    return outputter<CharT>::write(*buffer, data);
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
