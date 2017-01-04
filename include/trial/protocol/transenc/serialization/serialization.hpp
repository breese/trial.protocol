#ifndef TRIAL_PROTOCOL_TRANSENC_SERIALIZATION_SERIALIZATION_HPP
#define TRIAL_PROTOCOL_TRANSENC_SERIALIZATION_SERIALIZATION_HPP

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
#include <trial/protocol/transenc/serialization/iarchive.hpp>
#include <trial/protocol/transenc/serialization/oarchive.hpp>
#include <trial/protocol/transenc/token.hpp>

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
struct save_overloader<transenc::oarchive,
                       Value,
                       typename boost::enable_if_c<has_save<transenc::oarchive, Value>::value>::type>
{
    static void save(transenc::oarchive& ar,
                     const Value& data,
                     const unsigned int)
    {
        ar.save<transenc::token::begin_record>();
        data.save(ar);
        ar.save<transenc::token::end_record>();
    }
};

template <typename Value>
struct load_overloader<transenc::iarchive,
                       Value,
                       typename boost::enable_if_c<has_load<transenc::iarchive, Value>::value>::type>
{
    static void load(transenc::iarchive& ar,
                     const Value& data,
                     const unsigned int)
    {
        ar.load<transenc::token::begin_record>();
        data.load(ar);
        ar.load<transenc::token::end_record>();
    }
};

template <typename Value>
struct serialize_overloader<transenc::iarchive,
                            Value,
                            typename boost::enable_if_c<has_serialize<transenc::iarchive, Value>::value ||
                                                        has_load<transenc::iarchive, Value>::value>::type>
{
    static void serialize(transenc::iarchive& ar,
                          Value& data,
                          const unsigned int protocol_version)
    {
        ar.template load<transenc::token::begin_record>();
        data.serialize(ar, protocol_version);
        ar.template load<transenc::token::end_record>();
    }
};

template <typename Value>
struct serialize_overloader<transenc::oarchive,
                            Value,
                            typename boost::enable_if_c<has_serialize<transenc::oarchive, Value>::value ||
                                                        has_save<transenc::oarchive, Value>::value>::type>
{
    static void serialize(transenc::oarchive& ar,
                          Value& data,
                          const unsigned int protocol_version)
    {
        ar.template save<transenc::token::begin_record>();
        data.serialize(ar, protocol_version);
        ar.template save<transenc::token::end_record>();
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
void save(trial::protocol::transenc::oarchive& ar,
          const Value& data,
          const unsigned int version)
{
    using namespace trial::protocol::serialization;
    save_overloader<trial::protocol::transenc::oarchive, Value>::save(ar, data, version);
}

// Boost.Serialization does not support perfect forwarding so we need two
// overloads (for const and non-const values)

template <typename Value>
void serialize(trial::protocol::transenc::oarchive& ar,
               const Value& data,
               const unsigned int version)
{
    using namespace trial::protocol::serialization;
    serialize_overloader<trial::protocol::transenc::oarchive, Value>::serialize(ar, data, version);
}

template <typename Value>
void serialize(trial::protocol::transenc::oarchive& ar,
               Value& data,
               const unsigned int version)
{
    using namespace trial::protocol::serialization;
    serialize_overloader<trial::protocol::transenc::oarchive, Value>::serialize(ar, data, version);
}

//-----------------------------------------------------------------------------
// iarchive
//-----------------------------------------------------------------------------

template <typename Value>
void load(trial::protocol::transenc::iarchive& ar,
          Value& data,
          const unsigned int version)
{
    using namespace trial::protocol::serialization;
    load_overloader<trial::protocol::transenc::iarchive, Value>::load(ar, data, version);
}

template <typename Value>
void serialize(trial::protocol::transenc::iarchive& ar,
               Value& data,
               const unsigned int version)
{
    using namespace trial::protocol::serialization;
    serialize_overloader<trial::protocol::transenc::iarchive, Value>::serialize(ar, data, version);
}


} // namespace serialization
} // namespace boost

#endif // TRIAL_PROTOCOL_TRANSENC_SERIALIZATION_SERIALIZATION_HPP
