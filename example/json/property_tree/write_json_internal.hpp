#ifndef TRIAL_PROTOCOL_JSON_EXAMPLE_WRITE_JSON_INTERNAL_HPP
#define TRIAL_PROTOCOL_JSON_EXAMPLE_WRITE_JSON_INTERNAL_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2015 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <ostream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/detail/json_parser_error.hpp>
#include <trial/protocol/buffer/ostream.hpp>
#include <trial/protocol/json/writer.hpp>

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
class printer
{
    typedef typename Ptree::key_type::value_type value_type;
    typedef typename std::basic_string<value_type> string_type;
    typedef typename Ptree::const_iterator const_iterator;

public:
    printer(std::basic_ostream<value_type>& stream,
            const Ptree& input)
        : writer(stream),
          input(input)
    {
    }

    void print()
    {
        print_object(input);
    }

    void print_object(const Ptree& scope)
    {
        if (scope.empty())
            return;

        writer.template value<json::token::begin_object>();
        for (const_iterator it = scope.begin();
             it != scope.end();
             ++it)
        {
            print_object_element(it->second, it->first);
        }
        writer.template value<json::token::end_object>();
    }

    void print_object_element(const Ptree& scope,
                              const string_type& key)
    {
        writer.value(key);
        print_array_element(scope);
    }

    void print_array(const Ptree& scope)
    {
        writer.template value<json::token::begin_array>();
        for (const_iterator it = scope.begin();
             it != scope.end();
             ++it)
        {
            print_array_element(it->second);
        }
        writer.template value<json::token::end_array>();
    }

    void print_array_element(const Ptree& scope)
    {
        if (scope.empty())
        {
            print_value(scope);
        }
        else if (scope.count(string_type()) == scope.size())
        {
            print_array(scope);
        }
        else
        {
            print_object(scope);
        }
    }

    void print_value(const Ptree& scope)
    {
        const string_type value = scope.template get_value<string_type>();
        if (value.empty())
        {
            writer.template value<json::token::null>();
        }
        else
        {
            // Ptree does not preserve the original value type, but we could
            // attempt to convert the value to a boolean or a number first.
            writer.value(value);
        }
    }

private:
    json::writer writer;
    const Ptree& input;
};

} // namespace detail

// Verify if ptree does not contain information that cannot be written to json
template<class Ptree>
bool verify_json(const Ptree &pt, int depth)
{
    typedef typename Ptree::key_type::value_type Ch;
    typedef typename std::basic_string<Ch> Str;

    // Root ptree cannot have data
    if (depth == 0 && !pt.template get_value<Str>().empty())
        return false;
        
    // Ptree cannot have both children and data
    if (!pt.template get_value<Str>().empty() && !pt.empty())
        return false;

    // Check children
    typename Ptree::const_iterator it = pt.begin();
    for (; it != pt.end(); ++it)
        if (!verify_json(it->second, depth + 1))
            return false;

    // Success
    return true;
}
    
template<class Ptree>
void write_json_internal(std::basic_ostream<typename Ptree::key_type::value_type> &stream, 
                         const Ptree &pt,
                         const std::string &filename,
                         bool pretty)
{
    using boost::property_tree::json_parser::json_parser_error;
    if (!verify_json(pt, 0))
        throw json_parser_error("ptree contains data that cannot be represented in JSON format", filename, 0);
    detail::printer<Ptree> printer(stream, pt);
    printer.print();
    stream << std::endl;
    if (!stream.good())
        throw json_parser_error("write error", filename, 0);
}

} // namespace example
} // namespace json
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_JSON_EXAMPLE_WRITE_JSON_INTERNAL_HPP
