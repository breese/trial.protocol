#ifndef TRIAL_PROTOCOL_JSON_SERIALIZATION_SET_HPP
#define TRIAL_PROTOCOL_JSON_SERIALIZATION_SET_HPP

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
#include <trial/protocol/serialization/set.hpp>

namespace trial
{
namespace protocol
{
namespace serialization
{

template <typename Key, typename Compare, typename Allocator>
struct save_functor< protocol::json::oarchive, typename std::set<Key, Compare, Allocator> >
{
    static void save(protocol::json::oarchive& ar,
                     const std::set<Key, Compare, Allocator>& data,
                     const unsigned int)
    {
        ar.save(json::begin_array);
        for (typename std::set<Key, Compare, Allocator>::const_iterator it = data.begin();
             it != data.end();
             ++it)
        {
            ar.save_override(*it);
        }
        ar.save(json::end_array);
    }
};

template <typename Key, typename Compare, typename Allocator>
struct load_functor< protocol::json::iarchive, typename std::set<Key, Compare, Allocator> >
{
    static void load(protocol::json::iarchive& ar,
                     std::set<Key, Compare, Allocator>& data,
                     const unsigned int)
    {
        ar.load(json::begin_array);
        while (!ar.at_end_array())
        {
            Key value;
            ar.load_override(value);
            data.insert(value);
        }
        ar.load(json::end_array);
    }
};

} // namespace serialization
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_JSON_SERIALIZATION_SET_HPP
