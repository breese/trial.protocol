#ifndef TRIAL_PROTOCOL_JSON_SERIALIZATION_STD_STRING_HPP
#define TRIAL_PROTOCOL_JSON_SERIALIZATION_STD_STRING_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2015 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <trial/protocol/json/serialization/serialization.hpp>
#include <trial/protocol/serialization/std/string.hpp>

namespace trial
{
namespace protocol
{
namespace serialization
{

template <>
struct save_overloader<protocol::json::oarchive, std::string>
{
    static void save(protocol::json::oarchive& ar,
                     const std::string& data,
                     const unsigned int)
    {
        ar.save(data);
    }
};

template <>
struct load_overloader<protocol::json::iarchive, std::string>
{
    static void load(protocol::json::iarchive& ar,
                     std::string& data,
                     const unsigned int)
    {
        ar.load(data);
    }
};

} // namespace serialization
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_JSON_SERIALIZATION_STD_STRING_HPP
