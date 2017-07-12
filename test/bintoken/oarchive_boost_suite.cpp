///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2017 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <trial/protocol/buffer/vector.hpp>
#include <trial/protocol/bintoken/serialization.hpp>
#include <trial/protocol/detail/lightweight_test.hpp>

namespace format = trial::protocol::bintoken;
namespace token = format::token;
using output_type = std::uint8_t;

//-----------------------------------------------------------------------------
// Optional
//-----------------------------------------------------------------------------

namespace optional_suite
{

void test_value()
{
    std::vector<output_type> result;
    format::oarchive ar(result);
    boost::optional<std::string> value("A");
    ar << value;

    output_type expected[] = { token::code::string8, 0x01, 0x41 };
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<output_type>());
}

void test_const_value()
{
    std::vector<output_type> result;
    format::oarchive ar(result);
    const boost::optional<std::string> value("A");
    ar << value;

    output_type expected[] = { token::code::string8, 0x01, 0x41 };
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<output_type>());
}

void test_null()
{
    std::vector<output_type> result;
    format::oarchive ar(result);
    boost::optional<std::string> value;
    ar << value;

    output_type expected[] = { token::code::null };
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<output_type>());
}

void run()
{
    test_value();
    test_const_value();
    test_null();
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
