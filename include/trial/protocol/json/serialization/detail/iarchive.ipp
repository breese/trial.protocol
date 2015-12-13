#ifndef TRIAL_PROTOCOL_JSON_SERIALIZATION_DETAIL_IARCHIVE_IPP
#define TRIAL_PROTOCOL_JSON_SERIALIZATION_DETAIL_IARCHIVE_IPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2015 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <trial/protocol/json/serialization/detail/array_load.hpp>

namespace trial
{
namespace protocol
{
namespace json
{

inline iarchive::iarchive(const json::reader& reader)
    : reader(reader)
{
}

inline iarchive::iarchive(const json::reader::view_type& view)
    : reader(view)
{
}

template <typename Iterator>
iarchive::iarchive(Iterator begin, Iterator end)
    : reader(json::reader::view_type(&*begin, std::distance(begin, end)))
{
}

template<typename value_type>
void iarchive::load_override(value_type& data)
{
    boost::archive::load(*this, data);
}

template<typename value_type>
void iarchive::load_override(value_type& data, long /* PFTO */)
{
    load_override(data);
}

template <typename T, std::size_t N>
void iarchive::load_override(T (&data)[N])
{
    // By-pass Boost.Serialization which has its own array formatting
    serialization::load_overloader<iarchive, T[N]>::load(*this, data, 0);
}

template <typename Tag>
void iarchive::load()
{
    next(Tag::code);
}

template <typename T>
void iarchive::load(T& value)
{
    value = reader.template value<T>();
    next();
}

template <typename Tag>
bool iarchive::at() const
{
    return (reader.code() == Tag::code);
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

inline void iarchive::next()
{
    if (!reader.next() && (reader.symbol() == token::symbol::error))
    {
        throw json::error(reader.error());
    }
}

inline void iarchive::next(token::code::value expect)
{
    if (!reader.next(expect) && (reader.symbol() == token::symbol::error))
    {
        throw json::error(reader.error());
    }
}

} // namespace json
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_JSON_SERIALIZATION_DETAIL_IARCHIVE_IPP
