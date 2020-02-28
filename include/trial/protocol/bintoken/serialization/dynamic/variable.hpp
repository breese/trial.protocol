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
        switch (data.code())
        {
        case dynamic::code::null:
            ar.template save<bintoken::token::null>();
            break;

        case dynamic::code::boolean:
            ar.save(data.value<bool>());
            break;

        case dynamic::code::signed_char:
            ar.save(data.value<signed char>());
            break;

        case dynamic::code::unsigned_char:
            ar.save(data.value<unsigned char>());
            break;

        case dynamic::code::signed_short_integer:
            ar.save(data.value<signed short int>());
            break;

        case dynamic::code::unsigned_short_integer:
            ar.save(data.value<unsigned short int>());
            break;

        case dynamic::code::signed_integer:
            ar.save(data.value<signed int>());
            break;

        case dynamic::code::unsigned_integer:
            ar.save(data.value<unsigned int>());
            break;

        case dynamic::code::signed_long_integer:
            ar.save(data.value<signed long int>());
            break;

        case dynamic::code::unsigned_long_integer:
            ar.save(data.value<unsigned long int>());
            break;

        case dynamic::code::signed_long_long_integer:
            ar.save(data.value<signed long long int>());
            break;

        case dynamic::code::unsigned_long_long_integer:
            ar.save(data.value<unsigned long long int>());
            break;

        case dynamic::code::real:
            ar.save(data.value<float>());
            break;

        case dynamic::code::long_real:
            ar.save(data.value<double>());
            break;

        case dynamic::code::long_long_real:
            // Format only supports 64-bit floats
            ar.save(data.value<double>());
            break;

        case dynamic::code::string:
            ar.save(data.value<dynamic::string>());
            break;

        case dynamic::code::wstring:
        case dynamic::code::u16string:
        case dynamic::code::u32string:
            throw bintoken::error(bintoken::incompatible_type);

        case dynamic::code::array:
            ar.template save<bintoken::token::begin_array>();
            ar.template save<std::size_t>(data.size());
            for (const auto& item : data)
            {
                ar.save_override(item, protocol_version);
            }
            ar.template save<bintoken::token::end_array>();
            break;

        case dynamic::code::map:
            ar.template save<bintoken::token::begin_assoc_array>();
            ar.template save<bintoken::token::null>();
            for (auto it = data.begin(); it != data.end(); ++it)
            {
                auto value = std::make_pair(it.key(), it.value());
                ar.save_override(value.first, protocol_version);
                ar.save_override(value.second, protocol_version);
            }
            ar.template save<bintoken::token::end_assoc_array>();
            break;
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
        switch (ar.code())
        {
        case token::code::null:
            ar.template load<token::null>();
            data = dynamic::null;
            break;

        case token::code::false_value:
        case token::code::true_value:
            {
                bool value = {};
                ar.load(value);
                data = value;
            }
            break;

        case token::code::int8:
            {
                std::int8_t value = {};
                ar.load(value);
                data = value;
            }
            break;

        case token::code::int16:
            {
                std::int16_t value = {};
                ar.load(value);
                data = value;
            }
            break;

        case token::code::int32:
            {
                std::int32_t value = {};
                ar.load(value);
                data = value;
            }
            break;

        case token::code::int64:
            {
                std::int64_t value = {};
                ar.load(value);
                data = value;
            }
            break;

        case token::code::float32:
            {
                float value = {};
                ar.load(value);
                data = value;
            }
            break;

        case token::code::float64:
            {
                double value = {};
                ar.load(value);
                data = value;
            }
            break;

        case token::code::string8:
        case token::code::string16:
        case token::code::string32:
        case token::code::string64:
            {
                std::string value;
                ar.load(value);
                data = value;
            }
            break;

        case token::code::begin_array:
            {
                ar.template load<token::begin_array>();

                boost::optional<std::size_t> count;
                ar.load_override(count);

                data = dynamic::array::make();
                while (!ar.template at<token::end_array>())
                {
                    dynamic::variable value;
                    ar.load_override(value);
                    data.insert(data.end(), value);
                }
                ar.template load<token::end_array>();
            }
            break;

        case token::code::deprecated_begin_assoc_array:
            {
                ar.template load<token::deprecated_begin_assoc_array>();

                boost::optional<std::size_t> count;
                ar.load_override(count);

                data = dynamic::map::make();
                while (!ar.template at<token::deprecated_end_assoc_array>())
                {
                    std::pair<std::string, dynamic::variable> value;
                    ar.load_override(value);
                    data.insert(data.end(), { std::move(value.first), std::move(value.second) });
                }
                ar.template load<token::deprecated_end_assoc_array>();
            }
            break;

        case token::code::begin_assoc_array:
            {
                ar.template load<token::begin_assoc_array>();

                boost::optional<std::size_t> count;
                ar.load_override(count);

                data = dynamic::map::make();
                while (!ar.template at<token::end_assoc_array>())
                {
                    std::pair<std::string, dynamic::variable> value;
                    ar.load_override(value.first);
                    ar.load_override(value.second);
                    data.insert(data.end(), { std::move(value.first), std::move(value.second) });
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
