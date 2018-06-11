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

#include <new>
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
    static void construct(Allocator& alloc, void *storage, Args... args)
    {
        using allocator_type = typename std::allocator_traits<Allocator>::template rebind_alloc<type>;
        using allocator_traits = typename std::allocator_traits<allocator_type>;

        allocator_type typed_allocator(alloc);

        // Place object in storage
        allocator_traits::construct(typed_allocator,
                                    &deref(storage),
                                    std::forward<Args...>(args...));
    }

    template <typename Allocator>
    static void destroy(Allocator& alloc, void *storage)
    {
        using allocator_type = typename std::allocator_traits<Allocator>::template rebind_alloc<type>;
        using allocator_traits = typename std::allocator_traits<allocator_type>;

        allocator_type typed_allocator(alloc);

        allocator_traits::destroy(typed_allocator, &deref(storage));
    }

    static void copy(void *target, const void *source)
    {
        deref(target) = deref(source);
    }

    static void move(void *target, const void *source)
    {
        deref(target) = std::move(deref(source));
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
        using allocator_type = typename std::allocator_traits<Allocator>::template rebind_alloc<type>;
        using allocator_traits = typename std::allocator_traits<allocator_type>;

        allocator_type typed_allocator(alloc);

        // Place object on heap
        auto ptr = allocator_traits::allocate(typed_allocator, 1);
        if (!ptr) throw std::bad_alloc{};
        allocator_traits::construct(typed_allocator,
                                    std::addressof(*ptr),
                                    std::forward<Args...>(args...));
        // Place pointer in storage
        ::new (storage) typename allocator_traits::pointer{ptr};
    }

    template <typename Allocator>
    static void destroy(Allocator& alloc, void *storage)
    {
        using allocator_type = typename std::allocator_traits<Allocator>::template rebind_alloc<type>;
        using allocator_traits = typename std::allocator_traits<allocator_type>;

        allocator_type typed_allocator(alloc);

        auto ptr = *static_cast<typename allocator_traits::pointer *>(storage);
        allocator_traits::destroy(typed_allocator, ptr);
        allocator_traits::deallocate(typed_allocator, ptr, 1);
    }

    static void copy(void *target, const void *source)
    {
        deref(target) = deref(source);
    }

    static void move(void *target, const void *source)
    {
        deref(target) = std::move(deref(source));
    }

    static type& deref(void *storage) noexcept { return **static_cast<pointer *>(storage); }
    static const type& deref(const void *storage) noexcept { return **static_cast<const pointer *>(storage); }
};

//-----------------------------------------------------------------------------
// small_union
//-----------------------------------------------------------------------------

template <typename Allocator, typename MaxType, typename IndexType, typename... Types>
template <typename T>
struct small_union<Allocator, MaxType, IndexType, Types...>::make_small
{
    using type = typename small_traits<sizeof(MaxType), typename std::decay<T>::type>::small_type;
};

template <typename Allocator, typename MaxType, typename IndexType, typename... Types>
template <typename T>
struct small_union<Allocator, MaxType, IndexType, Types...>::to_index
{
private:
    using small_type = typename make_small<T>::type;
    static_assert(meta::contains<typelist, small_type>::value, "T is not valid");

public:
    using type = typename meta::to_index<typelist, small_type>::type;
    static const std::size_t value = type::value;
};

template <typename Allocator, typename MaxType, typename IndexType, typename... Types>
template <typename T>
small_union<Allocator, MaxType, IndexType, Types...>::small_union(T value, const allocator_type& alloc)
    : Allocator(alloc),
      current(to_index<T>::value)
{
    using type = typename std::decay<T>::type;

    assert(current < sizeof...(Types));
    small_traits<sizeof(MaxType), type>::construct(static_cast<allocator_type&>(*this),
                                                   std::addressof(storage),
                                                   std::move(value));
}

template <typename Allocator, typename MaxType, typename IndexType, typename... Types>
small_union<Allocator, MaxType, IndexType, Types...>::small_union(const small_union& other)
    : Allocator(std::allocator_traits<Allocator>::select_on_container_copy_construction(other)),
      current(other.current)
{
    call<copier, void>(other);
}

template <typename Allocator, typename MaxType, typename IndexType, typename... Types>
small_union<Allocator, MaxType, IndexType, Types...>::small_union(small_union&& other)
    : Allocator(other),
      current(other.current)
{
    call<mover, void>(std::move(other));
}

template <typename Allocator, typename MaxType, typename IndexType, typename... Types>
template <typename T>
void small_union<Allocator, MaxType, IndexType, Types...>::operator= (T value)
{
    using type = typename std::decay<T>::type;

    call<destructor, void>();
    small_traits<sizeof(MaxType), type>::construct(static_cast<allocator_type&>(*this),
                                                   std::addressof(storage),
                                                   std::move(value));
    current = to_index<type>::value;
}

template <typename Allocator, typename MaxType, typename IndexType, typename... Types>
auto small_union<Allocator, MaxType, IndexType, Types...>::operator= (const small_union& other) -> small_union&
{
    if (this == &other)
        return *this;

    assert(other.current < sizeof...(Types));

    if (std::allocator_traits<Allocator>::propagate_on_container_copy_assignment::value)
    {
        // Destroy with old allocator
        call<destructor, void>();
        // Create with new allocator
        static_cast<allocator_type&>(*this) = other.get_allocator();
        call<reconstructor, void>(other);
    }
    else
    {
        call<copier, void>(other);
    }
    current = other.current;
    return *this;
}

