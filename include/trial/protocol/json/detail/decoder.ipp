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
// decoder::type_matcher
//-----------------------------------------------------------------------------

template <typename ReturnType, typename Enable>
struct decoder::type_matcher
{
};

// Integers

template <typename ReturnType>
struct decoder::type_matcher<ReturnType,
                             typename boost::enable_if< boost::is_integral<ReturnType> >::type>
{
    static ReturnType convert(decoder& self)
    {
        if (self.code() != token::code::integer)
        {
            self.code(token::code::error_incompatible_type);
            throw json::error(self.error());
        }

        typename view_type::const_iterator it = self.literal().begin();

        const bool is_negative = (*it == traits<char>::alpha_minus);
        if (is_negative)
        {
            if (boost::is_unsigned<ReturnType>::value)
            {
                self.code(token::code::error_invalid_value);
                throw json::error(self.error());
            }
            ++it;
        }
        ReturnType result = ReturnType();
        while (it != self.literal().end())
        {
            const ReturnType old = result;
            result *= ReturnType(10);
            result += traits<char>::to_int(*it);
            if (result < old)
            {
                // Overflow
                self.code(token::code::error_invalid_value);
                throw json::error(self.error());
            }
            ++it;
        }
        return is_negative ? -result : result;
    }
};

// Floating-point numbers

template <typename ReturnType>
struct decoder::type_matcher<ReturnType,
                             typename boost::enable_if< boost::is_floating_point<ReturnType> >::type>
{
    static ReturnType convert(decoder& self)
    {
        if (self.code() != token::code::floating)
        {
            self.code(token::code::error_incompatible_type);
            throw json::error(self.error());
        }

        return std::atof(self.literal().data());
    }
};

// Strings

template <>
struct decoder::type_matcher<std::string>
{
    typedef std::string return_type;

