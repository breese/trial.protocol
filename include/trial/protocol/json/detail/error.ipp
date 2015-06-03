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

namespace trial
{
namespace protocol
{
namespace json
{
namespace detail
{

class error_category : public boost::system::error_category
{
public:
    const char *name() const BOOST_SYSTEM_NOEXCEPT
    {
        return "trial.protocol.json";
    }

    std::string message(int value) const
    {
        switch (value)
        {
        case not_implemented:
            return "not implemented";

        case unexpected_token:
            return "unexpected token";

        case invalid_value:
            return "invalid value";

        case unbalanced_array_end_bracket:
            return "unbalanced array end bracket";

        case unbalanced_object_end_bracket:
            return "unbalanced object end bracket";

        case expected_array_end_bracket:
            return "expected array end bracket";

        case expected_object_end_bracket:
            return "expected object end bracket";
        }
        return "trial.protocol.json error";
    }
};

} // namespace detail

inline const boost::system::error_category& error_category()
{
    static detail::error_category instance;
    return instance;
}

} // namespace json
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_JSON_DETAIL_ERROR_IPP
