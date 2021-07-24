#ifndef TRIAL_TRIBOOL_HPP
#define TRIAL_TRIBOOL_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2021 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

namespace trial
{
namespace detail
{

// http://breese.github.io/2015/07/05/layers-of-three-valued-logic.html

template <typename T>
struct tribool_traits;

struct tribool_kleene_tag;

template <>
struct tribool_traits<tribool_kleene_tag>
{
    enum value_type
    {
        indeterminate_value = -1,
        false_value = 0,
        true_value = 1,
        initial_value = indeterminate_value
    };

    static value_type convert(bool value) noexcept
    {
        return value ? true_value : false_value;
    }

    static bool convert(value_type value) noexcept
    {
        return value == true_value;
    }

    //  == | F | T | U
    // ----+---+---+---
    //   F | T | F | U
    //   T | F | T | U
    //   U | U | U | U

    static value_type equal_to(value_type lhs, value_type rhs) noexcept
    {
        if ((lhs == indeterminate_value) ||
            (rhs == indeterminate_value))
            return indeterminate_value;
        return (lhs == rhs) ? true_value : false_value;
    }

    static bool empty(value_type value) noexcept
    {
        return value == indeterminate_value;
    }

    //  ! |
    // ---+---
    //  F | T
    //  T | F
    //  U | U

    static value_type negation(value_type lhs) noexcept
    {
        if (lhs == indeterminate_value)
            return indeterminate_value;
        return lhs == true_value ? false_value : true_value;
    }

    //  && | F | T | U
    // ----+---+---+---
    //   F | F | F | F
    //   T | F | T | U
    //   U | F | U | U

    static value_type conjunction(value_type lhs, value_type rhs) noexcept
    {
        if (lhs == false_value)
            return false_value;
        if (lhs == true_value)
            return rhs;
        // assert(lhs == indeterminate_value)
        if (rhs == true_value)
            return indeterminate_value;
        return rhs;
    }

    //  || | F | T | U
    // ----+---+---+---
    //   F | F | T | U
    //   T | T | T | T
    //   U | U | T | U

    static value_type disjunction(value_type lhs, value_type rhs) noexcept
    {
        if (lhs == false_value)
            return rhs;
        if (lhs == true_value)
            return true_value;
        // assert(lhs == indeterminate_value)
        if (rhs == true_value)
            return true_value;
        return indeterminate_value;
    }
};

template <typename T>
class basic_tribool
{
    using traits_type = detail::tribool_traits<T>;

public:
    using value_type = typename traits_type::value_type;

    basic_tribool() noexcept
        : value(traits_type::initial_value)
    {
    }

    basic_tribool(const basic_tribool&) noexcept = default;
    basic_tribool& operator=(const basic_tribool&) noexcept = default;
    basic_tribool(basic_tribool&&) noexcept = default;
    basic_tribool& operator=(basic_tribool&&) noexcept = default;

    basic_tribool(bool value)
        : value(traits_type::convert(value))
    {
    }

    explicit operator bool() noexcept
    {
        return traits_type::convert(value);
    }

    bool empty() const noexcept
    {
        return traits_type::empty(value);
    }

    friend basic_tribool operator! (const basic_tribool& lhs)
    {
        return traits_type::negation(lhs.value);
    }

    friend basic_tribool operator&& (const basic_tribool& lhs, const basic_tribool& rhs) noexcept
    {
        return traits_type::conjunction(lhs.value, rhs.value);
    }

    friend basic_tribool operator&& (const basic_tribool& lhs, bool rhs) noexcept
    {
        return lhs && basic_tribool(rhs);
    }

    friend basic_tribool operator&& (bool lhs, const basic_tribool& rhs) noexcept
    {
        return basic_tribool(lhs) && rhs;
    }

    friend basic_tribool operator|| (const basic_tribool& lhs, const basic_tribool& rhs) noexcept
    {
        return traits_type::disjunction(lhs.value, rhs.value);
    }

    friend basic_tribool operator|| (const basic_tribool& lhs, bool rhs) noexcept
    {
        return lhs || basic_tribool(rhs);
    }

    friend basic_tribool operator|| (bool lhs, const basic_tribool& rhs) noexcept
    {
        return basic_tribool(lhs) || rhs;
    }

    friend basic_tribool operator==(const basic_tribool& lhs, const basic_tribool& rhs) noexcept
    {
        return traits_type::equal_to(lhs.value, rhs.value);
    }

    friend basic_tribool operator==(const basic_tribool& lhs, bool rhs) noexcept
    {
        return lhs == basic_tribool(rhs);
    }

    friend basic_tribool operator==(bool lhs, const basic_tribool& rhs) noexcept
    {
        return basic_tribool(lhs) == rhs;
    }

    friend basic_tribool operator!=(const basic_tribool& lhs, const basic_tribool& rhs) noexcept
    {
        return traits_type::negation(traits_type::equal_to(lhs.value, rhs.value));
    }

    friend basic_tribool operator!=(const basic_tribool& lhs, bool rhs) noexcept
    {
        return lhs != basic_tribool(rhs);
    }

    friend basic_tribool operator!=(bool lhs, const basic_tribool& rhs) noexcept
    {
        return basic_tribool(lhs) != rhs;
    }

private:
    basic_tribool(value_type value)
        : value(value)
    {
    }

    typename traits_type::value_type value;
};

} // namespace detail

using tribool = detail::basic_tribool<detail::tribool_kleene_tag>;

} // namespace trial

#endif // TRIAL_TRIBOOL_HPP
