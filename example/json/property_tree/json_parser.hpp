#ifndef TRIAL_PROTOCOL_JSON_EXAMPLE_JSON_PARSER_HPP
#define TRIAL_PROTOCOL_JSON_EXAMPLE_JSON_PARSER_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2015 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <locale>
#include <fstream>
#include <boost/property_tree/detail/json_parser_error.hpp>
#include "read_json_internal.hpp"
#include "write_json_internal.hpp"

namespace boost
{
namespace property_tree
{
namespace json_parser
{

template<class Ptree>
void read_json(std::basic_istream<typename Ptree::key_type::value_type> &stream,
               Ptree &pt)
{
    trial::protocol::json::example::read_json_internal(stream, pt, std::string());
}

template<class Ptree>
void read_json(const std::string &filename,
               Ptree &pt,
               const std::locale &loc = std::locale())
{
    std::basic_ifstream<typename Ptree::key_type::value_type> stream(filename.c_str());
    if (!stream)
        BOOST_PROPERTY_TREE_THROW(json_parser_error("cannot open file", filename, 0));
    std::noskipws(stream);
    stream.imbue(loc);
    trial::protocol::json::example::read_json_internal(stream, pt, filename);
}

template<class Ptree>
void write_json(std::basic_ostream<typename Ptree::key_type::value_type>& stream,
                const Ptree &pt,
                bool pretty = true)
{
    trial::protocol::json::example::write_json_internal(stream, pt, std::string(), pretty);
}

template<class Ptree>
void write_json(const std::string &filename,
                const Ptree &pt,
                const std::locale &loc = std::locale(),
                bool pretty = true)
{
    std::basic_ofstream<typename Ptree::key_type::value_type> stream(filename.c_str());
    if (!stream)
        BOOST_PROPERTY_TREE_THROW(json_parser_error("cannot open file", filename, 0));
    stream.imbue(loc);
    trial::protocol::json::example::write_json_internal(stream, pt, filename, pretty);
}

} // namespace json_parser
} // namespace property_tree
} // namespace boost


#endif // TRIAL_PROTOCOL_JSON_EXAMPLE_JSON_PARSER_HPP
