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
#include <cstring> // std::memcmp
#include <cstdlib> // std::atof
#include <iterator>
#include <limits>
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
// basic_decoder_functor
//-----------------------------------------------------------------------------

template <typename CharT, typename ReturnType, typename Enable = void>
struct basic_decoder_functor
{
    static ReturnType convert(const basic_decoder<CharT>&);
};

template <typename CharT, typename ReturnType>
struct basic_decoder_functor<CharT,
                             ReturnType,
                             typename boost::enable_if< boost::is_integral<ReturnType> >::type>
{
    static ReturnType convert(const basic_decoder<CharT>& self)
    {
        if (self.token() != token::integer)
        {
            self.current.token = token::error_incompatible_type;
            throw json::error(self.error());
        }

        typename basic_decoder<CharT>::view_type::const_iterator it = self.literal().begin();

        const bool is_negative = (*it == traits<CharT>::alpha_minus);
        if (is_negative)
        {
            if (boost::is_unsigned<ReturnType>::value)
            {
                self.current.token = token::error_invalid_value;
                throw json::error(self.error());
            }
            ++it;
        }
        ReturnType result = ReturnType();
        while (it != self.literal().end())
        {
            const ReturnType old = result;
            result *= ReturnType(10);
            result += traits<CharT>::to_int(*it);
            if (result < old)
            {
                // Overflow
                self.current.token = token::error_invalid_value;
                throw json::error(self.error());
            }
            ++it;
        }
        return is_negative ? -result : result;
    }
};

template <typename ReturnType>
struct basic_decoder_functor<char,
                             ReturnType,
                             typename boost::enable_if< boost::is_floating_point<ReturnType> >::type>
{
    static ReturnType convert(const basic_decoder<char>& self)
    {
        if (self.token() != token::floating)
        {
            self.current.token = token::error_incompatible_type;
            throw json::error(self.error());
        }

        return std::atof(self.literal().data());
    }
};

