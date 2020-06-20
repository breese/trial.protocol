#ifndef TRIAL_PROTOCOL_CORE_DETAIL_LIGHTWEIGHT_TEST_HPP
#define TRIAL_PROTOCOL_CORE_DETAIL_LIGHTWEIGHT_TEST_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2015 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <cmath>
#include <string>
#include <algorithm>
#include <iterator>
#include <boost/version.hpp>
#include <boost/detail/lightweight_test.hpp>

namespace trial
{
namespace protocol
{
namespace core
{
namespace detail
{

void test_success()
{
#if BOOST_VERSION >= 106800
    ::boost::detail::test_results();
#else
    ::boost::detail::report_errors_remind();
#endif
}

void test_failure()
{
#if BOOST_VERSION >= 106800
    ::boost::detail::test_results().errors();
#else
    ++::boost::detail::test_errors();
#endif
}

template <class T, class U>
void test_eq_impl(char const * expr1,
                  char const * expr2,
                  char const * file, int line, char const * function,
                  const T& lhs, const U& rhs)
{
# if BOOST_VERSION >= 106800
    ::boost::detail::test_with_impl(::boost::detail::lw_test_eq(), expr1, expr2, file, line, function, lhs, rhs);
#else
    ::boost::detail::test_eq_impl(expr1, expr2, file, line, function, lhs, rhs);
#endif
}

template <typename T>
inline void test_close_impl(char const * expr1,
                            char const * expr2,
                            char const * file, int line, char const * function,
                            const T& lhs, const T& rhs, T tolerance)
{
    if (std::fabs(lhs - rhs) <= tolerance)
    {
        test_success();
    }
    else
    {
        BOOST_LIGHTWEIGHT_TEST_OSTREAM
            << file << "(" << line << "): test '" << expr1 << " == " << expr2
            << "' failed in function '" << function << "': "
            << "'" << lhs << "' != '" << rhs << "'" << std::endl;
        test_failure();
    }
}

#if !defined(BOOST_TEST_ALL_EQ)
template<class FormattedOutputFunction, class InputIterator1, class InputIterator2>
void test_all_eq_impl(FormattedOutputFunction& output,
                      char const * file, int line, char const * function,
                      InputIterator1 first_begin, InputIterator1 first_end,
                      InputIterator2 second_begin, InputIterator2 second_end)
{
    InputIterator1 first_it = first_begin;
    InputIterator2 second_it = second_begin;
    typename std::iterator_traits<InputIterator1>::difference_type first_index = 0;
    typename std::iterator_traits<InputIterator2>::difference_type second_index = 0;
    std::size_t error_count = 0;
    const std::size_t max_count = 8;
    do
    {
        while ((first_it != first_end) && (second_it != second_end) && (*first_it == *second_it))
        {
            ++first_it;
            ++second_it;
            ++first_index;
            ++second_index;
        }
        if ((first_it == first_end) || (second_it == second_end))
        {
            break; // do-while
        }
        if (error_count == 0)
        {
            output << file << "(" << line << "): Container contents differ in function '" << function << "':";
        }
        else if (error_count >= max_count)
        {
            output << " ...";
            break;
        }
        output << " [" << first_index << "] '" << *first_it << "' != '" << *second_it << "'";
        ++first_it;
        ++second_it;
        ++first_index;
        ++second_index;
        ++error_count;
    } while (first_it != first_end);

    first_index += std::distance(first_it, first_end);
    second_index += std::distance(second_it, second_end);
    if (first_index != second_index)
    {
        if (error_count == 0)
        {
            output << file << "(" << line << "): Container sizes differ in function '" << function << "': size(" << first_index << ") != size(" << second_index << ")";
        }
        else
        {
            output << " [*] size(" << first_index << ") != size(" << second_index << ")";
        }
        ++error_count;
    }

    if (error_count == 0)
    {
        test_success();
    }
    else
    {
        output << std::endl;
        test_failure();
    }
}
#endif

#if !defined(BOOST_TEST_ALL_WITH)
template<class FormattedOutputFunction, class InputIterator1, class InputIterator2, typename Predicate>
void test_all_with_impl(FormattedOutputFunction& output,
                        char const * file, int line, char const * function,
                        InputIterator1 first_begin, InputIterator1 first_end,
                        InputIterator2 second_begin, InputIterator2 second_end,
                        Predicate predicate)
{
    InputIterator1 first_it = first_begin;
    InputIterator2 second_it = second_begin;
    typename std::iterator_traits<InputIterator1>::difference_type first_index = 0;
    typename std::iterator_traits<InputIterator2>::difference_type second_index = 0;
    std::size_t error_count = 0;
    const std::size_t max_count = 8;
    do
    {
        while ((first_it != first_end) && (second_it != second_end) && predicate(*first_it, *second_it))
        {
            ++first_it;
            ++second_it;
            ++first_index;
            ++second_index;
        }
        if ((first_it == first_end) || (second_it == second_end))
        {
            break; // do-while
        }
        if (error_count == 0)
        {
            output << file << "(" << line << "): Container contents differ in function '" << function << "':";
        }
        else if (error_count >= max_count)
        {
            output << " ...";
            break;
        }
        output << " [" << first_index << "]";
        ++first_it;
        ++second_it;
        ++first_index;
        ++second_index;
        ++error_count;
    } while (first_it != first_end);

    first_index += std::distance(first_it, first_end);
    second_index += std::distance(second_it, second_end);
    if (first_index != second_index)
    {
        if (error_count == 0)
        {
            output << file << "(" << line << "): Container sizes differ in function '" << function << "': size(" << first_index << ") != size(" << second_index << ")";
        }
        else
        {
            output << " [*] size(" << first_index << ") != size(" << second_index << ")";
        }
        ++error_count;
    }

    if (error_count == 0)
    {
        test_success();
    }
    else
    {
        output << std::endl;
        test_failure();
    }
}
#endif

} // namespace detail
} // namespace core
} // namespace protocol
} // namespace trial

