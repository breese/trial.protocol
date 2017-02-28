#ifndef TRIAL_PROTOCOL_BINTOKEN_SERIALIZATION_STD_VECTOR_HPP
#define TRIAL_PROTOCOL_BINTOKEN_SERIALIZATION_STD_VECTOR_HPP

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
#include <trial/protocol/bintoken/serialization/boost/optional.hpp>
#include <trial/protocol/serialization/std/vector.hpp>

namespace trial
{
namespace protocol
{
namespace serialization
{

template <typename T, typename Allocator>
struct save_overloader< bintoken::oarchive,
                        typename std::vector<T, Allocator> >
{
    static void save(bintoken::oarchive& ar,
                     const std::vector<T, Allocator>& data,
                     const unsigned int /* protocol_version */)
    {
        ar.save<bintoken::token::begin_array>();
        ar.save<std::size_t>(data.size());
        for (typename std::vector<T, Allocator>::const_iterator it = data.begin();
             it != data.end();
             ++it)
        {
            ar.save_override(*it);
        }
        ar.save<bintoken::token::end_array>();
    }
};

template <typename T, typename Allocator>
struct load_overloader< bintoken::iarchive,
                        typename std::vector<T, Allocator> >
{
    static void load(bintoken::iarchive& ar,
                     std::vector<T, Allocator>& data,
                     const unsigned int /* protocol_version */)
    {
        ar.load<bintoken::token::begin_array>();

        boost::optional<std::size_t> count;
        ar.load_override(count);
        if (count)
        {
            data.reserve(*count);
        }

        while (!ar.at<bintoken::token::end_array>())
        {
            T value;
            ar >> value;
            data.push_back(value);
        }
        ar.load<bintoken::token::end_array>();
    }
};

// Specialization for binary data

template <typename Allocator>
struct save_overloader< bintoken::oarchive,
                        typename std::vector<std::uint8_t, Allocator> >
{
    static void save(bintoken::oarchive& ar,
                     const std::vector<std::uint8_t, Allocator>& data,
                     const unsigned int /* protocol_version */)
    {
        ar.save(data);
    }
};

template <typename Allocator>
struct load_overloader< bintoken::iarchive,
                        typename std::vector<std::uint8_t, Allocator> >
{
    static void load(bintoken::iarchive& ar,
                     std::vector<std::uint8_t, Allocator>& data,
                     const unsigned int /* protocol_version */)
    {
        switch (ar.symbol())
        {
        case bintoken::token::symbol::binary:
            {
                bintoken::iarchive::view_type view;
                ar.load(view);
                data.clear();
                data.insert(data.begin(), view.begin(), view.end());
            }
            break;

        default:
            throw bintoken::error(bintoken::incompatible_type);
        }
    }
};

// Specialization for std::vector<bool>

template <typename Allocator>
struct save_overloader< bintoken::oarchive,
                        typename std::vector<bool, Allocator> >
{
    static void save(bintoken::oarchive& ar,
                     const std::vector<bool, Allocator>& data,
                     const unsigned int /* protocol_version */)
    {
        ar.save<bintoken::token::begin_array>();
        ar.save<std::size_t>(data.size());
        for (typename std::vector<bool, Allocator>::const_iterator it = data.begin();
             it != data.end();
             ++it)
        {
            bool value = *it;
            ar.save_override(value);
        }
        ar.save<bintoken::token::end_array>();
    }
};

} // namespace serialization
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_BINTOKEN_SERIALIZATION_STD_VECTOR_HPP
