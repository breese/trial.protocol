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
struct save_functor< json::basic_oarchive<CharT>,
                     typename std::map<Key, T, Compare, Allocator> >
{
    static void save(json::basic_oarchive<CharT>& archive,
                     const std::map<Key, T, Compare, Allocator>& data,
                     const unsigned int /* protocol_version */)
    {
        archive.template save<json::token::begin_array>();
        for (typename std::map<Key, T, Compare, Allocator>::const_iterator it = data.begin();
             it != data.end();
             ++it)
        {
            archive.save_override(*it);
        }
        archive.template save<json::token::end_array>();
    }
};

template <typename CharT, typename Key, typename T, typename Compare, typename Allocator>
struct load_functor< json::basic_iarchive<CharT>,
                     typename std::map<Key, T, Compare, Allocator> >
{
    static void load(json::basic_iarchive<CharT>& archive,
                     std::map<Key, T, Compare, Allocator>& data,
                     const unsigned int /* protocol_version */)
    {
        archive.template load<json::token::begin_array>();
        while (!archive.template at<json::token::end_array>())
        {
            // We cannot use std::map<Key, T>::value_type because it has a const key
            std::pair<Key, T> value;
            archive.load_override(value);
            data.insert(value);
        }
        archive.template load<json::token::end_array>();
    }
};

// Specialization for map<string, T>
template <typename CharT, typename Traits, typename StringAllocator,
          typename T, typename Compare, typename MapAllocator>
struct save_functor< json::basic_oarchive<CharT>,
                     typename std::map<std::basic_string<CharT, Traits, StringAllocator>, T, Compare, MapAllocator> >
{
    typedef std::basic_string<CharT, Traits, StringAllocator> key_type;
    static void save(json::basic_oarchive<CharT>& archive,
                     const std::map<key_type, T, Compare, MapAllocator>& data,
                     const unsigned int /* protocol_version */)
    {
        archive.template save<json::token::begin_object>();
        for (typename std::map<key_type, T, Compare, MapAllocator>::const_iterator it = data.begin();
             it != data.end();
             ++it)
        {
            archive.save_override(it->first);
            archive.save_override(it->second);
        }
        archive.template save<json::token::end_object>();
    }
};

template <typename CharT, typename Traits, typename StringAllocator,
          typename T, typename Compare, typename MapAllocator>
struct load_functor< json::basic_iarchive<CharT>,
                     typename std::map<std::basic_string<CharT, Traits, StringAllocator>, T, Compare, MapAllocator> >
{
    typedef std::basic_string<CharT, Traits, StringAllocator> key_type;
    static void load(json::basic_iarchive<CharT>& archive,
                     std::map<key_type, T, Compare, MapAllocator>& data,
                     const unsigned int /* protocol_version*/)
    {
        archive.template load<json::token::begin_object>();
        while (!archive.template at<json::token::end_object>())
        {
            // We cannot use std::map<Key, T>::value_type because it has a const key
            std::pair<key_type, T> value;
            archive.load_override(value.first);
            archive.load_override(value.second);
            data.insert(value);
        }
        archive.template load<json::token::end_object>();
    }
};

} // namespace serialization
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_JSON_SERIALIZATION_MAP_HPP
