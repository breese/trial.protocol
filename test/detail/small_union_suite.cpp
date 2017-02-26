///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2017 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <string>
#include <trial/protocol/detail/lightweight_test.hpp>
#include <trial/protocol/detail/small_union.hpp>

using namespace trial::protocol::detail;

//-----------------------------------------------------------------------------
// Constructor
//-----------------------------------------------------------------------------

namespace ctor_suite
{

void test_int()
{
    small_union<sizeof(int), bool, int> data{true};
    TRIAL_PROTOCOL_TEST_EQUAL(data.get<bool>(), true);
}

void test_int_with_longlong()
{
    small_union<sizeof(int), bool, int, long long> data{3LL};
    TRIAL_PROTOCOL_TEST_EQUAL(data.get<long long>(), 3LL);
}

void test_int_with_string()
{
    small_union<sizeof(int), bool, int, std::string> data{std::string("alpha")};
    TRIAL_PROTOCOL_TEST_EQUAL(data.get<std::string>(), std::string("alpha"));
}

void run()
{
    test_int();
    test_int_with_longlong();
    test_int_with_string();
}

} // namespace ctor_suite

//-----------------------------------------------------------------------------
// main
//-----------------------------------------------------------------------------

int main()
{
    ctor_suite::run();

    return boost::report_errors();
}
