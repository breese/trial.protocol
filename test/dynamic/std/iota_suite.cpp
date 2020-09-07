///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2017 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <numeric>
#include <trial/protocol/core/detail/lightweight_test.hpp>
#include <trial/dynamic/variable.hpp>

using namespace trial::dynamic;

//-----------------------------------------------------------------------------
// std::iota
//-----------------------------------------------------------------------------

void test_array_boolean()
{
#if __cplusplus < 201703L // bool.operator++ forbidden since C++17
    variable data = array::repeat(4, null);
    std::iota(data.begin(), data.end(), false);
    variable result = array::make({ false, true, true, true });
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                 result.begin(), result.end(),
                                 std::equal_to<variable>());
#endif
}

void test_array_integer()
{
    variable data = array::repeat(4, null);
    std::iota(data.begin(), data.end(), 1);
    variable result = array::make({ 1, 2, 3, 4 });
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                 result.begin(), result.end(),
                                 std::equal_to<variable>());
}

void test_array_real()
{
    variable data = array::repeat(4, null);
    std::iota(data.begin(), data.end(), 1.0);
    variable result = array::make({ 1.0, 2.0, 3.0, 4.0 });
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                 result.begin(), result.end(),
                                 std::equal_to<variable>());
}

int main()
{
    test_array_boolean();
    test_array_integer();
    test_array_real();

    return boost::report_errors();
}
