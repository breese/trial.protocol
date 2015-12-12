#ifndef TRIAL_PROTOCOL_TRANSENC_SERIALIZATION_DETAIL_ARRAY_SAVE_HPP
#define TRIAL_PROTOCOL_TRANSENC_SERIALIZATION_DETAIL_ARRAY_SAVE_HPP

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
#include <trial/protocol/serialization/array.hpp>

namespace trial
{
namespace protocol
{
namespace serialization
{

template <typename T, std::size_t N>
struct save_overloader< transenc::oarchive,
                        T[N] >
{
    static void save(transenc::oarchive& ar,
                     const T (&data)[N],
                     const unsigned int /* protocol_version */)
    {
        ar.save<transenc::token::begin_array>();
        ar.save<std::size_t>(N);
        for (std::size_t i = 0; i < N; ++i)
        {
            ar.save_override(data[i]);
        }
        ar.save<transenc::token::end_array>();
    }
};

} // namespace serialization
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_TRANSENC_SERIALIZATION_DETAIL_ARRAY_SAVE_HPP
