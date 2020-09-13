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
namespace token
{

//-----------------------------------------------------------------------------
// Token constants
//-----------------------------------------------------------------------------

inline symbol::value symbol::convert(code::value value)
{
    switch (value)
    {
    case code::end:
        return symbol::end;

    case code::uninitialized:
    case code::shifted:
    case code::error_name_separator:
    case code::error_value_separator:
    case code::error_unexpected_token:
    case code::error_invalid_key:
    case code::error_invalid_value:
    case code::error_incompatible_type:
    case code::error_unbalanced_end_array:
    case code::error_unbalanced_end_object:
    case code::error_expected_end_array:
    case code::error_expected_end_object:
        return symbol::error;

    case code::null:
        return symbol::null;

    case code::true_value:
    case code::false_value:
        return symbol::boolean;

    case code::integer:
        return symbol::integer;

    case code::real:
        return symbol::real;

    case code::string:
        return symbol::string;

    case code::begin_array:
        return symbol::begin_array;

    case code::end_array:
        return symbol::end_array;

    case code::begin_object:
        return symbol::begin_object;

    case code::end_object:
        return symbol::end_object;
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
    case symbol::real:
    case symbol::string:
        return category::data;

    case symbol::begin_array:
    case symbol::end_array:
    case symbol::begin_object:
    case symbol::end_object:
        return category::structural;
    }

    return category::status;
}

inline category::value category::convert(code::value value)
{
    return category::convert(symbol::convert(value));
}

} // namespace token
} // namespace json
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_JSON_TOKEN_IPP
