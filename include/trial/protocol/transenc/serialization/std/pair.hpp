#ifndef TRIAL_PROTOCOL_TRANSENC_SERIALIZATION_STD_PAIR_HPP
#define TRIAL_PROTOCOL_TRANSENC_SERIALIZATION_STD_PAIR_HPP

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
#include <trial/protocol/serialization/std/pair.hpp>

namespace trial
{
namespace protocol
{
namespace serialization
{

template <typename T1, typename T2>
struct save_overloader< protocol::transenc::oarchive,
                        typename std::pair<T1, T2> >
{
    static void save(protocol::transenc::oarchive& ar,
                     const std::pair<T1, T2>& data,
                     const unsigned int)
    {
        ar.save<transenc::token::begin_record>();
        ar.save_override(data.first);
        ar.save_override(data.second);
        ar.save<transenc::token::end_record>();
    }
};

template <typename T1, typename T2>
struct load_overloader< protocol::transenc::iarchive,
                        typename std::pair<T1, T2> >
{
    static void load(protocol::transenc::iarchive& ar,
                     std::pair<T1, T2>& data,
                     const unsigned int)
    {
        ar.load<transenc::token::begin_record>();
        ar.load_override(data.first);
        ar.load_override(data.second);
        ar.load<transenc::token::end_record>();
    }
};

} // namespace serialization
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_TRANSENC_SERIALIZATION_STD_PAIR_HPP
