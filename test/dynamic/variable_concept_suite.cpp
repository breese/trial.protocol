///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2017 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <limits>
#include <trial/protocol/core/detail/lightweight_test.hpp>
#include <trial/dynamic/detail/meta.hpp>
#include <trial/dynamic/variable.hpp>

using namespace trial::dynamic;

#define TRIAL_DYNAMIC_HAS_TYPE(x,y)                                    \
    template <typename T, typename = void> struct x : std::false_type {}; \
    template <typename T> struct x <T, trial::dynamic::meta::void_t<typename T:: y >> : std::true_type {};

//-----------------------------------------------------------------------------
// Container concept
//-----------------------------------------------------------------------------

namespace container_suite
{

TRIAL_DYNAMIC_HAS_TYPE(has_value_type, value_type)
TRIAL_DYNAMIC_HAS_TYPE(has_reference, reference)
TRIAL_DYNAMIC_HAS_TYPE(has_const_reference, const_reference)
TRIAL_DYNAMIC_HAS_TYPE(has_iterator, iterator)
TRIAL_DYNAMIC_HAS_TYPE(has_const_iterator, const_iterator)
TRIAL_DYNAMIC_HAS_TYPE(has_difference_type, difference_type)
TRIAL_DYNAMIC_HAS_TYPE(has_size_type, size_type)

void container_types()
{
    static_assert(has_value_type<variable>::value, "variable::value_type missing");

    static_assert(has_reference<variable>::value, "variable::reference missing");
    static_assert(has_const_reference<variable>::value, "variable::const_reference missing");

    static_assert(has_iterator<variable>::value, "variable::iterator missing");
    static_assert(has_const_iterator<variable>::value, "variable::const_iterator missing");

    static_assert(has_difference_type<variable>::value, "variable::difference_type missing");
    static_assert(std::is_signed<variable::difference_type>::value, "variable::difference_type must be signed");
    static_assert(std::is_same<variable::difference_type, variable::iterator::difference_type>::value, "Container and iterator must have same difference_type");
    static_assert(std::is_same<variable::difference_type, variable::const_iterator::difference_type>::value, "Container and const_iterator must have same difference_type");

    static_assert(has_size_type<variable>::value, "variable::size_type missing");
    static_assert(std::is_unsigned<variable::size_type>::value, "variable::size_type must be unsigned");
    static_assert(std::numeric_limits<variable::size_type>::max() >= std::numeric_limits<variable::difference_type>::max(), "size_type can represent any non-negative value of difference_type");
}

void container_constructible()
{
    static_assert(std::is_default_constructible<variable>::value, "is_default_constructible");
    static_assert(std::is_copy_constructible<variable>::value, "is_copy_constructible");
    static_assert(std::is_move_constructible<variable>::value, "is_move_constructible");
}

void container_destructible()
{
    static_assert(std::is_destructible<variable>::value, "is_destructible");
}

void container_assignable()
{
    static_assert(std::is_copy_assignable<variable>::value, "is_copy_assignable");
    static_assert(std::is_move_assignable<variable>::value, "is_move_assignable");
}

void run()
{
    // [container.requirements.general]
    container_types();
    container_constructible();
    container_destructible();
    container_assignable();
    // Required member functions are checked elsewhere
    //   variable::begin()
    //   variable::end()
    //   variable::cbegin()
    //   variable::cend()
    //   variable::swap()
    //   Equality operators
    //   Capacity
}

} // namespace container_suite

//-----------------------------------------------------------------------------
// main
//-----------------------------------------------------------------------------

int main()
{
    container_suite::run();

    return boost::report_errors();
}
