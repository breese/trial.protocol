///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2015 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <boost/test/unit_test.hpp>

#include <sstream>
#include <boost/utility/base_from_member.hpp>
#include <trial/protocol/buffer/ostream.hpp>
#include <trial/protocol/json/writer.hpp>
#include "is_system_error.hpp"

using namespace trial::protocol;

BOOST_AUTO_TEST_SUITE(json_writer_suite)

struct test_stream
    : private boost::base_from_member<std::ostringstream>,
      public buffer::ostream
{
    test_stream()
        : boost::base_from_member<std::ostringstream>(),
          buffer::ostream(boost::base_from_member<std::ostringstream>::member)
    {}

    std::string data() const
    {
        return boost::base_from_member<std::ostringstream>::member.str().data();
    }
};

//-----------------------------------------------------------------------------
// Basic types
//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(test_empty)
{
    test_stream buffer;
    json::writer writer(buffer);
    BOOST_REQUIRE_EQUAL(buffer.data(), "");
}

BOOST_AUTO_TEST_CASE(test_null)
{
    test_stream buffer;
    json::writer writer(buffer);
    BOOST_REQUIRE_EQUAL(writer.value(json::null), 4);
    BOOST_REQUIRE_EQUAL(buffer.data(), "null");
}

BOOST_AUTO_TEST_CASE(test_true)
{
    test_stream buffer;
    json::writer writer(buffer);
    BOOST_REQUIRE_EQUAL(writer.value(true), 4);
    BOOST_REQUIRE_EQUAL(buffer.data(), "true");
}

BOOST_AUTO_TEST_CASE(test_false)
{
    test_stream buffer;
    json::writer writer(buffer);
    BOOST_REQUIRE_EQUAL(writer.value(false), 5);
    BOOST_REQUIRE_EQUAL(buffer.data(), "false");
}

//-----------------------------------------------------------------------------
// Integer
//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(test_int_literal_zero)
{
    test_stream buffer;
    json::writer writer(buffer);
    BOOST_REQUIRE_EQUAL(writer.value(0), 1);
    BOOST_REQUIRE_EQUAL(buffer.data(), "0");
}

BOOST_AUTO_TEST_CASE(test_int_zero)
{
    test_stream buffer;
    json::writer writer(buffer);
    BOOST_REQUIRE_EQUAL(writer.value(int(0)), 1);
    BOOST_REQUIRE_EQUAL(buffer.data(), "0");
}

BOOST_AUTO_TEST_CASE(test_intmax_zero)
{
    test_stream buffer;
    json::writer writer(buffer);
    BOOST_REQUIRE_EQUAL(writer.value(boost::intmax_t(0)), 1);
    BOOST_REQUIRE_EQUAL(buffer.data(), "0");
}

BOOST_AUTO_TEST_CASE(test_int_literal_zero_one)
{
    test_stream buffer;
    json::writer writer(buffer);
    BOOST_REQUIRE_EQUAL(writer.value(0), 1);
    BOOST_REQUIRE_EQUAL(writer.value(1), 1);
    BOOST_REQUIRE_EQUAL(buffer.data(), "0,1");
}

//-----------------------------------------------------------------------------
// Float
//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(test_float_literal_zero)
{
    test_stream buffer;
    json::writer writer(buffer);
    BOOST_REQUIRE_EQUAL(writer.value(0.0), 1);
    BOOST_REQUIRE_EQUAL(buffer.data(), "0");
}

//-----------------------------------------------------------------------------
// String
//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(test_string_literal_empty)
{
    test_stream buffer;
    json::writer writer(buffer);
    BOOST_REQUIRE_EQUAL(writer.value(""), 2);
    BOOST_REQUIRE_EQUAL(buffer.data(), "\"\"");
}

BOOST_AUTO_TEST_CASE(test_string_literal_alpha)
{
    test_stream buffer;
    json::writer writer(buffer);
    BOOST_REQUIRE_EQUAL(writer.value("alpha"), 7);
    BOOST_REQUIRE_EQUAL(buffer.data(), "\"alpha\"");
}

BOOST_AUTO_TEST_CASE(test_string_empty)
{
    test_stream buffer;
    json::writer writer(buffer);
    BOOST_REQUIRE_EQUAL(writer.value(std::string()), 2);
    BOOST_REQUIRE_EQUAL(buffer.data(), "\"\"");
}

