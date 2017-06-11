#ifndef TRIAL_PROTOCOL_BINTOKEN_SERIALIZATION_STD_ARRAY_HPP
#define TRIAL_PROTOCOL_BINTOKEN_SERIALIZATION_STD_ARRAY_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2017 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <trial/protocol/bintoken/serialization/serialization.hpp>
#include <trial/protocol/serialization/std/array.hpp>

namespace trial
{
namespace protocol
{
namespace serialization
{

template <typename T, std::size_t N>
struct save_overloader< protocol::bintoken::oarchive,
                        typename std::array<T, N> >
{
    static void save(protocol::bintoken::oarchive& ar,
                     const std::array<T, N>& data,
                     const unsigned int)
    {
        ar.save<bintoken::token::begin_record>();
        ar.save_override(data.first);
        ar.save_override(data.second);
        ar.save<bintoken::token::end_record>();
    }
};

template <typename T, std::size_t N>
struct load_overloader< protocol::bintoken::iarchive,
                        typename std::array<T, N> >
{
    static void load(protocol::bintoken::iarchive& ar,
                     std::array<T, N>& data,
                     const unsigned int)
    {
        ar.load<bintoken::token::begin_record>();
        ar.load_override(data.first);
        ar.load_override(data.second);
        ar.load<bintoken::token::end_record>();
    }
};

} // namespace serialization
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_BINTOKEN_SERIALIZATION_STD_ARRAY_HPP
