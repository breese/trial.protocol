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
        error_not_implemented,
        error_unexpected_token,
        error_invalid_key,
        error_invalid_value,
        error_incompatible_type,
        error_unbalanced_end_array,
        error_unbalanced_end_object,
        error_expected_end_array,
        error_expected_end_object,

        null,
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

struct type
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

        begin_array,
        end_array,
        begin_object,
        end_object,

        separator
    };

    static value convert(token::value);
};

struct category
{
    enum value
    {
        status,
        nullable,
        data,
        structural,
    };

    static value convert(token::value);
    static value convert(type::value);
};

} // namespace json
} // namespace protocol
} // namespace trial

#include <trial/protocol/json/detail/token.ipp>

#endif /* TRIAL_PROTOCOL_JSON_TOKEN_HPP */
