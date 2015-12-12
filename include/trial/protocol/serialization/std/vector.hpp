#ifndef TRIAL_PROTOCOL_SERIALIZATION_STD_VECTOR_HPP
#define TRIAL_PROTOCOL_SERIALIZATION_STD_VECTOR_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2015 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <vector>
#include <trial/protocol/serialization/serialization.hpp>

namespace trial
{
namespace protocol
{
namespace serialization
{

template <typename Archive, typename T, typename Allocator>
struct save_overloader< Archive, typename std::vector<T, Allocator> >
{
    static void save (Archive&,
                      const std::vector<T, Allocator>&,
                      const unsigned int);
};

template <typename Archive, typename T, typename Allocator>
struct load_overloader< Archive, typename std::vector<T, Allocator> >
{
    static void load(Archive&,
                     std::vector<T, Allocator>&,
                     const unsigned int);
};

template <typename Archive, typename T, typename Allocator>
struct serialize_overloader<Archive,
                            typename std::vector<T, Allocator>,
                            typename boost::enable_if<typename Archive::is_loading>::type>
{
    static void serialize(Archive& ar,
                          std::vector<T, Allocator>& data,
                          const unsigned int version)
    {
        boost::serialization::split_free(ar, data, version);
    }
};

template <typename Archive, typename T, typename Allocator>
struct serialize_overloader<Archive,
                            typename std::vector<T, Allocator>,
                            typename boost::enable_if<typename Archive::is_saving>::type>
{
    static void serialize(Archive& ar,
                          const std::vector<T, Allocator>& data,
                          const unsigned int version)
    {
        boost::serialization::split_free(ar, data, version);
    }
};

} // namespace serialization
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_SERIALIZATION_STD_VECTOR_HPP
