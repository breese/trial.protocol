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

namespace detail
{

struct code
{
    enum value
    {
        end = 0,
        uninitialized,

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

        value_separator,
        name_separator,

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

} // namespace detail

struct code
{
    enum value
    {
        end = detail::code::end,
        error_unexpected_token = detail::code::error_unexpected_token,
        error_invalid_key = detail::code::error_invalid_key,
        error_invalid_value = detail::code::error_invalid_value,
        error_incompatible_type = detail::code::error_incompatible_type,
        error_unbalanced_end_array = detail::code::error_unbalanced_end_array,
        error_unbalanced_end_object = detail::code::error_unbalanced_end_object,
        error_expected_end_array = detail::code::error_expected_end_array,
        error_expected_end_object = detail::code::error_expected_end_object,

        null = detail::code::null,
        true_value = detail::code::true_value,
        false_value = detail::code::false_value,
        integer = detail::code::integer,
        real = detail::code::real,
        string = detail::code::string,

        begin_array = detail::code::begin_array,
        end_array = detail::code::end_array,
        begin_object = detail::code::begin_object,
        end_object = detail::code::end_object
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

static token::code::value convert(token::detail::code::value);

struct value_separator
{
    static const token::detail::code::value code = token::detail::code::value_separator;
};

struct name_separator
{
    static const token::detail::code::value code = token::detail::code::name_separator;
};

} // namespace detail

} // namespace token
} // namespace json
} // namespace protocol
} // namespace trial

#include <trial/protocol/json/detail/token.ipp>

#endif /* TRIAL_PROTOCOL_JSON_TOKEN_HPP */
