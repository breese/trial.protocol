///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2017 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <sstream>
#include <ios>
#include <trial/protocol/core/detail/lightweight_test.hpp>
#include <trial/protocol/dynamic/variable_io.hpp>

using namespace trial::protocol::dynamic;

//-----------------------------------------------------------------------------
// std::ostringstream
//-----------------------------------------------------------------------------

namespace ostringstream_suite
{

void test_null()
{
    std::ostringstream stream;
    variable data;
    stream << data;
    TRIAL_PROTOCOL_TEST_EQUAL(stream.str(), "null");
}

void test_boolean()
{
    std::ostringstream stream;
    variable data(true);
    stream << data;
    TRIAL_PROTOCOL_TEST_EQUAL(stream.str(), "true");
}

void test_integer()
{
    std::ostringstream stream;
    variable data(2);
    stream << data;
    TRIAL_PROTOCOL_TEST_EQUAL(stream.str(), "2");
}

void test_number()
{
    std::ostringstream stream;
    variable data(3.0);
    stream << data;
    TRIAL_PROTOCOL_TEST_EQUAL(stream.str(), "3.00000000000000");
}

void test_string()
{
    {
        std::ostringstream stream;
        variable data("alpha");
        stream << data;
        TRIAL_PROTOCOL_TEST_EQUAL(stream.str(), "\"alpha\"");
    }
    {
        // Wide-characters cannot be serialized
        std::ostringstream stream;
        variable data(L"alpha");
        TRIAL_PROTOCOL_TEST_THROW_EQUAL((stream << data),
                                        trial::protocol::json::error,
                                        "incompatible type");
    }
    {
        // char16_t strings cannot be serialized
        std::ostringstream stream;
        variable data(u"alpha");
        TRIAL_PROTOCOL_TEST_THROW_EQUAL((stream << data),
                                        trial::protocol::json::error,
                                        "incompatible type");
    }
    {
        // char32_t strings cannot be serialized
        std::ostringstream stream;
        variable data(U"alpha");
        TRIAL_PROTOCOL_TEST_THROW_EQUAL((stream << data),
                                        trial::protocol::json::error,
                                        "incompatible type");
    }
}

void test_array()
{
    std::ostringstream stream;
    variable data = array::make({ true, 2, 3.0, "alpha" });
    stream << data;
    TRIAL_PROTOCOL_TEST_EQUAL(stream.str(), "[true,2,3.00000000000000,\"alpha\"]");
}

void test_map()
{
    std::ostringstream stream;
    variable data = map::make(
        {
            { "alpha", true },
            { "bravo", 2 },
            { "charlie", 3.0 },
            { "delta", "hydrogen" }
        });
    stream << data;
    TRIAL_PROTOCOL_TEST_EQUAL(stream.str(), "{\"alpha\":true,\"bravo\":2,\"charlie\":3.00000000000000,\"delta\":\"hydrogen\"}");
}

void run()
{
    test_null();
    test_boolean();
    test_integer();
    test_number();
    test_string();
    test_array();
    test_map();
}

} // namespace ostringstream_suite

//-----------------------------------------------------------------------------
// main
//-----------------------------------------------------------------------------

int main()
{
    ostringstream_suite::run();

    return boost::report_errors();
}
