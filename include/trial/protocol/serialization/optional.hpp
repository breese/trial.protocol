#ifndef TRIAL_PROTOCOL_SERIALIZATION_OPTIONAL_HPP
#define TRIAL_PROTOCOL_SERIALIZATION_OPTIONAL_HPP

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
#include <trial/protocol/serialization/serialization.hpp>

namespace trial
{
namespace protocol
{
namespace serialization
{

template <typename Archive, typename T>
struct save_functor< Archive, typename boost::optional<T> >
{
    static void save(Archive&,
                     const boost::optional<T>&,
                     const unsigned int);
};

template <typename Archive, typename T>
struct load_functor< Archive, typename boost::optional<T> >
{
    static void load(Archive&,
                     boost::optional<T>&,
                     const unsigned int);
};

template <typename T>
struct serialize_functor< typename boost::optional<T> >
{
    template <typename Archive>
    static typename boost::enable_if<typename Archive::is_loading, void>::type
    serialize(Archive& ar,
              boost::optional<T>& data,
              const unsigned int version)
    {
        boost::serialization::split_free(ar, data, version);
    }

    template <typename Archive>
    static typename boost::enable_if<typename Archive::is_saving, void>::type
    serialize(Archive& ar,
              const boost::optional<T>& data,
              const unsigned int version)
    {
        boost::serialization::split_free(ar, data, version);
    }
};

} // namespace serialization
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_SERIALIZATION_OPTIONAL_HPP
