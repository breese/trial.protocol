#ifndef TRIAL_DYNAMIC_VARIABLE_IO_HPP
#define TRIAL_DYNAMIC_VARIABLE_IO_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2017 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <ostream>
#include <trial/protocol/buffer/ostream.hpp>
#include <trial/protocol/json/serialization.hpp>
#include <trial/dynamic/variable.hpp>

namespace trial
{
namespace dynamic
{

inline std::ostream& operator<< (std::ostream& stream, const variable& value)
{
    protocol::json::oarchive archive(stream);
    archive << value;
    return stream;
}

} // namespace dynamic
} // namespace trial

#endif // TRIAL_DYNAMIC_VARIABLE_IO_HPP
