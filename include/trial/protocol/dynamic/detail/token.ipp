#ifndef TRIAL_PROTOCOL_DYNAMIC_TOKEN_IPP
#define TRIAL_PROTOCOL_DYNAMIC_TOKEN_IPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2017 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <trial/protocol/core/detail/config.hpp>

namespace trial
{
namespace protocol
{
namespace dynamic
{
namespace token
{

inline symbol::value symbol::convert(code::value value)
{
    switch (value)
    {
    case code::null:
        return symbol::null;
    case code::boolean:
        return symbol::boolean;
    case code::signed_char:
    case code::unsigned_char:
    case code::signed_short_integer:
    case code::unsigned_short_integer:
    case code::signed_integer:
    case code::unsigned_integer:
    case code::signed_long_integer:
    case code::unsigned_long_integer:
    case code::signed_long_long_integer:
    case code::unsigned_long_long_integer:
        return symbol::integer;
    case code::float_number:
    case code::double_number:
    case code::long_double_number:
        return symbol::number;
    case code::string:
        return symbol::string;
    case code::array:
        return symbol::array;
    case code::map:
        return symbol::map;
    }
    TRIAL_PROTOCOL_UNREACHABLE();
}

} // namespace token
} // namespace dynamic
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_DYNAMIC_TOKEN_IPP
