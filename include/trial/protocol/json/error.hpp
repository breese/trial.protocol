#ifndef TRIAL_PROTOCOL_JSON_ERROR_HPP
#define TRIAL_PROTOCOL_JSON_ERROR_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2015 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <boost/system/error_code.hpp>
#include <boost/system/system_error.hpp>
#include <trial/protocol/json/token.hpp>

namespace trial
{
namespace protocol
{
namespace json
{

enum errc
{
    no_error = 0,

    unexpected_token,
    invalid_key,
    invalid_value,
    incompatible_type,

    unbalanced_end_array,
    unbalanced_end_object,
    expected_end_array,
    expected_end_object
};

const boost::system::error_category& error_category();

enum errc to_errc(token::code::value);

inline boost::system::error_code make_error_code(json::errc e = no_error)
{
    return boost::system::error_code(static_cast<int>(e),
                                     json::error_category());
}

class error : public boost::system::system_error
{
public:
    error(boost::system::error_code ec)
        : system_error(ec)
    {}
};

} // namespace json
} // namespace protocol
} // namespace trial

namespace boost
{
namespace system
{

template<> struct is_error_code_enum<trial::protocol::json::errc>
{
  static const bool value = true;
};

} // namespace system
} // namespace boost

#include <trial/protocol/json/detail/error.ipp>

#endif // TRIAL_PROTOCOL_JSON_ERROR_HPP
