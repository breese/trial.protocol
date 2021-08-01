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
#include <trial/protocol/core/serialization/std/pair.hpp>

namespace trial
{
namespace protocol
{
namespace serialization
{

template <typename CharT, typename T1, typename T2>
struct save_overloader< json::basic_oarchive<CharT>,
                        typename std::pair<T1, T2> >
{
    static void save(json::basic_oarchive<CharT>& archive,
                     const std::pair<T1, T2>& data,
                     const unsigned int protocol_version)
    {
        archive.template save<json::token::begin_array>();
        archive.save_override(data.first, protocol_version);
        archive.save_override(data.second, protocol_version);
        archive.template save<json::token::end_array>();
    }
};

template <typename Reader, typename T1, typename T2>
struct load_overloader< json::basic_iarchive<Reader>,
                        typename std::pair<T1, T2> >
{
    static void load(json::basic_iarchive<Reader>& archive,
                     std::pair<T1, T2>& data,
                     const unsigned int protocol_version)
    {
        archive.template load<json::token::begin_array>();
        archive.load_override(data.first, protocol_version);
        archive.load_override(data.second, protocol_version);
        archive.template load<json::token::end_array>();
    }
};

} // namespace serialization
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_JSON_SERIALIZATION_STD_PAIR_HPP
