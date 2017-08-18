#ifndef TRIAL_PROTOCOL_CORE_DETAIL_META_HPP
#define TRIAL_PROTOCOL_CORE_DETAIL_META_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2017 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

// Mostly taken from Peter Dimov's "Simple C++11 metaprogramming" articles.

#include <type_traits>

namespace trial
{
namespace protocol
{
namespace core
{
namespace detail
{
namespace meta
{

template <typename... Types>
struct list {};

//-----------------------------------------------------------------------------
// identity
//-----------------------------------------------------------------------------

template <typename T>
using identity_t = T;

//-----------------------------------------------------------------------------
// void
//-----------------------------------------------------------------------------

template <typename...>
using void_t = void;

//-----------------------------------------------------------------------------
// contains
//-----------------------------------------------------------------------------

namespace impl
{

template <typename List, typename T>
struct contains;

template <template <typename...> class List, typename... Tail, typename T>
struct contains<List<T, Tail...>, T>
{
    using type = std::true_type;
    static const bool value = true;
};

template <template <typename...> class List, typename Head, typename... Tail, typename T>
struct contains<List<Head, Tail...>, T>
    : contains<List<Tail...>, T>
{
};

} // namespace impl

template <typename List, typename T>
using contains = typename impl::contains<List, T>::type;

//-----------------------------------------------------------------------------
// transform
//-----------------------------------------------------------------------------

namespace impl
{

template <template <typename...> class Transformer, typename List>
struct transform;

template <template <typename...> class Transformer, template <typename...> class List, typename... Types>
struct transform<Transformer, List<Types...>>
{
    using type = List<typename Transformer<Types>::type...>;
};

} // namespace impl

template <typename List, template <typename...> class Transformer>
using transform = typename impl::transform<Transformer, List>::type;

//-----------------------------------------------------------------------------
// to_index
//-----------------------------------------------------------------------------

namespace impl
{

template <typename List, typename T>
struct to_index;

template <template <typename...> class List, typename T>
struct to_index<List<>, T>
{
    using type = std::integral_constant<std::size_t, 0>;
};

template <template <typename...> class List, typename... Tail, typename T>
struct to_index<List<T, Tail...>, T>
{
    using type = std::integral_constant<std::size_t, 0>;
};

template <template <typename...> class List, typename Head, typename... Tail, typename T>
struct to_index<List<Head, Tail...>, T>
{
private:
    using previous_type = typename to_index<List<Tail...>, T>::type;
public:
    using type = std::integral_constant<std::size_t, 1 + previous_type::value>;
};

} // namespace impl

template <typename List, typename T>
using to_index = typename impl::to_index<List, T>::type;

//-----------------------------------------------------------------------------
// to_type
//-----------------------------------------------------------------------------

namespace impl
{

template <typename List, std::size_t Index>
struct to_type;

template <template <typename...> class List, typename Head, typename... Tail>
struct to_type<List<Head, Tail...>, 0>
{
    using type = Head;
};

template <template <typename...> class List, typename Head, typename... Tail, std::size_t Index>
struct to_type<List<Head, Tail...>, Index>
{
    using type = typename to_type<List<Tail...>, Index - 1>::type;
};

} // namespace impl

template <typename List, std::size_t N>
using to_type = typename impl::to_type<List, N>::type;

} // namespace meta
} // namespace detail
} // namespace core
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_CORE_DETAIL_META_HPP
