#ifndef TRIAL_PROTOCOL_SERIALIZATION_MAP_HPP
#define TRIAL_PROTOCOL_SERIALIZATION_MAP_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2015 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <map>
#include <trial/protocol/serialization/serialization.hpp>
#include <trial/protocol/serialization/pair.hpp>

namespace trial
{
namespace protocol
{
namespace serialization
{

template <typename Archive, typename Key, typename T, typename Compare, typename Allocator>
struct save_functor< Archive, typename std::map<Key, T, Compare, Allocator> >
{
    // If this is missing while linking, then you probably forgot to include the
    // map serialization for a specific protocol.
    static void save(Archive&,
                     const std::map<Key, T, Compare, Allocator>&,
                     const unsigned int);
};

template <typename Archive, typename Key, typename T, typename Compare, typename Allocator>
struct load_functor< Archive, typename std::map<Key, T, Compare, Allocator> >
{
    static void load(Archive&,
                     std::map<Key, T, Compare, Allocator>&,
                     const unsigned int);
};

template <typename Key, typename T, typename Compare, typename Allocator>
struct serialize_functor< typename std::map<Key, T, Compare, Allocator> >
{
    template <typename Archive>
    static typename boost::enable_if<typename Archive::is_loading, void>::type
    serialize(Archive& ar,
              std::map<Key, T, Compare, Allocator>& data,
              const unsigned int version)
    {
        boost::serialization::split_free(ar, data, version);
    }

    template <typename Archive>
    static typename boost::enable_if<typename Archive::is_saving, void>::type
    serialize(Archive& ar,
              const std::map<Key, T, Compare, Allocator>& data,
              const unsigned int version)
    {
        boost::serialization::split_free(ar, data, version);
    }
};

} // namespace serialization
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_SERIALIZATION_MAP_HPP