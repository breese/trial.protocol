#ifndef TRIAL_PROTOCOL_TRANSENC_SERIALIZATION_BOOST_OPTIONAL_HPP
#define TRIAL_PROTOCOL_TRANSENC_SERIALIZATION_BOOST_OPTIONAL_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2015 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <trial/protocol/transenc/serialization/serialization.hpp>
#include <trial/protocol/serialization/boost/optional.hpp>

namespace trial
{
namespace protocol
{
namespace serialization
{

template <typename T>
struct save_overloader< protocol::transenc::oarchive,
                        typename boost::optional<T> >
{
    static void save(protocol::transenc::oarchive& ar,
                     const boost::optional<T>& data,
                     const unsigned int)
    {
        if (data)
        {
            ar.save_override(*data);
        }
        else
        {
            ar.save<transenc::token::null>();
        }
    }
};

template <typename T>
struct load_overloader< protocol::transenc::iarchive,
                        typename boost::optional<T> >
{
    static void load(protocol::transenc::iarchive& ar,
                     boost::optional<T>& data,
                     const unsigned int)
    {
        if (ar.at<transenc::token::null>())
        {
            data = boost::none;
            ar.load<transenc::token::null>();
        }
        else
        {
            data = T(); // Engage
            ar.load_override(*data);
        }
    }
};

} // namespace serialization
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_TRANSENC_SERIALIZATION_BOOST_OPTIONAL_HPP
