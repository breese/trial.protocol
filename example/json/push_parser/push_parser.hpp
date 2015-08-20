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
            case json::type::null:
                callbacks.on_null();
                break;

            case json::type::boolean:
                callbacks.on_boolean(reader.value<bool>());
                break;

            case json::type::integer:
                callbacks.on_integer(reader.value<boost::intmax_t>());
                break;

            case json::type::floating:
                callbacks.on_floating(reader.value<double>());
                break;

            case json::type::string:
                callbacks.on_string(reader.value<std::string>());
                break;

            case json::type::begin_array:
                callbacks.on_begin_array();
                break;

            case json::type::end_array:
                callbacks.on_end_array();
                break;

            case json::type::begin_object:
                callbacks.on_begin_object();
                break;

            case json::type::end_object:
                callbacks.on_end_object();
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
