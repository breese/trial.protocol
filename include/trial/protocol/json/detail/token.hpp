#ifndef TRIAL_PROTOCOL_JSON_DETAIL_TOKEN_HPP
#define TRIAL_PROTOCOL_JSON_DETAIL_TOKEN_HPP

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
namespace detail
{

struct token
{
    enum value
    {
        eof,
        error,

        null_value,
        true_value,
        false_value,

        integer,
        floating,
        string,

        begin_array,
        end_array,
        begin_object,
        end_object,

        value_separator,
        name_separator
    };
};

} // namespace detail
} // namespace json
} // namespace protocol
} // namespace trial

#endif /* TRIAL_PROTOCOL_JSON_DETAIL_TOKEN_HPP */
