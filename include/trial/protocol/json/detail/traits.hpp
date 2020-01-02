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

    BOOST_STATIC_CONSTANT(value_type, alpha_backspace = '\b');
    BOOST_STATIC_CONSTANT(value_type, alpha_formfeed = '\f');
    BOOST_STATIC_CONSTANT(value_type, alpha_newline = '\n');
    BOOST_STATIC_CONSTANT(value_type, alpha_tab = '\t');
    BOOST_STATIC_CONSTANT(value_type, alpha_return = '\r');
    BOOST_STATIC_CONSTANT(value_type, alpha_quote = '"');
    BOOST_STATIC_CONSTANT(value_type, alpha_plus = '+');
    BOOST_STATIC_CONSTANT(value_type, alpha_comma = ',');
    BOOST_STATIC_CONSTANT(value_type, alpha_minus = '-');
    BOOST_STATIC_CONSTANT(value_type, alpha_dot = '.');
    BOOST_STATIC_CONSTANT(value_type, alpha_solidus = '/');
    BOOST_STATIC_CONSTANT(value_type, alpha_0 = '0');
    BOOST_STATIC_CONSTANT(value_type, alpha_1 = '1');
    BOOST_STATIC_CONSTANT(value_type, alpha_2 = '2');
    BOOST_STATIC_CONSTANT(value_type, alpha_3 = '3');
    BOOST_STATIC_CONSTANT(value_type, alpha_4 = '4');
    BOOST_STATIC_CONSTANT(value_type, alpha_5 = '5');
    BOOST_STATIC_CONSTANT(value_type, alpha_6 = '6');
    BOOST_STATIC_CONSTANT(value_type, alpha_7 = '7');
    BOOST_STATIC_CONSTANT(value_type, alpha_8 = '8');
    BOOST_STATIC_CONSTANT(value_type, alpha_9 = '9');
    BOOST_STATIC_CONSTANT(value_type, alpha_colon = ':');
    BOOST_STATIC_CONSTANT(value_type, alpha_question_mark = '?');
    BOOST_STATIC_CONSTANT(value_type, alpha_A = 'A');
    BOOST_STATIC_CONSTANT(value_type, alpha_E = 'E');
    BOOST_STATIC_CONSTANT(value_type, alpha_a = 'a');
    BOOST_STATIC_CONSTANT(value_type, alpha_b = 'b');
    BOOST_STATIC_CONSTANT(value_type, alpha_e = 'e');
    BOOST_STATIC_CONSTANT(value_type, alpha_f = 'f');
    BOOST_STATIC_CONSTANT(value_type, alpha_l = 'l');
    BOOST_STATIC_CONSTANT(value_type, alpha_n = 'n');
    BOOST_STATIC_CONSTANT(value_type, alpha_r = 'r');
    BOOST_STATIC_CONSTANT(value_type, alpha_s = 's');
    BOOST_STATIC_CONSTANT(value_type, alpha_t = 't');
    BOOST_STATIC_CONSTANT(value_type, alpha_u = 'u');
    BOOST_STATIC_CONSTANT(value_type, alpha_bracket_open = '[');
    BOOST_STATIC_CONSTANT(value_type, alpha_reverse_solidus = '\\');
    BOOST_STATIC_CONSTANT(value_type, alpha_bracket_close = ']');
    BOOST_STATIC_CONSTANT(value_type, alpha_brace_open = '{');
    BOOST_STATIC_CONSTANT(value_type, alpha_brace_close = '}');

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

    BOOST_STATIC_CONSTANT(value_type, alpha_backspace = '\b');
    BOOST_STATIC_CONSTANT(value_type, alpha_formfeed = '\f');
    BOOST_STATIC_CONSTANT(value_type, alpha_newline = '\n');
    BOOST_STATIC_CONSTANT(value_type, alpha_tab = '\t');
    BOOST_STATIC_CONSTANT(value_type, alpha_return = '\r');
    BOOST_STATIC_CONSTANT(value_type, alpha_quote = '"');
    BOOST_STATIC_CONSTANT(value_type, alpha_plus = '+');
    BOOST_STATIC_CONSTANT(value_type, alpha_comma = ',');
    BOOST_STATIC_CONSTANT(value_type, alpha_minus = '-');
    BOOST_STATIC_CONSTANT(value_type, alpha_dot = '.');
    BOOST_STATIC_CONSTANT(value_type, alpha_solidus = '/');
    BOOST_STATIC_CONSTANT(value_type, alpha_0 = '0');
    BOOST_STATIC_CONSTANT(value_type, alpha_1 = '1');
    BOOST_STATIC_CONSTANT(value_type, alpha_2 = '2');
    BOOST_STATIC_CONSTANT(value_type, alpha_3 = '3');
    BOOST_STATIC_CONSTANT(value_type, alpha_4 = '4');
    BOOST_STATIC_CONSTANT(value_type, alpha_5 = '5');
    BOOST_STATIC_CONSTANT(value_type, alpha_6 = '6');
    BOOST_STATIC_CONSTANT(value_type, alpha_7 = '7');
    BOOST_STATIC_CONSTANT(value_type, alpha_8 = '8');
    BOOST_STATIC_CONSTANT(value_type, alpha_9 = '9');
    BOOST_STATIC_CONSTANT(value_type, alpha_colon = ':');
    BOOST_STATIC_CONSTANT(value_type, alpha_question_mark = '?');
    BOOST_STATIC_CONSTANT(value_type, alpha_A = 'A');
    BOOST_STATIC_CONSTANT(value_type, alpha_E = 'E');
    BOOST_STATIC_CONSTANT(value_type, alpha_a = 'a');
    BOOST_STATIC_CONSTANT(value_type, alpha_b = 'b');
    BOOST_STATIC_CONSTANT(value_type, alpha_e = 'e');
    BOOST_STATIC_CONSTANT(value_type, alpha_f = 'f');
    BOOST_STATIC_CONSTANT(value_type, alpha_l = 'l');
    BOOST_STATIC_CONSTANT(value_type, alpha_n = 'n');
    BOOST_STATIC_CONSTANT(value_type, alpha_r = 'r');
    BOOST_STATIC_CONSTANT(value_type, alpha_s = 's');
    BOOST_STATIC_CONSTANT(value_type, alpha_t = 't');
    BOOST_STATIC_CONSTANT(value_type, alpha_u = 'u');
    BOOST_STATIC_CONSTANT(value_type, alpha_bracket_open = '[');
    BOOST_STATIC_CONSTANT(value_type, alpha_reverse_solidus = '\\');
    BOOST_STATIC_CONSTANT(value_type, alpha_bracket_close = ']');
    BOOST_STATIC_CONSTANT(value_type, alpha_brace_open = '{');
    BOOST_STATIC_CONSTANT(value_type, alpha_brace_close = '}');

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
