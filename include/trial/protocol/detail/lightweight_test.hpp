#ifndef TRIAL_PROTOCOL_DETAIL_LIGHTWEIGHT_TEST_HPP
#define TRIAL_PROTOCOL_DETAIL_LIGHTWEIGHT_TEST_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2015 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <string>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <boost/detail/lightweight_test.hpp>

namespace trial
{
namespace protocol
{
namespace detail
{

template<class InputIt1, class InputIt2, class Predicate>
inline void test_mismatch_impl(char const * file, int line, char const * function,
                               InputIt1 first_begin, InputIt1 first_end,
                               InputIt2 second_begin, InputIt2 second_end,
                               Predicate predicate)
{
    if (std::distance(first_begin, first_end) != std::distance(second_begin, second_end))
    {
        ::boost::detail::error_impl("Container sizes are different", file, line, function);
    }
    else
    {
        std::pair<InputIt1, InputIt2> result = std::mismatch(first_begin, first_end, second_begin, predicate);
        if (result.first == first_end)
        {
            boost::detail::report_errors_remind();
        }
        else
        {
            std::ostringstream indices;
            while (result.first != first_end)
            {
                indices << ' ' << std::distance(first_begin, result.first);
                result = std::mismatch(++result.first, first_end, ++result.second);
            }
            BOOST_LIGHTWEIGHT_TEST_OSTREAM
                << file << "(" << line << "): Container contents differ in function '" << function << "': mismatching indices"
                << indices.str() << std::endl;
            ++boost::detail::test_errors();
        }
    }
}

} // namespace detail
} // namespace protocol
} // namespace trial

#define TRIAL_PROTOCOL_TEST BOOST_TEST
#define TRIAL_PROTOCOL_TEST_EQUAL BOOST_TEST_EQ

#define TRIAL_PROTOCOL_TEST_THROW_EQUAL(EXPR, EXCEP, MSG)               \
        try {                                                           \
        EXPR;                                                           \
        ::boost::detail::throw_failed_impl                              \
              (#EXCEP, __FILE__, __LINE__, BOOST_CURRENT_FUNCTION);     \
    }                                                                   \
    catch(EXCEP const& ex) {                                            \
        ::boost::detail::test_eq_impl                                   \
            (#EXPR, #EXPR, __FILE__, __LINE__, BOOST_CURRENT_FUNCTION, std::string(ex.what()), MSG); \
    }                                                                   \
    catch(...) {                                                        \
        ::boost::detail::throw_failed_impl                              \
            (#EXCEP, __FILE__, __LINE__, BOOST_CURRENT_FUNCTION);       \
    }

#define TRIAL_PROTOCOL_TEST_NO_THROW(EXPR)                              \
    try {                                                               \
        EXPR;                                                           \
    }                                                                   \
    catch (...) {                                                       \
        const char *msg = "Unexpected exception from '" #EXPR "'";      \
        ::boost::detail::error_impl(msg, __FILE__, __LINE__, BOOST_CURRENT_FUNCTION); \
    }

#define TRIAL_PROTOCOL_TEST_ALL_WITH(FIRST_BEGIN, FIRST_END, SECOND_BEGIN, SECOND_END, PREDICATE) ::trial::protocol::detail::test_mismatch_impl(__FILE__, __LINE__, BOOST_CURRENT_FUNCTION, FIRST_BEGIN, FIRST_END, SECOND_BEGIN, SECOND_END, PREDICATE)

#endif // TRIAL_PROTOCOL_DETAIL_LIGHTWEIGHT_TEST_HPP
