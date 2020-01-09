#ifndef TRIAL_PROTOCOL_CORE_DETAIL_BIT_HPP
#define TRIAL_PROTOCOL_CORE_DETAIL_BIT_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2020 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#if __cplusplus >= 201806L
# define TRIAL_PROTOCOL_HAS_HEADER_BIT 1
# include <bit>
#else
# include <type_traits>
#endif

namespace trial
{
namespace protocol
{
namespace core
{
namespace detail
{

#if defined(TRIAL_PROTOCOL_HAS_HEADER_BIT)

using std::countl_zero;

#else

namespace detail
{

#if defined(__GNUC__) || defined(__clang__)

constexpr int countl_zero(unsigned char x) noexcept
{
    return __builtin_ctz(x);
}

constexpr int countl_zero(unsigned short x) noexcept
{
    return __builtin_ctz(x);
}

constexpr int countl_zero(unsigned x) noexcept
{
    return __builtin_ctz(x);
}

constexpr int countl_zero(unsigned long x) noexcept
{
        return __builtin_ctzl(x);
}

constexpr int countl_zero(unsigned long long x) noexcept
{
        return __builtin_ctzll(x);
}

#endif

} // namespace detail

template <typename T>
constexpr int countl_zero(T x) noexcept
{
#if defined(__GNUC__) || defined(__clang__)
    return detail::countl_zero(typename std::make_unsigned<T>::type(x));
#else
# error "No countl_zero implementation"
#endif
}

#endif

} // namespace detail
} // namespace core
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_CORE_DETAIL_BIT_HPP
