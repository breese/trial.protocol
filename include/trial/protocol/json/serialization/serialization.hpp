#ifndef TRIAL_PROTOCOL_JSON_SERIALIZATION_SERIALIZATION_HPP
#define TRIAL_PROTOCOL_JSON_SERIALIZATION_SERIALIZATION_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2015 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <trial/protocol/serialization/serialization.hpp>
#include <trial/protocol/json/serialization/iarchive.hpp>
#include <trial/protocol/json/serialization/oarchive.hpp>

//-----------------------------------------------------------------------------
// Records
//-----------------------------------------------------------------------------

namespace trial
{
namespace protocol
{
namespace serialization
{

template <typename Value>
struct save_overloader<json::oarchive, Value>
{
    static void save(json::oarchive& ar,
                     const Value& data,
                     const unsigned int protocol_version)
    {
        ar.template save<json::token::begin_array>();
        data.save(ar, protocol_version);
        ar.template save<json::token::end_array>();
    }
};

template <typename Value>
struct load_overloader<json::iarchive, Value>
{
    static void load(json::iarchive& ar,
                     const Value& data,
                     const unsigned int protocol_version)
    {
        ar.template load<json::token::begin_array>();
        data.load(ar, protocol_version);
        ar.template load<json::token::end_array>();
    }
};

template <typename Value>
struct serialize_overloader<Value>
{
    template <typename Archive>
    static typename boost::enable_if<typename boost::is_base_of<json::iarchive, Archive>::type, void>::type
    serialize(Archive& ar,
              Value& data,
              const unsigned int protocol_version)
    {
        ar.template load<json::token::begin_array>();
        data.serialize(ar, protocol_version);
        ar.template load<json::token::end_array>();
    }

    template <typename Archive>
    static typename boost::enable_if<typename boost::is_base_of<json::oarchive, Archive>::type, void>::type
    serialize(Archive& ar,
              Value& data,
              const unsigned int protocol_version)
    {
        ar.template save<json::token::begin_array>();
        data.serialize(ar, protocol_version);
        ar.template save<json::token::end_array>();
    }
};

} // namespace serialization
} // namespace protocol 
} // namespace trial

namespace boost
{
namespace serialization
{

//-----------------------------------------------------------------------------
// oarchive
//-----------------------------------------------------------------------------

// C++ does not have partial specialization of template functions so we use
// functors to achieve the same effect.

template <typename Value>
void save(trial::protocol::json::oarchive& ar,
          const Value& data,
          const unsigned int version)
{
    using namespace trial::protocol::serialization;
    save_overloader<trial::protocol::json::oarchive, Value>::save(ar, data, version);
}

// Boost.Serialization does not support perfect forwarding so we need two
// overloads (for const and non-const values)

template <typename Value>
void serialize(trial::protocol::json::oarchive& ar,
               const Value& data,
               const unsigned int version)
{
    using namespace trial::protocol::serialization;
    serialize_overloader<Value>::serialize(ar, data, version);
}

template <typename Value>
void serialize(trial::protocol::json::oarchive& ar,
               Value& data,
               const unsigned int version)
{
    using namespace trial::protocol::serialization;
    serialize_overloader<Value>::serialize(ar, data, version);
}

//-----------------------------------------------------------------------------
// iarchive
//-----------------------------------------------------------------------------

template <typename Value>
void load(trial::protocol::json::iarchive& ar,
          Value& data,
          const unsigned int version)
{
    using namespace trial::protocol::serialization;
    load_overloader<trial::protocol::json::iarchive, Value>::load(ar, data, version);
}

template <typename Value>
void serialize(trial::protocol::json::iarchive& ar,
               Value& data,
               const unsigned int version)
{
    using namespace trial::protocol::serialization;
    serialize_overloader<Value>::serialize(ar, data, version);
}


} // namespace serialization
} // namespace boost

#endif // TRIAL_PROTOCOL_JSON_SERIALIZATION_SERIALIZATION_HPP
