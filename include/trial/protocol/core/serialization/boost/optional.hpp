#ifndef TRIAL_PROTOCOL_CORE_SERIALIZATION_BOOST_OPTIONAL_HPP
#define TRIAL_PROTOCOL_CORE_SERIALIZATION_BOOST_OPTIONAL_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2015 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <boost/optional.hpp>
#include <boost/none.hpp>
#include <trial/protocol/core/serialization/serialization.hpp>

namespace trial
{
namespace protocol
{
namespace serialization
{

template <typename Archive, typename T>
struct save_overloader< Archive, typename boost::optional<T> >
{
    static void save(Archive&,
                     const boost::optional<T>&,
                     const unsigned int);
};

template <typename Archive, typename T>
struct load_overloader< Archive, typename boost::optional<T> >
{
    static void load(Archive&,
                     boost::optional<T>&,
                     const unsigned int);
};

template <typename Archive, typename T>
struct serialize_overloader<Archive,
                            typename boost::optional<T>,
                            typename std::enable_if<Archive::is_loading::value>::type>
{
    static void serialize(Archive& ar,
                          boost::optional<T>& data,
                          const unsigned int version)
    {
        boost::serialization::split_free(ar, data, version);
    }
};

template <typename Archive, typename T>
struct serialize_overloader<Archive,
                            typename boost::optional<T>,
                            typename std::enable_if<Archive::is_saving::value>::type>
{
    static void serialize(Archive& ar,
                          const boost::optional<T>& data,
                          const unsigned int version)
    {
        boost::serialization::split_free(ar, data, version);
    }
};

} // namespace serialization
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_CORE_SERIALIZATION_BOOST_OPTIONAL_HPP
