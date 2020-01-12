#ifndef TRIAL_PROTOCOL_CORE_DETAIL_SPAN_HPP
#define TRIAL_PROTOCOL_CORE_DETAIL_SPAN_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2020 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <cstddef> // std::size_t

namespace trial
{
namespace protocol
{
namespace core
{
namespace detail
{

// Span without fixed extent

template <typename T>
class span
{
public:
    using value_type = T;
    using size_type = std::size_t;
    using const_pointer = const value_type *;

    span() noexcept = default;
    span(const span&) noexcept = default;
    span(span&&) noexcept = default;
    span& operator=(const span&) noexcept = delete;
    span& operator=(span&&) noexcept = default;

    span(const_pointer first, const_pointer last)
        : head(first),
          tail(last)
    {
    }
    span(const_pointer first, size_type size)
        : head(first),
          tail(head + size)
    {
    }

    const_pointer data() const noexcept
    {
        return head;
    }
    size_type size() const noexcept
    {
        return tail - head;
    }
    bool empty() const noexcept
    {
        return head == tail;
    }
    value_type front() const noexcept
    {
        return *head;
    }
    value_type back() const noexcept
    {
        return *(tail - 1);
    }
    value_type operator[](size_type index) const noexcept
    {
        return head[index];
    }

    void remove_front(size_type amount = 1) noexcept
    {
        head += amount;
    }

    const_pointer begin() const noexcept
    {
        return head;
    }
    const_pointer end() const noexcept
    {
        return tail;
    }

    // For test purposes
    template <std::size_t M>
    bool operator==(const char (&rhs)[M]) const noexcept
    {
        const auto rhs_size = M - 1;
        if (size() != rhs_size)
            return false;
        for (std::size_t k = 0; k < rhs_size; ++k)
        {
            if ((*this)[k] != rhs[k])
                return false;
        }
        return true;
    }
private:
    const_pointer head = nullptr;
    const_pointer tail = nullptr;
};

} // namespace detail
} // namespace core
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_CORE_DETAIL_SPAN_HPP
