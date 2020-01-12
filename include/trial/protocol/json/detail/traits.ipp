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
namespace traits
{

template <typename CharT>
auto to_category(CharT value) noexcept -> category
{
    static constexpr category data[] = {
        category::illegal,
        category::illegal,
        category::illegal,
        category::illegal,
        category::illegal,
        category::illegal,
        category::illegal,
        category::illegal,
        category::illegal,
        category::illegal,
        category::illegal,
        category::illegal,
        category::illegal,
        category::illegal,
        category::illegal,
        category::illegal,
        category::illegal,
        category::illegal,
        category::illegal,
        category::illegal,
        category::illegal,
        category::illegal,
        category::illegal,
        category::illegal,
        category::illegal,
        category::illegal,
        category::illegal,
        category::illegal,
        category::illegal,
        category::illegal,
        category::illegal,
        category::illegal,
        category::narrow,
        category::narrow,
        category::quote,
        category::narrow,
        category::narrow,
        category::narrow,
        category::narrow,
        category::narrow,
        category::narrow,
        category::narrow,
        category::narrow,
        category::narrow,
        category::narrow,
        category::narrow,
        category::narrow,
        category::narrow,
        category::narrow,
        category::narrow,
        category::narrow,
        category::narrow,
        category::narrow,
        category::narrow,
        category::narrow,
        category::narrow,
        category::narrow,
        category::narrow,
        category::narrow,
        category::narrow,
        category::narrow,
        category::narrow,
        category::narrow,
        category::narrow,
        category::narrow,
        category::narrow,
        category::narrow,
        category::narrow,
        category::narrow,
        category::narrow,
        category::narrow,
        category::narrow,
        category::narrow,
        category::narrow,
        category::narrow,
        category::narrow,
        category::narrow,
        category::narrow,
        category::narrow,
        category::narrow,
        category::narrow,
        category::narrow,
        category::narrow,
        category::narrow,
        category::narrow,
        category::narrow,
        category::narrow,
        category::narrow,
        category::narrow,
        category::narrow,
        category::narrow,
        category::narrow,
        category::escape,
        category::narrow,
        category::narrow,
        category::narrow,
        category::narrow,
        category::narrow,
        category::narrow,
        category::narrow,
        category::narrow,
        category::narrow,
        category::narrow,
        category::narrow,
        category::narrow,
        category::narrow,
        category::narrow,
        category::narrow,
        category::narrow,
        category::narrow,
        category::narrow,
        category::narrow,
        category::narrow,
        category::narrow,
        category::narrow,
        category::narrow,
        category::narrow,
        category::narrow,
        category::narrow,
        category::narrow,
        category::narrow,
        category::narrow,
        category::narrow,
        category::narrow,
        category::narrow,
        category::narrow,
        category::narrow,
        category::narrow,
        category::illegal,
        category::illegal,
        category::illegal,
        category::illegal,
        category::illegal,
        category::illegal,
        category::illegal,
        category::illegal,
        category::illegal,
        category::illegal,
        category::illegal,
        category::illegal,
        category::illegal,
        category::illegal,
        category::illegal,
        category::illegal,
        category::illegal,
        category::illegal,
        category::illegal,
        category::illegal,
        category::illegal,
        category::illegal,
        category::illegal,
        category::illegal,
        category::illegal,
        category::illegal,
        category::illegal,
        category::illegal,
        category::illegal,
        category::illegal,
        category::illegal,
        category::illegal,
        category::illegal,
        category::illegal,
        category::illegal,
        category::illegal,
        category::illegal,
        category::illegal,
        category::illegal,
        category::illegal,
        category::illegal,
        category::illegal,
        category::illegal,
        category::illegal,
        category::illegal,
        category::illegal,
        category::illegal,
        category::illegal,
        category::illegal,
        category::illegal,
        category::illegal,
        category::illegal,
        category::illegal,
        category::illegal,
        category::illegal,
        category::illegal,
        category::illegal,
        category::illegal,
        category::illegal,
        category::illegal,
        category::illegal,
        category::illegal,
        category::illegal,
        category::illegal,
        category::extra_1,
        category::extra_1,
        category::extra_1,
        category::extra_1,
        category::extra_1,
        category::extra_1,
        category::extra_1,
        category::extra_1,
        category::extra_1,
        category::extra_1,
        category::extra_1,
        category::extra_1,
        category::extra_1,
        category::extra_1,
        category::extra_1,
        category::extra_1,
        category::extra_1,
        category::extra_1,
        category::extra_1,
        category::extra_1,
        category::extra_1,
        category::extra_1,
        category::extra_1,
        category::extra_1,
        category::extra_1,
        category::extra_1,
        category::extra_1,
        category::extra_1,
        category::extra_1,
        category::extra_1,
        category::extra_1,
        category::extra_1,
        category::extra_2,
        category::extra_2,
        category::extra_2,
        category::extra_2,
        category::extra_2,
        category::extra_2,
        category::extra_2,
        category::extra_2,
        category::extra_2,
        category::extra_2,
        category::extra_2,
        category::extra_2,
        category::extra_2,
        category::extra_2,
        category::extra_2,
        category::extra_2,
        category::extra_3,
        category::extra_3,
        category::extra_3,
        category::extra_3,
        category::extra_3,
        category::extra_3,
        category::extra_3,
        category::extra_3,
        category::extra_4,
        category::extra_4,
        category::extra_4,
        category::extra_4,
        category::extra_5,
        category::extra_5,
        category::extra_5,
        category::extra_5
    };
    return data[std::uint8_t(value)];
}

template <typename CharT>
int to_hexint(CharT value) noexcept
{
    static constexpr int data[] = {
        // 0x00
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        // 0x10
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        // 0x20
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        // 0x30
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
        0x08, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        // 0x40
        0x00, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        // 0x50
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        // 0x60
        0x00, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x00,
        // Rest not needed
    };
    return data[unsigned(value)];
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

} // namespace traits
} // namespace detail
} // namespace json
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_JSON_DETAIL_TRAITS_IPP
