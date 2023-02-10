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

#include <trial/protocol/core/detail/config.hpp>
#include <trial/protocol/core/detail/bit.hpp>
#include <trial/protocol/core/detail/simd.hpp>
#include <trial/protocol/json/detail/traits.hpp>

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
    // Swaps space and quote characters
    const auto permuter = _mm_set1_epi8(0x02);
    // Covers permuted quote and control characters + extra characters
    const auto lower = _mm_set1_epi8(0x21);
    const auto escape = _mm_set1_epi8(0x5e);
    while (tail - marker > 16)
    {
        const auto data = _mm_xor_si128(_mm_loadu_si128((const __m128i *)marker),
                                        permuter);
        const auto avoid = _mm_or_si128(_mm_cmpeq_epi8(data, escape),
                                        _mm_cmplt_epi8(data, lower));
        const auto mask = _mm_movemask_epi8(avoid);
        if (mask != 0)
            return marker + core::detail::countr_zero(mask);
        marker += 16;
    }
#endif

    while (marker != tail)
    {
        if (traits::to_category(*marker) == traits::category::narrow)
        {
            ++marker;
        }
        else
            break;
    }
    return marker;
}

template <typename CharT>
auto scan_digit(const CharT *marker,
                const CharT * const tail) noexcept -> const CharT *
{
#if defined(TRIAL_PROTOCOL_USE_SSE2)
    // Shift digits to range [0x75, 0x7F] to make single range comparison
    const auto offset = _mm_set1_epi8(0x7F - 0x39);
    const auto legal = _mm_set1_epi8(0x7F - 10);
    while (tail - marker > 16)
    {
        auto data = _mm_loadu_si128((const __m128i *)marker);
        data = _mm_add_epi8(data, offset);
        data = _mm_cmplt_epi8(data, legal);
        const auto mask = _mm_movemask_epi8(data);
        if (mask != 0)
            return marker + core::detail::countr_zero(mask);
        marker += 16;
    }
#endif

    while (marker != tail)
    {
        if (traits::is_digit(*marker))
        {
            ++marker;
        }
        else
            break;
    }
    return marker;
}

template <typename CharT>
auto scan_whitespace(const CharT *marker,
                     const CharT * const tail) noexcept -> const CharT *
{
    while (marker != tail)
    {
        if (traits::is_space(*marker))
        {
            ++marker;
        }
        else
            break;
    }
    return marker;
}

} // namespace detail
} // namespace json
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_JSON_DETAIL_SCAN_HPP
