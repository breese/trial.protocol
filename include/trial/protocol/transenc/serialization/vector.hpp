#ifndef TRIAL_PROTOCOL_TRANSENC_SERIALIZATION_VECTOR_HPP
#define TRIAL_PROTOCOL_TRANSENC_SERIALIZATION_VECTOR_HPP

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
#include <trial/protocol/transenc/serialization/optional.hpp>
#include <trial/protocol/serialization/vector.hpp>

namespace trial
{
namespace protocol
{
namespace serialization
{

// Specialization for binary data

template <typename Allocator>
struct save_overloader< transenc::oarchive,
                        typename std::vector<boost::uint8_t, Allocator> >
{
    static void save(transenc::oarchive& ar,
                     const std::vector<boost::uint8_t, Allocator>& data,
                     const unsigned int /* protocol_version */)
    {
        ar.save(data);
    }
};

template <typename Allocator>
struct load_overloader< transenc::iarchive,
                        typename std::vector<boost::uint8_t, Allocator> >
{
    static void load(transenc::iarchive& ar,
                     std::vector<boost::uint8_t, Allocator>& data,
                     const unsigned int /* protocol_version */)
    {
        switch (ar.symbol())
        {
        case transenc::token::symbol::binary:
            {
                transenc::iarchive::view_type view;
                ar.load(view);
                data.clear();
                data.insert(data.begin(), view.begin(), view.end());
            }
            break;

        default:
            throw transenc::error(transenc::incompatible_type);
        }
    }
};

// Specialization for generic vector data

template <typename T, typename Allocator>
struct save_overloader< transenc::oarchive,
                        typename std::vector<T, Allocator> >
{
    static void save(transenc::oarchive& ar,
                     const std::vector<T, Allocator>& data,
                     const unsigned int /* protocol_version */)
    {
        ar.save<transenc::token::begin_array>();
        ar.save<std::size_t>(data.size());
        for (typename std::vector<T, Allocator>::const_iterator it = data.begin();
             it != data.end();
             ++it)
        {
            ar.save_override(*it);
        }
        ar.save<transenc::token::end_array>();
    }
};

template <typename T, typename Allocator>
struct load_overloader< transenc::iarchive,
                        typename std::vector<T, Allocator> >
{
    static void load(transenc::iarchive& ar,
                     std::vector<T, Allocator>& data,
                     const unsigned int /* protocol_version */)
    {
        ar.load<transenc::token::begin_array>();

        boost::optional<std::size_t> count;
        ar.load_override(count);
        if (count)
        {
            data.reserve(*count);
        }

        while (!ar.at<transenc::token::end_array>())
        {
            T value;
            ar >> value;
            data.push_back(value);
        }
        ar.load<transenc::token::end_array>();
    }
};

} // namespace serialization
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_TRANSENC_SERIALIZATION_VECTOR_HPP
