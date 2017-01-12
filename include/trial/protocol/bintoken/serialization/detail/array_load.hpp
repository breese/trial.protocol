#ifndef TRIAL_PROTOCOL_BINTOKEN_SERIALIZATION_DETAIL_ARRAY_LOAD_HPP
#define TRIAL_PROTOCOL_BINTOKEN_SERIALIZATION_DETAIL_ARRAY_LOAD_HPP

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

namespace trial
{
namespace protocol
{
namespace serialization
{

template <typename T, std::size_t N>
struct load_overloader< bintoken::iarchive,
                        T[N] >
{
    static void load(bintoken::iarchive& ar,
                     T (&data)[N],
                     const unsigned int /* protocol_version */)
    {
        ar.load<bintoken::token::begin_array>();

        std::size_t count;
        ar.load_override(count);
        if (count != N)
            throw bintoken::error(bintoken::incompatible_type);

        for (std::size_t i = 0; i < N; ++i)
        {
            T value;
            ar >> value;
            data[i] = value;
        }
        if (!ar.at<bintoken::token::end_array>())
            throw bintoken::error(bintoken::expected_end_array);
        ar.load<bintoken::token::end_array>();
    }
};

} // namespace serialization
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_BINTOKEN_SERIALIZATION_DETAIL_ARRAY_LOAD_HPP
