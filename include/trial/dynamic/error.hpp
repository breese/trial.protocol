#ifndef TRIAL_DYNAMIC_ERROR_HPP
#define TRIAL_DYNAMIC_ERROR_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2017 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <system_error>

namespace trial
{
namespace dynamic
{

enum errc
{
    no_error = 0,

    incompatible_type
};

const std::error_category& error_category();

inline std::error_code make_error_code(dynamic::errc e = no_error)
{
    return std::error_code(static_cast<int>(e),
                           dynamic::error_category());
}

//! @brief Dynamic system error.
//!
//! Specialization of @c std::system_error that is used to distinguish between
//! exceptions throw from Trial.Dynamic and other components.
class error : public std::system_error
{
public:
    error(std::error_code ec)
        : system_error(std::move(ec))
    {}
};

} // namespace dynamic
} // namespace trial

namespace std
{

template <>
struct is_error_code_enum<trial::dynamic::errc>
    : public std::true_type
{
};

} // namespace std

#include <trial/dynamic/detail/error.ipp>

#endif // TRIAL_DYNAMIC_ERROR_HPP
