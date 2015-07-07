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
#include <boost/cstdint.hpp>
#include <trial/protocol/json/reader.hpp>

namespace example
{

namespace json = trial::protocol::json;

template <typename Callbacks>
class push_parser
{
public:
    push_parser(const json::reader& reader)
        : reader(reader)
    {
    }

    void parse()
    {
        do
        {
            switch (reader.type())
            {
            case json::token::begin_array:
                callbacks.on_begin_array();
                break;

            case json::token::end_array:
                callbacks.on_end_array();
                break;

            case json::token::begin_object:
                callbacks.on_begin_object();
                break;

            case json::token::end_object:
                callbacks.on_end_object();
                break;

            case json::token::null:
                callbacks.on_null();
                break;

            case json::token::boolean:
                callbacks.on_boolean(reader.value<bool>());
                break;

            case json::token::integer:
                callbacks.on_integer(reader.value<boost::intmax_t>());
                break;

            case json::token::floating:
                callbacks.on_floating(reader.value<double>());
                break;

            case json::token::string:
                callbacks.on_string(reader.value<std::string>());
                break;

            default:
                break;
            }
            
        } while (reader.next());
    }

private:
    json::reader reader;
    Callbacks callbacks;
};

} // namespace example
