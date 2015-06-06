#ifndef TRIAL_PROTOCOL_JSON_TOKEN_HPP
#define TRIAL_PROTOCOL_JSON_TOKEN_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2015 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

namespace trial
{
namespace protocol
{
namespace json
{

struct token
{
    enum value
    {
        end,
        error,

        null,
        boolean,
        integer,
        floating,
        string,

        array_open,
        array_close,
        object_open,
        object_close
    };
};

} // namespace json
} // namespace protocol
} // namespace trial

#endif /* TRIAL_PROTOCOL_JSON_TOKEN_HPP */