#define TRIAL_PROTOCOL_TEST BOOST_TEST
#define TRIAL_PROTOCOL_TEST_EQUAL BOOST_TEST_EQ
#define TRIAL_PROTOCOL_TEST_NE BOOST_TEST_NE
#define TRIAL_PROTOCOL_TEST_THROWS BOOST_TEST_THROWS

#define TRIAL_PROTOCOL_TEST_THROW_EQUAL(EXPR, EXCEP, MSG)               \
    try {                                                               \
        EXPR;                                                           \
        ::boost::detail::throw_failed_impl                              \
              (#EXCEP, __FILE__, __LINE__, BOOST_CURRENT_FUNCTION);     \
    }                                                                   \
    catch(EXCEP const& ex) {                                            \
        ::trial::protocol::core::detail::test_eq_impl                   \
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

#define TRIAL_PROTOCOL_TEST_CLOSE(LHS, RHS, TOLERANCE) ::trial::protocol::core::detail::test_close_impl(#LHS, #RHS, __FILE__, __LINE__, BOOST_CURRENT_FUNCTION, LHS, RHS, TOLERANCE)

#if !defined(BOOST_TEST_ALL_EQ)
# define TRIAL_PROTOCOL_TEST_ALL_EQUAL(FIRST_BEGIN, FIRST_END, SECOND_BEGIN, SECOND_END) ::trial::protocol::core::detail::test_all_eq_impl(BOOST_LIGHTWEIGHT_TEST_OSTREAM, __FILE__, __LINE__, BOOST_CURRENT_FUNCTION, FIRST_BEGIN, FIRST_END, SECOND_BEGIN, SECOND_END)
#else
# define TRIAL_PROTOCOL_TEST_ALL_EQUAL BOOST_TEST_ALL_EQ
#endif

#if !defined(BOOST_TEST_ALL_WITH)
# define TRIAL_PROTOCOL_TEST_ALL_WITH(FIRST_BEGIN, FIRST_END, SECOND_BEGIN, SECOND_END, PREDICATE) ::trial::protocol::core::detail::test_all_with_impl(BOOST_LIGHTWEIGHT_TEST_OSTREAM, __FILE__, __LINE__, BOOST_CURRENT_FUNCTION, FIRST_BEGIN, FIRST_END, SECOND_BEGIN, SECOND_END, PREDICATE)
#else
# define TRIAL_PROTOCOL_TEST_ALL_WITH BOOST_TEST_ALL_WITH
#endif

#endif // TRIAL_PROTOCOL_CORE_DETAIL_LIGHTWEIGHT_TEST_HPP
