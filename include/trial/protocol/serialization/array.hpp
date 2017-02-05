#ifndef TRIAL_PROTOCOL_SERIALIZATION_ARRAY_HPP
#define TRIAL_PROTOCOL_SERIALIZATION_ARRAY_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2015 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <trial/protocol/serialization/serialization.hpp>

namespace trial
{
namespace protocol
{
namespace serialization
{

template <typename Archive, typename T, std::size_t N>
struct serialize_overloader<Archive,
                            T[N],
                            typename std::enable_if<Archive::is_loading>::type>
{
    static void serialize(Archive& ar,
                          T (&data)[N], // Prevent decay
                          const unsigned int version)
    {
        boost::serialization::split_free(ar, data, version);
    }
};

template <typename Archive, typename T, std::size_t N>
struct serialize_overloader<Archive,
                            T[N],
                            typename std::enable_if<Archive::is_saving>::type>
{
    static void serialize(Archive& ar,
                          const T (&data)[N],
                          const unsigned int version)
    {
        boost::serialization::split_free(ar, data, version);
    }
};

} // namespace serialization
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_SERIALIZATION_ARRAY_HPP
