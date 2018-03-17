#ifndef TRIAL_PROTOCOL_JSON_VIEWER_HPP
#define TRIAL_PROTOCOL_JSON_VIEWER_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2018 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <iterator>
#include <type_traits>
#include <trial/protocol/json/reader.hpp>

namespace trial
{
namespace protocol
{
namespace json
{

template <typename CharT>
class basic_viewer
{
    using reader_type = basic_reader<CharT>;

public:
    using value_type = typename reader_type::value_type;
    using size_type = typename reader_type::size_type;
    using view_type = typename reader_type::view_type;

    basic_viewer(const view_type& view)
        : view(view)
    {}

    class const_iterator
    {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = view_type;
        using difference_type = typename value_type::difference_type;
        using pointer = typename std::add_pointer<value_type>::type;
        using reference = typename std::add_lvalue_reference<value_type>::type;
        using const_reference = typename std::add_const<reference>::type;

        const_iterator(const view_type& view)
            : reader(view)
        {
        }

        const_iterator(const const_iterator& other)
            : reader(other.reader)
        {
        }

        const_iterator(const_iterator&& other)
            : reader(std::move(other.reader))
        {
        }

        const_iterator& operator++ ()
        {
            reader.next();
            return *this;
        }

        bool operator== (const const_iterator& other) const
        {
            return reader.literal().data() == other.reader.literal().data();
        }

        bool operator!= (const const_iterator& other) const
        {
            return !(*this == other);
        }

        const view_type& operator* () const
        {
            return reader.literal();
        }

        token::code::value code() const BOOST_NOEXCEPT
        {
            return reader.code();
        }

        token::symbol::value symbol() const BOOST_NOEXCEPT
        {
            return reader.symbol();
        }

        token::category::value category() const BOOST_NOEXCEPT
        {
            return reader.category();
        }

        template <typename ReturnType> ReturnType value() const
        {
            return reader.template value<ReturnType>();
        }

    private:
        reader_type reader;
    };

    const_iterator begin() const &
    {
        return const_iterator(view);
    }

    const_iterator end() const &
    {
        // Point to end of view
        return const_iterator({view.data() + view.size(), 0});
    }

private:
    view_type view;
};

using viewer = basic_viewer<char>;

} // namespace json
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_JSON_VIEWER_HPP
