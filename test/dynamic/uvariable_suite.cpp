///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2017 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <limits>
#include <functional>
#include <trial/protocol/detail/lightweight_test.hpp>
#include <trial/protocol/dynamic/variable.hpp>

using namespace trial::protocol::dynamic;

using uvariable = basic_variable<unsigned char>;

//-----------------------------------------------------------------------------
// uvariable
//-----------------------------------------------------------------------------

namespace uvariable_suite
{

void test_ctor()
{
    {
        uvariable data;
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<uvariable::null_type>(), true);
    }
    {
        uvariable data(true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
    }
    {
        uvariable data(2);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
    }
    {
        uvariable data(3.0);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<float>(), true);
    }
    {
        const unsigned char literal[] = { 'a', 'l', 'p', 'h', 'a', 0 };
        uvariable data(literal);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<uvariable::string_type>(), true);
    }
}

void run()
{
    test_ctor();
}

} // namespace uvariable_suite

//-----------------------------------------------------------------------------
// main
//-----------------------------------------------------------------------------

int main()
{
    uvariable_suite::run();
    return boost::report_errors();
}
