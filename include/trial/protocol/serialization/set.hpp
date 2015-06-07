#ifndef TRIAL_PROTOCOL_SERIALIZATION_SET_HPP
#define TRIAL_PROTOCOL_SERIALIZATION_SET_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2015 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <set>
#include <trial/protocol/serialization/serialization.hpp>

namespace trial
{
namespace protocol
{
namespace serialization
{

template <typename Archive, typename Key, typename Compare, typename Allocator>
struct save_functor< Archive, typename std::set<Key, Compare, Allocator> >
{
    static void save(Archive&,
                     const std::set<Key, Compare, Allocator>&,
                     const unsigned int);
};

template <typename Archive, typename Key, typename Compare, typename Allocator>
struct load_functor< Archive, typename std::set<Key, Compare, Allocator> >
{
    static void load(Archive&,
                     std::set<Key, Compare, Allocator>&,
                     const unsigned int);
};

template <typename Key, typename Compare, typename Allocator>
struct serialize_functor< typename std::set<Key, Compare, Allocator> >
{
    template <typename Archive>
    static typename boost::enable_if<typename Archive::is_loading, void>::type
    serialize(Archive& ar,
              std::set<Key, Compare, Allocator>& data,
              const unsigned int version)
    {
        boost::serialization::split_free(ar, data, version);
    }

    template <typename Archive>
    static typename boost::enable_if<typename Archive::is_saving, void>::type
    serialize(Archive& ar,
              const std::set<Key, Compare, Allocator>& data,
              const unsigned int version)
    {
        boost::serialization::split_free(ar, data, version);
    }
};

} // namespace serialization
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_SERIALIZATION_SET_HPP
