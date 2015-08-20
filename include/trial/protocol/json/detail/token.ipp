#ifndef TRIAL_PROTOCOL_JSON_TOKEN_IPP
#define TRIAL_PROTOCOL_JSON_TOKEN_IPP

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

inline type::value type::convert(token::value value)
{
    switch (value)
    {
    case token::end:
        return type::end;

    case token::error_not_implemented:
    case token::error_unexpected_token:
    case token::error_invalid_key:
    case token::error_invalid_value:
    case token::error_incompatible_type:
    case token::error_unbalanced_end_array:
    case token::error_unbalanced_end_object:
    case token::error_expected_end_array:
    case token::error_expected_end_object:
        return type::error;

    case token::null:
        return type::null;

    case token::true_value:
    case token::false_value:
        return type::boolean;

    case token::integer:
        return type::integer;

    case token::floating:
        return type::floating;

    case token::string:
        return type::string;

    case token::begin_array:
        return type::begin_array;

    case token::end_array:
        return type::end_array;

    case token::begin_object:
        return type::begin_object;

    case token::end_object:
        return type::end_object;

    case token::value_separator:
    case token::name_separator:
        return type::separator;
    }
    return type::error;
}

inline category::value category::convert(type::value value)
{
    switch (value)
    {
    case type::end:
    case type::error:
        return category::status;

    case type::null:
        return category::nullable;

    case type::boolean:
    case type::integer:
    case type::floating:
    case type::string:
        return category::data;

    case type::begin_array:
    case type::end_array:
    case type::begin_object:
    case type::end_object:
    case type::separator:
        return category::structural;
    }

    return category::status;
}

inline category::value category::convert(token::value value)
{
    return category::convert(type::convert(value));
}

} // namespace json
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_JSON_TOKEN_IPP
