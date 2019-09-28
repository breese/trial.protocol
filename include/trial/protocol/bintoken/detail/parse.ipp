#ifndef TRIAL_PROTOCOL_BINTOKEN_DETAIL_PARSE_IPP
#define TRIAL_PROTOCOL_BINTOKEN_DETAIL_PARSE_IPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2018 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <trial/protocol/bintoken/error.hpp>
#include <trial/protocol/bintoken/reader.hpp>

namespace trial
{
namespace protocol
{
namespace bintoken
{
namespace detail
{

template <typename Allocator>
class basic_parser
{
public:
    using variable_type = dynamic::basic_variable<Allocator>;

    basic_parser(bintoken::reader& reader)
        : reader(reader)
    {}

    // Parse outer scope
    variable_type parse()
    {
        variable_type outer;

        switch (reader.symbol())
        {
        case token::symbol::begin_record:
            outer = parse_record();
            if (reader.symbol() == token::symbol::end_record)
                reader.next();
            break;

        case token::symbol::end_record:
            throw bintoken::error(make_error_code(bintoken::unexpected_token));

        case token::symbol::array:
            outer = parse_compact_array();
            break;

        case token::symbol::begin_array:
            outer = parse_array();
            if (reader.symbol() == token::symbol::end_array)
                reader.next();
            break;

        case token::symbol::end_array:
            throw bintoken::error(make_error_code(bintoken::unexpected_token));

        case token::symbol::begin_assoc_array:
            outer = parse_assoc_array();
            if (reader.symbol() == token::symbol::end_assoc_array)
                reader.next();
            break;
            
        case token::symbol::end_assoc_array:
            throw bintoken::error(make_error_code(bintoken::unexpected_token));

        case token::symbol::end:
            if (reader.literal().size() > 0)
                throw bintoken::error(make_error_code(bintoken::unexpected_token));
            break;

        case token::symbol::error:
            throw bintoken::error(reader.error());

        default:
            outer = parse_value();
            reader.next();
            break;
        }

        return outer;
    }

private:
    variable_type parse_record()
    {
        assert(reader.symbol() == token::symbol::begin_record);

        auto scope = dynamic::basic_array<Allocator>::make();

        while (reader.next())
        {
            switch (reader.symbol())
            {
            case token::symbol::begin_record:
                scope.insert(parse_record());
                break;

            case token::symbol::end_record:
                return scope;

            case token::symbol::array:
                scope.insert(parse_compact_array());
                break;

            case token::symbol::begin_array:
                scope.insert(parse_array());
                break;

            case token::symbol::end_array:
                throw bintoken::error(make_error_code(bintoken::unexpected_token));

            case token::symbol::begin_assoc_array:
                scope.insert(parse_assoc_array());
                break;

            case token::symbol::end_assoc_array:
                throw bintoken::error(make_error_code(bintoken::unexpected_token));

            default:
                scope.insert(parse_value());
                break;
            }
        }

        throw bintoken::error(make_error_code(bintoken::expected_end_array));
    }

    variable_type parse_array()
    {
        assert(reader.symbol() == token::symbol::begin_array);

        auto scope = dynamic::basic_array<Allocator>::make();

        while (reader.next())
        {
            switch (reader.symbol())
            {
            case token::symbol::begin_record:
                scope.insert(parse_record());
                break;

            case token::symbol::end_record:
                throw bintoken::error(make_error_code(bintoken::unexpected_token));

            case token::symbol::array:
                scope.insert(parse_compact_array());
                break;

            case token::symbol::begin_array:
                scope.insert(parse_array());
                break;

            case token::symbol::end_array:
                return scope;

            case token::symbol::begin_assoc_array:
                scope.insert(parse_assoc_array());
                break;

            case token::symbol::end_assoc_array:
                throw bintoken::error(make_error_code(bintoken::unexpected_token));

            default:
                scope.insert(parse_value());
                break;
            }
        }

        throw bintoken::error(make_error_code(bintoken::expected_end_array));
    }

