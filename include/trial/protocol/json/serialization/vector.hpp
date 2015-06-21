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
struct save_functor< protocol::json::oarchive, typename std::vector<T, Allocator> >
{
    static void save(protocol::json::oarchive& ar,
                     const std::vector<T, Allocator>& data,
                     const unsigned int /* protocol_version */)
    {
        ar.save(json::begin_array);
        for (typename std::vector<T, Allocator>::const_iterator it = data.begin();
             it != data.end();
             ++it)
        {
            ar.save_override(*it);
        }
        ar.save(json::end_array);
    }
};

template <typename T, typename Allocator>
struct load_functor< protocol::json::iarchive, typename std::vector<T, Allocator> >
{
    static void load(protocol::json::iarchive& ar,
                     std::vector<T, Allocator>& data,
                     const unsigned int /* protocol_version */)
    {
        ar.load(json::begin_array);
        while (!ar.at_end_array())
        {
            T value;
            ar.load_override(value);
            data.push_back(value);
        }
        ar.load(json::end_array);
    }
};

} // namespace serialization
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_JSON_SERIALIZATION_VECTOR_HPP
