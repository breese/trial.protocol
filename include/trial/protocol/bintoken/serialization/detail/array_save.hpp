#ifndef TRIAL_PROTOCOL_BINTOKEN_SERIALIZATION_DETAIL_ARRAY_SAVE_HPP
#define TRIAL_PROTOCOL_BINTOKEN_SERIALIZATION_DETAIL_ARRAY_SAVE_HPP

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
#include <trial/protocol/serialization/array.hpp>

//-----------------------------------------------------------------------------
// By-pass Boost.Serialization which has its own array formatting
//-----------------------------------------------------------------------------

namespace boost
{
namespace serialization
{

template <typename T, std::size_t N>
void save(trial::protocol::bintoken::oarchive& ar,
          const T (&data)[N],
          const unsigned int version)
{
    using namespace trial::protocol::serialization;
    save_overloader<trial::protocol::bintoken::oarchive, T[N]>::save(ar, data, version);
}

template <typename T, std::size_t N>
void serialize(trial::protocol::bintoken::oarchive& ar,
               const T (&data)[N],
               const unsigned int version)
{
    using namespace trial::protocol::serialization;
    serialize_overloader<trial::protocol::bintoken::oarchive, T[N]>::serialize(ar, data, version);
}

template <typename T, std::size_t N>
void serialize(trial::protocol::bintoken::oarchive& ar,
               T (&data)[N],
               const unsigned int version)
{
    using namespace trial::protocol::serialization;
    serialize_overloader<trial::protocol::bintoken::oarchive, T[N]>::serialize(ar, data, version);
}

} // namespace serialization
} // namespace boost

//-----------------------------------------------------------------------------
// T[N]
//-----------------------------------------------------------------------------

namespace trial
{
namespace protocol
{
namespace serialization
{

template <typename T, std::size_t N>
struct save_overloader< bintoken::oarchive,
                        T[N] >
{
    static void save(bintoken::oarchive& ar,
                     const T (&data)[N],
                     const unsigned int protocol_version)
    {
        ar.save<bintoken::token::begin_array>();
        ar.save<std::size_t>(N);
        for (std::size_t i = 0; i < N; ++i)
        {
            ar.save_override(data[i], protocol_version);
        }
        ar.save<bintoken::token::end_array>();
    }
};

// Specialization for binary data

template <std::size_t N>
struct save_overloader< bintoken::oarchive,
                        std::uint8_t[N] >
{
    static void save(bintoken::oarchive& ar,
                     const std::uint8_t (&data)[N],
                     const unsigned int /* protocol_version */)
    {
        ar.save_binary(data, N);
    }
};

} // namespace serialization
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_BINTOKEN_SERIALIZATION_DETAIL_ARRAY_SAVE_HPP
