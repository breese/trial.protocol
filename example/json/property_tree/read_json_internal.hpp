#ifndef TRIAL_PROTOCOL_JSON_EXAMPLE_READ_JSON_INTERNAL_HPP
#define TRIAL_PROTOCOL_JSON_EXAMPLE_READ_JSON_INTERNAL_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2015 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <algorithm>
#include <string>
#include <istream>
#include <trial/protocol/json/reader.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser/error.hpp>

namespace trial
{
namespace protocol
{
namespace json
{
namespace example
{

namespace detail
{

template <typename Ptree>
class parser
{
    typedef typename Ptree::key_type::value_type value_type;
    typedef typename Ptree::iterator iterator;
    typedef typename std::basic_string<value_type> string_type;

public:
    parser(const std::basic_string<value_type>& input,
           Ptree& result,
           const std::string& filename)
        : reader(input),
          result(result),
          filename(filename),
          begin(input.begin())
    {
    }

    void parse()
    {
        switch (symbol())
        {
        case json::token::symbol::begin_object:
            parse_object(result);
            break;

        default:
            throw_error("expected object");
            break;
        }

        if (reader.next())
        {
            throw_error("expected end of input");
        }
    }

private:
    void parse_object(Ptree& scope)
    {
        assert(reader.symbol() == json::token::symbol::begin_object);

        while (reader.next())
        {
            switch (reader.symbol())
            {
            case json::token::symbol::end_object:
                return;

            case json::token::symbol::string:
                parse_object_element(scope);
                break;

            default:
                throw_error("expected object name");
            }
        }
    }

    void parse_object_element(Ptree& scope)
    {
        assert(reader.symbol() == json::token::symbol::string);

        const string_type key = reader.template value<string_type>();
        Ptree& child = scope.push_back(std::make_pair(key, Ptree()))->second;

        if (!reader.next())
            throw_error("expected object value");

        switch (reader.symbol())
        {
        case json::token::symbol::begin_array:
            parse_array(key, child);
            break;

        case json::token::symbol::begin_object:
            parse_object(child);
            break;

        case json::token::symbol::null:
            break;

        case json::token::symbol::boolean:
        case json::token::symbol::integer:
        case json::token::symbol::real:
        case json::token::symbol::string:
            parse_value(child);
            break;

        case json::token::symbol::error:
            throw_error(reader.error().message());

        default:
            throw_error("expected object value");
        }
    }

    void parse_array(const std::string& key,
                     Ptree& scope)
    {
        assert(reader.symbol() == json::token::symbol::begin_array);

        while (reader.next())
        {
            switch (reader.symbol())
            {
            case json::token::symbol::end_array:
                return;

            case json::token::symbol::end:
            case json::token::symbol::end_object:
                throw_error("expected array value");

            case json::token::symbol::error:
                throw_error(reader.error().message());

            default:
                {
                    Ptree& child = scope.push_back(std::make_pair("", Ptree()))->second;
                    parse_array_element(child);
                }
                break;
            }
        }
    }


    void parse_array_element(Ptree& scope)
    {
        switch (reader.symbol())
        {
        case json::token::symbol::begin_object:
            parse_object(scope);
            break;

        case json::token::symbol::null:
            break;

        case json::token::symbol::boolean:
        case json::token::symbol::integer:
        case json::token::symbol::real:
        case json::token::symbol::string:
            parse_value(scope);
            break;

        case json::token::symbol::error:
            throw_error(reader.error().message());

        default:
            throw_error("expected array value");
        }
    }

    void parse_value(Ptree& scope)
    {
        switch (reader.symbol())
        {
        case json::token::symbol::boolean:
            // Read as bool to ensure that it becomes converted to the correct
            // format for boost::property_tree.
            scope.put_value(reader.template value<bool>());
            break;

        case json::token::symbol::integer:
        case json::token::symbol::real:
            // Read literal value to avoid choosing a concrete number type.
            scope.put_value(string_type(reader.literal().begin(),
                                        reader.literal().end()));
            break;

        case json::token::symbol::string:
            // Read as value to ensure that string is properly UTF-8 encoded.
            scope.put_value(reader.template value<string_type>());
            break;

        default:
            assert(false);
            break;
        }
    }

    json::token::symbol::value symbol()
    {
        json::token::symbol::value symbol = reader.symbol();
        switch (symbol)
        {
        case json::token::symbol::end:
        case json::token::symbol::error:
            throw json::error(reader.error());

        default:
            return symbol;
        }
    }

    void throw_error(const std::string& message)
    {
        using boost::property_tree::json_parser::json_parser_error;
        throw json_parser_error(message,
                                filename,
                                count_lines(&*begin, reader.literal().begin()));
    }

    template <typename InputIt>
    int count_lines(InputIt begin, InputIt end)
    {
        return std::count(begin, end, value_type('\n')) + 1;
    }

private:
    json::basic_reader<value_type> reader;
    Ptree& result;
    std::string filename;
    typename std::basic_string<value_type>::const_iterator begin;
};

} // namespace detail

template <typename Ptree>
void read_json_internal(std::basic_istream<typename Ptree::key_type::value_type> &input,
                        Ptree &pt,
                        const std::string &filename)
{
    typedef typename Ptree::key_type::value_type value_type;
    std::basic_string<value_type> buffer((std::istream_iterator<value_type>(input)),
                                         (std::istream_iterator<value_type>()));
    if (input.eof())
    {
        detail::parser<Ptree> parser(buffer, pt, filename);
        parser.parse();
    }
    else
    {
        using boost::property_tree::json_parser::json_parser_error;
        throw json_parser_error("read error", filename, 0);
    }
}

} // namespace example
} // namespace json
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_JSON_EXAMPLE_READ_JSON_INTERNAL_HPP
