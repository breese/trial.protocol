#ifndef TRIAL_PROTOCOL_BINKTOKEN_FORMAT_HPP
#define TRIAL_PROTOCOL_BINKTOKEN_FORMAT_HPP

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
#include <trial/protocol/bintoken/writer.hpp>
#include <trial/protocol/bintoken/detail/format.ipp>

namespace trial
{
namespace protocol
{
namespace bintoken
{

namespace partial
{

//! @brief Encode dynamic variable into BinToken at current position.
//!
//! @param data Dynamic variable.
//! @param[out] writer Writer pointing to arbitrary location within a buffer.
//! @throw bintoken::error if input contains a long double, wstring, u16string,
//!        or u32string.
template <typename Allocator>
void format(const trial::dynamic::basic_variable<Allocator>& data,
            bintoken::writer& writer)
{
    detail::basic_formatter<Allocator> vis(writer);
    trial::dynamic::visit(vis, data);
}

} // namespace partial

//! @brief Encode dynamic variable into BinToken.
//!
//! @param data Dynamic variable.
//! @returns Buffer containing the formatted BinToken output.
//! @throw bintoken::error if input contains a long double, wstring, u16string,
//!        or u32string.

template <typename T, typename Allocator>
auto format(const trial::dynamic::basic_variable<Allocator>& data) -> T
{
    T result;
    bintoken::writer writer(result);
    partial::format(data, writer);
    return result;
}

//! @brief Encode dynamic variable into BinToken.
//!
//! @param data Dynamic variable.
//! @param[out] result Buffer containing the formatted BinToken output.
//! @throw bintoken::error if input contains a long double, wstring, u16string,
//!        or u32string.

template <typename T, typename Allocator>
void format(const trial::dynamic::basic_variable<Allocator>& data,
            T& result)
{
    bintoken::writer writer(result);
    partial::format(data, writer);
}

} // namespace bintoken
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_BINKTOKEN_FORMAT_HPP
