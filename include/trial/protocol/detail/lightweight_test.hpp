#ifndef TRIAL_PROTOCOL_TEST_LIGHTWEIGHT_TEST_HPP
#define TRIAL_PROTOCOL_TEST_LIGHTWEIGHT_TEST_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2015 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <iterator>
#include <boost/detail/lightweight_test.hpp>

#define TRIAL_PROTOCOL_TEST BOOST_TEST
#define TRIAL_PROTOCOL_TEST_EQUAL BOOST_TEST_EQ

#define TRIAL_PROTOCOL_TEST_THROWS_CODE( EXPR, EXCEP, CODE )            \
    try {                                                               \
        EXPR;                                                           \
        ::boost::detail::throw_failed_impl                              \
              (#EXCEP, __FILE__, __LINE__, BOOST_CURRENT_FUNCTION);     \
    }                                                                   \
    catch(EXCEP const& ex) {                                            \
        ::boost::detail::test_eq_impl                                   \
            (#EXPR, #CODE, __FILE__, __LINE__, BOOST_CURRENT_FUNCTION, ex.code(), CODE); \
    }                                                                   \
    catch(...) {                                                        \
        ::boost::detail::throw_failed_impl                              \
            (#EXCEP, __FILE__, __LINE__, BOOST_CURRENT_FUNCTION);       \
    }                                                                   \

#define TRIAL_PROTOCOL_TEST_NO_THROW( EXPR )                            \
    try {                                                               \
        EXPR;                                                           \
    }                                                                   \
    catch (...) {                                                       \
        const char *msg = "Unexpected exception from '" #EXPR "'";      \
        ::boost::detail::error_impl(msg, __FILE__, __LINE__, BOOST_CURRENT_FUNCTION); \
    }

#define TRIAL_PROTOCOL_TEST_EQUAL_COLLECTIONS(FIRST_BEGIN, FIRST_END, SECOND_BEGIN, SECOND_END) \
    if (std::distance(FIRST_BEGIN, FIRST_END) != std::distance(SECOND_BEGIN, SECOND_END)) \
        ::boost::detail::error_impl("Container sizes are diffrent", __FILE__, __LINE__, BOOST_CURRENT_FUNCTION); \
    else if (!std::equal(FIRST_BEGIN, FIRST_END, SECOND_BEGIN))         \
        ::boost::detail::error_impl("Container contents differ", __FILE__, __LINE__, BOOST_CURRENT_FUNCTION);

#endif // TRIAL_PROTOCOL_TEST_LIGHTWEIGHT_TEST_HPP
