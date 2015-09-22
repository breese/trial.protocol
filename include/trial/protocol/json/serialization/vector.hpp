#ifndef TRIAL_PROTOCOL_JSON_SERIALIZATION_VECTOR_HPP
#define TRIAL_PROTOCOL_JSON_SERIALIZATION_VECTOR_HPP

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
#include <trial/protocol/serialization/vector.hpp>

namespace trial
{
namespace protocol
{
namespace serialization
{

template <typename T, typename Allocator>
struct save_functor< json::oarchive,
                     typename std::vector<T, Allocator> >
{
    static void save(json::oarchive& archive,
                     const std::vector<T, Allocator>& data,
                     const unsigned int /* protocol_version */)
    {
        archive.template save<json::token::begin_array>();
        for (typename std::vector<T, Allocator>::const_iterator it = data.begin();
             it != data.end();
             ++it)
        {
            archive.save_override(*it);
        }
        archive.template save<json::token::end_array>();
    }
};

template <typename T, typename Allocator>
struct load_functor< json::iarchive,
                     typename std::vector<T, Allocator> >
{
    static void load(json::iarchive& archive,
                     std::vector<T, Allocator>& data,
                     const unsigned int /* protocol_version */)
    {
        archive.template load<json::token::begin_array>();
        while (!archive.template at<json::token::end_array>())
        {
            T value;
            archive.load_override(value);
            data.push_back(value);
        }
        archive.template load<json::token::end_array>();
    }
};

} // namespace serialization
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_JSON_SERIALIZATION_VECTOR_HPP