template <typename Allocator, typename MaxType, typename IndexType, typename... Types>
auto small_union<Allocator, MaxType, IndexType, Types...>::operator= (small_union&& other) -> small_union&
{
    if (this == &other)
        return *this;

    assert(other.current < sizeof...(Types));

    if (std::allocator_traits<Allocator>::propagate_on_container_move_assignment::value)
    {
        static_cast<allocator_type&>(*this) = std::move(static_cast<allocator_type&>(other));
        call<mover, void>(std::move(other));
    }
    else if (static_cast<allocator_type&>(*this) == static_cast<allocator_type&>(other))
    {
        call<mover, void>(std::move(other));
    }
    else
    {
        call<destructor, void>();
        static_cast<allocator_type&>(*this) = std::move(static_cast<allocator_type&>(other));
        call<reconstructor, void>(std::move(other));
    }
    current = other.current;
    return *this;
}

template <typename Allocator, typename MaxType, typename IndexType, typename... Types>
small_union<Allocator, MaxType, IndexType, Types...>::~small_union()
{
    call<destructor, void>();
}

template <typename Allocator, typename MaxType, typename IndexType, typename... Types>
template <typename T>
T& small_union<Allocator, MaxType, IndexType, Types...>::get() noexcept
{
    using type = typename std::decay<T>::type;
    return small_traits<sizeof(MaxType), type>::deref(std::addressof(storage));
}

template <typename Allocator, typename MaxType, typename IndexType, typename... Types>
template <typename T>
const T& small_union<Allocator, MaxType, IndexType, Types...>::get() const noexcept
{
    using type = typename std::decay<T>::type;
    return small_traits<sizeof(MaxType), type>::deref(std::addressof(storage));
}

template <typename Allocator, typename MaxType, typename IndexType, typename... Types>
template <typename Visitor, typename R>
R small_union<Allocator, MaxType, IndexType, Types...>::call()
{
    assert(current < sizeof...(Types));

    using signature = decltype(&Visitor::template call<int>);
    static constexpr signature table[] = { &Visitor::template call<Types>... };
    return table[current](*this);
}

template <typename Allocator, typename MaxType, typename IndexType, typename... Types>
template <typename Visitor, typename R>
R small_union<Allocator, MaxType, IndexType, Types...>::call() const
{
    assert(current < sizeof...(Types));

    using signature = decltype(&Visitor::template call<int>);
    static constexpr signature table[] = { &Visitor::template call<Types>... };
    return table[current](*this);
}

template <typename Allocator, typename MaxType, typename IndexType, typename... Types>
template <typename Visitor, typename R, typename... Args>
R small_union<Allocator, MaxType, IndexType, Types...>::call(Args&&... args)
{
    assert(current < sizeof...(Types));

    using signature = decltype(&Visitor::template call<int>);
    static constexpr signature table[] = { &Visitor::template call<Types>... };
    return table[current](*this, std::forward<Args...>(args...));
}

template <typename Allocator, typename MaxType, typename IndexType, typename... Types>
template <typename Visitor, typename R, typename... Args>
R small_union<Allocator, MaxType, IndexType, Types...>::call(Args&&... args) const
{
    assert(current < sizeof...(Types));

    using signature = decltype(&Visitor::template call<int>);
    static constexpr signature table[] = { &Visitor::template call<Types>... };
    return table[current](*this, std::forward<Args...>(args...));
}

template <typename Allocator, typename MaxType, typename IndexType, typename... Types>
struct small_union<Allocator, MaxType, IndexType, Types...>::reconstructor
{
    template <typename T>
    static void call(small_union& self, const small_union& other)
    {
        small_traits<sizeof(MaxType), T>::construct(static_cast<allocator_type&>(self),
                                                    std::addressof(self.storage),
                                                    other.get<T>());
    }
};

template <typename Allocator, typename MaxType, typename IndexType, typename... Types>
struct small_union<Allocator, MaxType, IndexType, Types...>::destructor
{
    template <typename T>
    static void call(small_union& self)
    {
        small_traits<sizeof(MaxType), T>::destroy(static_cast<allocator_type&>(self),
                                                  std::addressof(self.storage));
    }
};

template <typename Allocator, typename MaxType, typename IndexType, typename... Types>
struct small_union<Allocator, MaxType, IndexType, Types...>::copier
{
    template <typename T>
    static void call(small_union& self, const small_union& other)
    {
        small_traits<sizeof(MaxType), T>::copy(std::addressof(self.storage),
                                               std::addressof(other.storage));
    }
};

template <typename Allocator, typename MaxType, typename IndexType, typename... Types>
struct small_union<Allocator, MaxType, IndexType, Types...>::mover
{
    template <typename T>
    static void call(small_union& self, small_union&& other)
    {
        small_traits<sizeof(MaxType), T>::move(std::addressof(self.storage),
                                               std::addressof(other.storage));
    }
};

} // namespace detail
} // namespace dynamic
} // namespace trial

#endif // TRIAL_DYNAMIC_DETAIL_SMALL_UNION_IPP
