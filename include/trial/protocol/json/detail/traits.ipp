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

#include <boost/type_traits.hpp>

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

inline int traits<char>::extra_bytes(value_type value) BOOST_NOEXCEPT
{
    switch (static_cast<boost::make_unsigned<value_type>::type>(value))
    {
    case 0xC0: case 0xC1: case 0xC2: case 0xC3:
    case 0xC4: case 0xC5: case 0xC6: case 0xC7:
    case 0xC8: case 0xC9: case 0xCA: case 0xCB:
    case 0xCC: case 0xCD: case 0xCE: case 0xCF:
    case 0xD0: case 0xD1: case 0xD2: case 0xD3:
    case 0xD4: case 0xD5: case 0xD6: case 0xD7:
    case 0xD8: case 0xD9: case 0xDA: case 0xDB:
    case 0xDC: case 0xDD: case 0xDE: case 0xDF:
        return 1;
    case 0xE0: case 0xE1: case 0xE2: case 0xE3:
    case 0xE4: case 0xE5: case 0xE6: case 0xE7:
    case 0xE8: case 0xE9: case 0xEA: case 0xEB:
    case 0xEC: case 0xED: case 0xEE: case 0xEF:
        return 2;
    case 0xF0: case 0xF1: case 0xF2: case 0xF3:
    case 0xF4: case 0xF5: case 0xF6: case 0xF7:
        return 3;
    case 0xF8: case 0xF9: case 0xFA: case 0xFB:
        return 4;
    case 0xFC: case 0xFD: case 0xFE: case 0xFF:
        return 5;
    default:
        return 0;
    }
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

} // namespace detail
} // namespace json
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_JSON_DETAIL_TRAITS_IPP
