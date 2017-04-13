#ifndef TRIAL_PROTOCOL_JSON_SERIALIZATION_DYNAMIC_VARIABLE_HPP
#define TRIAL_PROTOCOL_JSON_SERIALIZATION_DYNAMIC_VARIABLE_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2017 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <trial/protocol/json/serialization/serialization.hpp>
#include <trial/protocol/serialization/dynamic/variable.hpp>
#include <trial/protocol/json/token.hpp>

namespace trial
{
namespace protocol
{
namespace serialization
{

template <typename CharT>
struct save_overloader< protocol::json::basic_oarchive<CharT>,
                        typename dynamic::variable >
{
    static void save(protocol::json::basic_oarchive<CharT>& ar,
                     const dynamic::variable& data,
                     const unsigned int protocol_version)
    {
        if (data.is<dynamic::variable::null_type>())
        {
            ar.template save<json::token::null>();
        }
        else if (data.is<dynamic::variable::boolean_type>())
        {
            ar.save(data.value<dynamic::variable::boolean_type>());
        }
        else if (data.same<signed short int>())
        {
            ar.save(data.value<signed short int>());
        }
        else if (data.same<unsigned short int>())
        {
            ar.save(data.value<unsigned short int>());
        }
        else if (data.same<signed int>())
        {
            ar.save(data.value<signed int>());
        }
        else if (data.same<unsigned int>())
        {
            ar.save(data.value<unsigned int>());
        }
        else if (data.same<signed long int>())
        {
            ar.save(data.value<signed long int>());
        }
        else if (data.same<unsigned long int>())
        {
            ar.save(data.value<unsigned long int>());
        }
        else if (data.same<signed long long int>())
        {
            ar.save(data.value<signed long long int>());
        }
        else if (data.same<unsigned long long int>())
        {
            ar.save(data.value<unsigned long long int>());
        }
        else if (data.is<dynamic::variable::number_type>())
        {
            ar.save(data.value<dynamic::variable::number_type>());
        }
        else if (data.is<dynamic::variable::string_type>())
        {
            ar.save(data.value<dynamic::variable::string_type>());
        }
        else if (data.is<dynamic::variable::array_type>())
        {
            ar.template save<json::token::begin_array>();
            for (const auto& item : data)
            {
                ar.save_override(item, protocol_version);
            }
            ar.template save<json::token::end_array>();
        }
        else if (data.is<dynamic::variable::map_type>())
        {
            ar.template save<json::token::begin_object>();
            for (auto it = data.begin(); it != data.end(); ++it)
            {
                ar.save_override(it.key(), protocol_version);
                ar.save_override(it.value(), protocol_version);
            }
            ar.template save<json::token::end_object>();
        }
        else
        {
            assert(false);
        }
    }
};

template <typename CharT>
struct load_overloader< protocol::json::basic_iarchive<CharT>,
                        typename dynamic::variable >
{
    static void load(protocol::json::basic_iarchive<CharT>& ar,
                     dynamic::variable& data,
                     const unsigned int /* protocol_version */)
    {
        using namespace trial::protocol::json;
        switch (ar.symbol())
        {
        case token::symbol::null:
            ar.template load<token::null>();
            data = dynamic::variable::null;
            break;

        case token::symbol::boolean:
            {
                dynamic::variable::boolean_type value = {};
                ar.load(value);
                data = value;
            }
            break;

        case token::symbol::integer:
            {
                std::intmax_t value = {};
                ar.load(value);
                data = value;
            }
            break;

        case token::symbol::number:
            {
                dynamic::variable::number_type value = {};
                ar.load(value);
                data = value;
            }
            break;

        case token::symbol::string:
            {
                dynamic::variable::string_type value = {};
                ar.load(value);
                data = value;
            }
            break;

        case token::symbol::begin_array:
            {
                ar.template load<token::begin_array>();
                data = dynamic::variable::array();
                while (!ar.template at<token::end_array>())
                {
                    dynamic::variable value;
                    ar.load_override(value);
                    data += value;
                }
                ar.template load<token::end_array>();
            }
            break;

        case token::symbol::begin_object:
            {
                ar.template load<token::begin_object>();
                data = dynamic::variable::map();
                while (!ar.template at<token::end_object>())
                {
                    dynamic::variable::map_type::key_type key;
                    ar.load_override(key);
                    dynamic::variable value;
                    ar.load_override(value);
                    data += dynamic::variable::map({{ key, value }});
                }
                ar.template load<token::end_object>();
            }
            break;

        default:
            assert(false);
            break;
        }
    }
};

} // namespace serialization
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_JSON_SERIALIZATION_DYNAMIC_VARIABLE_HPP
