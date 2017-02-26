#ifndef TRIAL_PROTOCOL_DYNAMIC_ERROR_IPP
#define TRIAL_PROTOCOL_DYNAMIC_ERROR_IPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2017 Bjorn Reese <breese@users.sourceforge.net>
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
namespace dynamic
{

namespace detail
{

class error_category : public std::error_category
{
public:
    const char *name() const BOOST_NOEXCEPT
    {
        return "trial.protocol.dynamic";
    }

    std::string message(int value) const
    {
        switch (value)
        {
        case incompatible_type:
            return "incompatible type";
        }
        return "trial.protocol.dynamic error";
    }
};

} // namespace detail

inline const std::error_category& error_category()
{
    static detail::error_category instance;
    return instance;
}

} // namespace dynamic
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_DYNAMIC_ERROR_IPP
