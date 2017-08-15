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

#include <cmath>
#include <iterator>
#include <array>
#include <type_traits>
#include <trial/protocol/buffer/base.hpp>
#include <trial/protocol/json/detail/string_converter.hpp>
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

template <typename T, typename Enable = void>
struct absolute
{
    static T value(T value)
    {
        return std::abs(value);
    }
};

template <typename T>
struct absolute<T,
                typename std::enable_if<std::is_unsigned<T>::value>::type>
{
    static T value(T value)
    {
        return value;
    }
};

//-----------------------------------------------------------------------------
// encoder::overloader
//-----------------------------------------------------------------------------

template <typename CharT, std::size_t N>
template <typename T, typename Enable>
struct basic_encoder<CharT, N>::overloader
{
};

// Tags

template <typename CharT, std::size_t N>
template <typename T>
struct basic_encoder<CharT, N>::overloader<
    T,
    typename std::enable_if<std::is_same<T, token::null>::value>::type>
{
    using size_type = typename basic_encoder<CharT, N>::size_type;

    inline static size_type write(basic_encoder<CharT, N>& self)
    {
        return self.null_value();
    }
};

template <typename CharT, std::size_t N>
template <typename T>
struct basic_encoder<CharT, N>::overloader<
    T,
    typename std::enable_if<std::is_same<T, token::begin_array>::value>::type>
{
    using size_type = typename basic_encoder<CharT, N>::size_type;

    inline static size_type write(basic_encoder<CharT, N>& self)
    {
        return self.begin_array_value();
    }
};

template <typename CharT, std::size_t N>
template <typename T>
struct basic_encoder<CharT, N>::overloader<
    T,
    typename std::enable_if<std::is_same<T, token::end_array>::value>::type>
{
    using size_type = typename basic_encoder<CharT, N>::size_type;

    inline static size_type write(basic_encoder<CharT, N>& self)
    {
        return self.end_array_value();
    }
};

template <typename CharT, std::size_t N>
template <typename T>
struct basic_encoder<CharT, N>::overloader<
    T,
    typename std::enable_if<std::is_same<T, token::begin_object>::value>::type>
{
    using size_type = typename basic_encoder<CharT, N>::size_type;

    inline static size_type write(basic_encoder<CharT, N>& self)
    {
        return self.begin_object_value();
    }
};

template <typename CharT, std::size_t N>
template <typename T>
struct basic_encoder<CharT, N>::overloader<
    T,
    typename std::enable_if<std::is_same<T, token::end_object>::value>::type>
{
    using size_type = typename basic_encoder<CharT, N>::size_type;

    inline static size_type write(basic_encoder<CharT, N>& self)
    {
        return self.end_object_value();
    }
};

template <typename CharT, std::size_t N>
template <typename T>
struct basic_encoder<CharT, N>::overloader<
    T,
    typename std::enable_if<std::is_same<T, token::detail::value_separator>::value>::type>
{
    using size_type = typename basic_encoder<CharT, N>::size_type;

    static size_type write(basic_encoder<CharT, N>& self)
    {
        return self.value_separator_value();
    }
};

template <typename CharT, std::size_t N>
template <typename T>
struct basic_encoder<CharT, N>::overloader<
    T,
    typename std::enable_if<std::is_same<T, token::detail::name_separator>::value>::type>
{
    using size_type = typename basic_encoder<CharT, N>::size_type;

    static size_type write(basic_encoder<CharT, N>& self)
    {
        return self.name_separator_value();
    }
};

// Integers

template <typename CharT, std::size_t N>
template <typename T>
struct basic_encoder<CharT, N>::overloader<
    T,
    typename std::enable_if<std::is_integral<T>::value>::type>
{
    using size_type = typename basic_encoder<CharT, N>::size_type;

    inline static size_type write(basic_encoder<CharT, N>& self,
                                  const T& data)
    {
        return self.integral_value(data);
    }
};

// Floating point numbers

template <typename CharT, std::size_t N>
template <typename T>
struct basic_encoder<CharT, N>::overloader<
    T,
    typename std::enable_if<std::is_floating_point<T>::value>::type>
{
    using size_type = typename basic_encoder<CharT, N>::size_type;

    inline static size_type write(basic_encoder<CharT, N>& self,
                                  const T& data)
    {
        return self.floating_value(data);
    }
};

// Strings

template <typename CharT, std::size_t N>
template <typename T>
struct basic_encoder<CharT, N>::overloader<
    T,
    typename std::enable_if<std::is_same<T, typename basic_encoder<CharT, N>::view_type>::value>::type>
{
    using size_type = typename basic_encoder<CharT, N>::size_type;
    using view_type = typename basic_encoder<CharT, N>::view_type;

    static size_type write(basic_encoder<CharT, N>& self,
                           const view_type& data)
    {
        return self.string_value(data);
    }
};

