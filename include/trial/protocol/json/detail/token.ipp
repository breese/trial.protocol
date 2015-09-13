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

inline symbol::value symbol::convert(token::value value)
{
    switch (value)
    {
    case token::end:
        return symbol::end;

    case token::error_not_implemented:
    case token::error_unexpected_token:
    case token::error_invalid_key:
    case token::error_invalid_value:
    case token::error_incompatible_type:
    case token::error_unbalanced_end_array:
    case token::error_unbalanced_end_object:
    case token::error_expected_end_array:
    case token::error_expected_end_object:
        return symbol::error;

    case token::null:
        return symbol::null;

    case token::true_value:
    case token::false_value:
        return symbol::boolean;

    case token::integer:
        return symbol::integer;

    case token::floating:
        return symbol::floating;

    case token::string:
        return symbol::string;

    case token::begin_array:
        return symbol::begin_array;

    case token::end_array:
        return symbol::end_array;

    case token::begin_object:
        return symbol::begin_object;

    case token::end_object:
        return symbol::end_object;

    case token::value_separator:
    case token::name_separator:
        return symbol::separator;
    }
    return symbol::error;
}

inline category::value category::convert(symbol::value value)
{
    switch (value)
    {
    case symbol::end:
    case symbol::error:
        return category::status;

    case symbol::null:
        return category::nullable;

    case symbol::boolean:
    case symbol::integer:
    case symbol::floating:
    case symbol::string:
        return category::data;

    case symbol::begin_array:
    case symbol::end_array:
    case symbol::begin_object:
    case symbol::end_object:
    case symbol::separator:
        return category::structural;
    }

    return category::status;
}

inline category::value category::convert(token::value value)
{
    return category::convert(symbol::convert(value));
}

} // namespace json
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_JSON_TOKEN_IPP
