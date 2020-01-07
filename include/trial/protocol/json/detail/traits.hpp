#ifndef TRIAL_PROTOCOL_JSON_DETAIL_TRAITS_HPP
#define TRIAL_PROTOCOL_JSON_DETAIL_TRAITS_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2015 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <cstddef> // std::size_t
#include <string>
#include <boost/config.hpp>
#include <trial/protocol/core/char_traits.hpp>

namespace trial
{
namespace protocol
{
namespace json
{
namespace detail
{

template <typename CharT>
struct alphabet
{
};

template <typename CharT>
class traits
{
    static int count_narrow(const CharT * const) noexcept;
};

enum class traits_category
{
    narrow,
    extra_1,
    extra_2,
    extra_3,
    extra_4,
    extra_5,
    quote,
    escape,
    illegal
};

enum
{
    character_space = 1 << 0,     // 0x09 | 0x0A | 0x0D | 0x20
    character_digit = 1 << 1,     // 0-9
    character_hex_upper = 1 << 2, // A-F
    character_hex_lower = 1 << 3, // a-f
    character_alpha = 1 << 4      // A-Z | a-z
};

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

template <>
class traits<char>
{
public:
    using value_type = char;
    using string_type = std::basic_string<value_type, core::char_traits<value_type>>;

    static bool is_space(value_type value) noexcept
    {
        return flags(value) & character_space;
    }
    static bool is_digit(value_type value) noexcept
    {
        return flags(value) & character_digit;
    }
    static bool is_hexdigit(value_type value) noexcept
    {
        return flags(value) & (character_digit | character_hex_upper | character_hex_lower);
    }
    static bool is_keyword(value_type value) noexcept
    {
        return flags(value) & character_alpha;
    }
    static traits_category to_category(value_type value) noexcept;
    static int to_int(value_type value) noexcept;

    static const value_type *skip_narrow(const value_type *) noexcept;

    static const string_type& false_text() noexcept;
    static const string_type& true_text() noexcept;
    static const string_type& null_text() noexcept;

private:
    static bool is_hex_upper(value_type value) noexcept
    {
        return flags(value) & character_hex_upper;
    }
    static bool is_hex_lower(value_type value) noexcept
    {
        return flags(value) & character_hex_lower;
    }
    static std::uint8_t flags(value_type index) noexcept
    {
        static constexpr std::uint8_t data[] = {
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
            0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
            0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
        };
        return data[std::uint8_t(index)];
    };
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

template <>
class traits<unsigned char>
{
public:
    using value_type = unsigned char;
    using string_type = std::basic_string<value_type, core::char_traits<value_type>>;

    static bool is_space(value_type value) noexcept
    {
        return flags(value) & character_space;
    }
    static bool is_digit(value_type value) noexcept
    {
        return flags(value) & character_digit;
    }
    static bool is_hexdigit(value_type value) noexcept
    {
        return flags(value) & (character_digit | character_hex_upper | character_hex_lower);
    }
    static bool is_keyword(value_type value) noexcept
    {
        return flags(value) & character_alpha;
    }
    static traits_category to_category(value_type value) noexcept;
    static int to_int(value_type value) noexcept;
    static const value_type *skip_narrow(const value_type *) noexcept;

    static const string_type& false_text() noexcept;
    static const string_type& true_text() noexcept;
    static const string_type& null_text() noexcept;

private:
    static bool is_hex_upper(value_type value) noexcept
    {
        return flags(value) & character_hex_upper;
    }
    static bool is_hex_lower(value_type value) noexcept
    {
        return flags(value) & character_hex_lower;
    }
    static std::uint8_t flags(value_type index) noexcept
    {
        static constexpr std::uint8_t data[] = {
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
            0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
            0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
        };
        return data[index];
    };
};

} // namespace detail
} // namespace json
} // namespace protocol
} // namespace trial

#include <trial/protocol/json/detail/traits.ipp>

#endif // TRIAL_PROTOCOL_JSON_DETAIL_TRAITS_HPP
