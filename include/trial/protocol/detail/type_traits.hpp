#ifndef TRIAL_PROTOCOL_DETAIL_TYPE_TRAITS_HPP
#define TRIAL_PROTOCOL_DETAIL_TYPE_TRAITS_HPP

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
#include <type_traits>

namespace trial
{
namespace protocol
{
namespace detail
{

template <typename T>
using is_bool = std::is_same<typename std::decay<T>::type, bool>;

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
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_DETAIL_TYPE_TRAITS_HPP
