#ifndef TRIAL_PROTOCOL_BINTOKEN_SERIALIZATION_SERIALIZATION_HPP
#define TRIAL_PROTOCOL_BINTOKEN_SERIALIZATION_SERIALIZATION_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2015 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <trial/protocol/core/serialization/serialization.hpp>
#include <trial/protocol/bintoken/serialization/iarchive.hpp>
#include <trial/protocol/bintoken/serialization/oarchive.hpp>
#include <trial/protocol/bintoken/token.hpp>

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
struct save_overloader<bintoken::oarchive,
                       Value,
                       typename std::enable_if<has_save<bintoken::oarchive, Value>::value>::type>
{
    static void save(bintoken::oarchive& ar,
                     const Value& data,
                     const unsigned int protocol_version)
    {
        ar.save<bintoken::token::begin_record>();
        data.save(ar, protocol_version);
        ar.save<bintoken::token::end_record>();
    }
};

template <typename Value>
struct load_overloader<bintoken::iarchive,
                       Value,
                       typename std::enable_if<has_load<bintoken::iarchive, Value>::value>::type>
{
    static void load(bintoken::iarchive& ar,
                     Value& data,
                     const unsigned int protocol_version)
    {
        ar.load<bintoken::token::begin_record>();
        data.load(ar, protocol_version);
        ar.load<bintoken::token::end_record>();
    }
};

template <typename Value>
struct serialize_overloader<bintoken::iarchive,
                            Value,
                            typename std::enable_if<has_serialize<bintoken::iarchive, Value>::value ||
                                                    has_load<bintoken::iarchive, Value>::value>::type>
{
    static void serialize(bintoken::iarchive& ar,
                          Value& data,
                          const unsigned int protocol_version)
    {
        ar.template load<bintoken::token::begin_record>();
        data.serialize(ar, protocol_version);
        ar.template load<bintoken::token::end_record>();
    }
};

template <typename Value>
struct serialize_overloader<bintoken::oarchive,
                            Value,
                            typename std::enable_if<has_serialize<bintoken::oarchive, Value>::value ||
                                                    has_save<bintoken::oarchive, Value>::value>::type>
{
    static void serialize(bintoken::oarchive& ar,
                          Value& data,
                          const unsigned int protocol_version)
    {
        ar.template save<bintoken::token::begin_record>();
        data.serialize(ar, protocol_version);
        ar.template save<bintoken::token::end_record>();
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
void save(trial::protocol::bintoken::oarchive& ar,
          const Value& data,
          const unsigned int version)
{
    using namespace trial::protocol::serialization;
    save_overloader<trial::protocol::bintoken::oarchive, Value>::save(ar, data, version);
}

// Boost.Serialization does not support perfect forwarding so we need two
// overloads (for const and non-const values)

template <typename Value>
void serialize(trial::protocol::bintoken::oarchive& ar,
               const Value& data,
               const unsigned int version)
{
    using namespace trial::protocol::serialization;
    serialize_overloader<trial::protocol::bintoken::oarchive, Value>::serialize(ar, data, version);
}

template <typename Value>
void serialize(trial::protocol::bintoken::oarchive& ar,
               Value& data,
               const unsigned int version)
{
    using namespace trial::protocol::serialization;
    serialize_overloader<trial::protocol::bintoken::oarchive, Value>::serialize(ar, data, version);
}

//-----------------------------------------------------------------------------
// iarchive
//-----------------------------------------------------------------------------

template <typename Value>
void load(trial::protocol::bintoken::iarchive& ar,
          Value& data,
          const unsigned int version)
{
    using namespace trial::protocol::serialization;
    load_overloader<trial::protocol::bintoken::iarchive, Value>::load(ar, data, version);
}

template <typename Value>
void serialize(trial::protocol::bintoken::iarchive& ar,
               Value& data,
               const unsigned int version)
{
    using namespace trial::protocol::serialization;
    serialize_overloader<trial::protocol::bintoken::iarchive, Value>::serialize(ar, data, version);
}


} // namespace serialization
} // namespace boost

#endif // TRIAL_PROTOCOL_BINTOKEN_SERIALIZATION_SERIALIZATION_HPP
