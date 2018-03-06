#ifndef TRIAL_PROTOCOL_BINTOKEN_PARSE_HPP
#define TRIAL_PROTOCOL_BINTOKEN_PARSE_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2018 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <trial/dynamic/variable.hpp>
#include <trial/protocol/bintoken/reader.hpp>
#include <trial/protocol/bintoken/detail/parse.ipp>

namespace trial
{
namespace protocol
{
namespace bintoken
{

namespace partial
{

template <template <typename> class Allocator = std::allocator>
auto parse(bintoken::reader& reader) -> dynamic::basic_variable<Allocator>
{
    detail::basic_parser<Allocator> parser(reader);
    return parser.parse();
}

} // namespace partial

template <typename U, template <typename> class Allocator = std::allocator>
auto parse(const U& input) -> dynamic::basic_variable<Allocator>
{
    bintoken::reader reader(input);
    auto result = partial::parse(reader);
    if (reader.symbol() != bintoken::token::symbol::end)
        throw bintoken::error(bintoken::unexpected_token);
    return result;
}

} // namespace bintoken
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_BINTOKEN_PARSE_HPP