template <typename CharT, std::size_t N>
template <typename T>
struct basic_encoder<CharT, N>::overloader<
    T,
    typename std::enable_if<std::is_same<T, std::basic_string<CharT> >::value>::type>
{
    using size_type = typename basic_encoder<CharT, N>::size_type;

    static size_type write(basic_encoder<CharT, N>& self,
                           const std::basic_string<CharT>& data)
    {
        return self.string_value(data);
    }
};

//-----------------------------------------------------------------------------
// basic_encoder<CharT, N>
//-----------------------------------------------------------------------------

template <typename CharT, std::size_t N>
template <typename T>
basic_encoder<CharT, N>::basic_encoder(T& output)
{
    static_assert(N >= sizeof(typename buffer::traits<T>::buffer_type),
                  "N is smaller than buffer_type");

    ::new (std::addressof(storage)) typename buffer::traits<T>::buffer_type(output);
}

template <typename CharT, std::size_t N>
basic_encoder<CharT, N>::~basic_encoder()
{
    buffer().~buffer_type();
}

template <typename CharT, std::size_t N>
template <typename U>
auto basic_encoder<CharT, N>::value(const U& data) -> size_type
{
    return basic_encoder<CharT, N>::overloader<U>::write(*this, data);
}

template <typename CharT, std::size_t N>
auto basic_encoder<CharT, N>::value(bool data) -> size_type
{
    if (data)
    {
        return write(traits<CharT>::true_text());
    }
    else
    {
        return write(traits<CharT>::false_text());
    }
}

template <typename CharT, std::size_t N>
auto basic_encoder<CharT, N>::value(const value_type *data) -> size_type
{
    return basic_encoder<CharT, N>::overloader<view_type>::write(*this, data);
}

template <typename CharT, std::size_t N>
template <typename U>
auto basic_encoder<CharT, N>::value() -> size_type
{
    return basic_encoder<CharT, N>::overloader<U>::write(*this);
}

template <typename CharT, std::size_t N>
auto basic_encoder<CharT, N>::literal(const view_type& data) -> size_type
{
    return write(data);
}

template <typename CharT, std::size_t N>
template <typename T>
auto basic_encoder<CharT, N>::integral_value(const T& data) -> size_type
{
    std::array<value_type, std::numeric_limits<T>::digits10 + 1> output;

    // Build buffer backwards
    typename decltype(output)::reverse_iterator where = output.rbegin();
    const bool is_negative = data < 0;
    using unsigned_type = typename std::make_unsigned<T>::type;
    auto number = unsigned_type(detail::absolute<T>::value(data));
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
    typename decltype(output)::const_iterator begin = where.base();
    const size_type size = size_type(std::distance(begin, output.cend()) + (is_negative ? 1 : 0));

    if (!buffer().grow(size))
    {
        return 0;
    }
    if (is_negative)
    {
        buffer().write(traits<CharT>::alpha_minus);
    }
    while (begin != output.end())
    {
        buffer().write(*begin);
        ++begin;
    }
    return size;
}

template <typename CharT, std::size_t N>
template <typename T>
auto basic_encoder<CharT, N>::floating_value(const T& data) -> size_type
{
    switch (std::fpclassify(data))
    {
    case FP_INFINITE:
    case FP_NAN:
        // Infinity and NaN must be encoded as null
        return write(traits<CharT>::null_text());
    default:
        return write(detail::string_converter<CharT, T>::encode(data));
    }
}

