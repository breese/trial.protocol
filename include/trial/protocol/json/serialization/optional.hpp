#ifndef TRIAL_PROTOCOL_JSON_SERIALIZATION_OPTIONAL_HPP
#define TRIAL_PROTOCOL_JSON_SERIALIZATION_OPTIONAL_HPP

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
#include <trial/protocol/serialization/optional.hpp>
#include <trial/protocol/json/token.hpp>

namespace trial
{
namespace protocol
{
namespace serialization
{

template <typename T>
struct save_overloader< protocol::json::oarchive,
                        typename boost::optional<T> >
{
    static void save(protocol::json::oarchive& ar,
                     const boost::optional<T>& data,
                     const unsigned int /* protocol_version */)
    {
        if (data)
        {
            ar.save_override(*data);
        }
        else
        {
            ar.template save<json::token::null>();
        }
    }
};

template <typename T>
struct load_overloader< protocol::json::iarchive,
                        typename boost::optional<T> >
{
    static void load(protocol::json::iarchive& ar,
                     boost::optional<T>& data,
                     const unsigned int /* protocol_version */)
    {
        if (ar.code() == protocol::json::token::code::null)
        {
            ar.template load<json::token::null>();
            data = boost::none;
        }
        else
        {
            T value; // FIXME: Replace with InPlaceFactory
            ar.load_override(value);
            data = value;
        }
    }
};

} // namespace serialization
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_JSON_SERIALIZATION_OPTIONAL_HPP
