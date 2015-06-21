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
#include <boost/filesystem/fstream.hpp>
#include <trial/protocol/buffer/ostream.hpp>
#include "pretty_printer.hpp"

namespace json = trial::protocol::json;

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
            trial::protocol::buffer::ostream stream(std::cout);
            json::writer writer(stream);
            json::example::pretty_printer printer(reader, writer);
            printer.print();
        }
    }
    catch (const std::exception& ex)
    {
        std::cout << "Error: " << ex.what() << std::endl;
    }
    return 0;
}