    // FIXME: Validate string [ http://www.w3.org/International/questions/qa-forms-utf-8 ]
    static return_type convert(decoder& self)
    {
        if (self.code() != token::code::string)
        {
            self.code(token::code::error_incompatible_type);
            throw json::error(self.error());
        }

        const typename view_type::size_type  approximateSize = self.literal().size();
        assert(approximateSize >= 2);

        return_type result;
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
// decoder
//-----------------------------------------------------------------------------

inline decoder::decoder(const view_type& input)
    : input(input)
{
    current.code = token::code::end;
    next();
}

inline void decoder::code(token::code::value value) BOOST_NOEXCEPT
{
    current.code = value;
}

inline token::code::value decoder::code() const BOOST_NOEXCEPT
{
    return current.code;
}

inline token::symbol::value decoder::symbol() const BOOST_NOEXCEPT
{
    return token::symbol::convert(current.code);
}

inline token::category::value decoder::category() const BOOST_NOEXCEPT
{
    return token::category::convert(current.code);
}

inline boost::system::error_code decoder::error() const BOOST_NOEXCEPT
{
    return json::make_error_code(to_errc(code()));
}

inline void decoder::next() BOOST_NOEXCEPT
{
    if (symbol() == token::symbol::error)
    {
        return;
    }

    skip_whitespaces();

    if (input.empty())
    {
        current.code = token::code::end;
        return;
    }

    switch (input.front())
    {
    case traits<char>::alpha_f:
        current.code = next_f_keyword();
        break;

    case traits<char>::alpha_n:
        current.code = next_n_keyword();
        break;

    case traits<char>::alpha_t:
        current.code = next_t_keyword();
        break;

    case traits<char>::alpha_minus:
    case traits<char>::alpha_0:
    case traits<char>::alpha_1:
    case traits<char>::alpha_2:
    case traits<char>::alpha_3:
    case traits<char>::alpha_4:
    case traits<char>::alpha_5:
    case traits<char>::alpha_6:
    case traits<char>::alpha_7:
    case traits<char>::alpha_8:
    case traits<char>::alpha_9:
        current.code = next_number();
        break;

    case traits<char>::alpha_quote:
        current.code = next_string();
        break;

    case traits<char>::alpha_brace_open:
        current.code = next_token(token::code::begin_object);
        break;

    case traits<char>::alpha_brace_close:
        current.code = next_token(token::code::end_object);
        break;

    case traits<char>::alpha_bracket_open:
        current.code = next_token(token::code::begin_array);
        break;

    case traits<char>::alpha_bracket_close:
        current.code = next_token(token::code::end_array);
        break;

    case traits<char>::alpha_comma:
        current.code = next_token(token::code::value_separator);
        break;

    case traits<char>::alpha_colon:
        current.code = next_token(token::code::name_separator);
        break;

    default:
        current.code = token::code::error_unexpected_token;
        break;
    }
}

template <typename ReturnType>
ReturnType decoder::value() const
{
    // Remove constness because we may need to update error state
    return type_matcher<ReturnType>::convert(const_cast<decoder&>(*this));
}

inline const decoder::view_type& decoder::literal() const BOOST_NOEXCEPT
{
    return current.view;
}

inline token::code::value decoder::next_token(token::code::value type) BOOST_NOEXCEPT
{
    current.view = view_type(input.begin(), 1);
    input.remove_prefix(1);
    return type;
}

inline token::code::value decoder::next_f_keyword() BOOST_NOEXCEPT
{
    token::code::value type = token::code::false_value;
    view_type::const_iterator begin = input.begin();

    const std::size_t size = traits<char>::false_text().size();
    if (input.size() < size)
    {
        input.remove_prefix(input.size());
        type = token::code::end;
        goto end;
    }
    if (traits<char>::false_text().compare(0, size, begin, size) != 0)
    {
        type = token::code::error_unexpected_token;
        goto end;
    }
    input.remove_prefix(size);
    if (!at_keyword_end())
    {
        while (!at_keyword_end())
            input.remove_prefix(1);
        type = token::code::error_unexpected_token;
    }

 end:
    current.view = view_type(begin, std::distance(begin, input.begin()));
    return type;
}

inline token::code::value decoder::next_n_keyword() BOOST_NOEXCEPT
{
    token::code::value type = token::code::null;
    view_type::const_iterator begin = input.begin();

    const std::size_t size = traits<char>::null_text().size();
    if (input.size() < size)
    {
        input.remove_prefix(input.size());
        type = token::code::end;
        goto end;
    }
    if (traits<char>::null_text().compare(0, size, begin, size) != 0)
    {
        type = token::code::error_unexpected_token;
        goto end;
    }
    input.remove_prefix(size);
    if (!at_keyword_end())
    {
        while (!at_keyword_end())
            input.remove_prefix(1);
        type = token::code::error_unexpected_token;
    }

 end:
    current.view = view_type(begin, std::distance(begin, input.begin()));
    return type;
}

inline token::code::value decoder::next_t_keyword() BOOST_NOEXCEPT
{
    token::code::value type = token::code::true_value;
    view_type::const_iterator begin = input.begin();

    const std::size_t size = traits<char>::true_text().size();
    if (input.size() < size)
    {
        input.remove_prefix(input.size());
        type = token::code::end;
        goto end;
    }
    if (traits<char>::true_text().compare(0, size, begin, size) != 0)
    {
        type = token::code::error_unexpected_token;
        goto end;
    }
    input.remove_prefix(size);
    if (!at_keyword_end())
    {
        while (!at_keyword_end())
            input.remove_prefix(1);
        type = token::code::error_unexpected_token;
    }

 end:
    current.view = view_type(begin, std::distance(begin, input.begin()));
    return type;
}

inline token::code::value decoder::next_number() BOOST_NOEXCEPT
{
    view_type::const_iterator begin = input.begin();
    token::code::value type = token::code::integer;

    const bool is_negative = (*begin == traits<char>::alpha_minus);
    if (is_negative)
    {
        input.remove_prefix(1); // Skip '-'
        if (input.empty())
        {
            type = token::code::end;
            goto end;
        }
    }

    {
        view_type::const_iterator digit_begin = input.begin();
        while (!input.empty() && traits<char>::is_digit(input.front()))
        {
            input.remove_prefix(1);
        }
        if (input.begin() == digit_begin)
        {
            // No digits found
            type = token::code::error_unexpected_token;
            goto end;
        }
        if (!input.empty())
        {
            if (input.front() == traits<char>::alpha_dot)
            {
                type = token::code::floating;
                input.remove_prefix(1);
                if (input.empty())
                {
                    type = token::code::end;
                    goto end;
                }
                view_type::const_iterator fraction_begin = input.begin();
                while (!input.empty() && traits<char>::is_digit(input.front()))
                {
                    input.remove_prefix(1);
                }
                if (input.begin() == fraction_begin)
                {
                    type = token::code::error_unexpected_token;
                    goto end;
                }
            }
            if (!input.empty() && ((input.front() == traits<char>::alpha_E) ||
                                   (input.front() == traits<char>::alpha_e)))
            {
                type = token::code::floating;
                input.remove_prefix(1);
                if (input.empty())
                {
                    type = token::code::end;
                    goto end;
                }

                if (input.front() == traits<char>::alpha_plus)
                {
                    input.remove_prefix(1);
                    if (input.empty())
                    {
                        type = token::code::end;
                        goto end;
                    }
                }
                else if (input.front() == traits<char>::alpha_minus)
                {
                    input.remove_prefix(1);
                    if (input.empty())
                    {
                        type = token::code::end;
                        goto end;
                    }
                }
                view_type::const_iterator exponent_begin = input.begin();
                while (!input.empty() && traits<char>::is_digit(input.front()))
                {
                    input.remove_prefix(1);
                }
                if (input.begin() == exponent_begin)
                {
                    type = token::code::error_unexpected_token;
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

inline token::code::value decoder::next_string() BOOST_NOEXCEPT
{
    assert(input.front() == traits<char>::alpha_quote);

    view_type::const_iterator marker = input.begin();
    view_type::const_iterator end = input.end();
    ++marker; // Skip initial '"'
    while (marker != end)
    {
        const view_type::size_type amount = traits<char>::extra_bytes(*marker);

        if (amount > 0)
        {
            // Skip UTF-8 characters
            const view_type::size_type distance = std::distance(marker, end);
            if (amount >= distance)
                goto error;

            ++marker;

            for (view_type::size_type i = 0; i < amount; ++i)
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
            if (character == traits<char>::alpha_reverse_solidus)
            {
                // Handle escaped character
                if (marker == end)
                    goto eof;
                switch (*marker++)
                {
                case traits<char>::alpha_quote:
                case traits<char>::alpha_reverse_solidus:
                case traits<char>::alpha_solidus:
                case traits<char>::alpha_b:
                case traits<char>::alpha_f:
                case traits<char>::alpha_n:
                case traits<char>::alpha_r:
                case traits<char>::alpha_t:
                    break;

                case traits<char>::alpha_u:
                    switch (std::distance(marker, end))
                    {
                    case 0:
                        goto eof;
                    case 1:
                        if (!traits<char>::is_hexdigit(*marker))
                            goto error;
                        ++marker;
                        goto eof;
                    case 2:
                        if (!traits<char>::is_hexdigit(*marker))
                            goto error;
                        ++marker;
                        if (!traits<char>::is_hexdigit(*marker))
                            goto error;
                        ++marker;
                        goto eof;
                    case 3:
                        if (!traits<char>::is_hexdigit(*marker))
                            goto error;
                        ++marker;
                        if (!traits<char>::is_hexdigit(*marker))
                            goto error;
                        ++marker;
                        if (!traits<char>::is_hexdigit(*marker))
                            goto error;
                        ++marker;
                        goto eof;
                    default:
                        if (!traits<char>::is_hexdigit(*marker))
                            goto error;
                        ++marker;
                        if (!traits<char>::is_hexdigit(*marker))
                            goto error;
                        ++marker;
                        if (!traits<char>::is_hexdigit(*marker))
                            goto error;
                        ++marker;
                        if (!traits<char>::is_hexdigit(*marker))
                            goto error;
                        ++marker;
                        break;
                    }
                    break;

                default:
                    goto error;
                }
            }
            else if (character == traits<char>::alpha_quote)
            {
                // Handle end of string
                current.view = view_type(input.begin(), std::distance(input.begin(), marker)); // Includes terminating '"'
                input.remove_prefix(std::distance(input.begin(), marker));
                return token::code::string;
            }
        }
    }
 eof:
    current.view = view_type(input.begin(), std::distance(input.begin(), marker));
    return token::code::end;

 error:
    current.view = view_type(input.begin(), std::distance(input.begin(), marker));
    return token::code::error_unexpected_token;
}

inline void decoder::skip_whitespaces() BOOST_NOEXCEPT
{
    view_type::size_type size = view_type::size_type();
    view_type::const_iterator end = input.end();
    for (view_type::const_iterator it = input.begin();
         it != end;
         ++it)
    {
        if (!traits<char>::is_space(*it))
            break;
        ++size;
    }
    if (size > 0)
    {
        input.remove_prefix(size);
    }
}

inline bool decoder::at_keyword_end() const BOOST_NOEXCEPT
{
    if (input.empty())
    {
        return true;
    }
    return !traits<char>::is_keyword(input.front());
}

} // namespace detail
} // namespace json
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_JSON_DETAIL_DECODER_IPP
