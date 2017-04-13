#ifndef TRIAL_PROTOCOL_BINTOKEN_SERIALIZATION_DYNAMIC_VARIABLE_HPP
#define TRIAL_PROTOCOL_BINTOKEN_SERIALIZATION_DYNAMIC_VARIABLE_HPP

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
#include <trial/protocol/bintoken/serialization/serialization.hpp>
#include <trial/protocol/serialization/dynamic/variable.hpp>
#include <trial/protocol/bintoken/token.hpp>

namespace trial
{
namespace protocol
{
namespace serialization
{

template <>
struct save_overloader< protocol::bintoken::oarchive,
                        typename dynamic::variable >
{
    static void save(protocol::bintoken::oarchive& ar,
                     const dynamic::variable& data,
                     const unsigned int protocol_version)
    {
        if (data.is<dynamic::variable::null_type>())
        {
            ar.template save<bintoken::token::null>();
        }
        else if (data.is<bool>())
        {
            ar.save(data.value<bool>());
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
            ar.template save<bintoken::token::begin_array>();
            ar.template save<std::size_t>(data.size());
            for (const auto& item : data)
            {
                ar.save_override(item, protocol_version);
            }
            ar.template save<bintoken::token::end_array>();
        }
        else if (data.is<dynamic::variable::map_type>())
        {
            ar.template save<bintoken::token::begin_assoc_array>();
            ar.template save<bintoken::token::null>();
            for (auto it = data.begin(); it != data.end(); ++it)
            {
                auto value = std::make_pair(it.key(), it.value());;
                ar.save_override(value, protocol_version);
            }
            ar.template save<bintoken::token::end_assoc_array>();
        }
        else
        {
            assert(false);
        }
    }
};

template <>
struct load_overloader< protocol::bintoken::iarchive,
                        typename dynamic::variable >
{
    static void load(protocol::bintoken::iarchive& ar,
                     dynamic::variable& data,
                     const unsigned int /* protocol_version */)
    {
        using namespace trial::protocol::bintoken;
        switch (ar.symbol())
        {
        case token::symbol::null:
            ar.template load<token::null>();
            data = dynamic::variable::null;
            break;

        case token::symbol::boolean:
            {
                bool value = {};
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

                boost::optional<std::size_t> count;
                ar.load_override(count);

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

        case token::symbol::begin_assoc_array:
            {
                ar.template load<token::begin_assoc_array>();

                boost::optional<std::size_t> count;
                ar.load_override(count);

                data = dynamic::variable::map();
                while (!ar.template at<token::end_assoc_array>())
                {
                    using map_type = dynamic::variable::map_type;
                    std::pair<map_type::key_type, map_type::mapped_type> value;
                    ar.load_override(value);
                    data += dynamic::variable::map({value});
                }
                ar.template load<token::end_assoc_array>();
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

#endif // TRIAL_PROTOCOL_BINTOKEN_SERIALIZATION_DYNAMIC_VARIABLE_HPP
