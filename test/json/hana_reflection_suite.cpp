///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2021 Vinícius dos Santos Oliveira
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <sstream>
#include <trial/protocol/buffer/ostream.hpp>
#include <trial/protocol/json/serialization/boost/hana.hpp>
#include <trial/protocol/core/detail/lightweight_test.hpp>

using namespace trial::protocol;

//-----------------------------------------------------------------------------
// Basic types
//-----------------------------------------------------------------------------

struct Foobar {
    BOOST_HANA_DEFINE_STRUCT(Foobar,
        (int, foo),
        (int, bar),
        (int, baz)
    );
};

namespace basic_suite
{

void test_oarchive()
{
    std::ostringstream result;
    json::oarchive ar(result);
    Foobar value{5, 10, 0};
    ar << value;
    TRIAL_PROTOCOL_TEST_EQUAL(result.str(), "{\"foo\":5,\"bar\":10,\"baz\":0}");
}

void test_iarchive()
{
    const char input[] = "{\"foo\":5,\"bar\":10,\"baz\":0}";
    json::iarchive in(input);
    Foobar value{1, 2, 3};
    TRIAL_PROTOCOL_TEST_NO_THROW(in >> value);
    TRIAL_PROTOCOL_TEST_EQUAL(value.foo, 5);
    TRIAL_PROTOCOL_TEST_EQUAL(value.bar, 10);
    TRIAL_PROTOCOL_TEST_EQUAL(value.baz, 0);
}

void run()
{
    test_oarchive();
    test_iarchive();
}

} // namespace basic_suite

//-----------------------------------------------------------------------------
// main
//-----------------------------------------------------------------------------

int main()
{
    basic_suite::run();

    return boost::report_errors();
}
