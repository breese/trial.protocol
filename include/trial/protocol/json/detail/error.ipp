#ifndef TRIAL_PROTOCOL_JSON_DETAIL_ERROR_IPP
#define TRIAL_PROTOCOL_JSON_DETAIL_ERROR_IPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2015 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <string>
#include <boost/config.hpp>

namespace trial
{
namespace protocol
{
namespace json
{
namespace detail
{

class error_category : public std::error_category
{
public:
    const char *name() const BOOST_NOEXCEPT
    {
        return "trial.protocol.json";
    }

    std::string message(int value) const
    {
        switch (value)
        {
        case unexpected_token:
            return "unexpected token";

        case invalid_value:
            return "invalid value";

        case incompatible_type:
            return "incompatible type";

        case unbalanced_end_array:
            return "unbalanced end array bracket";

        case unbalanced_end_object:
            return "unbalanced end object bracket";

        case expected_end_array:
            return "expected end array bracket";

        case expected_end_object:
            return "expected end object bracket";

        case insufficient_tokens:
            return "algorithm used requires more tokens than available";
        }
        return "trial.protocol.json error";
    }
};

} // namespace detail

inline const std::error_category& error_category()
{
    static detail::error_category instance;
    return instance;
}

inline enum errc to_errc(token::code::value value)
{
    switch (value)
    {
    case token::code::error_unexpected_token:
        return unexpected_token;

    case token::code::error_invalid_key:
        return invalid_key;

    case token::code::error_invalid_value:
        return invalid_value;

    case token::code::error_incompatible_type:
        return incompatible_type;

    case token::code::error_unbalanced_end_array:
        return unbalanced_end_array;

    case token::code::error_unbalanced_end_object:
        return unbalanced_end_object;

    case token::code::error_expected_end_array:
        return expected_end_array;

    case token::code::error_expected_end_object:
        return expected_end_object;

    default:
        return no_error;
    }
}

} // namespace json
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_JSON_DETAIL_ERROR_IPP
