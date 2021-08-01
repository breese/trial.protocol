#ifndef TRIAL_PROTOCOL_JSON_SERIALIZATION_STD_VECTOR_HPP
#define TRIAL_PROTOCOL_JSON_SERIALIZATION_STD_VECTOR_HPP

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
#include <trial/protocol/core/serialization/std/vector.hpp>

namespace trial
{
namespace protocol
{
namespace serialization
{

template <typename CharT, typename T, typename Allocator>
struct save_overloader< json::basic_oarchive<CharT>,
                        typename std::vector<T, Allocator> >
{
    static void save(json::basic_oarchive<CharT>& archive,
                     const std::vector<T, Allocator>& data,
                     const unsigned int protocol_version)
    {
        archive.template save<json::token::begin_array>();
        for (typename std::vector<T, Allocator>::const_iterator it = data.begin();
             it != data.end();
             ++it)
        {
            archive.save_override(*it, protocol_version);
        }
        archive.template save<json::token::end_array>();
    }
};

template <typename Reader, typename T, typename Allocator>
struct load_overloader< json::basic_iarchive<Reader>,
                        typename std::vector<T, Allocator> >
{
    static void load(json::basic_iarchive<Reader>& archive,
                     std::vector<T, Allocator>& data,
                     const unsigned int protocol_version)
    {
        archive.template load<json::token::begin_array>();
        while (!archive.template at<json::token::end_array>())
        {
            T value;
            archive.load_override(value, protocol_version);
            data.push_back(value);
        }
        archive.template load<json::token::end_array>();
    }
};

// Specialization for std::vector<bool>

template <typename CharT, typename Allocator>
struct save_overloader< json::basic_oarchive<CharT>,
                        typename std::vector<bool, Allocator> >
{
    static void save(json::basic_oarchive<CharT>& archive,
                     const std::vector<bool, Allocator>& data,
                     const unsigned int protocol_version)
    {
        archive.template save<json::token::begin_array>();
        for (typename std::vector<bool, Allocator>::const_iterator it = data.begin();
             it != data.end();
             ++it)
        {
            bool value = *it;
            archive.save_override(value, protocol_version);
        }
        archive.template save<json::token::end_array>();
    }
};

} // namespace serialization
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_JSON_SERIALIZATION_STD_VECTOR_HPP
