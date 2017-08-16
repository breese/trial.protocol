///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2017 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <trial/protocol/core/detail/lightweight_test.hpp>
#include <trial/protocol/dynamic/boost/any.hpp>

using namespace trial::protocol::dynamic;

//-----------------------------------------------------------------------------
// boost::any
//-----------------------------------------------------------------------------

namespace any_suite
{

void convert_null()
{
    boost::any any;
    variable result = convert<variable>(any);
    TRIAL_PROTOCOL_TEST(result.is<nullable>());
}

void convert_boolean()
{
    boost::any any(true);
    variable result = convert<variable>(any);
    TRIAL_PROTOCOL_TEST(result.is<boolean>());
    TRIAL_PROTOCOL_TEST_EQUAL(result.value<boolean>(), true);
}

void convert_integer()
{
    boost::any any(2);
    variable result = convert<variable>(any);
    TRIAL_PROTOCOL_TEST(result.is<int>());
    TRIAL_PROTOCOL_TEST_EQUAL(result.value<int>(), 2);
}

void convert_number()
{
    boost::any any(3.0);
    variable result = convert<variable>(any);
    TRIAL_PROTOCOL_TEST(result.is<double>());
    TRIAL_PROTOCOL_TEST_EQUAL(result.value<double>(), 3.0);
}

void convert_string()
{
    boost::any any(std::string("alpha"));
    variable result = convert<variable>(any);
    TRIAL_PROTOCOL_TEST(result.is<string>());
    TRIAL_PROTOCOL_TEST_EQUAL(result.value<std::string>(), "alpha");
}

void convert_string_literal()
{
    boost::any any("alpha");
    variable result = convert<variable>(any);
    TRIAL_PROTOCOL_TEST(result.is<string>());
    TRIAL_PROTOCOL_TEST_EQUAL(result.value<std::string>(), "alpha");
}

void fail_on_struct()
{
    struct record {};
    boost::any any(record{});
    std::error_code error;
    variable result = convert<variable>(any, error);
    TRIAL_PROTOCOL_TEST(result.is<nullable>());
    TRIAL_PROTOCOL_TEST(error == make_error_code(incompatible_type));
}

void throw_on_struct()
{
    struct record {};
    boost::any any(record{});
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(convert<variable>(any),
                                    error,
                                    "incompatible type");
}

void run()
{
    convert_null();
    convert_boolean();
    convert_integer();
    convert_number();
    convert_string();
    convert_string_literal();
    fail_on_struct();
    throw_on_struct();
}

} // namespace any_suite

//-----------------------------------------------------------------------------
// main
//-----------------------------------------------------------------------------

int main()
{
    any_suite::run();

    return boost::report_errors();
}
