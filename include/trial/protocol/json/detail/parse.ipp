#ifndef TRIAL_PROTOCOL_JSON_DETAIL_PARSE_IPP
#define TRIAL_PROTOCOL_JSON_DETAIL_PARSE_IPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2018 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <limits>
#include <trial/protocol/json/error.hpp>
#include <trial/protocol/json/reader.hpp>
#include <trial/protocol/json/detail/compact.hpp>

namespace trial
{
namespace protocol
{
namespace json
{
namespace detail
{

template <typename CharT, typename Allocator>
class basic_parser
{
public:
    using variable_type = dynamic::basic_variable<Allocator>;
    using string_type = typename variable_type::string_type;

    basic_parser(basic_reader<CharT>& reader)
        : reader(reader)
    {}

    // Parse outer scope
    variable_type parse()
    {
        variable_type outer;

        switch (reader.symbol())
        {
        case token::symbol::begin_array:
            outer = parse_array();
            if (reader.symbol() == token::symbol::end_array)
                reader.next();
            break;

        case token::symbol::end_array:
            throw json::error(make_error_code(json::unbalanced_end_array));

        case token::symbol::begin_object:
            outer = parse_object();
            if (reader.symbol() == token::symbol::end_object)
                reader.next();
            break;
            
        case token::symbol::end_object:
            throw json::error(make_error_code(json::unbalanced_end_object));

        case token::symbol::end:
            if (reader.literal().size() > 0)
                throw json::error(make_error_code(json::unexpected_token));
            break;

        case token::symbol::error:
            throw json::error(reader.error());

        default:
            outer = parse_value();
            reader.next();
            break;
        }

        return outer;
    }

private:
    variable_type parse_array()
    {
        assert(reader.symbol() == token::symbol::begin_array);

        auto scope = dynamic::basic_array<Allocator>::make();

        while (reader.next())
        {
            switch (reader.symbol())
            {
            case token::symbol::begin_array:
                scope.insert(parse_array());
                break;

            case token::symbol::end_array:
                return scope;

            case token::symbol::begin_object:
                scope.insert(parse_object());
                break;

            case token::symbol::end_object:
                throw json::error(make_error_code(json::unbalanced_end_object));

            default:
                scope.insert(parse_value());
                break;
            }
        }

        throw json::error(make_error_code(json::expected_end_array));
    }

    variable_type parse_object()
    {
        assert(reader.symbol() == token::symbol::begin_object);

        auto scope = dynamic::basic_map<Allocator>::make();

        while (reader.next())
        {
            // Key
            string_type key;
            key.reserve(reader.literal().size());
            switch (reader.symbol())
            {
            case token::symbol::end_object:
                return scope;
            case token::symbol::string:
            {
                const auto err = reader.value(key);
                if (err != json::no_error)
                    throw json::error(make_error_code(err));
                break;
            }
            default:
                throw json::error(make_error_code(json::invalid_key));
            }

            if (!reader.next())
                throw json::error(make_error_code(json::invalid_value));

            // Value
            switch (reader.symbol())
            {
            case token::symbol::begin_array:
                scope.insert({ std::move(key), std::move(parse_array()) });
                break;

            case token::symbol::begin_object:
                scope.insert({ std::move(key), std::move(parse_object()) });
                break;

            case token::symbol::end_array:
            case token::symbol::end_object:
                throw json::error(make_error_code(json::unexpected_token));

            case token::symbol::error:
                throw json::error(reader.error());

            case token::symbol::end:
                break;

            default:
                scope.insert({ std::move(key), std::move(parse_value()) });
                break;
            }
        }

        if (reader.literal().size() > 0)
            throw json::error(make_error_code(json::expected_end_object));

        return scope;
    }

    variable_type parse_value()
    {
        switch (reader.symbol())
        {
        case token::symbol::null:
            return trial::dynamic::null;

        case token::symbol::boolean:
            return reader.template value<bool>();

        case token::symbol::integer:
            if (reader.literal()[0] == traits::alphabet<CharT>::minus)
            {
                return compact<variable_type>(reader.template value<std::intmax_t>());
            }
            else
            {
                return compact<variable_type>(reader.template value<std::uintmax_t>());
            }

        case token::symbol::real:
            return compact<variable_type>(reader.template value<long double>());

        case token::symbol::string:
        {
            string_type value;
            value.reserve(reader.literal().size());
            const auto err = reader.value(value);
            if (err != json::no_error)
                throw json::error(make_error_code(err));
            return value;
        }

        default:
            throw json::error(make_error_code(json::unexpected_token));
        }
    }

    json::basic_reader<CharT>& reader;
};

} // namespace detail
} // namespace json
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_JSON_DETAIL_PARSE_IPP
