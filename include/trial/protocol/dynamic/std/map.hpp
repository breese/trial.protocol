#ifndef TRIAL_PROTOCOL_DYNAMIC_STD_MAP_HPP
#define TRIAL_PROTOCOL_DYNAMIC_STD_MAP_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2017 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <map>
#include <trial/protocol/dynamic/variable.hpp>
#include <trial/protocol/dynamic/convert.hpp>

namespace trial
{
namespace protocol
{
namespace dynamic
{
namespace detail
{

template <typename CharT, typename Key, typename Value>
struct convert_overloader<
    basic_variable<CharT>,
    std::map<Key, Value>>
{
    static basic_variable<CharT> convert(const std::map<Key, Value>& map,
                                         std::error_code&)
    {
        auto result = basic_map<CharT>::make();
        for (const auto& entry : map)
        {
            result += map::make(entry.first, entry.second);
        }
        return result;
    }
};

} // namespace detail
} // namespace dynamic
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_DYNAMIC_STD_MAP_HPP
