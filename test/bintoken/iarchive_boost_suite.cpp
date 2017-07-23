///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2017 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <trial/protocol/buffer/array.hpp>
#include <trial/protocol/bintoken/serialization.hpp>
#include <trial/protocol/core/detail/lightweight_test.hpp>

namespace format = trial::protocol::bintoken;
namespace token = format::token;
using value_type = format::reader::value_type;

//-----------------------------------------------------------------------------
// Optional
//-----------------------------------------------------------------------------

namespace optional_suite
{

void test_value()
{
    const value_type input[] = { token::code::string8, 0x01, 'A' };
    format::iarchive in(input);
    boost::optional<std::string> value;
    TRIAL_PROTOCOL_TEST_NO_THROW(in >> value);
    TRIAL_PROTOCOL_TEST(value);
    TRIAL_PROTOCOL_TEST_EQUAL(*value, "A");
}

void test_null()
{
    const value_type input[] = { token::code::null };
    format::iarchive in(input);
    boost::optional<std::string> value;
    TRIAL_PROTOCOL_TEST_NO_THROW(in >> value);
    TRIAL_PROTOCOL_TEST(!value);
}

void test_null_value()
{
    const value_type input[] = { token::code::null,
                                 token::code::true_value };
    format::iarchive in(input);
    boost::optional<bool> value;
    TRIAL_PROTOCOL_TEST_NO_THROW(in >> value);
    TRIAL_PROTOCOL_TEST(!value);
    TRIAL_PROTOCOL_TEST_NO_THROW(in >> value);
    TRIAL_PROTOCOL_TEST(value);
    TRIAL_PROTOCOL_TEST_EQUAL(*value, true);
}

void fail_wrong_type()
{
    const value_type input[] = { token::code::true_value };
    format::iarchive in(input);
    boost::optional<std::string> value;
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(in >> value,
                                    format::error, "invalid value");
}

void run()
{
    test_value();
    test_null();
    test_null_value();
    fail_wrong_type();
}

} // namespace optional_suite

//-----------------------------------------------------------------------------
// main
//-----------------------------------------------------------------------------

int main()
{
    optional_suite::run();

    return boost::report_errors();
}
