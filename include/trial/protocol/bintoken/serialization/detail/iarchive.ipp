#ifndef TRIAL_PROTOCOL_BINTOKEN_SERIALIZATION_IARCHIVE_IPP
#define TRIAL_PROTOCOL_BINTOKEN_SERIALIZATION_IARCHIVE_IPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2015 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <trial/protocol/bintoken/serialization/detail/array_load.hpp>

namespace trial
{
namespace protocol
{
namespace bintoken
{

template <typename T>
iarchive::iarchive(const T& input)
    : reader(input)
{
}

template <typename T>
void iarchive::load_override(T& data)
{
    serialization::load_overloader<iarchive, T>::
        load(*this, data, 0);
}

template <typename T>
void iarchive::load_override(T& data, long protocol_version)
{
    serialization::load_overloader<iarchive, T>::
        load(*this, data, protocol_version);
}

inline void iarchive::load(view_type& data)
{
    data = reader.literal();
    next();
}

template <typename T>
void iarchive::load(T& data)
{
    data = reader.value<T>();
    next();
}

template <typename T>
void iarchive::load_array(T *data, std::size_t size)
{
    reader.array(data, size);
    next();
}

template <typename Tag>
void iarchive::load()
{
    static_assert(token::is_tag<Tag>::value, "Cannot use type as tag");
    next(Tag::code);
}

template <typename Tag>
bool iarchive::at() const
{
    static_assert(token::is_tag<Tag>::value, "Cannot use type as tag");
    return Tag::same(reader.code());
}

inline token::code::value iarchive::code() const
{
    return reader.code();
}

inline token::symbol::value iarchive::symbol() const
{
    return reader.symbol();
}

inline token::category::value iarchive::category() const
{
    return reader.category();
}

inline auto iarchive::length() const -> size_type
{
    return reader.length();
}

inline void iarchive::next()
{
    if (!reader.next() && (reader.symbol() == token::symbol::error))
    {
        throw bintoken::error(reader.error());
    }
}

inline void iarchive::next(token::code::value expect)
{
    if (!reader.next(expect) && (reader.symbol() == token::symbol::error))
    {
        throw bintoken::error(reader.error());
    }
}

} // namespace bintoken
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_BINTOKEN_SERIALIZATION_IARCHIVE_IPP
