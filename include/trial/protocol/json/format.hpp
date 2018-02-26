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

namespace partial
{

template <template <typename> class Allocator>
void format(const trial::dynamic::basic_variable<Allocator>& data,
            json::writer& writer)
{
    detail::basic_formatter<char, Allocator> vis(writer);
    trial::dynamic::visit(vis, data);
}

} // namespace partial

//! @brief Encode dynamic variable into JSON.
//!
//! @param data Dynamic variable.
//! @returns Buffer containing the formatted JSON output.
//! @throws json::error if input contains a wstring, u16string, or u32string.

template <typename T, template <typename> class Allocator>
auto format(const trial::dynamic::basic_variable<Allocator>& data) -> T
{
    T result;
    json::writer writer(result);
    partial::format(data, writer);
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
    json::writer writer(result);
    partial::format(data, writer);
}

} // namespace tree
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_JSON_FORMAT_HPP
