#ifndef TRIAL_DYNAMIC_DETAIL_EMPTY_VALUE_HPP
#define TRIAL_DYNAMIC_DETAIL_EMPTY_VALUE_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2018 Glen Joseph Fernandes
// Copyright (C) 2019 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <type_traits>
#include <boost/version.hpp>
#if BOOST_VERSION < 107000
# include <boost/type_traits/is_final.hpp>
#else
# include <boost/core/empty_value.hpp>
# define TRIAL_PROTOCOL_USE_BOOST_EMPTY_VALUE 1
#endif

namespace trial
{
namespace dynamic
{
namespace detail
{

#if TRIAL_PROTOCOL_USE_BOOST_EMPTY_VALUE

template <typename... Ts>
using empty_value = boost::empty_value<Ts...>;

using boost::empty_init_t;

#else // boost::empty_value is not available

// Mostly copied from boost::empty_value

struct empty_init_t {};

template <typename T>
struct use_empty_value_base
{
    enum { value = std::is_empty<T>::value && boost::is_final<T>::value };
};

template <typename T,
          bool Enable = use_empty_value_base<T>::value>
class empty_value
{
public:
    using type = T;

    empty_value() = default;

    template <typename... Args>
    empty_value(empty_init_t, Args&&... args)
        : value(std::forward<Args>(args)...)
    {
    }


    const T& get() const noexcept
    {
        return value;
    }

    T& get() noexcept
    {
        return value;
    }

private:
    T value;
};

template <typename T>
class empty_value<T, true>
    : T
{
public:
    using type = T;

    empty_value() = default;

    template <typename... Args>
    empty_value(empty_init_t, Args&&... args)
        : T(std::forward<Args>(args)...)
    {
    }

    const T& get() const noexcept
    {
        return *this;
    }

    T& get() noexcept
    {
        return *this;
    }
};

#endif

} // namespace detail
} // namespace dynamic
} // namespace trial

#endif // TRIAL_DYNAMIC_DETAIL_EMPTY_VALUE_HPP