    variable_type parse_assoc_array()
    {
        assert(reader.symbol() == token::symbol::begin_assoc_array);

        auto scope = dynamic::basic_map<Allocator>::make();

        while (reader.next())
        {
            // Key
            dynamic::variable key;
            switch (reader.symbol())
            {
            case token::symbol::end_assoc_array:
                return scope;

            case token::symbol::boolean:
            case token::symbol::integer:
            case token::symbol::real:
            case token::symbol::string:
                key = parse_value();
                break;

            default:
                throw bintoken::error(make_error_code(bintoken::incompatible_type));
            }

            if (!reader.next())
                throw bintoken::error(make_error_code(bintoken::invalid_value));

            // Value
            switch (reader.symbol())
            {
            case token::symbol::begin_record:
                scope.insert({ std::move(key), parse_record() });
                break;

            case token::symbol::end_record:
                throw bintoken::error(make_error_code(bintoken::unexpected_token));

            case token::symbol::begin_array:
                scope.insert({ std::move(key), parse_array() });
                break;

            case token::symbol::begin_assoc_array:
                scope.insert({ std::move(key), parse_assoc_array() });
                break;

            case token::symbol::end_array:
            case token::symbol::end_assoc_array:
                throw bintoken::error(make_error_code(bintoken::unexpected_token));

            case token::symbol::error:
                throw bintoken::error(reader.error());

            case token::symbol::end:
                break;

            default:
                scope.insert({ std::move(key), parse_value() });
                break;
            }
        }

        if (reader.literal().size() > 0)
            throw bintoken::error(make_error_code(bintoken::expected_end_assoc_array));

        return scope;
    }

    variable_type parse_compact_array()
    {
        assert(reader.symbol() == token::symbol::array);

        switch (reader.code())
        {
        case token::code::array8_int8:
        case token::code::array16_int8:
        case token::code::array32_int8:
        case token::code::array64_int8:
            {
                std::vector<std::int8_t> input(reader.length());
                reader.array<std::int8_t>(input.data(), input.size());
                reader.next();
                return dynamic::basic_array<Allocator>::make(input.begin(), input.end());
            }

        case token::code::array8_int16:
        case token::code::array16_int16:
        case token::code::array32_int16:
        case token::code::array64_int16:
            {
                std::vector<std::int16_t> input(reader.length());
                reader.array<std::int16_t>(input.data(), input.size());
                reader.next();
                return dynamic::basic_array<Allocator>::make(input.begin(), input.end());
            }

        case token::code::array8_int32:
        case token::code::array16_int32:
        case token::code::array32_int32:
        case token::code::array64_int32:
            {
                std::vector<std::int32_t> input(reader.length());
                reader.array<std::int32_t>(input.data(), input.size());
                reader.next();
                return dynamic::basic_array<Allocator>::make(input.begin(), input.end());
            }

        case token::code::array8_int64:
        case token::code::array16_int64:
        case token::code::array32_int64:
        case token::code::array64_int64:
            {
                std::vector<std::int64_t> input(reader.length());
                reader.array<std::int64_t>(input.data(), input.size());
                reader.next();
                return dynamic::basic_array<Allocator>::make(input.begin(), input.end());
            }

        default:
            throw bintoken::error(make_error_code(bintoken::unexpected_token));
        }
    }

    variable_type parse_value()
    {
        switch (reader.code())
        {
        case token::code::null:
            return trial::dynamic::null;

        case token::code::false_value:
            return false;

        case token::code::true_value:
            return true;

        case token::code::int8:
            return reader.template value<std::int8_t>();

        case token::code::int16:
            return reader.template value<std::int16_t>();

        case token::code::int32:
            return reader.template value<std::int32_t>();

        case token::code::int64:
            return reader.template value<std::int64_t>();

        case token::code::float32:
            return reader.template value<float>();

        case token::code::float64:
            return reader.template value<double>();

        case token::code::string8:
        case token::code::string16:
        case token::code::string32:
        case token::code::string64:
            return reader.template value<std::string>();

        default:
            throw bintoken::error(make_error_code(bintoken::unexpected_token));
        }
    }

    bintoken::reader& reader;
};

} // namespace detail
} // namespace bintoken
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_BINTOKEN_DETAIL_PARSE_IPP
