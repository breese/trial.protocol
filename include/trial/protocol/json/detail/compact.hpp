#ifndef TRIAL_PROTOCOL_JSON_DETAIL_COMPACT_HPP
#define TRIAL_PROTOCOL_JSON_DETAIL_COMPACT_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2018 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <cstdint>

namespace trial
{
namespace protocol
{
namespace json
{
namespace detail
{

// Convert std::intmax_t into smallest possible signed integer
template <typename ReturnType>
auto compact(std::intmax_t value) -> ReturnType
{
    if ((value <= std::numeric_limits<signed char>::max()) &&
        (value >= std::numeric_limits<signed char>::min()))
        return static_cast<signed char>(value);
    if ((value <= std::numeric_limits<signed short int>::max()) &&
        (value >= std::numeric_limits<signed short int>::min()))
        return static_cast<signed short int>(value);
    if ((value <= std::numeric_limits<signed int>::max()) &&
        (value >= std::numeric_limits<signed int>::min()))
        return static_cast<signed int>(value);
    if ((value <= std::numeric_limits<signed long int>::max()) &&
        (value >= std::numeric_limits<signed long int>::min()))
        return static_cast<signed long int>(value);
    return value;
}

// Convert std::uintmax_t into smallest possible unsigned integer
template <typename ReturnType>
auto compact(std::uintmax_t value) -> ReturnType
{
    if (value <= std::numeric_limits<unsigned char>::max())
        return static_cast<unsigned char>(value);
    if (value <= std::numeric_limits<unsigned short int>::max())
        return static_cast<unsigned short int>(value);
    if (value <= std::numeric_limits<unsigned int>::max())
        return static_cast<unsigned int>(value);
    if (value <= std::numeric_limits<unsigned long int>::max())
        return static_cast<unsigned long int>(value);
    return value;
}

// Convert long double into smallest possible floating-point number
template <typename ReturnType>
auto compact(long double value) -> ReturnType
{
    // Check that
    //   1. Value is large enough to be represented as type.
    //   2. Value is larger than the lowest number of type.
    //   3. Value is smaller than the highest number of type.

    // float
    {
        using real_type = float;
        const auto tolerance = 1.0L + std::numeric_limits<real_type>::epsilon();
        if ((std::abs(value) * tolerance >= std::numeric_limits<real_type>::min()) &&
            (value >= std::numeric_limits<real_type>::lowest() * tolerance) &&
            (value <= std::numeric_limits<real_type>::max() * tolerance))
        {
            return static_cast<real_type>(value);
        }
    }
    // double
    {
        using real_type = double;
        const auto tolerance = 1.0L + std::numeric_limits<real_type>::epsilon();
        if ((std::abs(value) * tolerance >= std::numeric_limits<real_type>::min()) &&
            (value >= std::numeric_limits<real_type>::lowest() * tolerance) &&
            (value <= std::numeric_limits<real_type>::max() * tolerance))
        {
            return static_cast<real_type>(value);
        }
    }
    // long double
    return value;
}

} // namespace detail
} // namespace json
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_JSON_DETAIL_COMPACT_HPP
