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

//-----------------------------------------------------------------------------
// char specialization
//-----------------------------------------------------------------------------

inline bool traits<char>::is_hex_upper(value_type value) BOOST_NOEXCEPT
{
    switch (value)
    {
    case 0x41: case 0x42: case 0x43: case 0x44: // A-F
    case 0x45: case 0x46:
        return true;
    default:
        return false;
    }
}

inline bool traits<char>::is_hex_lower(value_type value) BOOST_NOEXCEPT
{
    switch (value)
    {
    case 0x61: case 0x62: case 0x63: case 0x64: // a-f
    case 0x65: case 0x66:
        return true;
    default:
        return false;
    }
}

inline traits_category traits<char>::to_category(value_type value) BOOST_NOEXCEPT
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

inline int traits<char>::to_int(value_type value) BOOST_NOEXCEPT
{
    if (is_digit(value))
        return value - alpha_0;
    if (is_hex_upper(value))
        return value - alpha_A + 10;
    if (is_hex_lower(value))
        return value - alpha_a + 10;
    assert(false);
    return 0;
}

inline auto traits<char>::skip_narrow(const value_type *marker) noexcept -> const value_type *
{
    while (traits<value_type>::to_category(*marker) == traits_category::narrow)
    {
        ++marker;
    }
    return marker;
}

inline const std::basic_string<char>& traits<char>::false_text() BOOST_NOEXCEPT
{
    static std::basic_string<value_type> text("false");
    return text;
}

inline const std::basic_string<char>& traits<char>::true_text() BOOST_NOEXCEPT
{
    static std::basic_string<value_type> text("true");
    return text;
}

inline const std::basic_string<char>& traits<char>::null_text() BOOST_NOEXCEPT
{
    static std::basic_string<value_type> text("null");
    return text;
}

//-----------------------------------------------------------------------------
// unsigned char specialization
//-----------------------------------------------------------------------------

inline bool traits<unsigned char>::is_hex_upper(value_type value) BOOST_NOEXCEPT
{
    switch (value)
    {
    case 0x41: case 0x42: case 0x43: case 0x44: // A-F
    case 0x45: case 0x46:
        return true;
    default:
        return false;
    }
}

inline bool traits<unsigned char>::is_hex_lower(value_type value) BOOST_NOEXCEPT
{
    switch (value)
    {
    case 0x61: case 0x62: case 0x63: case 0x64: // a-f
    case 0x65: case 0x66:
        return true;
    default:
        return false;
    }
}

inline traits_category traits<unsigned char>::to_category(value_type value) BOOST_NOEXCEPT
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
    return data[value];
}

inline int traits<unsigned char>::to_int(value_type value) BOOST_NOEXCEPT
{
    if (is_digit(value))
        return value - alpha_0;
    if (is_hex_upper(value))
        return value - alpha_A + 10;
    if (is_hex_lower(value))
        return value - alpha_a + 10;
    assert(false);
    return 0;
}

inline auto traits<unsigned char>::skip_narrow(const value_type *marker) noexcept -> const value_type *
{
    while (traits<value_type>::to_category(*marker) == traits_category::narrow)
    {
        ++marker;
    }
    return marker;
}

inline auto traits<unsigned char>::false_text() BOOST_NOEXCEPT -> const string_type&
{
    static string_type text(reinterpret_cast<const value_type *>("false"));
    return text;
}

inline auto traits<unsigned char>::true_text() BOOST_NOEXCEPT -> const string_type&
{
    static string_type text(reinterpret_cast<const value_type *>("true"));
    return text;
}

inline auto traits<unsigned char>::null_text() BOOST_NOEXCEPT -> const string_type&
{
    static string_type text(reinterpret_cast<const value_type *>("null"));
    return text;
}

} // namespace detail
} // namespace json
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_JSON_DETAIL_TRAITS_IPP
