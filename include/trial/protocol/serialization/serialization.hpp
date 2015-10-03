#ifndef TRIAL_PROTOCOL_SERIALIZATION_SERIALIZATION_HPP
#define TRIAL_PROTOCOL_SERIALIZATION_SERIALIZATION_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2015 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <boost/utility/enable_if.hpp>
#include <boost/serialization/split_free.hpp>

// Non-intrusive serialization

namespace trial
{
namespace protocol
{
namespace serialization
{

// Generalized functors.
//
// These must be specialized by the concrete protocols.

template <typename Archive, typename Value>
struct save_overloader
{
    static void save(Archive&, const Value&, const unsigned int);
};

template <typename Archive, typename Value>
struct load_overloader
{
    static void load(Archive&, const Value&, const unsigned int);
};

template <typename Value, typename Enable = void>
struct serialize_overloader
{
    template <typename Archive>
    static void serialize(Archive&, Value&, const unsigned int);
};

} // namespace serialization
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_SERIALIZATION_SERIALIZATION_HPP
