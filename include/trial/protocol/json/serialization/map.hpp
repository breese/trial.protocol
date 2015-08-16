#ifndef TRIAL_PROTOCOL_JSON_SERIALIZATION_MAP_HPP
#define TRIAL_PROTOCOL_JSON_SERIALIZATION_MAP_HPP

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
#include <trial/protocol/serialization/map.hpp>

namespace trial
{
namespace protocol
{
namespace serialization
{

template <typename CharT, typename Key, typename T, typename Compare, typename Allocator>
struct save_functor< protocol::json::basic_oarchive<CharT>,
                     typename std::map<Key, T, Compare, Allocator> >
{
    static void save(protocol::json::basic_oarchive<CharT>& ar,
                     const std::map<Key, T, Compare, Allocator>& data,
                     const unsigned int /* protocol_version */)
    {
        ar.save(json::begin_array);
        for (typename std::map<Key, T, Compare, Allocator>::const_iterator it = data.begin();
             it != data.end();
             ++it)
        {
            ar.save_override(*it);
        }
        ar.save(json::end_array);
    }
};

template <typename CharT, typename Key, typename T, typename Compare, typename Allocator>
struct load_functor< protocol::json::basic_iarchive<CharT>,
                     typename std::map<Key, T, Compare, Allocator> >
{
    static void load(protocol::json::basic_iarchive<CharT>& ar,
                     std::map<Key, T, Compare, Allocator>& data,
                     const unsigned int /* protocol_version */)
    {
        ar.load(json::begin_array);
        while (!ar.at_end_array())
        {
            // We cannot use std::map<Key, T>::value_type because it has a const key
            std::pair<Key, T> value;
            ar.load_override(value);
            data.insert(value);
        }
        ar.load(json::end_array);
    }
};

// Specialization for map<string, T>
template <typename CharT, typename Traits, typename StringAllocator,
          typename T, typename Compare, typename MapAllocator>
struct save_functor< protocol::json::basic_oarchive<CharT>,
                     typename std::map<std::basic_string<CharT, Traits, StringAllocator>, T, Compare, MapAllocator> >
{
    typedef std::basic_string<CharT, Traits, StringAllocator> key_type;
    static void save(protocol::json::basic_oarchive<CharT>& ar,
                     const std::map<key_type, T, Compare, MapAllocator>& data,
                     const unsigned int /* protocol_version */)
    {
        ar.save(json::begin_object);
        for (typename std::map<key_type, T, Compare, MapAllocator>::const_iterator it = data.begin();
             it != data.end();
             ++it)
        {
            ar << it->first;
            ar << it->second;
        }
        ar.save(json::end_object);
    }
};

template <typename CharT, typename Traits, typename StringAllocator,
          typename T, typename Compare, typename MapAllocator>
struct load_functor< protocol::json::basic_iarchive<CharT>,
                     typename std::map<std::basic_string<CharT, Traits, StringAllocator>, T, Compare, MapAllocator> >
{
    typedef std::basic_string<CharT, Traits, StringAllocator> key_type;
    static void load(protocol::json::basic_iarchive<CharT>& ar,
                     std::map<key_type, T, Compare, MapAllocator>& data,
                     const unsigned int /* protocol_version*/)
    {
        ar.load(json::begin_object);
        while (!ar.at_end_object())
        {
            // We cannot use std::map<Key, T>::value_type because it has a const key
            std::pair<key_type, T> value;
            ar >> value.first;
            ar >> value.second;
            data.insert(value);
        }
        ar.load(json::end_object);
    }
};

} // namespace serialization
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_JSON_SERIALIZATION_MAP_HPP
