#ifndef TRIAL_PROTOCOL_JSON_DETAIL_TRAITS_IPP
#define TRIAL_PROTOCOL_JSON_DETAIL_TRAITS_IPP

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
#include <type_traits>

namespace trial
{
namespace protocol
{
namespace json
{
namespace detail
{

template <typename CharT>
auto to_category(CharT value) noexcept -> traits_category
{
    static constexpr traits_category data[] = {
        traits_category::illegal,
        traits_category::illegal,
        traits_category::illegal,
        traits_category::illegal,
        traits_category::illegal,
        traits_category::illegal,
        traits_category::illegal,
        traits_category::illegal,
        traits_category::illegal,
        traits_category::illegal,
        traits_category::illegal,
        traits_category::illegal,
        traits_category::illegal,
        traits_category::illegal,
        traits_category::illegal,
        traits_category::illegal,
        traits_category::illegal,
        traits_category::illegal,
        traits_category::illegal,
        traits_category::illegal,
        traits_category::illegal,
        traits_category::illegal,
        traits_category::illegal,
        traits_category::illegal,
        traits_category::illegal,
        traits_category::illegal,
        traits_category::illegal,
        traits_category::illegal,
        traits_category::illegal,
        traits_category::illegal,
        traits_category::illegal,
        traits_category::illegal,
        traits_category::narrow,
        traits_category::narrow,
        traits_category::quote,
        traits_category::narrow,
        traits_category::narrow,
        traits_category::narrow,
        traits_category::narrow,
        traits_category::narrow,
        traits_category::narrow,
        traits_category::narrow,
        traits_category::narrow,
        traits_category::narrow,
        traits_category::narrow,
        traits_category::narrow,
        traits_category::narrow,
        traits_category::narrow,
        traits_category::narrow,
        traits_category::narrow,
        traits_category::narrow,
        traits_category::narrow,
        traits_category::narrow,
        traits_category::narrow,
        traits_category::narrow,
        traits_category::narrow,
        traits_category::narrow,
        traits_category::narrow,
        traits_category::narrow,
        traits_category::narrow,
        traits_category::narrow,
        traits_category::narrow,
        traits_category::narrow,
        traits_category::narrow,
        traits_category::narrow,
        traits_category::narrow,
        traits_category::narrow,
        traits_category::narrow,
        traits_category::narrow,
        traits_category::narrow,
        traits_category::narrow,
        traits_category::narrow,
        traits_category::narrow,
        traits_category::narrow,
        traits_category::narrow,
        traits_category::narrow,
        traits_category::narrow,
        traits_category::narrow,
        traits_category::narrow,
        traits_category::narrow,
        traits_category::narrow,
        traits_category::narrow,
        traits_category::narrow,
        traits_category::narrow,
        traits_category::narrow,
        traits_category::narrow,
        traits_category::narrow,
        traits_category::narrow,
        traits_category::narrow,
        traits_category::narrow,
        traits_category::narrow,
        traits_category::narrow,
        traits_category::escape,
        traits_category::narrow,
        traits_category::narrow,
        traits_category::narrow,
        traits_category::narrow,
        traits_category::narrow,
        traits_category::narrow,
        traits_category::narrow,
        traits_category::narrow,
        traits_category::narrow,
        traits_category::narrow,
        traits_category::narrow,
        traits_category::narrow,
        traits_category::narrow,
        traits_category::narrow,
        traits_category::narrow,
        traits_category::narrow,
        traits_category::narrow,
        traits_category::narrow,
        traits_category::narrow,
        traits_category::narrow,
        traits_category::narrow,
        traits_category::narrow,
        traits_category::narrow,
        traits_category::narrow,
        traits_category::narrow,
        traits_category::narrow,
        traits_category::narrow,
        traits_category::narrow,
        traits_category::narrow,
        traits_category::narrow,
        traits_category::narrow,
        traits_category::narrow,
        traits_category::narrow,
        traits_category::narrow,
        traits_category::narrow,
        traits_category::illegal,
        traits_category::illegal,
        traits_category::illegal,
        traits_category::illegal,
        traits_category::illegal,
        traits_category::illegal,
        traits_category::illegal,
        traits_category::illegal,
        traits_category::illegal,
        traits_category::illegal,
        traits_category::illegal,
        traits_category::illegal,
        traits_category::illegal,
        traits_category::illegal,
        traits_category::illegal,
        traits_category::illegal,
        traits_category::illegal,
        traits_category::illegal,
        traits_category::illegal,
        traits_category::illegal,
        traits_category::illegal,
        traits_category::illegal,
        traits_category::illegal,
        traits_category::illegal,
        traits_category::illegal,
        traits_category::illegal,
        traits_category::illegal,
        traits_category::illegal,
        traits_category::illegal,
        traits_category::illegal,
        traits_category::illegal,
        traits_category::illegal,
        traits_category::illegal,
        traits_category::illegal,
        traits_category::illegal,
        traits_category::illegal,
        traits_category::illegal,
        traits_category::illegal,
        traits_category::illegal,
        traits_category::illegal,
        traits_category::illegal,
        traits_category::illegal,
        traits_category::illegal,
        traits_category::illegal,
        traits_category::illegal,
        traits_category::illegal,
        traits_category::illegal,
        traits_category::illegal,
        traits_category::illegal,
        traits_category::illegal,
        traits_category::illegal,
        traits_category::illegal,
        traits_category::illegal,
        traits_category::illegal,
        traits_category::illegal,
        traits_category::illegal,
        traits_category::illegal,
        traits_category::illegal,
        traits_category::illegal,
        traits_category::illegal,
        traits_category::illegal,
        traits_category::illegal,
        traits_category::illegal,
        traits_category::illegal,
        traits_category::extra_1,
        traits_category::extra_1,
        traits_category::extra_1,
        traits_category::extra_1,
        traits_category::extra_1,
        traits_category::extra_1,
        traits_category::extra_1,
        traits_category::extra_1,
        traits_category::extra_1,
        traits_category::extra_1,
        traits_category::extra_1,
        traits_category::extra_1,
        traits_category::extra_1,
        traits_category::extra_1,
        traits_category::extra_1,
        traits_category::extra_1,
        traits_category::extra_1,
        traits_category::extra_1,
        traits_category::extra_1,
        traits_category::extra_1,
        traits_category::extra_1,
        traits_category::extra_1,
        traits_category::extra_1,
        traits_category::extra_1,
        traits_category::extra_1,
        traits_category::extra_1,
        traits_category::extra_1,
        traits_category::extra_1,
        traits_category::extra_1,
        traits_category::extra_1,
        traits_category::extra_1,
        traits_category::extra_1,
        traits_category::extra_2,
        traits_category::extra_2,
        traits_category::extra_2,
        traits_category::extra_2,
        traits_category::extra_2,
        traits_category::extra_2,
        traits_category::extra_2,
        traits_category::extra_2,
        traits_category::extra_2,
        traits_category::extra_2,
        traits_category::extra_2,
        traits_category::extra_2,
        traits_category::extra_2,
        traits_category::extra_2,
        traits_category::extra_2,
        traits_category::extra_2,
        traits_category::extra_3,
        traits_category::extra_3,
        traits_category::extra_3,
        traits_category::extra_3,
        traits_category::extra_3,
        traits_category::extra_3,
        traits_category::extra_3,
        traits_category::extra_3,
        traits_category::extra_4,
        traits_category::extra_4,
        traits_category::extra_4,
        traits_category::extra_4,
        traits_category::extra_5,
        traits_category::extra_5,
        traits_category::extra_5,
        traits_category::extra_5
    };
    return data[std::uint8_t(value)];
}

template <typename CharT>
int to_hexint(CharT value) noexcept
{
    if (is_digit(value))
        return value - alphabet<CharT>::digit_0;
    if (flags(value) & character_hex_upper)
        return value - alphabet<CharT>::letter_A + 10;
    if (flags(value) & character_hex_lower)
        return value - alphabet<CharT>::letter_a + 10;
    return 0;
}

//-----------------------------------------------------------------------------

template <typename CharT>
auto skip_narrow(const CharT *marker) noexcept -> const CharT *
{
    while (to_category(*marker) == traits_category::narrow)
    {
        ++marker;
    }
    return marker;
}

//-----------------------------------------------------------------------------
// char specialization
//-----------------------------------------------------------------------------

template <>
struct alphabet<char>
{
    static constexpr char backspace = '\b';
    static constexpr char formfeed = '\f';
    static constexpr char newline = '\n';
    static constexpr char tabulator = '\t';
    static constexpr char carriage_return = '\r';
    static constexpr char quote = '"';
    static constexpr char plus = '+';
    static constexpr char comma = ',';
    static constexpr char minus = '-';
    static constexpr char dot = '.';
    static constexpr char solidus = '/';
    static constexpr char digit_0 = '0';
    static constexpr char digit_1 = '1';
    static constexpr char digit_2 = '2';
    static constexpr char digit_3 = '3';
    static constexpr char digit_4 = '4';
    static constexpr char digit_5 = '5';
    static constexpr char digit_6 = '6';
    static constexpr char digit_7 = '7';
    static constexpr char digit_8 = '8';
    static constexpr char digit_9 = '9';
    static constexpr char colon = ':';
    static constexpr char question_mark = '?';
    static constexpr char letter_A = 'A';
    static constexpr char letter_E = 'E';
    static constexpr char letter_a = 'a';
    static constexpr char letter_b = 'b';
    static constexpr char letter_e = 'e';
    static constexpr char letter_f = 'f';
    static constexpr char letter_l = 'l';
    static constexpr char letter_n = 'n';
    static constexpr char letter_r = 'r';
    static constexpr char letter_s = 's';
    static constexpr char letter_t = 't';
    static constexpr char letter_u = 'u';
    static constexpr char bracket_open = '[';
    static constexpr char reverse_solidus = '\\';
    static constexpr char bracket_close = ']';
    static constexpr char brace_open = '{';
    static constexpr char brace_close = '}';
};

//-----------------------------------------------------------------------------
// unsigned char specialization
//-----------------------------------------------------------------------------

template <>
struct alphabet<unsigned char>
{
    static constexpr unsigned char backspace = '\b';
    static constexpr unsigned char formfeed = '\f';
    static constexpr unsigned char newline = '\n';
    static constexpr unsigned char tabulator = '\t';
    static constexpr unsigned char carriage_return = '\r';
    static constexpr unsigned char quote = '"';
    static constexpr unsigned char plus = '+';
    static constexpr unsigned char comma = ',';
    static constexpr unsigned char minus = '-';
    static constexpr unsigned char dot = '.';
    static constexpr unsigned char solidus = '/';
    static constexpr unsigned char digit_0 = '0';
    static constexpr unsigned char digit_1 = '1';
    static constexpr unsigned char digit_2 = '2';
    static constexpr unsigned char digit_3 = '3';
    static constexpr unsigned char digit_4 = '4';
    static constexpr unsigned char digit_5 = '5';
    static constexpr unsigned char digit_6 = '6';
    static constexpr unsigned char digit_7 = '7';
    static constexpr unsigned char digit_8 = '8';
    static constexpr unsigned char digit_9 = '9';
    static constexpr unsigned char colon = ':';
    static constexpr unsigned char question_mark = '?';
    static constexpr unsigned char letter_A = 'A';
    static constexpr unsigned char letter_E = 'E';
    static constexpr unsigned char letter_a = 'a';
    static constexpr unsigned char letter_b = 'b';
    static constexpr unsigned char letter_e = 'e';
    static constexpr unsigned char letter_f = 'f';
    static constexpr unsigned char letter_l = 'l';
    static constexpr unsigned char letter_n = 'n';
    static constexpr unsigned char letter_r = 'r';
    static constexpr unsigned char letter_s = 's';
    static constexpr unsigned char letter_t = 't';
    static constexpr unsigned char letter_u = 'u';
    static constexpr unsigned char bracket_open = '[';
    static constexpr unsigned char reverse_solidus = '\\';
    static constexpr unsigned char bracket_close = ']';
    static constexpr unsigned char brace_open = '{';
    static constexpr unsigned char brace_close = '}';
};

} // namespace detail
} // namespace json
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_JSON_DETAIL_TRAITS_IPP
