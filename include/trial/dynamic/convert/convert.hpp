#ifndef TRIAL_DYNAMIC_CONVERT_CONVERT_HPP
#define TRIAL_DYNAMIC_CONVERT_CONVERT_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2018 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <trial/dynamic/detail/type_traits.hpp>
#include <trial/dynamic/error.hpp>
#include <trial/dynamic/variable.hpp>

namespace trial
{
namespace dynamic
{
namespace convert
{

//! @brief Customization point for dynamic variable conversion.
//!
//! Conversion between dynamic variable and custom types can be added by
//! specializing @c overloader.
//!
//! One specialization is needed for converting a dynamic variable into a
//! custom type. The specialization must contain a static @c into function.
//!
//!     template <>
//!     struct overloader<custom_type, dynamic::variable>
//!     {
//!         static custom_type into(const dynamic::variable& input,
//!                                 std::error_code& error) noexcept
//!         {
//!             // Return converted type
//!         }
//!     };
//!
//! The @c into function must report errors in the @c std::error_code output
//! parameter.
//!
//! Another specialization is needed for converting a custom type into a
//! dynamic variable:
//!
//!     template <>
//!     struct overloader<dynamic::variable, custom_type>
//!     {
//!         static dynamic::variable into(const custom_type& input,
//!                                       std::error_code& error) noexcept
//!         {
//!             // Return converted type
//!         }
//!     };
//!
//! The @c overloader struct enables us to do partial specialization of the
//! custom type.

template <typename T, typename U, typename = void>
struct overloader
{
    detail::static_assert_t<T, U> unsupported_type;
};

//! @brief Convert between dynamic variable and another type.
//!
//! Requires that a specialized @overloader struct has been included.
//!
//! Convert a dynamic variable to @c custom_type:
//!
//!     dynamic::variable input;
//!     auto result = dynamic::convert::into<custom_type>(input);
//!
//! Convert into a dynamic variable.
//!
//!     custom_type input;
//!     auto result = dynamic::convert::into<dynamic::variable>(input);
//!
//! @param[in] u From type.
//! @param[out] error Error code.

template <typename T, typename U>
T into(const U& u, std::error_code& error) noexcept
{
    // A compiler error here indicates that the appropriate header file of the
    // type to be converted has not been included.
    return convert::overloader<T, U>::into(u, error);
}

template <typename T, typename U>
T into(const U& u)
{
    std::error_code error;
    auto result = into<T>(u, error);
    if (error)
        throw dynamic::error(error);
    return result;
}

} // namespace convert
} // namespace dynamic
} // namespace trial

#endif // TRIAL_DYNAMIC_CONVERT_CONVERT_HPP
