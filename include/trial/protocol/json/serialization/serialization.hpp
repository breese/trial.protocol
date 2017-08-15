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

#include <trial/protocol/core/serialization/serialization.hpp>
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

template <typename CharT, typename Value>
struct save_overloader<json::basic_oarchive<CharT>,
                       Value,
                       typename std::enable_if<has_save<json::basic_oarchive<CharT>, Value>::value>::type>
{
    static void save(json::basic_oarchive<CharT>& ar,
                     const Value& data,
                     const unsigned int protocol_version)
    {
        ar.template save<json::token::begin_array>();
        data.save(ar, protocol_version);
        ar.template save<json::token::end_array>();
    }
};

template <typename CharT, typename Value>
struct load_overloader<json::basic_iarchive<CharT>,
                       Value,
                       typename std::enable_if<has_load<json::basic_iarchive<CharT>, Value>::value>::type>
{
    static void load(json::basic_iarchive<CharT>& ar,
                     const Value& data,
                     const unsigned int protocol_version)
    {
        ar.template load<json::token::begin_array>();
        data.load(ar, protocol_version);
        ar.template load<json::token::end_array>();
    }
};

template <typename CharT, typename Value>
struct serialize_overloader<json::basic_iarchive<CharT>,
                            Value,
                            typename std::enable_if<has_serialize<json::basic_iarchive<CharT>, Value>::value ||
                                                    has_load<json::basic_iarchive<CharT>, Value>::value>::type>
{
    static void serialize(json::basic_iarchive<CharT>& ar,
                          Value& data,
                          const unsigned int protocol_version)
    {
        ar.template load<json::token::begin_array>();
        data.serialize(ar, protocol_version);
        ar.template load<json::token::end_array>();
    }
};

template <typename CharT, typename Value>
struct serialize_overloader<json::basic_oarchive<CharT>,
                            Value,
                            typename std::enable_if<has_serialize<json::basic_oarchive<CharT>, Value>::value ||
                                                    has_save<json::basic_oarchive<CharT>, Value>::value>::type>
{
    static void serialize(json::basic_oarchive<CharT>& ar,
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

template <typename CharT, typename Value>
void save(trial::protocol::json::basic_oarchive<CharT>& ar,
          const Value& data,
          const unsigned int version)
{
    using namespace trial::protocol::serialization;
    save_overloader<trial::protocol::json::basic_oarchive<CharT>, Value>::save(ar, data, version);
}

// Boost.Serialization does not support perfect forwarding so we need two
// overloads (for const and non-const values)

template <typename CharT, typename Value>
void serialize(trial::protocol::json::basic_oarchive<CharT>& ar,
               const Value& data,
               const unsigned int version)
{
    using namespace trial::protocol::serialization;
    serialize_overloader<trial::protocol::json::basic_oarchive<CharT>, Value>::serialize(ar, data, version);
}

template <typename CharT, typename Value>
void serialize(trial::protocol::json::basic_oarchive<CharT>& ar,
               Value& data,
               const unsigned int version)
{
    using namespace trial::protocol::serialization;
    serialize_overloader<trial::protocol::json::basic_oarchive<CharT>, Value>::serialize(ar, data, version);
}

//-----------------------------------------------------------------------------
// iarchive
//-----------------------------------------------------------------------------

template <typename CharT, typename Value>
void load(trial::protocol::json::basic_iarchive<CharT>& ar,
          Value& data,
          const unsigned int version)
{
    using namespace trial::protocol::serialization;
    load_overloader<trial::protocol::json::basic_iarchive<CharT>, Value>::load(ar, data, version);
}

template <typename CharT, typename Value>
void serialize(trial::protocol::json::basic_iarchive<CharT>& ar,
               Value& data,
               const unsigned int version)
{
    using namespace trial::protocol::serialization;
    serialize_overloader<trial::protocol::json::basic_iarchive<CharT>, Value>::serialize(ar, data, version);
}


} // namespace serialization
} // namespace boost

#endif // TRIAL_PROTOCOL_JSON_SERIALIZATION_SERIALIZATION_HPP
