///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2015 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <sstream>
#include <trial/protocol/buffer/ostream.hpp>
#include <trial/protocol/json/writer.hpp>
#include <trial/protocol/core/detail/lightweight_test.hpp>

using namespace trial::protocol;
namespace token = json::token;

//-----------------------------------------------------------------------------
// Basic types
//-----------------------------------------------------------------------------

namespace basic_suite
{

void test_empty()
{
    std::ostringstream result;
    json::writer writer(result);
    TRIAL_PROTOCOL_TEST_EQUAL(result.str(), "");
}

void test_null()
{
    std::ostringstream result;
    json::writer writer(result);
    TRIAL_PROTOCOL_TEST_EQUAL(writer.value<token::null>(), 4);
    TRIAL_PROTOCOL_TEST_EQUAL(result.str(), "null");
}

void test_true()
{
    std::ostringstream result;
    json::writer writer(result);
    TRIAL_PROTOCOL_TEST_EQUAL(writer.value(true), 4);
    TRIAL_PROTOCOL_TEST_EQUAL(result.str(), "true");
}

void test_false()
{
    std::ostringstream result;
    json::writer writer(result);
    TRIAL_PROTOCOL_TEST_EQUAL(writer.value(false), 5);
    TRIAL_PROTOCOL_TEST_EQUAL(result.str(), "false");
}

void run()
{
    test_empty();
    test_null();
    test_true();
    test_false();
}

} // namespace basic_suite

namespace ubasic_suite
{

using unsigned_ostringstream = std::basic_ostringstream<unsigned char, core::char_traits<unsigned char>>;
using unsigned_writer = json::basic_writer<unsigned char>;

void test_empty()
{
#if defined(TRIAL_PROTOCOL_JSON_WITH_UNSIGNED_CHAR)
    unsigned_ostringstream result;
    unsigned_writer writer(result);
    TRIAL_PROTOCOL_TEST_EQUAL(result.str().empty(), true);
#endif
}

void run()
{
    test_empty();
}

} // namespace ubasic_suite

//-----------------------------------------------------------------------------
// Integer
//-----------------------------------------------------------------------------

