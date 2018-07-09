#ifndef TRIAL_DYNAMIC_CONVERT_STD_SET_HPP
#define TRIAL_DYNAMIC_CONVERT_STD_SET_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2018 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <set>
#include <trial/dynamic/variable.hpp>
#include <trial/dynamic/convert/convert.hpp>

namespace trial
{
namespace dynamic
{
namespace convert
{

template <template <typename> class Allocator, typename T>
struct overloader<
    basic_variable<Allocator>,
    std::set<T>>
{
    static basic_variable<Allocator> into(const std::set<T>& container,
                                          std::error_code&)
    {
        auto result = basic_array<Allocator>::make();
        for (const auto& entry : container)
        {
            result += entry;
        }
        return result;
    }
};

template <template <typename> class Allocator, typename T>
struct overloader<
    std::set<T>,
    basic_variable<Allocator>>
{
    static std::set<T> into(const basic_variable<Allocator>& container,
                            std::error_code& error)
    {
        std::set<T> result;
        for (const auto& entry : container)
        {
            if (entry.template is<T>())
                result.insert(entry.template assume_value<T>());
            else
                error = dynamic::make_error_code(incompatible_type);

            if (error)
                return {};
        }
        return result;
    }
};

// Special case for std::vector<variable>

template <template <typename> class Allocator>
struct overloader<
    std::set<basic_variable<Allocator>>,
    basic_variable<Allocator>>
{
    static std::set<basic_variable<Allocator>> into(const basic_variable<Allocator>& container,
                                                    std::error_code&)
    {
        std::set<basic_variable<Allocator>> result;
        for (const auto& item : container)
        {
            result.insert(item);
        }
        return result;
    }
};

} // namespace convert
} // namespace dynamic
} // namespace trial

#endif // TRIAL_DYNAMIC_CONVERT_STD_SET_HPP
