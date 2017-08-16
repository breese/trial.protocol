#ifndef TRIAL_PROTOCOL_DYNAMIC_STD_VECTOR_HPP
#define TRIAL_PROTOCOL_DYNAMIC_STD_VECTOR_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2017 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <vector>

namespace trial
{
namespace protocol
{
namespace dynamic
{
namespace detail
{

template <typename CharT, typename T>
struct convert_overloader<
    basic_variable<CharT>,
    std::vector<T>>
{
    static basic_variable<CharT> convert(const std::vector<T>& array,
                                         std::error_code&)
    {
        auto result = basic_array<CharT>::make();
        for (const auto& entry : array)
        {
            result += entry;
        }
        return result;
    }
};

} // namespace detail
} // namespace dynamic
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_DYNAMIC_STD_VECTOR_HPP
