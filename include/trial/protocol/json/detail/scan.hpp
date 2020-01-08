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

#include <trial/protocol/json/detail/scan.hpp>

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
