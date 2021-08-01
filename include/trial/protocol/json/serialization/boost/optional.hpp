#ifndef TRIAL_PROTOCOL_JSON_SERIALIZATION_BOOST_OPTIONAL_HPP
#define TRIAL_PROTOCOL_JSON_SERIALIZATION_BOOST_OPTIONAL_HPP

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
#include <trial/protocol/core/serialization/boost/optional.hpp>
#include <trial/protocol/json/token.hpp>

namespace trial
{
namespace protocol
{
namespace serialization
{

template <typename CharT, typename T>
struct save_overloader< protocol::json::basic_oarchive<CharT>,
                        typename boost::optional<T> >
{
    static void save(protocol::json::basic_oarchive<CharT>& ar,
                     const boost::optional<T>& data,
                     const unsigned int protocol_version)
    {
        if (data)
        {
            ar.save_override(*data, protocol_version);
        }
        else
        {
            ar.template save<json::token::null>();
        }
    }
};

template <typename Reader, typename T>
struct load_overloader< protocol::json::basic_iarchive<Reader>,
                        typename boost::optional<T> >
{
    static void load(protocol::json::basic_iarchive<Reader>& ar,
                     boost::optional<T>& data,
                     const unsigned int protocol_version)
    {
        if (ar.code() == protocol::json::token::code::null)
        {
            ar.template load<json::token::null>();
            data = boost::none;
        }
        else
        {
            T value; // FIXME: Replace with InPlaceFactory
            ar.load_override(value, protocol_version);
            data = value;
        }
    }
};

} // namespace serialization
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_JSON_SERIALIZATION_BOOST_OPTIONAL_HPP
