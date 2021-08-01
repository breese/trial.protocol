#ifndef TRIAL_PROTOCOL_JSON_SERIALIZATION_DETAIL_ARRAY_LOAD_HPP
#define TRIAL_PROTOCOL_JSON_SERIALIZATION_DETAIL_ARRAY_LOAD_HPP

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
#include <trial/protocol/core/serialization/array.hpp>

//-----------------------------------------------------------------------------
// By-pass Boost.Serialization which has its own array formatting
//-----------------------------------------------------------------------------

namespace boost
{
namespace serialization
{

template <typename Reader, typename T, std::size_t N>
void load(trial::protocol::json::basic_iarchive<Reader>& ar,
          T (&data)[N],
          const unsigned int version)
{
    using namespace trial::protocol::serialization;
    load_overloader<trial::protocol::json::basic_iarchive<Reader>, T[N]>::
        load(ar, data, version);
}

template <typename Reader, typename T, std::size_t N>
void serialize(trial::protocol::json::basic_iarchive<Reader>& ar,
               T (&data)[N],
               const unsigned int version)
{
    using namespace trial::protocol::serialization;
    serialize_overloader<trial::protocol::json::basic_iarchive<Reader>, T[N]>::
        serialize(ar, data, version);
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

template <typename Reader, typename T, std::size_t N>
struct load_overloader< json::basic_iarchive<Reader>,
                        T[N] >
{
    static void load(json::basic_iarchive<Reader>& ar,
                     T (&data)[N],
                     const unsigned int protocol_version)
    {
        ar.template load<json::token::begin_array>();
        for (std::size_t i = 0; i < N; ++i)
        {
            T value;
            ar.load_override(value, protocol_version);
            data[i] = value;
        }
        if (!ar.template at<json::token::end_array>())
            throw json::error(json::expected_end_array);
        ar.template load<json::token::end_array>();
    }
};

} // namespace serialization
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_JSON_SERIALIZATION_DETAIL_ARRAY_LOAD_HPP
