#ifndef TRIAL_DYNAMIC_DETAIL_SMALL_UNION_IPP
#define TRIAL_DYNAMIC_DETAIL_SMALL_UNION_IPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2017 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <memory>

namespace trial
{
namespace dynamic
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

    template <typename Allocator, typename... Args>
    static void construct(Allocator&, void *storage, Args... args)
    {
        // Place object in storage
        ::new (storage) type(std::forward<Args...>(args...));
    }

    template <typename Allocator>
    static void destroy(Allocator&, void *storage)
    {
        deref(static_cast<type *>(storage)).~T();
    }

    static void copy(void *target, const void *source)
    {
        deref(static_cast<type *>(target)) = deref(static_cast<const type *>(source));
    }

    static void move(void *target, const void *source)
    {
        deref(static_cast<type *>(target)) = std::move(deref(static_cast<const type *>(source)));
    }

    static type& deref(void *storage) noexcept { return *static_cast<type *>(storage); }
    static const type& deref(const void *storage) noexcept { return *static_cast<const type *>(storage); }
};

template <std::size_t M, typename T>
struct small_traits<M, T, typename std::enable_if<(sizeof(T) > M)>::type>
{
    using type = typename std::remove_reference<T>::type;
    using pointer = typename std::add_pointer<type>::type;
    using small_type = pointer;

    static_assert(M >= sizeof(pointer), "N must be larger than a pointer");

    template <typename Allocator, typename... Args>
    static void construct(Allocator& alloc, void *storage, Args... args)
    {
        using traits_type = typename std::allocator_traits<Allocator>::template rebind_traits<type>;
        typename traits_type::allocator_type allocator(alloc);
        auto ptr = traits_type::allocate(allocator, 1);
        traits_type::construct(allocator, ptr, std::forward<Args...>(args...));
        // Place pointer in storage
        ::new (storage) pointer{ptr};
    }

    template <typename Allocator>
    static void destroy(Allocator& alloc, void *storage)
    {
        using traits_type = typename std::allocator_traits<Allocator>::template rebind_traits<type>;
        typename traits_type::allocator_type allocator(alloc);
        auto ptr = &deref(storage);
        traits_type::destroy(allocator, ptr);
        traits_type::deallocate(allocator, ptr, sizeof(pointer));
    }

    static void copy(void *target, const void *source)
    {
        deref(static_cast<type *>(target)) = deref(static_cast<const type *>(source));
    }

    static void move(void *target, const void *source)
    {
        deref(static_cast<type *>(target)) = std::move(deref(static_cast<const type *>(source)));
    }

    static type& deref(void *storage) noexcept { return **static_cast<pointer *>(storage); }
    static const type& deref(const void *storage) noexcept { return **static_cast<const pointer *>(storage); }
};

//-----------------------------------------------------------------------------
// small_union
//-----------------------------------------------------------------------------

template <template <typename> class Allocator, typename IndexType, IndexType N, typename... Types>
template <typename T>
struct small_union<Allocator, IndexType, N, Types...>::make_small
{
    using type = typename small_traits<N, typename std::decay<T>::type>::small_type;
};

template <template <typename> class Allocator, typename IndexType, IndexType N, typename... Types>
template <typename T>
struct small_union<Allocator, IndexType, N, Types...>::to_index
{
private:
    using small_type = typename make_small<T>::type;
    static_assert(meta::contains<typelist, small_type>::value, "T is not valid");

public:
    using type = typename meta::to_index<typelist, small_type>::type;
    static const std::size_t value = type::value;
};

template <template <typename> class Allocator, typename IndexType, IndexType N, typename... Types>
template <typename T>
small_union<Allocator, IndexType, N, Types...>::small_union(T value)
    : current(to_index<T>::value)
{
    using type = typename std::decay<T>::type;

    assert(current < sizeof...(Types));
    small_traits<N, type>::construct(*this, std::addressof(storage), std::move(value));
}

template <template <typename> class Allocator, typename IndexType, IndexType N, typename... Types>
small_union<Allocator, IndexType, N, Types...>::small_union(const small_union& other)
    : Allocator<void>(other),
      current(other.current)
{
    call<copier, void>(other);
}

template <template <typename> class Allocator, typename IndexType, IndexType N, typename... Types>
small_union<Allocator, IndexType, N, Types...>::small_union(small_union&& other)
    : Allocator<void>(other),
      current(other.current)
{
    call<mover, void>(std::move(other));
}

template <template <typename> class Allocator, typename IndexType, IndexType N, typename... Types>
auto small_union<Allocator, IndexType, N, Types...>::operator= (const small_union& other) -> small_union&
{
    assert(other.current < sizeof...(Types));
    call<copier, void>(other);
    current = other.current;
    return *this;
}

