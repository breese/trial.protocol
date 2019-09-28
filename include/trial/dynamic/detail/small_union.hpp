#ifndef TRIAL_DYNAMIC_DETAIL_SMALL_UNION_HPP
#define TRIAL_DYNAMIC_DETAIL_SMALL_UNION_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2017 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

// Partly inspired by Agustín Bergé's "Eggs.Variant" articles.

#include <cassert>
#include <type_traits>
#include <trial/dynamic/detail/meta.hpp>

namespace trial
{
namespace dynamic
{
namespace detail
{

//-----------------------------------------------------------------------------
// small_union
//-----------------------------------------------------------------------------

template <typename Allocator, typename MaxType, typename IndexType, typename... Types>
class small_union : public Allocator
{
    template <typename T> struct make_small;
    using typelist = meta::transform<meta::list<Types...>, make_small>;

public:
    using allocator_type = Allocator;
    using index_type = IndexType;

    template <typename T> struct to_index;

    template <typename T> explicit small_union(T value, const allocator_type& = allocator_type{});
    small_union(const small_union&);
    small_union(small_union&&);
    template <typename T> void operator= (T value);
    small_union& operator= (const small_union&);
    small_union& operator= (small_union&&);
    ~small_union();

    index_type index() const noexcept { return current; }
    const allocator_type& get_allocator() const noexcept { return *this; }
    allocator_type& get_allocator() noexcept { return *this; }

    template <typename T> T& get() noexcept;
    template <typename T> const T& get() const noexcept;

    template <typename Visitor, typename R> R call();
    template <typename Visitor, typename R> R call() const;
    template <typename Visitor, typename R, typename... Args> R call(Args&&...);
    template <typename Visitor, typename R, typename... Args> R call(Args&&...) const;

private:
    template <std::size_t M, typename T, typename Enable> friend struct small_traits;

    struct reconstructor;
    struct destructor;
    struct copier;
    struct mover;

    typename std::aligned_storage<sizeof(MaxType), alignof(MaxType)>::type storage;
    index_type current;
};

} // namespace detail
} // namespace dynamic
} // namespace trial

#include <trial/dynamic/detail/small_union.ipp>

#endif // TRIAL_DYNAMIC_DETAIL_SMALL_UNION_HPP
