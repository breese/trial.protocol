#ifndef TRIAL_PROTOCOL_DYNAMIC_CONVERT_HPP
#define TRIAL_PROTOCOL_DYNAMIC_CONVERT_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2017 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <trial/protocol/dynamic/error.hpp>

namespace trial
{
namespace protocol
{
namespace dynamic
{

namespace detail
{

template <typename T, typename U, typename Enable = void>
struct convert_overloader
{
    static_assert(sizeof(T) == 0, "Unsupported type");
};

} // namespace detail

template <typename T, typename U>
T convert(const U& u, std::error_code& error) noexcept
{
    // A compiler error here indicates that the appropriate header file of the
    // type to be converted has not been included.
    return detail::convert_overloader<T, U>::convert(u, error);
}

template <typename T, typename U>
T convert(const U& u)
{
    std::error_code error;
    auto result = convert<T>(u, error);
    if (error)
        throw dynamic::error(error);
    return result;
}

} // namespace dynamic
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_DYNAMIC_CONVERT_HPP
