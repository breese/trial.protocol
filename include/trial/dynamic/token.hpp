#ifndef TRIAL_DYNAMIC_TOKEN_HPP
#define TRIAL_DYNAMIC_TOKEN_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2017 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

namespace trial
{
namespace dynamic
{
inline namespace token
{

struct code
{
    enum value
    {
        null,
        boolean,
        signed_char,
        unsigned_char,
        signed_short_integer,
        unsigned_short_integer,
        signed_integer,
        unsigned_integer,
        signed_long_integer,
        unsigned_long_integer,
        signed_long_long_integer,
        unsigned_long_long_integer,
        real,
        long_real,
        long_long_real,
        string,
        wstring,
        u16string,
        u32string,
        array,
        map,

        // Aliases
        float_number = real,
        double_number = long_real,
        long_double_number = long_long_real
    };
};

struct symbol
{
    enum value
    {
        null,
        boolean,
        integer,
        real,
        string,
        wstring,
        u16string,
        u32string,
        array,
        map
    };
};

} // namespace token
} // namespace dynamic
} // namespace trial

#endif // TRIAL_DYNAMIC_TOKEN_HPP
