#ifndef TRIAL_PROTOCOL_JSON_FORMAT_HPP
#define TRIAL_PROTOCOL_JSON_FORMAT_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2018 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <trial/dynamic/algorithm/visit.hpp>
#include <trial/protocol/json/detail/format.ipp>

namespace trial
{
namespace protocol
{
namespace json
{

//! @brief Encode dynamic variable into JSON.
//!
//! @param data Dynamic variable.
//! @returns Buffer containing the formatted JSON output.
//! @throws json::error if input contains a wstring, u16string, or u32string.

template <typename T, template <typename> class Allocator>
auto format(const trial::dynamic::basic_variable<Allocator>& data) -> T
{
    T result;
    detail::basic_formatter<char, Allocator> vis(result);
    trial::dynamic::visit(vis, data);
    return result;
}

//! @brief Encode dynamic variable into JSON.
//!
//! @param data Dynamic variable.
//! @param[out] result Buffer containing the formatted JSON output.
//! @throws json::error if input contains a wstring, u16string, or u32string.

template <typename T, template <typename> class Allocator>
void format(const trial::dynamic::basic_variable<Allocator>& data,
            T& result)
{
    detail::basic_formatter<char, Allocator> vis(result);
    trial::dynamic::visit(vis, data);
}

} // namespace tree
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_JSON_FORMAT_HPP
