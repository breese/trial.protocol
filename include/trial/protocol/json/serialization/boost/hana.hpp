///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2021 Vinícius dos Santos Oliveira
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#ifndef TRIAL_PROTOCOL_JSON_SERIALIZATION_BOOST_HANA_HPP
#define TRIAL_PROTOCOL_JSON_SERIALIZATION_BOOST_HANA_HPP

#include <trial/protocol/json/serialization/serialization.hpp>
#include <boost/hana.hpp>
#include <trial/protocol/json/token.hpp>
#include <trial/protocol/json/partial/skip.hpp>

namespace trial
{
namespace protocol
{
namespace serialization
{

template <typename CharT, typename Value>
struct save_overloader<json::basic_oarchive<CharT>,
                       Value,
                       std::enable_if_t<boost::hana::Struct<Value>::value>>
{
    static void save(json::basic_oarchive<CharT>& ar,
                     const Value& data,
                     const unsigned int /*protocol_version*/)
    {
        using string_view = core::detail::basic_string_view<CharT>;

        ar.template save<json::token::begin_object>();
        boost::hana::for_each(data, [&ar](auto member) {
            auto key = boost::hana::first(member);
            ar.save(string_view(key.c_str(), boost::hana::size(key)));
            // TODO: what if subvalue uses old reflection infra? then it
            // requires us to write the necessary framing (begin_array and
            // end_array)
            ar << boost::hana::second(member);
        });
        ar.template save<json::token::end_object>();
    }
};

template <typename CharT, typename Value>
struct load_overloader<json::basic_iarchive<CharT>,
                       Value,
                       std::enable_if_t<boost::hana::Struct<Value>::value>>
{
    static void load(json::basic_iarchive<CharT>& ar,
                     Value& data,
                     const unsigned int /*protocol_version*/)
    {
        ar.template load<json::token::begin_object>();
        for (;;) {
            if (ar.symbol() == json::token::symbol::end_object) {
                ar.template load<json::token::end_object>();
                break;
            }

            // skip key
            //json::partial::skip(ar.reader());
            json::partial::skip(const_cast<json::reader&>(ar.reader()));
            // skip value
            //json::partial::skip(ar.reader());
            json::partial::skip(const_cast<json::reader&>(ar.reader()));

            // TODO: actually decode stuff
            //ar >> x;
        }
        ar.template load<json::token::end_object>();
    }
};

} // namespace serialization
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_JSON_SERIALIZATION_BOOST_HANA_HPP
