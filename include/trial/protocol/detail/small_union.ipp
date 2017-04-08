#ifndef TRIAL_PROTOCOL_DETAIL_SMALL_UNION_IPP
#define TRIAL_PROTOCOL_DETAIL_SMALL_UNION_IPP

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
namespace protocol
{
namespace detail
{

//-----------------------------------------------------------------------------
// small_traits
//-----------------------------------------------------------------------------

template <std::size_t M, typename T, typename Enable = void>
struct small_traits
{
    using type = typename std::remove_reference<T>::type;
    using small_type = type;

    template <typename... Args>
    static void construct(void *ptr, Args... args)
    {
        ::new (ptr) type(std::forward<Args...>(args...));
    }

    static void destroy(void *ptr)
    {
        deref(static_cast<type *>(ptr)).~T();
    }

    static void copy(void *target, const void *source)
    {
        deref(static_cast<type *>(target)) = deref(static_cast<const type *>(source));
    }

    static void move(void *target, const void *source)
    {
        deref(static_cast<type *>(target)) = std::move(deref(static_cast<const type *>(source)));
    }

    static type& deref(void *ptr) { return *static_cast<type *>(ptr); }
    static const type& deref(const void *ptr) { return *static_cast<const type *>(ptr); }
};

template <std::size_t M, typename T>
struct small_traits<M, T, typename std::enable_if<(sizeof(T) > M)>::type>
{
    using type = typename std::remove_reference<T>::type;
    using pointer = typename std::add_pointer<type>::type;
    using small_type = pointer;

    template <typename... Args>
    static void construct(void *ptr, Args... args)
    {
        ::new (ptr) pointer{new type(std::forward<Args...>(args...))};
    }

    static void destroy(void *ptr)
    {
        delete *static_cast<pointer *>(ptr);
    }

    static void copy(void *target, const void *source)
    {
        deref(static_cast<type *>(target)) = deref(static_cast<const type *>(source));
    }

    static void move(void *target, const void *source)
    {
        deref(static_cast<type *>(target)) = std::move(deref(static_cast<const type *>(source)));
    }

    static type& deref(void *ptr) { return **static_cast<pointer *>(ptr); }
    static const type& deref(const void *ptr) { return **static_cast<const pointer *>(ptr); }
};

//-----------------------------------------------------------------------------
// small_union
//-----------------------------------------------------------------------------

template <std::size_t N, typename... Types>
template <typename T>
struct small_union<N, Types...>::make_small
{
    using type = typename small_traits<N, typename std::decay<T>::type>::small_type;
};

template <std::size_t N, typename... Types>
template <typename T>
struct small_union<N, Types...>::index
{
private:
    using small_type = typename make_small<T>::type;
    static_assert(meta::contains<typelist, small_type>::value, "T is not valid");

public:
    using type = typename meta::to_index<typelist, small_type>::type;
    static const std::size_t value = type::value;
};

template <std::size_t N, typename... Types>
template <typename T>
small_union<N, Types...>::small_union(T value)
    : current(index<T>::value)
{
    using type = typename std::decay<T>::type;

    assert(current < sizeof...(Types));
    small_traits<N, type>::construct(std::addressof(storage), std::move(value));
}

template <std::size_t N, typename... Types>
small_union<N, Types...>::small_union(const small_union& other)
    : current(other.current)
{
    call<copier>(other);
}

template <std::size_t N, typename... Types>
small_union<N, Types...>::small_union(small_union&& other)
    : current(other.current)
{
    call<mover>(std::move(other));
}

template <std::size_t N, typename... Types>
auto small_union<N, Types...>::operator= (const small_union& other) -> small_union&
{
    assert(other.current < sizeof...(Types));
    call<copier>(other);
    current = other.current;
    return *this;
}

template <std::size_t N, typename... Types>
auto small_union<N, Types...>::operator= (small_union&& other) -> small_union&
{
    assert(other.current < sizeof...(Types));
    call<mover>(std::move(other));
    current = other.current;
    return *this;
}

template <std::size_t N, typename... Types>
small_union<N, Types...>::~small_union()
{
    call<destructor>();
}

template <std::size_t N, typename... Types>
template <typename T>
T& small_union<N, Types...>::get()
{
    using type = typename std::decay<T>::type;
    return small_traits<N, type>::deref(std::addressof(storage));
}

template <std::size_t N, typename... Types>
template <typename T>
const T& small_union<N, Types...>::get() const
{
    using type = typename std::decay<T>::type;
    return small_traits<N, type>::deref(std::addressof(storage));
}

template <std::size_t N, typename... Types>
template <typename T>
void small_union<N, Types...>::operator= (const T& value)
{
    using type = typename std::decay<T>::type;

    call<destructor>();
    small_traits<N, type>::construct(std::addressof(storage), value);
    current = index<type>::value;
}

template <std::size_t N, typename... Types>
template <typename T>
void small_union<N, Types...>::operator= (T&& value)
{
    using type = typename std::decay<T>::type;

    call<destructor>();
    small_traits<N, type>::construct(std::addressof(storage), std::move(value));
    current = index<type>::value;
}

template <std::size_t N, typename... Types>
template <typename Visitor>
void small_union<N, Types...>::call()
{
    assert(current < sizeof...(Types));

    using signature = decltype(&Visitor::template call<int>);
    static constexpr signature table[] = { &Visitor::template call<Types>... };
    table[current](*this);
}

template <std::size_t N, typename... Types>
template <typename Visitor, typename... Args>
void small_union<N, Types...>::call(Args&&... args)
{
    assert(current < sizeof...(Types));

    using signature = decltype(&Visitor::template call<int>);
    static constexpr signature table[] = { &Visitor::template call<Types>... };
    table[current](*this, std::forward<Args...>(args...));
}

template <std::size_t N, typename... Types>
struct small_union<N, Types...>::destructor
{
    template <typename T>
    static void call(small_union& self)
    {
        small_traits<N, T>::destroy(std::addressof(self.storage));
    }
};

template <std::size_t N, typename... Types>
struct small_union<N, Types...>::copier
{
    template <typename T>
    static void call(small_union& self, const small_union& other)
    {
        small_traits<N, T>::copy(std::addressof(self.storage),
                                 std::addressof(other.storage));
    }
};

template <std::size_t N, typename... Types>
struct small_union<N, Types...>::mover
{
    template <typename T>
    static void call(small_union& self, small_union&& other)
    {
        small_traits<N, T>::move(std::addressof(self.storage),
                                 std::addressof(other.storage));
    }
};

} // namespace detail
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_DETAIL_SMALL_UNION_IPP
