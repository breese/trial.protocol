#ifndef TRIAL_PROTOCOL_JSON_SERIALIZATION_PAIR_HPP
#define TRIAL_PROTOCOL_JSON_SERIALIZATION_PAIR_HPP

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
#include <trial/protocol/serialization/pair.hpp>

namespace trial
{
namespace protocol
{
namespace serialization
{

template <typename T1, typename T2>
struct save_functor< protocol::json::oarchive, typename std::pair<T1, T2> >
{
    static void save(protocol::json::oarchive& ar,
                     const std::pair<T1, T2>& data,
                     const unsigned int version)
    {
        ar.save(json::array_open);
        ar << data.first;
        ar << data.second;
        ar.save(json::array_close);
    }
};

template <typename T1, typename T2>
struct load_functor< protocol::json::iarchive, typename std::pair<T1, T2> >
{
    static void load(protocol::json::iarchive& ar,
                     std::pair<T1, T2>& data,
                     const unsigned int version)
    {
        ar.load(json::array_open);
        ar >> data.first;
        ar >> data.second;
        ar.load(json::array_close);
    }
};

} // namespace serialization
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_JSON_SERIALIZATION_PAIR_HPP