template <template <typename> class Allocator, typename IndexType, IndexType N, typename... Types>
auto small_union<Allocator, IndexType, N, Types...>::operator= (small_union&& other) -> small_union&
{
    assert(other.current < sizeof...(Types));
    call<mover, void>(std::move(other));
    current = other.current;
    return *this;
}

template <template <typename> class Allocator, typename IndexType, IndexType N, typename... Types>
small_union<Allocator, IndexType, N, Types...>::~small_union()
{
    call<destructor, void>();
}

template <template <typename> class Allocator, typename IndexType, IndexType N, typename... Types>
template <typename T>
T& small_union<Allocator, IndexType, N, Types...>::get() noexcept
{
    using type = typename std::decay<T>::type;
    return small_traits<N, type>::deref(std::addressof(storage));
}

template <template <typename> class Allocator, typename IndexType, IndexType N, typename... Types>
template <typename T>
const T& small_union<Allocator, IndexType, N, Types...>::get() const noexcept
{
    using type = typename std::decay<T>::type;
    return small_traits<N, type>::deref(std::addressof(storage));
}

template <template <typename> class Allocator, typename IndexType, IndexType N, typename... Types>
void small_union<Allocator, IndexType, N, Types...>::swap(small_union& other) noexcept
{
    using std::swap;
    swap(storage, other.storage);
    swap(current, other.current);
}

template <template <typename> class Allocator, typename IndexType, IndexType N, typename... Types>
template <typename T>
void small_union<Allocator, IndexType, N, Types...>::operator= (const T& value)
{
    using type = typename std::decay<T>::type;

    call<destructor, void>();
    small_traits<N, type>::construct(*this, std::addressof(storage), value);
    current = to_index<type>::value;
}

template <template <typename> class Allocator, typename IndexType, IndexType N, typename... Types>
template <typename T>
void small_union<Allocator, IndexType, N, Types...>::operator= (T&& value)
{
    using type = typename std::decay<T>::type;

    call<destructor, void>();
    small_traits<N, type>::construct(*this, std::addressof(storage), std::move(value));
    current = to_index<type>::value;
}

template <template <typename> class Allocator, typename IndexType, IndexType N, typename... Types>
template <typename Visitor, typename R>
R small_union<Allocator, IndexType, N, Types...>::call()
{
    assert(current < sizeof...(Types));

    using signature = decltype(&Visitor::template call<int>);
    static constexpr signature table[] = { &Visitor::template call<Types>... };
    return table[current](*this);
}

template <template <typename> class Allocator, typename IndexType, IndexType N, typename... Types>
template <typename Visitor, typename R>
R small_union<Allocator, IndexType, N, Types...>::call() const
{
    assert(current < sizeof...(Types));

    using signature = decltype(&Visitor::template call<int>);
    static constexpr signature table[] = { &Visitor::template call<Types>... };
    return table[current](*this);
}

template <template <typename> class Allocator, typename IndexType, IndexType N, typename... Types>
template <typename Visitor, typename R, typename... Args>
R small_union<Allocator, IndexType, N, Types...>::call(Args&&... args)
{
    assert(current < sizeof...(Types));

    using signature = decltype(&Visitor::template call<int>);
    static constexpr signature table[] = { &Visitor::template call<Types>... };
    return table[current](*this, std::forward<Args...>(args...));
}

template <template <typename> class Allocator, typename IndexType, IndexType N, typename... Types>
template <typename Visitor, typename R, typename... Args>
R small_union<Allocator, IndexType, N, Types...>::call(Args&&... args) const
{
    assert(current < sizeof...(Types));

    using signature = decltype(&Visitor::template call<int>);
    static constexpr signature table[] = { &Visitor::template call<Types>... };
    return table[current](*this, std::forward<Args...>(args...));
}

template <template <typename> class Allocator, typename IndexType, IndexType N, typename... Types>
struct small_union<Allocator, IndexType, N, Types...>::destructor
{
    template <typename T>
    static void call(small_union& self)
    {
        small_traits<N, T>::destroy(self, std::addressof(self.storage));
    }
};

template <template <typename> class Allocator, typename IndexType, IndexType N, typename... Types>
struct small_union<Allocator, IndexType, N, Types...>::copier
{
    template <typename T>
    static void call(small_union& self, const small_union& other)
    {
        small_traits<N, T>::copy(std::addressof(self.storage),
                                 std::addressof(other.storage));
    }
};

template <template <typename> class Allocator, typename IndexType, IndexType N, typename... Types>
struct small_union<Allocator, IndexType, N, Types...>::mover
{
    template <typename T>
    static void call(small_union& self, small_union&& other)
    {
        small_traits<N, T>::move(std::addressof(self.storage),
                                 std::addressof(other.storage));
    }
};

} // namespace detail
} // namespace dynamic
} // namespace trial

#endif // TRIAL_DYNAMIC_DETAIL_SMALL_UNION_IPP
