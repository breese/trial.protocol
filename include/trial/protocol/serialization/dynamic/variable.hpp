#ifndef TRIAL_PROTOCOL_SERIALIZATION_DYNAMIC_VARIABLE_HPP
#define TRIAL_PROTOCOL_SERIALIZATION_DYNAMIC_VARIABLE_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2017 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <trial/protocol/dynamic/variable.hpp>
#include <trial/protocol/serialization/serialization.hpp>

namespace trial
{
namespace protocol
{
namespace serialization
{

template <typename Archive>
struct save_overloader< Archive, typename dynamic::variable >
{
    static void save(Archive&,
                     const dynamic::variable&,
                     const unsigned int);
};

template <typename Archive>
struct load_overloader< Archive, typename dynamic::variable >
{
    static void load(Archive&,
                     dynamic::variable&,
                     const unsigned int);
};

template <typename Archive>
struct serialize_overloader<Archive,
                            typename dynamic::variable,
                            typename std::enable_if<Archive::is_loading::value>::type>
{
    static void serialize(Archive& ar,
                          dynamic::variable& data,
                          const unsigned int version)
    {
        boost::serialization::split_free(ar, data, version);
    }
};

template <typename Archive>
struct serialize_overloader<Archive,
                            typename dynamic::variable,
                            typename std::enable_if<Archive::is_saving::value>::type>
{
    static void serialize(Archive& ar,
                          const dynamic::variable& data,
                          const unsigned int version)
    {
        boost::serialization::split_free(ar, data, version);
    }
};

} // namespace serialization
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_SERIALIZATION_DYNAMIC_VARIABLE_HPP
