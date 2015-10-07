#ifndef TRIAL_PROTOCOL_TRANSENC_SERIALIZATION_MAP_HPP
#define TRIAL_PROTOCOL_TRANSENC_SERIALIZATION_MAP_HPP

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
#include <trial/protocol/transenc/serialization/pair.hpp>
#include <trial/protocol/transenc/serialization/optional.hpp>
#include <trial/protocol/serialization/map.hpp>

namespace trial
{
namespace protocol
{
namespace serialization
{

template <typename Key, typename T, typename Compare, typename Allocator>
struct save_overloader< protocol::transenc::oarchive,
                        typename std::map<Key, T, Compare, Allocator> >
{
    static void save(protocol::transenc::oarchive& ar,
                     const std::map<Key, T, Compare, Allocator>& data,
                     const unsigned int)
    {
        ar.save<transenc::token::begin_assoc_array>();
        ar.save<transenc::token::null>();
        for (typename std::map<Key, T, Compare, Allocator>::const_iterator it = data.begin();
             it != data.end();
             ++it)
        {
            ar.save_override(*it);
        }
        ar.save<transenc::token::end_assoc_array>();
    }
};

template <typename Key, typename T, typename Compare, typename Allocator>
struct load_overloader< protocol::transenc::iarchive,
                        typename std::map<Key, T, Compare, Allocator> >
{
    static void load(protocol::transenc::iarchive& ar,
                     std::map<Key, T, Compare, Allocator>& data,
                     const unsigned int version)
    {
        ar.load<transenc::token::begin_assoc_array>();
        boost::optional<std::size_t> count;
        ar.load_override(count);
        while (!ar.at<transenc::token::end_assoc_array>())
        {
            // We cannot use std::map<Key, T>::value_type because it has a const key
            std::pair<Key, T> value;
            ar.load_override(value, version);
            data.insert(value);
        }
        ar.load<transenc::token::end_assoc_array>();
    }
};

} // namespace serialization
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_TRANSENC_SERIALIZATION_MAP_HPP
