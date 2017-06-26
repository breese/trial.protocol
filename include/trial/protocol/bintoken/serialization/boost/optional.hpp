#ifndef TRIAL_PROTOCOL_BINTOKEN_SERIALIZATION_BOOST_OPTIONAL_HPP
#define TRIAL_PROTOCOL_BINTOKEN_SERIALIZATION_BOOST_OPTIONAL_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2015 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <trial/protocol/bintoken/serialization/serialization.hpp>
#include <trial/protocol/serialization/boost/optional.hpp>

namespace trial
{
namespace protocol
{
namespace serialization
{

template <typename T>
struct save_overloader< protocol::bintoken::oarchive,
                        typename boost::optional<T> >
{
    static void save(protocol::bintoken::oarchive& ar,
                     const boost::optional<T>& data,
                     const unsigned int protocol_version)
    {
        if (data)
        {
            ar.save_override(*data, protocol_version);
        }
        else
        {
            ar.save<bintoken::token::null>();
        }
    }
};

template <typename T>
struct load_overloader< protocol::bintoken::iarchive,
                        typename boost::optional<T> >
{
    static void load(protocol::bintoken::iarchive& ar,
                     boost::optional<T>& data,
                     const unsigned int protocol_version)
    {
        if (ar.at<bintoken::token::null>())
        {
            data = boost::none;
            ar.load<bintoken::token::null>();
        }
        else
        {
            data = T(); // Engage
            ar.load_override(*data, protocol_version);
        }
    }
};

} // namespace serialization
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_BINTOKEN_SERIALIZATION_BOOST_OPTIONAL_HPP
