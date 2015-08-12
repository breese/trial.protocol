///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2015 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <string>
#include <iostream>
#include <ios>
#include <boost/filesystem/fstream.hpp>
#include <trial/protocol/buffer/ostream.hpp>
#include "push_parser.hpp"

namespace json = trial::protocol::json;

class printing_callbacks
{
public:
    void on_null()
    {
        std::cout << "null" << std::endl;
    }

    void on_boolean(bool value)
    {
        std::cout << "bool: " << std::boolalpha << value << std::endl;
    }

    void on_integer(boost::intmax_t value)
    {
        std::cout << "integer: " << value << std::endl;
    }

    void on_floating(double value)
    {
        std::cout << "float: " << value << std::endl;
    }

    void on_string(const std::string& value)
    {
        std::cout << "string: " << value << std::endl;
    }

    void on_begin_array()
    {
        std::cout << "begin_array" << std::endl;
    }

    void on_end_array()
    {
        std::cout << "end_array" << std::endl;
    }

    void on_begin_object()
    {
        std::cout << "begin_object" << std::endl;
    }

    void on_end_object()
    {
        std::cout << "end_object" << std::endl;
    }
};

int main(int argc, char *argv[])
{
    try
    {
        if (argc != 2)
        {
            std::cerr << "Usage: " << argv[0] << " <file>" << std::endl;
            return 1;
        }

        boost::filesystem::path input_name(argv[1]);
        boost::filesystem::ifstream input(input_name);
        if (input)
        {
            std::noskipws(input);
            std::string buffer((std::istream_iterator<char>(input)),
                               (std::istream_iterator<char>()));

            json::reader reader(buffer);
            example::push_parser<printing_callbacks> parser(reader);
            parser.parse();
        }
    }
    catch (const std::exception& ex)
    {
        std::cout << "Error: " << ex.what() << std::endl;
    }
    return 0;
}
