#ifndef TRIAL_PROTOCOL_SERIALIZATION_STRING_HPP
#define TRIAL_PROTOCOL_SERIALIZATION_STRING_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2015 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <string>
#include <trial/protocol/serialization/serialization.hpp>

namespace trial
{
namespace protocol
{
namespace serialization
{

template <typename Archive, typename CharT, typename Traits, typename Allocator>
struct save_functor< Archive, typename std::basic_string<CharT, Traits, Allocator> >
{
    static void save(Archive&,
                     const std::basic_string<CharT, Traits, Allocator>&,
                     const unsigned int);
};

template <typename Archive, typename CharT, typename Traits, typename Allocator>
struct load_functor< Archive, typename std::basic_string<CharT, Traits, Allocator> >
{
    static void load(Archive&,
                     std::basic_string<CharT, Traits, Allocator>&,
                     const unsigned int);
};

template <typename CharT, typename Traits, typename Allocator>
struct serialize_functor< typename std::basic_string<CharT, Traits, Allocator> >
{
    template <typename Archive>
    static typename boost::enable_if<typename Archive::is_loading, void>::type
    serialize(Archive& ar,
              std::basic_string<CharT, Traits, Allocator>& data,
              const unsigned int version)
    {
        boost::serialization::split_free(ar, data, version);
    }

    template <typename Archive>
    static typename boost::enable_if<typename Archive::is_saving, void>::type
    serialize(Archive& ar,
              const std::basic_string<CharT, Traits, Allocator>& data,
              const unsigned int version)
    {
        boost::serialization::split_free(ar, data, version);
    }
};

} // namespace serialization
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_SERIALIZATION_STRING_HPP
