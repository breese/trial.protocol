#ifndef TRIAL_PROTOCOL_DETAIL_SMALL_UNION_HPP
#define TRIAL_PROTOCOL_DETAIL_SMALL_UNION_HPP

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
#include <trial/protocol/detail/meta.hpp>

namespace trial
{
namespace protocol
{
namespace detail
{

//-----------------------------------------------------------------------------
// small_union
//-----------------------------------------------------------------------------

template <std::size_t N, typename... Types>
class small_union
{
    template <typename T> struct make_small;
    using typelist = meta::transform<meta::list<Types...>, make_small>;

public:
    template <typename T> struct index;

    template <typename T> explicit small_union(T value);
    small_union(const small_union&);
    small_union(small_union&&);
    small_union& operator= (const small_union&);
    small_union& operator= (small_union&&);
    ~small_union();

    std::size_t which() const { return current; }

    template <typename T> T& get();
    template <typename T> const T& get() const;

    template <typename T> void operator= (const T& value);
    template <typename T> void operator= (T&& value);

    template <typename Visitor> void call();
    template <typename Visitor, typename... Args> void call(Args&&...);

private:
    template <std::size_t M, typename T, typename Enable> friend struct small_traits;

    struct destructor;
    struct copier;
    struct mover;

    typename std::aligned_union<0, typelist>::type storage;
    std::size_t current;
};

} // namespace detail
} // namespace protocol
} // namespace trial

#include <trial/protocol/detail/small_union.ipp>

#endif // TRIAL_PROTOCOL_DETAIL_SMALL_UNION_HPP
