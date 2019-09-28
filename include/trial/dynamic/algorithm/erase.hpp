#ifndef TRIAL_DYNAMIC_ALGORITHM_ERASE_HPP
#define TRIAL_DYNAMIC_ALGORITHM_ERASE_HPP

#include <trial/dynamic/algorithm/find.hpp>

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2018 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <trial/dynamic/variable.hpp>

namespace trial
{
namespace dynamic
{
namespace key
{

template <typename Allocator, typename T>
auto erase(basic_variable<Allocator>& self,
           const T& other) -> typename basic_variable<Allocator>::key_iterator
{
    switch (self.symbol())
    {
    case symbol::map:
        {
            auto where = key::find(self, other);
            auto result = where;
            ++result;
            self.erase(where.base());
            return result;
        }

    default:
        return self.key_end();
    }
}

} // namespace key
} // namespace dynamic
} // namespace trial

#endif // TRIAL_DYNAMIC_ALGORITHM_ERASE_HPP
