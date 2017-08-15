///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2017 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <trial/protocol/core/detail/lightweight_test.hpp>
#include <trial/protocol/core/detail/meta.hpp>

using namespace trial::protocol::core::detail;

//-----------------------------------------------------------------------------
// transform
//-----------------------------------------------------------------------------

namespace transform_suite
{

void test_add_const()
{
    using typelist = meta::list<bool, int>;
    using constlist = meta::transform<typelist, std::add_const>;
    TRIAL_PROTOCOL_TEST_EQUAL((meta::to_index<constlist, bool>::value), 2);
    TRIAL_PROTOCOL_TEST_EQUAL((meta::to_index<constlist, const bool>::value), 0);
    TRIAL_PROTOCOL_TEST_EQUAL((meta::to_index<constlist, int>::value), 2);
    TRIAL_PROTOCOL_TEST_EQUAL((meta::to_index<constlist, const int>::value), 1);
}

void run()
{
    test_add_const();
}

} // namespace transform_suite

//-----------------------------------------------------------------------------
// to_index
//-----------------------------------------------------------------------------

namespace to_index_suite
{

void test_two()
{
    using typelist = meta::list<bool, int>;
    TRIAL_PROTOCOL_TEST_EQUAL((meta::to_index<typelist, bool>::value), 0);
    TRIAL_PROTOCOL_TEST_EQUAL((meta::to_index<typelist, int>::value), 1);
}

void run()
{
    test_two();
}

} // namespace to_index_suite

//-----------------------------------------------------------------------------
// to_type
//-----------------------------------------------------------------------------

namespace to_type_suite
{

void test_two()
{
    using typelist = meta::list<bool, int>;
    using first_type = meta::to_type<typelist, 0>;
    using second_type = meta::to_type<typelist, 1>;
    TRIAL_PROTOCOL_TEST_EQUAL((meta::to_index<typelist, first_type>::value), 0);
    TRIAL_PROTOCOL_TEST_EQUAL((meta::to_index<typelist, second_type>::value), 1);
}

void run()
{
    test_two();
}

} // namespace to_type_suite

//-----------------------------------------------------------------------------
// main
//-----------------------------------------------------------------------------

int main()
{
    transform_suite::run();
    to_index_suite::run();
    to_type_suite::run();

    return boost::report_errors();
}
