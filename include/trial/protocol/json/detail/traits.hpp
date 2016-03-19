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
};

//-----------------------------------------------------------------------------
// char specialization
//-----------------------------------------------------------------------------

template <>
class traits<char>
{
public:
    typedef char value_type;
    typedef std::size_t size_type;

    static bool is_space(value_type value) BOOST_NOEXCEPT;
    static bool is_digit(value_type value) BOOST_NOEXCEPT;
    static bool is_hexdigit(value_type value) BOOST_NOEXCEPT;
    static bool is_keyword(value_type value) BOOST_NOEXCEPT;
    static size_type extra_bytes(value_type value) BOOST_NOEXCEPT;
    static int to_int(value_type value) BOOST_NOEXCEPT;

    static const std::basic_string<value_type>& false_text() BOOST_NOEXCEPT;
    static const std::basic_string<value_type>& true_text() BOOST_NOEXCEPT;
    static const std::basic_string<value_type>& null_text() BOOST_NOEXCEPT;

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
    BOOST_STATIC_CONSTANT(value_type, alpha_A = 'A');
    BOOST_STATIC_CONSTANT(value_type, alpha_E = 'E');
    BOOST_STATIC_CONSTANT(value_type, alpha_a = 'a');
    BOOST_STATIC_CONSTANT(value_type, alpha_b = 'b');
    BOOST_STATIC_CONSTANT(value_type, alpha_e = 'e');
    BOOST_STATIC_CONSTANT(value_type, alpha_f = 'f');
    BOOST_STATIC_CONSTANT(value_type, alpha_n = 'n');
    BOOST_STATIC_CONSTANT(value_type, alpha_r = 'r');
    BOOST_STATIC_CONSTANT(value_type, alpha_t = 't');
    BOOST_STATIC_CONSTANT(value_type, alpha_u = 'u');
    BOOST_STATIC_CONSTANT(value_type, alpha_bracket_open = '[');
    BOOST_STATIC_CONSTANT(value_type, alpha_reverse_solidus = '\\');
    BOOST_STATIC_CONSTANT(value_type, alpha_bracket_close = ']');
    BOOST_STATIC_CONSTANT(value_type, alpha_brace_open = '{');
    BOOST_STATIC_CONSTANT(value_type, alpha_brace_close = '}');

private:
    static bool is_hex_upper(value_type value) BOOST_NOEXCEPT;
    static bool is_hex_lower(value_type value) BOOST_NOEXCEPT;
};

//-----------------------------------------------------------------------------
// unsigned char specialization
//-----------------------------------------------------------------------------

template <>
class traits<unsigned char>
{
public:
    typedef unsigned char value_type;
    typedef std::size_t size_type;

    static bool is_space(value_type value) BOOST_NOEXCEPT;
    static bool is_digit(value_type value) BOOST_NOEXCEPT;
    static bool is_hexdigit(value_type value) BOOST_NOEXCEPT;
    static bool is_keyword(value_type value) BOOST_NOEXCEPT;
    static size_type extra_bytes(value_type value) BOOST_NOEXCEPT;
    static int to_int(value_type value) BOOST_NOEXCEPT;

    static const std::basic_string<value_type>& false_text() BOOST_NOEXCEPT;
    static const std::basic_string<value_type>& true_text() BOOST_NOEXCEPT;
    static const std::basic_string<value_type>& null_text() BOOST_NOEXCEPT;

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
    BOOST_STATIC_CONSTANT(value_type, alpha_A = 'A');
    BOOST_STATIC_CONSTANT(value_type, alpha_E = 'E');
    BOOST_STATIC_CONSTANT(value_type, alpha_a = 'a');
    BOOST_STATIC_CONSTANT(value_type, alpha_b = 'b');
    BOOST_STATIC_CONSTANT(value_type, alpha_e = 'e');
    BOOST_STATIC_CONSTANT(value_type, alpha_f = 'f');
    BOOST_STATIC_CONSTANT(value_type, alpha_n = 'n');
    BOOST_STATIC_CONSTANT(value_type, alpha_r = 'r');
    BOOST_STATIC_CONSTANT(value_type, alpha_t = 't');
    BOOST_STATIC_CONSTANT(value_type, alpha_u = 'u');
    BOOST_STATIC_CONSTANT(value_type, alpha_bracket_open = '[');
    BOOST_STATIC_CONSTANT(value_type, alpha_reverse_solidus = '\\');
    BOOST_STATIC_CONSTANT(value_type, alpha_bracket_close = ']');
    BOOST_STATIC_CONSTANT(value_type, alpha_brace_open = '{');
    BOOST_STATIC_CONSTANT(value_type, alpha_brace_close = '}');

private:
    static bool is_hex_upper(value_type value) BOOST_NOEXCEPT;
    static bool is_hex_lower(value_type value) BOOST_NOEXCEPT;
};

} // namespace detail
} // namespace json
} // namespace protocol
} // namespace trial

#include <trial/protocol/json/detail/traits.ipp>

#endif // TRIAL_PROTOCOL_JSON_DETAIL_TRAITS_HPP
