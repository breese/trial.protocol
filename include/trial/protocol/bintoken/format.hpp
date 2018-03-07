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

template <template <typename> class Allocator>
void format(const trial::dynamic::basic_variable<Allocator>& data,
            bintoken::writer& writer)
{
    detail::basic_formatter<Allocator> vis(writer);
    trial::dynamic::visit(vis, data);
}

} // namespace partial

template <typename T, template <typename> class Allocator>
auto format(const trial::dynamic::basic_variable<Allocator>& data) -> T
{
    T result;
    bintoken::writer writer(result);
    partial::format(data, writer);
    return result;
}

template <typename T, template <typename> class Allocator>
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
