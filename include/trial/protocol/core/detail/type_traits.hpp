#ifndef TRIAL_PROTOCOL_CORE_DETAIL_TYPE_TRAITS_HPP
#define TRIAL_PROTOCOL_CORE_DETAIL_TYPE_TRAITS_HPP

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
#include <trial/protocol/core/detail/meta.hpp>

namespace trial
{
namespace protocol
{
namespace core
{
namespace detail
{

template <typename T>
using is_bool = std::is_same<typename std::decay<T>::type, bool>;

template <typename, typename = void>
struct is_iterator : std::false_type {};

template <typename T>
struct is_iterator<T, meta::void_t<typename T::iterator_category>> : std::true_type {};

template <typename>
struct is_pair : std::false_type {};

template <typename T, typename U>
struct is_pair<std::pair<T, U>> : std::true_type {};

template <typename T>
struct make_floating_point
{
    using type = typename std::conditional<
        std::is_same< float, std::common_type<T, float> >::value,
        float,
        typename std::conditional<
            std::is_same< double, std::common_type<T, double> >::value,
            double,
            long double
            >::type
        >::type;
};

template <typename T>
struct make_integral
{
    // This is a crude approximation
    using type = typename std::conditional<
        sizeof(T) <= sizeof(std::int32_t),
            std::int32_t, typename std::conditional<
            sizeof(T) <= sizeof(std::int64_t),
                std::int64_t,
                std::intmax_t
                >::type
        >::type;
};

} // namespace detail
} // namespace core
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_CORE_DETAIL_TYPE_TRAITS_HPP