BOOST_AUTO_TEST_CASE(test_string_alpha)
{
    test_stream buffer;
    json::writer writer(buffer);
    BOOST_REQUIRE_EQUAL(writer.value(std::string("alpha")), 7);
    BOOST_REQUIRE_EQUAL(buffer.data(), "\"alpha\"");
}

//-----------------------------------------------------------------------------
// Array
//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(test_array_empty)
{
    test_stream buffer;
    json::writer writer(buffer);
    BOOST_REQUIRE_EQUAL(writer.value(json::array_open), 1);
    BOOST_REQUIRE_EQUAL(writer.value(json::array_close), 1);
    BOOST_REQUIRE_EQUAL(buffer.data(), "[]");
}

BOOST_AUTO_TEST_CASE(test_array_bool_one)
{
    test_stream buffer;
    json::writer writer(buffer);
    BOOST_REQUIRE_EQUAL(writer.value(json::array_open), 1);
    BOOST_REQUIRE_EQUAL(writer.value(false), 5);
    BOOST_REQUIRE_EQUAL(writer.value(json::array_close), 1);
    BOOST_REQUIRE_EQUAL(buffer.data(), "[false]");
}

BOOST_AUTO_TEST_CASE(test_array_bool_two)
{
    test_stream buffer;
    json::writer writer(buffer);
    BOOST_REQUIRE_EQUAL(writer.value(json::array_open), 1);
    BOOST_REQUIRE_EQUAL(writer.value(false), 5);
    BOOST_REQUIRE_EQUAL(writer.value(true), 4);
    BOOST_REQUIRE_EQUAL(writer.value(json::array_close), 1);
    BOOST_REQUIRE_EQUAL(buffer.data(), "[false,true]");
}

BOOST_AUTO_TEST_CASE(fail_array_missing_begin)
{
    test_stream buffer;
    json::writer writer(buffer);
    BOOST_REQUIRE_EXCEPTION(writer.value(json::array_close),
                            boost::system::system_error,
                            test::is_system_error(json::unexpected_token));
}

//-----------------------------------------------------------------------------
// Object
//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(test_object_empty)
{
    test_stream buffer;
    json::writer writer(buffer);
    BOOST_REQUIRE_EQUAL(writer.value(json::object_open), 1);
    BOOST_REQUIRE_EQUAL(writer.value(json::object_close), 1);
    BOOST_REQUIRE_EQUAL(buffer.data(), "{}");
}

BOOST_AUTO_TEST_CASE(test_object_bool_one)
{
    test_stream buffer;
    json::writer writer(buffer);
    BOOST_REQUIRE_EQUAL(writer.value(json::object_open), 1);
    BOOST_REQUIRE_EQUAL(writer.value("key1"), 6);
    BOOST_REQUIRE_EQUAL(writer.value(false), 5);
    BOOST_REQUIRE_EQUAL(writer.value(json::object_close), 1);
    BOOST_REQUIRE_EQUAL(buffer.data(), "{\"key1\":false}");
}

BOOST_AUTO_TEST_CASE(test_object_bool_two)
{
    test_stream buffer;
    json::writer writer(buffer);
    BOOST_REQUIRE_EQUAL(writer.value(json::object_open), 1);
    BOOST_REQUIRE_EQUAL(writer.value("key1"), 6);
    BOOST_REQUIRE_EQUAL(writer.value(false), 5);
    BOOST_REQUIRE_EQUAL(writer.value("key2"), 6);
    BOOST_REQUIRE_EQUAL(writer.value(true), 4);
    BOOST_REQUIRE_EQUAL(writer.value(json::object_close), 1);
    BOOST_REQUIRE_EQUAL(buffer.data(), "{\"key1\":false,\"key2\":true}");
}

BOOST_AUTO_TEST_CASE(fail_object_missing_begin)
{
    test_stream buffer;
    json::writer writer(buffer);
    BOOST_REQUIRE_EXCEPTION(writer.value(json::object_close),
                            boost::system::system_error,
                            test::is_system_error(json::unexpected_token));
}

BOOST_AUTO_TEST_SUITE_END()
