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

namespace trial
{
namespace protocol
{
namespace json
{

const boost::system::error_category& error_category();

enum errors
{
    no_error = 0,

    not_implemented,
    unexpected_token,
    invalid_value,
    incompatible_type,

    unbalanced_array_end_bracket,
    unbalanced_object_end_bracket,
    expected_array_end_bracket,
    expected_object_end_bracket
};

inline boost::system::error_code make_error_code(json::errors e = no_error)
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

template<> struct is_error_code_enum<trial::protocol::json::errors>
{
  static const bool value = true;
};

} // namespace system
} // namespace boost

#include <trial/protocol/json/detail/error.ipp>

#endif // TRIAL_PROTOCOL_JSON_ERROR_HPP
