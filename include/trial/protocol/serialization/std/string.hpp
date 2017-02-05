#ifndef TRIAL_PROTOCOL_SERIALIZATION_STD_STRING_HPP
#define TRIAL_PROTOCOL_SERIALIZATION_STD_STRING_HPP

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
struct save_overloader< Archive, typename std::basic_string<CharT, Traits, Allocator> >
{
    static void save(Archive&,
                     const std::basic_string<CharT, Traits, Allocator>&,
                     const unsigned int);
};

template <typename Archive, typename CharT, typename Traits, typename Allocator>
struct load_overloader< Archive, typename std::basic_string<CharT, Traits, Allocator> >
{
    static void load(Archive&,
                     std::basic_string<CharT, Traits, Allocator>&,
                     const unsigned int);
};

template <typename Archive, typename CharT, typename Traits, typename Allocator>
struct serialize_overloader<Archive,
                            typename std::basic_string<CharT, Traits, Allocator>,
                            typename std::enable_if<Archive::is_loading::value>::type>
{
    static void serialize(Archive& ar,
                          std::basic_string<CharT, Traits, Allocator>& data,
                          const unsigned int version)
    {
        boost::serialization::split_free(ar, data, version);
    }
};

template <typename Archive, typename CharT, typename Traits, typename Allocator>
struct serialize_overloader<Archive,
                            typename std::basic_string<CharT, Traits, Allocator>,
                            typename std::enable_if<Archive::is_saving::value>::type>
{
    static void serialize(Archive& ar,
                          const std::basic_string<CharT, Traits, Allocator>& data,
                          const unsigned int version)
    {
        boost::serialization::split_free(ar, data, version);
    }
};

} // namespace serialization
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_SERIALIZATION_STD_STRING_HPP
