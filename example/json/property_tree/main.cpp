#include <string>
#include <iostream>
#include <boost/filesystem/fstream.hpp>
#include <boost/property_tree/detail/json_parser_error.hpp>
#include "json_parser.hpp"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cout << "Usage: " << argv[0] << " <file>" << std::endl;
        return 1;
    }

    try
    {
        std::string filename(argv[1]);
        boost::property_tree::ptree tree;
        boost::property_tree::json_parser::read_json(filename, tree);
        boost::property_tree::json_parser::write_json(std::cout, tree, false);
    }
    catch (const std::exception& ex)
    {
        std::cerr << "Error: " << ex.what() << std::endl;
    }
    return 0;
}
