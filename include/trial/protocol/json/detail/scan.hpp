#ifndef TRIAL_PROTOCOL_JSON_DETAIL_SCAN_HPP
#define TRIAL_PROTOCOL_JSON_DETAIL_SCAN_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2020 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <trial/protocol/core/detail/bit.hpp>
#include <trial/protocol/core/detail/simd.hpp>

namespace trial
{
namespace protocol
{
namespace json
{
namespace detail
{

template <typename CharT>
auto scan_narrow(const CharT *marker,
                 const CharT * const tail) noexcept -> const CharT *
{
#if defined(TRIAL_PROTOCOL_USE_SSE2)
    const auto quote = _mm_set1_epi8(0x22);
    const auto escape = _mm_set1_epi8(0x5C);
    const auto control = _mm_set1_epi8(0x20); // and extra
    while (tail - marker > 16)
    {
        const auto data = _mm_loadu_si128((const __m128i *)marker);
        const auto avoid = _mm_or_si128(_mm_or_si128(_mm_cmpeq_epi8(data, quote),
                                                     _mm_cmpeq_epi8(data, escape)),
                                        _mm_cmplt_epi8(data, control));
        const auto mask = _mm_movemask_epi8(avoid);
        if (mask != 0)
            return marker + core::detail::countl_zero(mask);
        marker += 16;
    }
#endif

    (void)tail;
    while (traits::to_category(*marker) == traits::category::narrow)
    {
        ++marker;
    }
    return marker;
}

template <typename CharT>
auto scan_digit(const CharT *marker,
                const CharT * const tail) noexcept -> const CharT *
{
#if defined(TRIAL_PROTOCOL_USE_SSE2)
    const auto digit_0 = _mm_set1_epi8(0x30);
    const auto digit_9 = _mm_set1_epi8(0x39);
    while (tail - marker > 16)
    {
        const auto data = _mm_loadu_si128((const __m128i *)marker);
        const auto avoid = _mm_or_si128(_mm_cmplt_epi8(data, digit_0),
                                        _mm_cmpgt_epi8(data, digit_9));
        const auto mask = _mm_movemask_epi8(avoid);
        if (mask != 0)
            return marker + core::detail::countl_zero(mask);
        marker += 16;
    }
#endif

    (void)tail;
    while (true)
    {
        if (!traits::is_digit(marker[0])) { break; }
        if (!traits::is_digit(marker[1])) { marker += 1; break; }
        if (!traits::is_digit(marker[2])) { marker += 2; break; }
        if (!traits::is_digit(marker[3])) { marker += 3; break; }
        marker += 4;
    }
    return marker;
}

} // namespace detail
} // namespace json
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_JSON_DETAIL_SCAN_HPP
