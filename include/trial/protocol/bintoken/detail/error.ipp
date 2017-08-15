#ifndef TRIAL_PROTOCOL_BINTOKEN_ERROR_IPP
#define TRIAL_PROTOCOL_BINTOKEN_ERROR_IPP

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
namespace bintoken
{

namespace detail
{

class error_category : public std::error_category
{
public:
    const char *name() const BOOST_NOEXCEPT
    {
        return "trial.protocol.bintoken";
    }

    std::string message(int value) const
    {
        switch (value)
        {
        case unknown_token:
            return "unknown token";

        case unexpected_token:
            return "unexpected token";

        case negative_length:
            return "negative length";

        case overflow:
            return "overflow";

        case invalid_value:
            return "invalid value";

        case incompatible_type:
            return "incompatible type";

        case expected_end_record:
            return "expected end record bracket";

        case expected_end_array:
            return "expected end array bracket";

        case expected_end_assoc_array:
            return "expected end assoc array bracket";
        }
        return "trial.protocol.bintoken error";
    }
};

} // namespace detail

inline const std::error_category& error_category()
{
    static detail::error_category instance;
    return instance;
}
} // namespace bintoken
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_BINTOKEN_ERROR_IPP
