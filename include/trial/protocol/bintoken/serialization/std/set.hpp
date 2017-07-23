#ifndef TRIAL_PROTOCOL_BINTOKEN_SERIALIZATION_STD_SET_HPP
#define TRIAL_PROTOCOL_BINTOKEN_SERIALIZATION_STD_SET_HPP

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
#include <trial/protocol/bintoken/serialization/boost/optional.hpp>
#include <trial/protocol/core/serialization/std/set.hpp>

namespace trial
{
namespace protocol
{
namespace serialization
{

template <typename Key, typename Compare, typename Allocator>
struct save_overloader< protocol::bintoken::oarchive,
                        typename std::set<Key, Compare, Allocator> >
{
    static void save(protocol::bintoken::oarchive& ar,
                     const std::set<Key, Compare, Allocator>& data,
                     const unsigned int protocol_version)
    {
        ar.save<bintoken::token::begin_array>();
        ar.save<bintoken::token::null>();
        for (typename std::set<Key, Compare, Allocator>::const_iterator it = data.begin();
             it != data.end();
             ++it)
        {
            ar.save_override(*it, protocol_version);
        }
        ar.save<bintoken::token::end_array>();
    }
};

template <typename Key, typename Compare, typename Allocator>
struct load_overloader< protocol::bintoken::iarchive,
                        typename std::set<Key, Compare, Allocator> >
{
    static void load(protocol::bintoken::iarchive& ar,
                     std::set<Key, Compare, Allocator>& data,
                     const unsigned int protocol_version)
    {
        ar.load<bintoken::token::begin_array>();

        boost::optional<std::size_t> count;
        ar.load_override(count, protocol_version);

        while (!ar.at<bintoken::token::end_array>())
        {
            Key value;
            ar.load_override(value, protocol_version);
            data.insert(value);
        }
        ar.load<bintoken::token::end_array>();
    }
};

} // namespace serialization
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_BINTOKEN_SERIALIZATION_STD_SET_HPP
