#ifndef TRIAL_PROTOCOL_JSON_PARSE_HPP
#define TRIAL_PROTOCOL_JSON_PARSE_HPP

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
#include <trial/protocol/json/reader.hpp>
#include <trial/protocol/json/detail/parse.ipp>

namespace trial
{
namespace protocol
{
namespace json
{

namespace partial
{

//! @brief Decode JSON formatted data into dynamic variable.
//!
//! Starts decoding at the current position of @c reader. Decodes a singular
//! value or a container. The @c reader will point to the remainder of the
//! encoded data after this function.
//!
//! @param reader Reader pointing to an arbitrary position within a buffer.
//! @returns Dynamic variable containing the decoded JSON data.

template <template <typename> class Allocator = std::allocator>
auto parse(json::reader& reader) -> dynamic::basic_variable<Allocator>
{
    detail::basic_parser<char, Allocator> parser(reader);
    return parser.parse();
}

} // namespace partial

//! @brief Decode JSON formatted data into dynamic variable.
//!
//! @param input The JSON formatted input buffer.
//! @returns Dynamic variable containing the decoded JSON data.

template <typename U, template <typename> class Allocator = std::allocator>
auto parse(const U& input) -> dynamic::basic_variable<Allocator>
{
    json::reader reader(input);
    auto result = partial::parse(reader);
    if (reader.symbol() != json::token::symbol::end)
        throw json::error(json::unexpected_token);
    return result;
}

} // namespace json
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_JSON_PARSE_HPP
