#ifndef TRIAL_PROTOCOL_BINTOKEN_SERIALIZATION_STD_MAP_HPP
#define TRIAL_PROTOCOL_BINTOKEN_SERIALIZATION_STD_MAP_HPP

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
#include <trial/protocol/bintoken/serialization/std/pair.hpp>
#include <trial/protocol/bintoken/serialization/boost/optional.hpp>
#include <trial/protocol/serialization/std/map.hpp>

namespace trial
{
namespace protocol
{
namespace serialization
{

template <typename Key, typename T, typename Compare, typename Allocator>
struct save_overloader< protocol::bintoken::oarchive,
                        typename std::map<Key, T, Compare, Allocator> >
{
    static void save(protocol::bintoken::oarchive& ar,
                     const std::map<Key, T, Compare, Allocator>& data,
                     const unsigned int)
    {
        ar.save<bintoken::token::begin_assoc_array>();
        ar.save<bintoken::token::null>();
        for (typename std::map<Key, T, Compare, Allocator>::const_iterator it = data.begin();
             it != data.end();
             ++it)
        {
            ar.save_override(*it);
        }
        ar.save<bintoken::token::end_assoc_array>();
    }
};

template <typename Key, typename T, typename Compare, typename Allocator>
struct load_overloader< protocol::bintoken::iarchive,
                        typename std::map<Key, T, Compare, Allocator> >
{
    static void load(protocol::bintoken::iarchive& ar,
                     std::map<Key, T, Compare, Allocator>& data,
                     const unsigned int version)
    {
        ar.load<bintoken::token::begin_assoc_array>();
        boost::optional<std::size_t> count;
        ar.load_override(count);
        while (!ar.at<bintoken::token::end_assoc_array>())
        {
            // We cannot use std::map<Key, T>::value_type because it has a const key
            std::pair<Key, T> value;
            ar.load_override(value, version);
            data.insert(value);
        }
        ar.load<bintoken::token::end_assoc_array>();
    }
};

} // namespace serialization
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_BINTOKEN_SERIALIZATION_STD_MAP_HPP
