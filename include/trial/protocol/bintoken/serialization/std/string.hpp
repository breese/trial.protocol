#ifndef TRIAL_PROTOCOL_BINTOKEN_SERIALIZATION_STD_STRING_HPP
#define TRIAL_PROTOCOL_BINTOKEN_SERIALIZATION_STD_STRING_HPP

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
#include <trial/protocol/core/serialization/std/string.hpp>

namespace trial
{
namespace protocol
{
namespace serialization
{

template <typename CharT, typename Traits, typename Allocator>
struct save_overloader< protocol::bintoken::oarchive,
                        typename std::basic_string<CharT, Traits, Allocator> >
{
    static void save(protocol::bintoken::oarchive& ar,
                     const std::basic_string<CharT, Traits, Allocator>& data,
                     const unsigned int)
    {
        ar.save(data);
    }
};

template <typename CharT, typename Traits, typename Allocator>
struct load_overloader< protocol::bintoken::iarchive,
                        typename std::basic_string<CharT, Traits, Allocator> >
{
    static void load(protocol::bintoken::iarchive& ar,
                     std::basic_string<CharT, Traits, Allocator>& data,
                     const unsigned int)
    {
        ar.load(data);
    }
};

} // namespace serialization
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_BINTOKEN_SERIALIZATION_STD_STRING_HPP