template <typename ReturnType>
struct basic_decoder_functor<char,
                             ReturnType,
                             typename boost::enable_if< boost::is_same<ReturnType, std::string> >::type>
{
    typedef typename basic_decoder<char>::view_type view_type;
    // FIXME: Validate string [ http://www.w3.org/International/questions/qa-forms-utf-8 ]
    static ReturnType convert(const basic_decoder<char>& self)
    {
        if (self.token() != token::string)
        {
            self.current.token = token::error_incompatible_type;
            throw json::error(self.error());
        }

        const typename view_type::size_type  approximateSize = self.literal().size();
        assert(approximateSize >= 2);

        std::string result;
        result.reserve(approximateSize);

        typename view_type::const_iterator begin = self.literal().begin();
        typename view_type::const_iterator end = self.literal().end();
        for (typename view_type::const_iterator it = begin;
             it != end;
             ++it)
        {
            if (*it == traits<char>::alpha_reverse_solidus)
            {
                assert(std::distance(it, end) >= 2);
                ++it;
                switch (*it)
                {
                case traits<char>::alpha_quote:
                case traits<char>::alpha_reverse_solidus:
                case traits<char>::alpha_solidus:
                    result += *it;
                    break;

                case traits<char>::alpha_b:
                    result += traits<char>::alpha_backspace;
                    break;

                case traits<char>::alpha_f:
                    result += traits<char>::alpha_formfeed;
                    break;

                case traits<char>::alpha_n:
                    result += traits<char>::alpha_newline;
                    break;

                case traits<char>::alpha_r:
                    result += traits<char>::alpha_return;
                    break;

                case traits<char>::alpha_t:
                    result += traits<char>::alpha_tab;
                    break;

                case traits<char>::alpha_u:
                    {
                        // Convert \uXXXX value to UTF-8
                        assert(std::distance(it, end) >= 5);
                        boost::uint32_t number = 0;
                        for (int i = 0; i < 4; ++i)
                        {
                            ++it;
                            number <<= 4;
                            if (traits<char>::is_hexdigit(*it))
                            {
                                number += traits<char>::to_int(*it);
                            }
                        }
                        if (number <= 0x007F)
                        {
                            // 0xxxxxxx
                            result += std::char_traits<char>::to_char_type(number & 0x7F);
                        }
                        else if (number <= 0x07FF)
                        {
                            // 110xxxxx 10xxxxxx
                            result += 0xC0 | std::char_traits<char>::to_char_type((number >> 6) & 0x1F);
                            result += 0x80 | std::char_traits<char>::to_char_type(number & 0x3F);
                        }
                        else
                        {
                            // 1110xxxx 10xxxxxx 10xxxxxx
                            result += 0xE0 | std::char_traits<char>::to_char_type((number >> 12) & 0x0F);
                            result += 0x80 | std::char_traits<char>::to_char_type((number >> 6) & 0x3F);
                            result += 0x80 | std::char_traits<char>::to_char_type(number & 0x3F);
                        }
                    }
                    break;

                default:
                    assert(false);
                    break;
                }
            }
            else if (*it == traits<char>::alpha_quote)
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
};

//-----------------------------------------------------------------------------
// basic_decoder
//-----------------------------------------------------------------------------

template <typename CharT>
basic_decoder<CharT>::basic_decoder(const view_type& input)
    : input(input)
{
    current.token = token::end;
    next();
}

template <typename CharT>
void basic_decoder<CharT>::token(json::token::value value) BOOST_NOEXCEPT
{
    current.token = value;
}

template <typename CharT>
token::value basic_decoder<CharT>::token() const BOOST_NOEXCEPT
{
    return current.token;
}

template <typename CharT>
type::value basic_decoder<CharT>::type() const BOOST_NOEXCEPT
{
    return type::convert(current.token);
}

template <typename CharT>
category::value basic_decoder<CharT>::category() const BOOST_NOEXCEPT
{
    return category::convert(current.token);
}

template <typename CharT>
boost::system::error_code basic_decoder<CharT>::error() const BOOST_NOEXCEPT
{
    switch (token())
    {
    case token::error_not_implemented:
        return json::make_error_code(not_implemented);

    case token::error_unexpected_token:
        return json::make_error_code(unexpected_token);

    case token::error_invalid_key:
        return json::make_error_code(invalid_key);

    case token::error_invalid_value:
        return json::make_error_code(invalid_value);

    case token::error_incompatible_type:
        return json::make_error_code(incompatible_type);

    case token::error_unbalanced_end_array:
        return json::make_error_code(unbalanced_end_array);

    case token::error_unbalanced_end_object:
        return json::make_error_code(unbalanced_end_object);

    case token::error_expected_end_array:
        return json::make_error_code(expected_end_array);

    case token::error_expected_end_object:
        return json::make_error_code(expected_end_object);

    default:
        return json::make_error_code(no_error);
    }
}

template <typename CharT>
void basic_decoder<CharT>::next() BOOST_NOEXCEPT
{
    if (type() == json::type::error)
    {
        return;
    }

    skip_whitespaces();

    if (input.empty())
    {
        current.token = token::end;
        return;
    }

    switch (input.front())
    {
    case traits<CharT>::alpha_f:
        current.token = next_f_keyword();
        break;

    case traits<CharT>::alpha_n:
        current.token = next_n_keyword();
        break;

    case traits<CharT>::alpha_t:
        current.token = next_t_keyword();
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
        current.token = next_number();
        break;

    case traits<CharT>::alpha_quote:
        current.token = next_string();
        break;

    case traits<CharT>::alpha_brace_open:
        current.token = next_token(token::begin_object);
        break;

    case traits<CharT>::alpha_brace_close:
        current.token = next_token(token::end_object);
        break;

    case traits<CharT>::alpha_bracket_open:
        current.token = next_token(token::begin_array);
        break;

    case traits<CharT>::alpha_bracket_close:
        current.token = next_token(token::end_array);
        break;

    case traits<CharT>::alpha_comma:
        current.token = next_token(token::value_separator);
        break;

    case traits<CharT>::alpha_colon:
        current.token = next_token(token::name_separator);
        break;

    default:
        current.token = token::error_unexpected_token;
        break;
    }
}

template <typename CharT>
template <typename ReturnType>
ReturnType basic_decoder<CharT>::value() const
{
    return basic_decoder_functor<CharT, ReturnType>::convert(*this);
}

template <typename CharT>
inline const typename basic_decoder<CharT>::view_type&
basic_decoder<CharT>::literal() const BOOST_NOEXCEPT
{
    return current.view;
}

template <typename CharT>
token::value basic_decoder<CharT>::next_token(token::value type) BOOST_NOEXCEPT
{
    current.view = view_type(input.begin(), 1);
    input.remove_prefix(1);
    return type;
}

template <typename CharT>
token::value basic_decoder<CharT>::next_f_keyword() BOOST_NOEXCEPT
{
    token::value type = token::false_value;
    typename view_type::const_iterator begin = input.begin();

    const std::size_t size = traits<CharT>::false_text().size();
    if (input.size() < size)
    {
        input.remove_prefix(input.size());
        type = token::end;
        goto end;
    }
    if (traits<CharT>::false_text().compare(0, size, begin, size) != 0)
    {
        type = token::error_unexpected_token;
        goto end;
    }
    input.remove_prefix(size);
    if (!at_keyword_end())
    {
        while (!at_keyword_end())
            input.remove_prefix(1);
        type = token::error_unexpected_token;
    }

 end:
    current.view = view_type(begin, std::distance(begin, input.begin()));
    return type;
}

template <typename CharT>
token::value basic_decoder<CharT>::next_n_keyword() BOOST_NOEXCEPT
{
    token::value type = token::null;
    typename view_type::const_iterator begin = input.begin();

    const std::size_t size = traits<CharT>::null_text().size();
    if (input.size() < size)
    {
        input.remove_prefix(input.size());
        type = token::end;
        goto end;
    }
    if (traits<CharT>::null_text().compare(0, size, begin, size) != 0)
    {
        type = token::error_unexpected_token;
        goto end;
    }
    input.remove_prefix(size);
    if (!at_keyword_end())
    {
        while (!at_keyword_end())
            input.remove_prefix(1);
        type = token::error_unexpected_token;
    }

 end:
    current.view = view_type(begin, std::distance(begin, input.begin()));
    return type;
}

template <typename CharT>
token::value basic_decoder<CharT>::next_t_keyword() BOOST_NOEXCEPT
{
    token::value type = token::true_value;
    typename view_type::const_iterator begin = input.begin();

    const std::size_t size = traits<CharT>::true_text().size();
    if (input.size() < size)
    {
        input.remove_prefix(input.size());
        type = token::end;
        goto end;
    }
    if (traits<CharT>::true_text().compare(0, size, begin, size) != 0)
    {
        type = token::error_unexpected_token;
        goto end;
    }
    input.remove_prefix(size);
    if (!at_keyword_end())
    {
        while (!at_keyword_end())
            input.remove_prefix(1);
        type = token::error_unexpected_token;
    }

 end:
    current.view = view_type(begin, std::distance(begin, input.begin()));
    return type;
}

template <typename CharT>
token::value basic_decoder<CharT>::next_number() BOOST_NOEXCEPT
{
    typename view_type::const_iterator begin = input.begin();
    token::value type = token::integer;

    const bool is_negative = (*begin == traits<CharT>::alpha_minus);
    if (is_negative)
    {
        input.remove_prefix(1); // Skip '-'
        if (input.empty())
        {
            type = token::end;
            goto end;
        }
    }

    {
        typename view_type::const_iterator digit_begin = input.begin();
        while (!input.empty() && traits<CharT>::is_digit(input.front()))
        {
            input.remove_prefix(1);
        }
        if (input.begin() == digit_begin)
        {
            // No digits found
            type = token::error_unexpected_token;
            goto end;
        }
        if (!input.empty())
        {
            if (input.front() == traits<CharT>::alpha_dot)
            {
                type = token::floating;
                input.remove_prefix(1);
                if (input.empty())
                {
                    type = token::end;
                    goto end;
                }
                typename view_type::const_iterator fraction_begin = input.begin();
                while (!input.empty() && traits<CharT>::is_digit(input.front()))
                {
                    input.remove_prefix(1);
                }
                if (input.begin() == fraction_begin)
                {
                    type = token::error_unexpected_token;
                    goto end;
                }
            }
            if (!input.empty() && ((input.front() == traits<CharT>::alpha_E) ||
                                   (input.front() == traits<CharT>::alpha_e)))
            {
                type = token::floating;
                input.remove_prefix(1);
                if (input.empty())
                {
                    type = token::end;
                    goto end;
                }

                if (input.front() == traits<CharT>::alpha_plus)
                {
                    input.remove_prefix(1);
                    if (input.empty())
                    {
                        type = token::end;
                        goto end;
                    }
                }
                else if (input.front() == traits<CharT>::alpha_minus)
                {
                    input.remove_prefix(1);
                    if (input.empty())
                    {
                        type = token::end;
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
                    type = token::error_unexpected_token;
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
token::value basic_decoder<CharT>::next_string() BOOST_NOEXCEPT
{
    assert(input.front() == traits<CharT>::alpha_quote);

    typename view_type::const_iterator marker = input.begin();
    typename view_type::const_iterator end = input.end();
    ++marker; // Skip initial '"'
    while (marker != end)
    {
        const typename view_type::size_type amount = traits<CharT>::extra_bytes(*marker);

        if (amount > 0)
        {
            // Skip UTF-8 characters
            if (amount >= std::distance(marker, end))
                goto error;

            ++marker;

            for (typename view_type::size_type i = 0; i < amount; ++i)
            {
                // Check for 10xxxxxx pattern of subsequent bytes
                if ((*marker & 0xC0) != 0x80)
                    goto error;
                ++marker;
            }
        }
        else
        {
            const value_type character = *marker++;
            if (character == traits<CharT>::alpha_reverse_solidus)
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
            else if (character == traits<CharT>::alpha_quote)
            {
                // Handle end of string
                current.view = view_type(input.begin(), std::distance(input.begin(), marker)); // Includes terminating '"'
                input.remove_prefix(std::distance(input.begin(), marker));
                return token::string;
            }
        }
    }
 eof:
    current.view = view_type(input.begin(), std::distance(input.begin(), marker));
    return token::end;

 error:
    current.view = view_type(input.begin(), std::distance(input.begin(), marker));
    return token::error_unexpected_token;
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
