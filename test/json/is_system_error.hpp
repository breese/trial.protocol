#ifndef TRIAL_PROTOCOL_TEST_IS_SYSTEM_ERROR_HPP
#define TRIAL_PROTOCOL_TEST_IS_SYSTEM_ERROR_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2015 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <boost/system/system_error.hpp>

namespace trial
{
namespace protocol
{
namespace test
{

struct is_system_error
{
    is_system_error(const boost::system::error_code& expect)
        : expect(expect)
    {
    }

    bool operator()(const boost::system::system_error& ex)
    {
        const bool is_same = ex.code() == expect;
        if (!is_same)
        {
            BOOST_TEST_MESSAGE(ex.code().message() + " != " + expect.message());
        }
        return is_same;
    }

    boost::system::error_code expect;
};

} // namespace test
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_TEST_IS_SYSTEM_ERROR_HPP
