#ifndef TRIAL_DYNAMIC_CONVERT_ENUM_HPP
#define TRIAL_DYNAMIC_CONVERT_ENUM_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2018 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <type_traits>
#include <trial/dynamic/variable.hpp>
#include <trial/dynamic/convert.hpp>

namespace trial
{
namespace dynamic
{
namespace convert
{

namespace detail
{

template <typename T>
struct is_enum
    : std::conditional<std::is_enum<T>::value &&
                       !dynamic::detail::is_null<T>::value,
                       std::true_type,
                       std::false_type>::type
{
};

} // namespace detail

//! @brief Trait for enum conversion.
//!
//! Specialize trait to enable conversion between dynamic variable and enum
//! using the underlying type.

template <typename T>
struct use_underlying_type : public std::false_type {};

template <template <typename> class Allocator, typename T>
struct overloader<
    basic_variable<Allocator>,
    T,
    typename std::enable_if<detail::is_enum<T>::value &&
                            use_underlying_type<T>::value>::type>
{
    static basic_variable<Allocator> into(const T& data,
                                          std::error_code&)
    {
        return static_cast<typename std::underlying_type<T>::type>(data);
    }
};

template <template <typename> class Allocator, typename T>
struct overloader<
    T,
    basic_variable<Allocator>,
    typename std::enable_if<detail::is_enum<T>::value &&
                            use_underlying_type<T>::value>::type>
{
    static T into(const basic_variable<Allocator>& data,
                  std::error_code& error)
    {
        return static_cast<T>(data.template value<typename std::underlying_type<T>::type>(error));
    }
};

} // namespace convert
} // namespace dynamic
} // namespace trial

#endif // TRIAL_DYNAMIC_CONVERT_ENUM_HPP