template <typename CharT, std::size_t N>
template <typename T>
auto basic_encoder<CharT, N>::string_value(const T& data) -> size_type
{
    // This is an approximation of the size. Further characters may be
    // added by escaped characters, in which case we grow the buffer
    // per escape character.
    size_type size = sizeof(char) + data.size() + sizeof(char);

    if (!buffer().grow(size))
    {
        return 0;
    }

    buffer().write(traits<CharT>::alpha_quote);
    typename T::const_iterator it = data.begin();
    while (it != data.end())
    {
        switch (*it)
        {
        case traits<CharT>::alpha_quote:
        case traits<CharT>::alpha_reverse_solidus:
        case traits<CharT>::alpha_solidus:
            if (write(traits<CharT>::alpha_reverse_solidus) == 0)
                return 0;
            buffer().write(*it);
            ++size;
            break;

        case traits<CharT>::alpha_backspace:
            if (write(traits<CharT>::alpha_reverse_solidus) == 0)
                return 0;
            buffer().write(traits<CharT>::alpha_b);
            ++size;
            break;

        case traits<CharT>::alpha_formfeed:
            if (write(traits<CharT>::alpha_reverse_solidus) == 0)
                return 0;
            buffer().write(traits<CharT>::alpha_f);
            ++size;
            break;

        case traits<CharT>::alpha_newline:
            if (write(traits<CharT>::alpha_reverse_solidus) == 0)
                return 0;
            buffer().write(traits<CharT>::alpha_n);
            ++size;
            break;

        case traits<CharT>::alpha_return:
            if (write(traits<CharT>::alpha_reverse_solidus) == 0)
                return 0;
            buffer().write(traits<CharT>::alpha_r);
            ++size;
            break;

        case traits<CharT>::alpha_tab:
            if (write(traits<CharT>::alpha_reverse_solidus) == 0)
                return 0;
            buffer().write(traits<CharT>::alpha_t);
            ++size;
            break;

        default:
            // Replace illegal UTF-8 sequences with question mark

            // The Unicode Standard, Version 7.0 - Core Specification, Table 3-6.

            if ((*it & 0x80) == 0x00)
            {
                // 0xxxxxxx
                buffer().write(*it);
                break;
            }
            else if ((*it & 0xE0) == 0xC0)
            {
                // 110xxxxx
                typename T::value_type first = *it;
                if (++it == data.end())
                {
                    if (write(traits<CharT>::alpha_question_mark) == 0)
                        return 0;
                    continue;
                }
                if ((*it & 0xC0) == 0x80)
                {
                    // 110xxxxx 10xxxxxx
                    buffer().write(first);
                    buffer().write(*it);
                    break;
                 }
            }
            else if ((*it & 0xF0) == 0xE0)
            {
                // 1110xxxx
                typename T::value_type first = *it;
                if (++it == data.end())
                {
                    if (write(traits<CharT>::alpha_question_mark) == 0)
                        return 0;
                    continue;
                }
                if ((*it & 0xC0) == 0x80)
                {
                    // 1110xxxx 10xxxxxx
                    typename T::value_type second = *it;
                    if (++it == data.end())
                    {
                        if (write(traits<CharT>::alpha_question_mark) == 0)
                            return 0;
                        continue;
                    }
                    if ((*it & 0xC0) == 0x80)
                    {
                        // 1110xxxx 10xxxxxx 10xxxxxx
                        buffer().write(first);
                        buffer().write(second);
                        buffer().write(*it);
                        break;
                    }
                }
            }
            if (write(traits<CharT>::alpha_question_mark) == 0)
                return 0;
            break;
        }
        ++it;
    }
    buffer().write(traits<CharT>::alpha_quote);

    return size;
}

template <typename CharT, std::size_t N>
auto basic_encoder<CharT, N>::null_value() -> size_type
{
    return write(traits<CharT>::null_text());
}

template <typename CharT, std::size_t N>
auto basic_encoder<CharT, N>::begin_array_value() -> size_type
{
    return write(traits<CharT>::alpha_bracket_open);
}

template <typename CharT, std::size_t N>
auto basic_encoder<CharT, N>::end_array_value() -> size_type
{
    return write(traits<CharT>::alpha_bracket_close);
}

template <typename CharT, std::size_t N>
auto basic_encoder<CharT, N>::begin_object_value() -> size_type
{
    return write(traits<CharT>::alpha_brace_open);
}

template <typename CharT, std::size_t N>
auto basic_encoder<CharT, N>::end_object_value() -> size_type
{
    return write(traits<CharT>::alpha_brace_close);
}

template <typename CharT, std::size_t N>
auto basic_encoder<CharT, N>::value_separator_value() -> size_type
{
    return write(traits<CharT>::alpha_comma);
}

template <typename CharT, std::size_t N>
auto basic_encoder<CharT, N>::name_separator_value() -> size_type
{
    return write(traits<CharT>::alpha_colon);
}

template <typename CharT, std::size_t N>
auto basic_encoder<CharT, N>::write(value_type character) -> size_type
{
    const size_type size = sizeof(character);
    if (buffer().grow(size))
    {
        buffer().write(character);
        return size;
    }
    return 0;
}

template <typename CharT, std::size_t N>
auto basic_encoder<CharT, N>::write(const view_type& data) -> size_type
{
    const typename view_type::size_type size = data.size();
    if (buffer().grow(size))
    {
        buffer().write(data);
        return size;
    }
    return 0;
}

template <typename CharT, std::size_t N>
auto basic_encoder<CharT, N>::write(const string_type& data) -> size_type
{
    const typename view_type::size_type size = data.size();
    if (buffer().grow(size))
    {
        buffer().write(data);
        return size;
    }
    return 0;
}

template <typename CharT, std::size_t N>
auto basic_encoder<CharT, N>::buffer() -> buffer_type&
{
    return reinterpret_cast<buffer_type&>(storage);
}

template <typename CharT, std::size_t N>
auto basic_encoder<CharT, N>::buffer() const -> const buffer_type&
{
    return reinterpret_cast<const buffer_type&>(storage);
}

} // namespace detail
} // namespace json
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_JSON_DETAIL_ENCODER_IPP
