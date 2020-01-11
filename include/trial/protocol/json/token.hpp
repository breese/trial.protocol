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
namespace token
{

//-----------------------------------------------------------------------------
// Token constants
//-----------------------------------------------------------------------------

struct code
{
    enum value
    {
        // Some parts of the code depends on the ordering

        end = 0,
        uninitialized,
        error_value_separator,
        error_name_separator,

        null,
        true_value,
        false_value,
        integer,
        real,
        string,

        begin_array,
        end_array,
        begin_object,
        end_object,

        error_unexpected_token = -1,
        error_invalid_key = -2,
        error_invalid_value = -3,
        error_incompatible_type = -4,
        error_unbalanced_end_array = -5,
        error_unbalanced_end_object = -6,
        error_expected_end_array = -7,
        error_expected_end_object = -8
    };
};

struct symbol
{
    enum value
    {
        end,
        error,

        null,
        boolean,
        integer,
        real,
        string,

        begin_array,
        end_array,
        begin_object,
        end_object
    };

    static value convert(code::value);
};

struct category
{
    enum value
    {
        status,
        nullable,
        data,
        structural
    };

    static value convert(code::value);
    static value convert(symbol::value);
};

//-----------------------------------------------------------------------------
// Token tags
//-----------------------------------------------------------------------------

struct null
{
    static const token::code::value code = token::code::null;
};

struct begin_array
{
    static const token::code::value code = token::code::begin_array;
};

struct end_array
{
    static const token::code::value code = token::code::end_array;
};

struct begin_object
{
    static const token::code::value code = token::code::begin_object;
};

struct end_object
{
    static const token::code::value code = token::code::end_object;
};

namespace detail
{

struct value_separator
{
    static const token::code::value code = token::code::error_value_separator;
};

struct name_separator
{
    static const token::code::value code = token::code::error_name_separator;
};

} // namespace detail

} // namespace token
} // namespace json
} // namespace protocol
} // namespace trial

#include <trial/protocol/json/detail/token.ipp>

#endif /* TRIAL_PROTOCOL_JSON_TOKEN_HPP */
