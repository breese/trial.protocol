#ifndef TRIAL_PROTOCOL_DYNAMIC_TOKEN_HPP
#define TRIAL_PROTOCOL_DYNAMIC_TOKEN_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2017 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <cstddef>

namespace trial
{
namespace protocol
{
namespace dynamic
{
namespace token
{

struct code
{
    enum value
    {
        null,
        boolean,
        signed_short_integer,
        unsigned_short_integer,
        signed_integer,
        unsigned_integer,
        signed_long_integer,
        unsigned_long_integer,
        signed_long_long_integer,
        unsigned_long_long_integer,
        float_number,
        double_number,
        long_double_number,
        string,
        array,
        map
    };
};

struct symbol
{
    enum value
    {
        null,
        boolean,
        integer,
        number,
        string,
        array,
        map
    };

    static symbol::value convert(code::value);
};

} // namespace token
} // namespace dynamic
} // namespace protocol
} // namespace trial

#include <trial/protocol/dynamic/detail/token.ipp>

#endif // TRIAL_PROTOCOL_DYNAMIC_TOKEN_HPP
