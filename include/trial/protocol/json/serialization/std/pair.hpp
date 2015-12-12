#ifndef TRIAL_PROTOCOL_JSON_SERIALIZATION_STD_PAIR_HPP
#define TRIAL_PROTOCOL_JSON_SERIALIZATION_STD_PAIR_HPP

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
#include <trial/protocol/serialization/std/pair.hpp>

namespace trial
{
namespace protocol
{
namespace serialization
{

template <typename T1, typename T2>
struct save_overloader< json::oarchive,
                        typename std::pair<T1, T2> >
{
    static void save(json::oarchive& archive,
                     const std::pair<T1, T2>& data,
                     const unsigned int version)
    {
        archive.template save<json::token::begin_array>();
        archive.save_override(data.first);
        archive.save_override(data.second);
        archive.template save<json::token::end_array>();
    }
};

template <typename T1, typename T2>
struct load_overloader< json::iarchive,
                        typename std::pair<T1, T2> >
{
    static void load(json::iarchive& archive,
                     std::pair<T1, T2>& data,
                     const unsigned int version)
    {
        archive.template load<json::token::begin_array>();
        archive.load_override(data.first);
        archive.load_override(data.second);
        archive.template load<json::token::end_array>();
    }
};

} // namespace serialization
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_JSON_SERIALIZATION_STD_PAIR_HPP
