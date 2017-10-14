#ifndef TRIAL_DYNAMIC_FUNCTIONAL_HPP
#define TRIAL_DYNAMIC_FUNCTIONAL_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2017 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

namespace trial
{
namespace dynamic
{

//! @brief Function object to check if variable has a given tag.
//!
//! @sa basic_variable<Allocator>::is<T>()

template <typename T>
struct is
{
    bool operator()(const variable& value) const
    {
        return value.is<T>();
    }
};

//! @brief Function object to check if variable has exactly a given type.
//!
//! @sa basic_variable<Allocator>::same<T>()

template <typename T>
struct same
{
    bool operator()(const variable& value) const
    {
        return value.same<T>();
    }
};

} // namespace dynamic
} // namespace trial

#endif // TRIAL_DYNAMIC_FUNCTIONAL_HPP
