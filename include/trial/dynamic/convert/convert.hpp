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

template <typename T, typename U, typename = void>
struct overloader
{
    detail::static_assert_t<T, U> unsupported_type;
};

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
