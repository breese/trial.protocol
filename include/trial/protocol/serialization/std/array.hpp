#ifndef TRIAL_PROTOCOL_SERIALIZATION_STD_ARRAY_HPP
#define TRIAL_PROTOCOL_SERIALIZATION_STD_ARRAY_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2017 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <array>
#include <trial/protocol/serialization/serialization.hpp>

namespace trial
{
namespace protocol
{
namespace serialization
{

template <typename Archive, typename T, std::size_t N>
struct save_overloader< Archive, typename std::array<T, N> >
{
    static void save(Archive&,
                     const std::array<T, N>&,
                     const unsigned int);
};

template <typename Archive, typename T, std::size_t N>
struct load_overloader< Archive, typename std::array<T, N> >
{
    static void load(Archive&,
                     std::array<T, N>&,
                     const unsigned int);
};

template <typename Archive, typename T, std::size_t N>
struct serialize_overloader<Archive,
                            typename std::array<T, N>,
                            typename std::enable_if<Archive::is_loading::value>::type>
{
    static void serialize(Archive& ar,
                          std::array<T, N>& data,
                          const unsigned int version)
    {
        boost::serialization::split_free(ar, data, version);
    }
};

template <typename Archive, typename T, std::size_t N>
struct serialize_overloader<Archive,
                            typename std::array<T, N>,
                            typename std::enable_if<Archive::is_saving::value>::type>
{
    static void serialize(Archive& ar,
                          const std::array<T, N>& data,
                          const unsigned int version)
    {
        boost::serialization::split_free(ar, data, version);
    }
};

} // namespace serialization
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_SERIALIZATION_STD_ARRAY_HPP
