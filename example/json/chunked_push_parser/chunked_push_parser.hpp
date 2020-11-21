///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2019 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <cstdint>
#include <cstring>
#include <string>
#include <trial/protocol/json/chunk_reader.hpp>

namespace example
{

namespace json = trial::protocol::json;

#define TRIAL_PROTOCOL_JSON_EXAMPLE_BUFFER_SIZE 8192

template <typename Callbacks>
class chunked_push_parser
{
    using view_type = json::chunk_reader::view_type;

public:
    void parse(const view_type& input)
    {
        assert(length + input.size() < sizeof(buffer));
        std::memcpy(&buffer[length], input.data(), input.size());
        length += input.size();
        if (reader.next(view_type(buffer, length)))
        {
            parse_loop();

            if (reader.tail().data() != buffer)
            {
                // Copy left-overs for next call
                length = reader.tail().size();
                std::memmove(&buffer, reader.tail().data(), length);
                reader.shift({ buffer, length });
            }
        }
    }

private:
    void parse_loop()
    {
        do
        {
            switch (reader.symbol())
            {
            case json::token::symbol::null:
                callbacks.on_null();
                break;

            case json::token::symbol::boolean:
                callbacks.on_boolean(reader.value<bool>());
                break;

            case json::token::symbol::integer:
                callbacks.on_integer(reader.value<std::intmax_t>());
                break;

            case json::token::symbol::real:
                callbacks.on_real(reader.value<double>());
                break;

            case json::token::symbol::string:
            case json::token::symbol::key:
                callbacks.on_string(reader.value<std::string>());
                break;

            case json::token::symbol::begin_array:
                callbacks.on_begin_array();
                break;

            case json::token::symbol::end_array:
                callbacks.on_end_array();
                break;

            case json::token::symbol::begin_object:
                callbacks.on_begin_object();
                break;

            case json::token::symbol::end_object:
                callbacks.on_end_object();
                break;

            default:
                break;
            }
        } while (reader.next());
    }

private:
    char buffer[TRIAL_PROTOCOL_JSON_EXAMPLE_BUFFER_SIZE];
    std::size_t length = 0;
    json::chunk_reader reader;
    Callbacks callbacks;
};

} // namespace example
