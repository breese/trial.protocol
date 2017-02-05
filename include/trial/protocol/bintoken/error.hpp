#ifndef TRIAL_PROTOCOL_BINTOKEN_ERROR_HPP
#define TRIAL_PROTOCOL_BINTOKEN_ERROR_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2015 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <system_error>
#include <trial/protocol/bintoken/token.hpp>

namespace trial
{
namespace protocol
{
namespace bintoken
{

const std::error_category& error_category();

enum errc
{
    no_error = 0,

    unknown_token,
    unexpected_token,
    negative_length,
    overflow,
    invalid_value,
    incompatible_type,
    expected_end_record,
    expected_end_array,
    expected_end_assoc_array
};

inline enum errc to_errc(token::code::value value)
{
    switch (value)
    {
    case token::code::error_unknown_token:
        return unknown_token;

    case token::code::error_unexpected_token:
        return unexpected_token;

    case token::code::error_negative_length:
        return negative_length;

    case token::code::error_overflow:
        return overflow;

    case token::code::error_invalid_value:
        return invalid_value;

    case token::code::error_expected_end_record:
        return expected_end_record;

    case token::code::error_expected_end_array:
        return expected_end_array;

    case token::code::error_expected_end_assoc_array:
        return expected_end_assoc_array;

    default:
        return no_error;
    }
}

inline std::error_code make_error_code(bintoken::errc e = no_error)
{
    return std::error_code(static_cast<int>(e),
                           bintoken::error_category());
}

class error : public std::system_error
{
public:
    error(std::error_code ec)
        : system_error(std::move(ec))
    {}
    error(enum errc e)
        : system_error(make_error_code(e))
    {}
};

} // namespace bintoken
} // namespace protocol
} // namespace trial

namespace std
{

template <>
struct is_error_code_enum<trial::protocol::bintoken::errc>
    : public std::true_type
{
};

} // namespace std

#include <trial/protocol/bintoken/detail/error.ipp>

#endif // TRIAL_PROTOCOL_BINTOKEN_ERROR_HPP
