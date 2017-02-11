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
#include <boost/detail/lightweight_test.hpp>

namespace trial
{
namespace protocol
{
namespace detail
{

template<class FormattedOutputFunction, class FwdIt1, class FwdIt2>
void test_all_eq_impl(FormattedOutputFunction& output,
                      char const * file, int line, char const * function,
                      FwdIt1 first_begin, FwdIt1 first_end,
                      FwdIt2 second_begin, FwdIt2 second_end)
{
    if (std::distance(first_begin, first_end) != std::distance(second_begin, second_end))
    {
        ::boost::detail::error_impl("Container sizes are different", __FILE__, __LINE__, BOOST_CURRENT_FUNCTION);
    }
    else
    {
        FwdIt1 first_it = first_begin;
        FwdIt2 second_it = second_begin;
        bool output_header = true;
        do
        {
            while ((first_it != first_end) && (second_it != second_end) && (*first_it == *second_it))
            {
                ++first_it;
                ++second_it;
            }
            if (first_it == first_end)
            {
                boost::detail::report_errors_remind();
                return;
            }
            if (output_header)
            {
                output_header = false;
                output << file << "(" << line << "): Container contents differ in function '" << function << "': mismatching indices";
            }
            output << " [" << std::distance(first_begin, first_it) << "] '" << *first_it << "' != '" << *second_it << "'";
            ++first_it;
            ++second_it;
        } while (first_it != first_end);
        output << std::endl;
        ++boost::detail::test_errors();
    }
}

template<class FwdIt1, class FwdIt2, class Predicate>
void test_all_with_impl(std::ostream& output,
                        char const * file, int line, char const * function,
                        FwdIt1 first_begin, FwdIt1 first_end,
                        FwdIt2 second_begin, FwdIt2 second_end,
                        Predicate predicate)
{
    if (std::distance(first_begin, first_end) != std::distance(second_begin, second_end))
    {
        ::boost::detail::error_impl("Container sizes are different", file, line, function);
    }
    else
    {
        FwdIt1 first_it = first_begin;
        FwdIt2 second_it = second_begin;
        bool output_header = true;
        do
        {
            while ((first_it != first_end) && (second_it != second_end) && predicate(*first_it, *second_it))
            {
                ++first_it;
                ++second_it;
            }
            if (first_it == first_end)
            {
                boost::detail::report_errors_remind();
                return;
            }
            if (output_header)
            {
                output_header = false;
                output << file << "(" << line << "): Container contents differ in function '" << function << "': mismatching indices";
            }
            output << ' ' << std::distance(first_begin, first_it);
            ++first_it;
            ++second_it;
        } while (first_it != first_end);
        output << std::endl;
        ++boost::detail::test_errors();
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

#define TRIAL_PROTOCOL_TEST_ALL_EQUAL(FIRST_BEGIN, FIRST_END, SECOND_BEGIN, SECOND_END) ::trial::protocol::detail::test_all_eq_impl(BOOST_LIGHTWEIGHT_TEST_OSTREAM, __FILE__, __LINE__, BOOST_CURRENT_FUNCTION, FIRST_BEGIN, FIRST_END, SECOND_BEGIN, SECOND_END)
#define TRIAL_PROTOCOL_TEST_ALL_WITH(FIRST_BEGIN, FIRST_END, SECOND_BEGIN, SECOND_END, PREDICATE) ::trial::protocol::detail::test_all_with_impl(BOOST_LIGHTWEIGHT_TEST_OSTREAM, __FILE__, __LINE__, BOOST_CURRENT_FUNCTION, FIRST_BEGIN, FIRST_END, SECOND_BEGIN, SECOND_END, PREDICATE)

#endif // TRIAL_PROTOCOL_DETAIL_LIGHTWEIGHT_TEST_HPP
