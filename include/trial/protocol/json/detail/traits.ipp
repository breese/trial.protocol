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

inline bool traits<char>::is_space(value_type value) BOOST_NOEXCEPT
{
    switch (value)
    {
    case 0x09: case 0x0A: case 0x0D: case 0x20:
        return true;
    default:
        return false;
    }
}

inline bool traits<char>::is_digit(value_type value) BOOST_NOEXCEPT
{
    switch (value)
    {
    case 0x30: case 0x31: case 0x32: case 0x33:
    case 0x34: case 0x35: case 0x36: case 0x37:
    case 0x38: case 0x39:
        return true;
    default:
        return false;
    }
}

inline bool traits<char>::is_hexdigit(value_type value) BOOST_NOEXCEPT
{
    switch (value)
    {
    case 0x30: case 0x31: case 0x32: case 0x33: // 0-9
    case 0x34: case 0x35: case 0x36: case 0x37:
    case 0x38: case 0x39:
    case 0x41: case 0x42: case 0x43: case 0x44: // A-F
    case 0x45: case 0x46:
    case 0x61: case 0x62: case 0x63: case 0x64: // a-f
    case 0x65: case 0x66:
        return true;
    default:
        return false;
    }
}

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

inline bool traits<char>::is_keyword(value_type value) BOOST_NOEXCEPT
{
    switch (value)
    {
    case 0x41: case 0x42: case 0x43: case 0x44: // A-Z
    case 0x45: case 0x46: case 0x47: case 0x48:
    case 0x49: case 0x4A: case 0x4B: case 0x4C:
    case 0x4D: case 0x4E: case 0x4F: case 0x50:
    case 0x51: case 0x52: case 0x53: case 0x54:
    case 0x55: case 0x56: case 0x57: case 0x58:
    case 0x59: case 0x5A:
    case 0x61: case 0x62: case 0x63: case 0x64: // a-z
    case 0x65: case 0x66: case 0x67: case 0x68:
    case 0x69: case 0x6A: case 0x6B: case 0x6C:
    case 0x6D: case 0x6E: case 0x6F: case 0x70:
    case 0x71: case 0x72: case 0x73: case 0x74:
    case 0x75: case 0x76: case 0x77: case 0x78:
    case 0x79: case 0x7A:
        return true;
    default:
        return false;
    }
}

inline traits<char>::size_type traits<char>::extra_bytes(value_type value) BOOST_NOEXCEPT
{
    using unsigned_value_type = std::make_unsigned<value_type>::type;
    const unsigned_value_type v = static_cast<unsigned_value_type>(value);

    if (v < 0xC0)
        return 0;
    else if (v < 0xE0)
        return 1;
    else if (v < 0xF0)
        return 2;
    else if (v < 0xF8)
        return 3;
    else if (v < 0xFC)
        return 4;
    else
        return 5;
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

inline bool traits<unsigned char>::is_space(value_type value) BOOST_NOEXCEPT
{
    switch (value)
    {
    case 0x09: case 0x0A: case 0x0D: case 0x20:
        return true;
    default:
        return false;
    }
}

inline bool traits<unsigned char>::is_digit(value_type value) BOOST_NOEXCEPT
{
    switch (value)
    {
    case 0x30: case 0x31: case 0x32: case 0x33:
    case 0x34: case 0x35: case 0x36: case 0x37:
    case 0x38: case 0x39:
        return true;
    default:
        return false;
    }
}

inline bool traits<unsigned char>::is_hexdigit(value_type value) BOOST_NOEXCEPT
{
    switch (value)
    {
    case 0x30: case 0x31: case 0x32: case 0x33: // 0-9
    case 0x34: case 0x35: case 0x36: case 0x37:
    case 0x38: case 0x39:
    case 0x41: case 0x42: case 0x43: case 0x44: // A-F
    case 0x45: case 0x46:
    case 0x61: case 0x62: case 0x63: case 0x64: // a-f
    case 0x65: case 0x66:
        return true;
    default:
        return false;
    }
}

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

inline bool traits<unsigned char>::is_keyword(value_type value) BOOST_NOEXCEPT
{
    switch (value)
    {
    case 0x41: case 0x42: case 0x43: case 0x44: // A-Z
    case 0x45: case 0x46: case 0x47: case 0x48:
    case 0x49: case 0x4A: case 0x4B: case 0x4C:
    case 0x4D: case 0x4E: case 0x4F: case 0x50:
    case 0x51: case 0x52: case 0x53: case 0x54:
    case 0x55: case 0x56: case 0x57: case 0x58:
    case 0x59: case 0x5A:
    case 0x61: case 0x62: case 0x63: case 0x64: // a-z
    case 0x65: case 0x66: case 0x67: case 0x68:
    case 0x69: case 0x6A: case 0x6B: case 0x6C:
    case 0x6D: case 0x6E: case 0x6F: case 0x70:
    case 0x71: case 0x72: case 0x73: case 0x74:
    case 0x75: case 0x76: case 0x77: case 0x78:
    case 0x79: case 0x7A:
        return true;
    default:
        return false;
    }
}

inline traits<unsigned char>::size_type traits<unsigned char>::extra_bytes(value_type value) BOOST_NOEXCEPT
{
    if (value < 0xC0)
        return 0;
    else if (value < 0xE0)
        return 1;
    else if (value < 0xF0)
        return 2;
    else if (value < 0xF8)
        return 3;
    else if (value < 0xFC)
        return 4;
    else
        return 5;
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

inline const std::basic_string<unsigned char>& traits<unsigned char>::false_text() BOOST_NOEXCEPT
{
    static std::basic_string<value_type> text(reinterpret_cast<const value_type *>("false"));
    return text;
}

inline const std::basic_string<unsigned char>& traits<unsigned char>::true_text() BOOST_NOEXCEPT
{
    static std::basic_string<value_type> text(reinterpret_cast<const value_type *>("true"));
    return text;
}

inline const std::basic_string<unsigned char>& traits<unsigned char>::null_text() BOOST_NOEXCEPT
{
    static std::basic_string<value_type> text(reinterpret_cast<const value_type *>("null"));
    return text;
}

} // namespace detail
} // namespace json
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_JSON_DETAIL_TRAITS_IPP
