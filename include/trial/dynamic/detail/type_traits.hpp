#ifndef TRIAL_DYNAMIC_DETAIL_TYPE_TRAITS_HPP
#define TRIAL_DYNAMIC_DETAIL_TYPE_TRAITS_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2016 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <cstdint>
#include <trial/dynamic/detail/meta.hpp>

namespace trial
{
namespace dynamic
{
namespace detail
{

// An alternative for static_assert that outputs the type T
template <typename...>
struct static_assert_t;

template <typename T>
using is_bool = std::is_same<typename std::decay<T>::type, bool>;

template <typename, typename = void>
struct is_iterator : std::false_type {};

template <typename T>
struct is_iterator<T, trial::dynamic::meta::void_t<typename T::iterator_category>> : std::true_type {};

template <typename>
struct is_pair : std::false_type {};

template <typename T, typename U>
struct is_pair<std::pair<T, U>> : std::true_type {};

} // namespace detail
} // namespace dynamic
} // namespace trial

#endif // TRIAL_DYNAMIC_DETAIL_TYPE_TRAITS_HPP
