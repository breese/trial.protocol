#ifndef TRIAL_DYNAMIC_CONVERT_STD_MAP_HPP
#define TRIAL_DYNAMIC_CONVERT_STD_MAP_HPP

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
#include <trial/dynamic/variable.hpp>
#include <trial/dynamic/convert.hpp>

namespace trial
{
namespace dynamic
{
namespace convert
{

template <template <typename> class Allocator, typename Key, typename Value>
struct overloader<
    basic_variable<Allocator>,
    std::map<Key, Value>>
{
    static basic_variable<Allocator> into(const std::map<Key, Value>& map,
                                          std::error_code&)
    {
        auto result = basic_map<Allocator>::make();
        for (const auto& entry : map)
        {
            result += map::make(entry.first, entry.second);
        }
        return result;
    }
};

template <template <typename> class Allocator, typename Key, typename Value>
struct overloader<
    std::map<Key, Value>,
    basic_variable<Allocator>>
{
    static std::map<Key, Value> into(const basic_variable<Allocator>& map,
                                     std::error_code& error)
    {
        std::map<Key, Value> result;
        for (auto it = map.begin(); it != map.end(); ++it)
        {
            if (it->template is<Value>())
                result.emplace(it.key().template value<Key>(error),
                               it->template assume_value<Value>());
            else
                error = dynamic::make_error_code(incompatible_type);

            if (error)
                return {};
        }
        return result;
    }
};

// Special case for std::map<T, variable>

template <template <typename> class Allocator, typename Key>
struct overloader<
    std::map<Key, basic_variable<Allocator>>,
    basic_variable<Allocator>>
{
    static std::map<Key, basic_variable<Allocator>> into(const basic_variable<Allocator>& map,
                                                         std::error_code& error)
    {
        std::map<Key, basic_variable<Allocator>> result;
        for (auto it = map.begin(); it != map.end(); ++it)
        {
            result.emplace(it.key().template value<Key>(error), it.value());

            if (error)
                return {};
        }
        return result;
    }
};

} // namespace convert
} // namespace dynamic
} // namespace trial

#endif // TRIAL_DYNAMIC_CONVERT_STD_MAP_HPP
