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
#include <trial/dynamic/variable.hpp>

using namespace trial::dynamic;

//-----------------------------------------------------------------------------
// std::rotate
//-----------------------------------------------------------------------------

void rotate_boolean()
{
    // Boolean is a single value container so rotating has no effect.
    variable data(true);
    std::rotate(data.begin(), ++data.begin(), data.end());
    TRIAL_PROTOCOL_TEST(data.is<boolean>());
    TRIAL_PROTOCOL_TEST(data == true);
}

void rotate_array()
{
    variable data = array::make({ null, true, 2, 3.0, "alpha", L"bravo", u"charlie", U"delta" });

    std::rotate(data.begin(), ++data.begin(), data.end());
    variable expect = array::make({ true, 2, 3.0, "alpha", L"bravo", u"charlie", U"delta", null });
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());

    std::rotate(data.begin(), ++(++data.begin()), data.end());
    expect = array::make({ 3.0, "alpha", L"bravo", u"charlie", U"delta", null, true, 2 });
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());

    std::rotate(data.begin(), ++(++(++data.begin())), data.end());
    expect = array::make({ u"charlie", U"delta", null, true, 2, 3.0, "alpha", L"bravo" });
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

int main()
{
    rotate_boolean();
    rotate_array();

    return boost::report_errors();
}
