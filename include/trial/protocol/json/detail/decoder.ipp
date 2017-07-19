#ifndef TRIAL_PROTOCOL_JSON_DETAIL_DECODER_IPP
#define TRIAL_PROTOCOL_JSON_DETAIL_DECODER_IPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2015 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <cstdlib> // std::atof
#include <iterator>
#include <limits>
#include <type_traits>
#include <trial/protocol/json/detail/string_converter.hpp>
#include <trial/protocol/json/detail/decoder.hpp>
#include <trial/protocol/json/detail/traits.hpp>
#include <trial/protocol/json/error.hpp>

// http://tools.ietf.org/html/rfc7159

//-----------------------------------------------------------------------------

namespace trial
{
namespace protocol
{
namespace json
{
namespace detail
{

//-----------------------------------------------------------------------------
// decoder::overloader
//-----------------------------------------------------------------------------

template <typename CharT>
template <typename ReturnType, typename Enable>
struct basic_decoder<CharT>::overloader
{
};

// Integers

template <typename CharT>
template <typename ReturnType>
struct basic_decoder<CharT>::overloader<ReturnType,
                                        typename std::enable_if<std::is_integral<ReturnType>::value>::type>
{
    inline static ReturnType value(const basic_decoder<CharT>& self)
    {
        return self.template integer_value<ReturnType>();
    }
};

// Floating-point numbers

template <typename CharT>
template <typename ReturnType>
struct basic_decoder<CharT>::overloader<ReturnType,
                                        typename std::enable_if<std::is_floating_point<ReturnType>::value>::type>
{
    inline static ReturnType value(const basic_decoder<CharT>& self)
    {
        return self.template number_value<ReturnType>();
    }
};

// Strings

template <typename CharT>
template <typename ReturnType>
struct basic_decoder<CharT>::overloader<ReturnType,
                                        typename std::enable_if<std::is_same<ReturnType, std::basic_string<CharT> >::value>::type>
{
    inline static std::string value(const basic_decoder<CharT>& self)
    {
        return self.string_value();
    }
};

//-----------------------------------------------------------------------------
// basic_decoder
//-----------------------------------------------------------------------------

template <typename CharT>
basic_decoder<CharT>::basic_decoder(const view_type& view)
    : input(view)
{
    current.code = token::detail::code::value::end;
    next();
}

template <typename CharT>
void basic_decoder<CharT>::code(token::detail::code::value code) BOOST_NOEXCEPT
{
    current.code = code;
}

template <typename CharT>
token::detail::code::value basic_decoder<CharT>::code() const BOOST_NOEXCEPT
{
    return current.code;
}

template <typename CharT>
std::error_code basic_decoder<CharT>::error() const BOOST_NOEXCEPT
{
    return json::make_error_code(to_errc(token::detail::convert(code())));
}

template <typename CharT>
void basic_decoder<CharT>::next() BOOST_NOEXCEPT
{
    switch (current.code)
    {
    case token::detail::code::error_unexpected_token:
    case token::detail::code::error_invalid_key:
    case token::detail::code::error_invalid_value:
    case token::detail::code::error_incompatible_type:
    case token::detail::code::error_unbalanced_end_array:
    case token::detail::code::error_unbalanced_end_object:
    case token::detail::code::error_expected_end_array:
    case token::detail::code::error_expected_end_object:
        return;
    default:
        break;
    }

    skip_whitespaces();

    if (input.empty())
    {
        current.code = token::detail::code::value::end;
        return;
    }

    switch (input.front())
    {
    case traits<CharT>::alpha_f:
        current.code = next_f_keyword();
        break;

    case traits<CharT>::alpha_n:
        current.code = next_n_keyword();
        break;

    case traits<CharT>::alpha_t:
        current.code = next_t_keyword();
        break;

    case traits<CharT>::alpha_minus:
    case traits<CharT>::alpha_0:
    case traits<CharT>::alpha_1:
    case traits<CharT>::alpha_2:
    case traits<CharT>::alpha_3:
    case traits<CharT>::alpha_4:
    case traits<CharT>::alpha_5:
    case traits<CharT>::alpha_6:
    case traits<CharT>::alpha_7:
    case traits<CharT>::alpha_8:
    case traits<CharT>::alpha_9:
        current.code = next_number();
        break;

    case traits<CharT>::alpha_quote:
        current.code = next_string();
        break;

    case traits<CharT>::alpha_brace_open:
        current.code = next_token(token::detail::code::begin_object);
        break;

    case traits<CharT>::alpha_brace_close:
        current.code = next_token(token::detail::code::end_object);
        break;

    case traits<CharT>::alpha_bracket_open:
        current.code = next_token(token::detail::code::begin_array);
        break;

    case traits<CharT>::alpha_bracket_close:
        current.code = next_token(token::detail::code::end_array);
        break;

    case traits<CharT>::alpha_comma:
        current.code = next_token(token::detail::code::value_separator);
        break;

    case traits<CharT>::alpha_colon:
        current.code = next_token(token::detail::code::name_separator);
        break;

    default:
        current.code = token::detail::code::error_unexpected_token;
        break;
    }
}

template <typename CharT>
template <typename ReturnType>
ReturnType basic_decoder<CharT>::value() const
{
    return basic_decoder<CharT>::overloader<ReturnType>::value(*this);
}

template <typename CharT>
template <typename ReturnType>
ReturnType basic_decoder<CharT>::integer_value() const
{
    if (current.code != token::detail::code::integer)
    {
        current.code = token::detail::code::error_incompatible_type;
        throw json::error(error());
    }

    typename view_type::const_iterator it = literal().begin();

    const bool is_negative = (*it == traits<CharT>::alpha_minus);
    if (is_negative)
    {
        if (std::is_unsigned<ReturnType>::value)
        {
            current.code = token::detail::code::error_invalid_value;
            throw json::error(error());
        }
        ++it;
    }
    ReturnType result = ReturnType();
    const ReturnType max = std::numeric_limits<ReturnType>::max();
    while (it != literal().end())
    {
        if (max / ReturnType(10) < result) {
            // Overflow
            current.code = token::detail::code::error_invalid_value;
            throw json::error(error());
        }
        result *= ReturnType(10);

        const ReturnType digit = ReturnType(traits<CharT>::to_int(*it));
        if (max - digit < result) {
            // Overflow
            current.code = token::detail::code::error_invalid_value;
            throw json::error(error());
        }
        result += digit;

        ++it;
    }
    return is_negative ? -result : result;
}

template <typename CharT>
template <typename ReturnType>
ReturnType basic_decoder<CharT>::number_value() const
{
    if (current.code != token::detail::code::number)
    {
        current.code = token::detail::code::error_incompatible_type;
        throw json::error(error());
    }
    
    return string_converter<CharT, ReturnType>::decode(current.view);
}

template <typename CharT>
std::basic_string<CharT> basic_decoder<CharT>::string_value() const
{
    // FIXME: Validate string [ http://www.w3.org/International/questions/qa-forms-utf-8 ]
    if (current.code != token::detail::code::string)
    {
        current.code = token::detail::code::error_incompatible_type;
        throw json::error(error());
    }

    const typename view_type::size_type  approximateSize = literal().size();
    assert(approximateSize >= 2);

    std::basic_string<CharT> result;
    result.reserve(approximateSize);

    typename view_type::const_iterator begin = literal().begin();
    typename view_type::const_iterator end = literal().end();
    for (typename view_type::const_iterator it = begin;
         it != end;
         ++it)
    {
        if (*it == traits<CharT>::alpha_reverse_solidus)
        {
            assert(std::distance(it, end) >= 2);
            ++it;
            switch (*it)
            {
            case traits<CharT>::alpha_quote:
            case traits<CharT>::alpha_reverse_solidus:
            case traits<CharT>::alpha_solidus:
                result += *it;
                break;

            case traits<CharT>::alpha_b:
                result += traits<CharT>::alpha_backspace;
                break;

            case traits<CharT>::alpha_f:
                result += traits<CharT>::alpha_formfeed;
                break;

            case traits<CharT>::alpha_n:
                result += traits<CharT>::alpha_newline;
                break;

            case traits<CharT>::alpha_r:
                result += traits<CharT>::alpha_return;
                break;

            case traits<CharT>::alpha_t:
                result += traits<CharT>::alpha_tab;
                break;

            case traits<CharT>::alpha_u:
                {
                    // Convert \uXXXX value to UTF-8
                    assert(std::distance(it, end) >= 5);
                    std::uint32_t number = 0;
                    for (int i = 0; i < 4; ++i)
                    {
                        ++it;
                        number <<= 4;
                        if (traits<CharT>::is_hexdigit(*it))
                        {
                            number += std::uint32_t(traits<CharT>::to_int(*it));
                        }
                    }
                    if (number <= 0x007F)
                    {
                        // 0xxxxxxx
                        result += std::char_traits<CharT>::to_char_type(number & 0x7F);
                    }
                    else if (number <= 0x07FF)
                    {
                        // 110xxxxx 10xxxxxx
                        result += 0xC0 | std::char_traits<CharT>::to_char_type((number >> 6) & 0x1F);
                        result += 0x80 | std::char_traits<CharT>::to_char_type(number & 0x3F);
                    }
                    else
                    {
                        // 1110xxxx 10xxxxxx 10xxxxxx
                        result += 0xE0 | std::char_traits<CharT>::to_char_type((number >> 12) & 0x0F);
                        result += 0x80 | std::char_traits<CharT>::to_char_type((number >> 6) & 0x3F);
                        result += 0x80 | std::char_traits<CharT>::to_char_type(number & 0x3F);
                    }
                }
                break;

            default:
                assert(false);
                break;
            }
        }
        else if (*it == traits<CharT>::alpha_quote)
        {
            assert((it == begin) || (it + 1 == end));
            // Ignore initial and terminating quotes
        }
        else
        {
            result += *it;
        }
    }
    return result;
}

template <typename CharT>
auto basic_decoder<CharT>::literal() const BOOST_NOEXCEPT -> const view_type&
{
    return current.view;
}

template <typename CharT>
auto basic_decoder<CharT>::tail() const BOOST_NOEXCEPT -> const view_type&
{
    return input;
}

template <typename CharT>
token::detail::code::value basic_decoder<CharT>::next_token(token::detail::code::value type) BOOST_NOEXCEPT
{
    current.view = view_type(input.begin(), 1);
    input.remove_prefix(1);
    return type;
}

template <typename CharT>
token::detail::code::value basic_decoder<CharT>::next_f_keyword() BOOST_NOEXCEPT
{
    token::detail::code::value type = token::detail::code::false_value;
    typename view_type::const_iterator begin = input.begin();

    const std::size_t size = traits<CharT>::false_text().size();
    if (input.size() < size)
    {
        type = token::detail::code::error_unexpected_token;
        goto end;
    }
    if (traits<CharT>::false_text().compare(0, size, begin, size) != 0)
    {
        type = token::detail::code::error_unexpected_token;
        goto end;
    }
    input.remove_prefix(size);
    if (!at_keyword_end())
    {
        while (!at_keyword_end())
            input.remove_prefix(1);
        type = token::detail::code::error_unexpected_token;
    }

 end:
    current.view = view_type(begin, std::distance(begin, input.begin()));
    return type;
}

template <typename CharT>
token::detail::code::value basic_decoder<CharT>::next_n_keyword() BOOST_NOEXCEPT
{
    token::detail::code::value type = token::detail::code::null;
    typename view_type::const_iterator begin = input.begin();

    const std::size_t size = traits<CharT>::null_text().size();
    if (input.size() < size)
    {
        type = token::detail::code::error_unexpected_token;
        goto end;
    }
    if (traits<CharT>::null_text().compare(0, size, begin, size) != 0)
    {
        type = token::detail::code::error_unexpected_token;
        goto end;
    }
    input.remove_prefix(size);
    if (!at_keyword_end())
    {
        while (!at_keyword_end())
            input.remove_prefix(1);
        type = token::detail::code::error_unexpected_token;
    }

 end:
    current.view = view_type(begin, std::distance(begin, input.begin()));
    return type;
}

template <typename CharT>
token::detail::code::value basic_decoder<CharT>::next_t_keyword() BOOST_NOEXCEPT
{
    token::detail::code::value type = token::detail::code::true_value;
    typename view_type::const_iterator begin = input.begin();

    const std::size_t size = traits<CharT>::true_text().size();
    if (input.size() < size)
    {
        type = token::detail::code::error_unexpected_token;
        goto end;
    }
    if (traits<CharT>::true_text().compare(0, size, begin, size) != 0)
    {
        type = token::detail::code::error_unexpected_token;
        goto end;
    }
    input.remove_prefix(size);
    if (!at_keyword_end())
    {
        while (!at_keyword_end())
            input.remove_prefix(1);
        type = token::detail::code::error_unexpected_token;
    }

 end:
    current.view = view_type(begin, std::distance(begin, input.begin()));
    return type;
}

template <typename CharT>
token::detail::code::value basic_decoder<CharT>::next_number() BOOST_NOEXCEPT
{
    typename view_type::const_iterator begin = input.begin();
    token::detail::code::value type = token::detail::code::integer;

    const bool is_negative = (*begin == traits<CharT>::alpha_minus);
    if (is_negative)
    {
        input.remove_prefix(1); // Skip '-'
        if (input.empty())
        {
            type = token::detail::code::end;
            goto end;
        }
    }

    {
        typename view_type::const_iterator digit_begin = input.begin();
        if (input.front() == traits<CharT>::alpha_0)
        {
            input.remove_prefix(1);
            if (!input.empty() && traits<CharT>::is_digit(input.front()))
            {
                // Leading zeros not allowed
                type = token::detail::code::error_invalid_value;
                goto end;
            }
        }
        else
        {
            while (!input.empty() && traits<CharT>::is_digit(input.front()))
            {
                input.remove_prefix(1);
            }
        }
        if (input.begin() == digit_begin)
        {
            // No digits found
            type = token::detail::code::error_unexpected_token;
            goto end;
        }
        if (!input.empty())
        {
            if (input.front() == traits<CharT>::alpha_dot)
            {
                type = token::detail::code::number;
                input.remove_prefix(1);
                if (input.empty())
                {
                    type = token::detail::code::end;
                    goto end;
                }
                typename view_type::const_iterator fraction_begin = input.begin();
                while (!input.empty() && traits<CharT>::is_digit(input.front()))
                {
                    input.remove_prefix(1);
                }
                if (input.begin() == fraction_begin)
                {
                    type = token::detail::code::error_unexpected_token;
                    goto end;
                }
            }
            if (!input.empty() && ((input.front() == traits<CharT>::alpha_E) ||
                                   (input.front() == traits<CharT>::alpha_e)))
            {
                type = token::detail::code::number;
                input.remove_prefix(1);
                if (input.empty())
                {
                    type = token::detail::code::end;
                    goto end;
                }

                if (input.front() == traits<CharT>::alpha_plus)
                {
                    input.remove_prefix(1);
                    if (input.empty())
                    {
                        type = token::detail::code::end;
                        goto end;
                    }
                }
                else if (input.front() == traits<CharT>::alpha_minus)
                {
                    input.remove_prefix(1);
                    if (input.empty())
                    {
                        type = token::detail::code::end;
                        goto end;
                    }
                }
                typename view_type::const_iterator exponent_begin = input.begin();
                while (!input.empty() && traits<CharT>::is_digit(input.front()))
                {
                    input.remove_prefix(1);
                }
                if (input.begin() == exponent_begin)
                {
                    type = token::detail::code::error_unexpected_token;
                    goto end;
                }
            }
        }
    }
 end:
    std::size_t size = std::distance(begin, input.begin());
    current.view = view_type(begin, size);
    return type;
}

template <typename CharT>
token::detail::code::value basic_decoder<CharT>::next_string() BOOST_NOEXCEPT
{
    assert(input.front() == traits<CharT>::alpha_quote);

    typename view_type::const_iterator marker = input.begin();
    typename view_type::const_iterator end = input.end();
    ++marker; // Skip initial '"'
    while (marker != end)
    {
        switch (traits<CharT>::to_category(*marker++))
        {
        case traits_category::escape:
            {
                // Handle escaped character
                if (marker == end)
                    goto eof;
                switch (*marker++)
                {
                case traits<CharT>::alpha_quote:
                case traits<CharT>::alpha_reverse_solidus:
                case traits<CharT>::alpha_solidus:
                case traits<CharT>::alpha_b:
                case traits<CharT>::alpha_f:
                case traits<CharT>::alpha_n:
                case traits<CharT>::alpha_r:
                case traits<CharT>::alpha_t:
                    break;

                case traits<CharT>::alpha_u:
                    switch (std::distance(marker, end))
                    {
                    case 0:
                        goto eof;
                    case 1:
                        if (!traits<CharT>::is_hexdigit(*marker))
                            goto error;
                        ++marker;
                        goto eof;
                    case 2:
                        if (!traits<CharT>::is_hexdigit(*marker))
                            goto error;
                        ++marker;
                        if (!traits<CharT>::is_hexdigit(*marker))
                            goto error;
                        ++marker;
                        goto eof;
                    case 3:
                        if (!traits<CharT>::is_hexdigit(*marker))
                            goto error;
                        ++marker;
                        if (!traits<CharT>::is_hexdigit(*marker))
                            goto error;
                        ++marker;
                        if (!traits<CharT>::is_hexdigit(*marker))
                            goto error;
                        ++marker;
                        goto eof;
                    default:
                        if (!traits<CharT>::is_hexdigit(*marker))
                            goto error;
                        ++marker;
                        if (!traits<CharT>::is_hexdigit(*marker))
                            goto error;
                        ++marker;
                        if (!traits<CharT>::is_hexdigit(*marker))
                            goto error;
                        ++marker;
                        if (!traits<CharT>::is_hexdigit(*marker))
                            goto error;
                        ++marker;
                        break;
                    }
                    break;

                default:
                    goto error;
                }
            }
            break;

        case traits_category::quote:
            // Handle end of string
            current.view = view_type(input.begin(), std::distance(input.begin(), marker)); // Includes terminating '"'
            input.remove_prefix(std::distance(input.begin(), marker));
            return token::detail::code::string;

        case traits_category::narrow:
            break;

        case traits_category::extra_5:
            // Skip UTF-8 characters
            // Check for 10xxxxxx pattern of subsequent bytes
            if (marker == end)
                goto error;
            if ((*marker & 0xC0) != 0x80)
                goto error;
            ++marker;
            // FALLTHROUGH
        case traits_category::extra_4:
            if (marker == end)
                goto error;
            if ((*marker & 0xC0) != 0x80)
                goto error;
            ++marker;
            // FALLTHROUGH
        case traits_category::extra_3:
            if (marker == end)
                goto error;
            if ((*marker & 0xC0) != 0x80)
                goto error;
            ++marker;
            // FALLTHROUGH
        case traits_category::extra_2:
            if (marker == end)
                goto error;
            if ((*marker & 0xC0) != 0x80)
                goto error;
            ++marker;
            // FALLTHROUGH
        case traits_category::extra_1:
            if (marker == end)
                goto error;
            if ((*marker & 0xC0) != 0x80)
                goto error;
            ++marker;
            break;

        case traits_category::illegal:
            goto error;
        }
    }
 eof:
    current.view = view_type(input.begin(), std::distance(input.begin(), marker));
    return token::detail::code::end;

 error:
    current.view = view_type(input.begin(), std::distance(input.begin(), marker));
    return token::detail::code::error_unexpected_token;
}

template <typename CharT>
void basic_decoder<CharT>::skip_whitespaces() BOOST_NOEXCEPT
{
    typename view_type::size_type size = typename view_type::size_type();
    typename view_type::const_iterator end = input.end();
    for (typename view_type::const_iterator it = input.begin();
         it != end;
         ++it)
    {
        if (!traits<CharT>::is_space(*it))
            break;
        ++size;
    }
    if (size > 0)
    {
        input.remove_prefix(size);
    }
}

template <typename CharT>
bool basic_decoder<CharT>::at_keyword_end() const BOOST_NOEXCEPT
{
    if (input.empty())
    {
        return true;
    }
    return !traits<CharT>::is_keyword(input.front());
}

} // namespace detail
} // namespace json
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_JSON_DETAIL_DECODER_IPP