namespace integer_suite
{

void test_literal_zero()
{
    std::ostringstream result;
    json::writer writer(result);
    TRIAL_PROTOCOL_TEST_EQUAL(writer.value(0), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(result.str(), "0");
}

void test_zero()
{
    std::ostringstream result;
    json::writer writer(result);
    TRIAL_PROTOCOL_TEST_EQUAL(writer.value(int(0)), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(result.str(), "0");
}

void test_intmax_zero()
{
    std::ostringstream result;
    json::writer writer(result);
    TRIAL_PROTOCOL_TEST_EQUAL(writer.value(std::intmax_t(0)), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(result.str(), "0");
}

void test_literal_zero_one()
{
    std::ostringstream result;
    json::writer writer(result);
    TRIAL_PROTOCOL_TEST_EQUAL(writer.value(0), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(writer.value(1), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(result.str(), "0,1");
}

void run()
{
    test_literal_zero();
    test_zero();
    test_intmax_zero();
    test_literal_zero_one();
}

} // namespace integer_suite

//-----------------------------------------------------------------------------
// Number
//-----------------------------------------------------------------------------

namespace number_suite
{

void test_literal_zero()
{
    std::ostringstream result;
    json::writer writer(result);
    TRIAL_PROTOCOL_TEST_EQUAL(writer.value(0.0), 16);
    TRIAL_PROTOCOL_TEST_EQUAL(result.str(), "0.00000000000000");
}

void test_zero()
{
    std::ostringstream result;
    json::writer writer(result);
    TRIAL_PROTOCOL_TEST_EQUAL(writer.value(double(0.0)), 16);
    TRIAL_PROTOCOL_TEST_EQUAL(result.str(), "0.00000000000000");
}

void run()
{
    test_literal_zero();
    test_zero();
}

} // namespace number_suite

//-----------------------------------------------------------------------------
// String
//-----------------------------------------------------------------------------

namespace string_suite
{

void test_literal_empty()
{
    std::ostringstream result;
    json::writer writer(result);
    TRIAL_PROTOCOL_TEST_EQUAL(writer.value(""), 2);
    TRIAL_PROTOCOL_TEST_EQUAL(result.str(), "\"\"");
}

void test_literal_alpha()
{
    std::ostringstream result;
    json::writer writer(result);
    TRIAL_PROTOCOL_TEST_EQUAL(writer.value("alpha"), 7);
    TRIAL_PROTOCOL_TEST_EQUAL(result.str(), "\"alpha\"");
}

void test_empty()
{
    std::ostringstream result;
    json::writer writer(result);
    TRIAL_PROTOCOL_TEST_EQUAL(writer.value(std::string()), 2);
    TRIAL_PROTOCOL_TEST_EQUAL(result.str(), "\"\"");
}

void test_alpha()
{
    std::ostringstream result;
    json::writer writer(result);
    TRIAL_PROTOCOL_TEST_EQUAL(writer.value(std::string("alpha")), 7);
    TRIAL_PROTOCOL_TEST_EQUAL(result.str(), "\"alpha\"");
}

void run()
{
    test_literal_empty();
    test_literal_alpha();
    test_empty();
    test_alpha();
}

} // namespace string_suite

//-----------------------------------------------------------------------------
// Array
//-----------------------------------------------------------------------------

namespace array_suite
{

void test_empty()
{
    std::ostringstream result;
    json::writer writer(result);
    TRIAL_PROTOCOL_TEST_EQUAL(writer.value<token::begin_array>(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(writer.value<token::end_array>(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(result.str(), "[]");
}

void test_bool_one()
{
    std::ostringstream result;
    json::writer writer(result);
    TRIAL_PROTOCOL_TEST_EQUAL(writer.value<token::begin_array>(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(writer.value(false), 5);
    TRIAL_PROTOCOL_TEST_EQUAL(writer.value<token::end_array>(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(result.str(), "[false]");
}

void test_bool_two()
{
    std::ostringstream result;
    json::writer writer(result);
    TRIAL_PROTOCOL_TEST_EQUAL(writer.value<token::begin_array>(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(writer.value(false), 5);
    TRIAL_PROTOCOL_TEST_EQUAL(writer.value(true), 4);
    TRIAL_PROTOCOL_TEST_EQUAL(writer.value<token::end_array>(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(result.str(), "[false,true]");
}

void test_nested_bool_one()
{
    std::ostringstream result;
    json::writer writer(result);
    TRIAL_PROTOCOL_TEST_EQUAL(writer.value<token::begin_array>(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(writer.value<token::begin_array>(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(writer.value(false), 5);
    TRIAL_PROTOCOL_TEST_EQUAL(writer.value<token::end_array>(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(writer.value<token::end_array>(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(result.str(), "[[false]]");
}

void fail_missing_begin()
{
    std::ostringstream result;
    json::writer writer(result);
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(writer.value<token::end_array>(),
                                    json::error, "unexpected token");
}

void fail_mismatched_end()
{
    std::ostringstream result;
    json::writer writer(result);
    TRIAL_PROTOCOL_TEST_EQUAL(writer.value<token::begin_array>(), 1);
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(writer.value<token::end_object>(),
                                    json::error, "unexpected token");
}

void run()
{
    test_empty();
    test_bool_one();
    test_bool_two();
    test_nested_bool_one();
    fail_missing_begin();
    fail_mismatched_end();
}

} // namespace array_suite

//-----------------------------------------------------------------------------
// Object
//-----------------------------------------------------------------------------

namespace object_suite
{

void test_empty()
{
    std::ostringstream result;
    json::writer writer(result);
    TRIAL_PROTOCOL_TEST_EQUAL(writer.value<token::begin_object>(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(writer.value<token::end_object>(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(result.str(), "{}");
}

void test_bool_one()
{
    std::ostringstream result;
    json::writer writer(result);
    TRIAL_PROTOCOL_TEST_EQUAL(writer.value<token::begin_object>(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(writer.value("key1"), 6);
    TRIAL_PROTOCOL_TEST_EQUAL(writer.value(false), 5);
    TRIAL_PROTOCOL_TEST_EQUAL(writer.value<token::end_object>(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(result.str(), "{\"key1\":false}");
}

void test_bool_two()
{
    std::ostringstream result;
    json::writer writer(result);
    TRIAL_PROTOCOL_TEST_EQUAL(writer.value<token::begin_object>(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(writer.value("key1"), 6);
    TRIAL_PROTOCOL_TEST_EQUAL(writer.value(false), 5);
    TRIAL_PROTOCOL_TEST_EQUAL(writer.value("key2"), 6);
    TRIAL_PROTOCOL_TEST_EQUAL(writer.value(true), 4);
    TRIAL_PROTOCOL_TEST_EQUAL(writer.value<token::end_object>(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(result.str(), "{\"key1\":false,\"key2\":true}");
}

void test_nested_bool_one()
{
    std::ostringstream result;
    json::writer writer(result);
    TRIAL_PROTOCOL_TEST_EQUAL(writer.value<token::begin_object>(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(writer.value("key1"), 6);
    TRIAL_PROTOCOL_TEST_EQUAL(writer.value<token::begin_object>(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(writer.value("key2"), 6);
    TRIAL_PROTOCOL_TEST_EQUAL(writer.value(false), 5);
    TRIAL_PROTOCOL_TEST_EQUAL(writer.value<token::end_object>(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(writer.value<token::end_object>(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(result.str(), "{\"key1\":{\"key2\":false}}");
}

void fail_missing_begin()
{
    std::ostringstream result;
    json::writer writer(result);
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(writer.value<token::end_object>(),
                                    json::error, "unexpected token");
}

void fail_mismatched_end()
{
    std::ostringstream result;
    json::writer writer(result);
    TRIAL_PROTOCOL_TEST_EQUAL(writer.value<token::begin_object>(), 1);
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(writer.value<token::end_array>(),
                                    json::error, "unexpected token");
}

void run()
{
    test_empty();
    test_bool_one();
    test_bool_two();
    test_nested_bool_one();
    fail_missing_begin();
    fail_mismatched_end();
}

} // namespace object_suite

//-----------------------------------------------------------------------------
// main
//-----------------------------------------------------------------------------

int main()
{
    basic_suite::run();
    ubasic_suite::run();
    integer_suite::run();
    number_suite::run();
    string_suite::run();
    array_suite::run();
    object_suite::run();

    return boost::report_errors();
}
