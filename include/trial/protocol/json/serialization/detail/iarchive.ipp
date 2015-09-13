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

namespace trial
{
namespace protocol
{
namespace json
{

template <typename CharT>
basic_iarchive<CharT>::basic_iarchive(const json::basic_reader<CharT>& reader)
    : reader(reader)
{
}

template <typename CharT>
basic_iarchive<CharT>::basic_iarchive(const typename json::basic_reader<CharT>::view_type& view)
    : reader(view)
{
}

template <typename CharT>
template <typename Iterator>
basic_iarchive<CharT>::basic_iarchive(Iterator begin, Iterator end)
    : reader(begin, end)
{
}

template <typename CharT>
template <typename T>
void basic_iarchive<CharT>::load(T& value)
{
    value = reader.template value<T>();
    next();
}

template <typename CharT>
void basic_iarchive<CharT>::load(json::null_t)
{
    next(json::code::null);
}

template <typename CharT>
void basic_iarchive<CharT>::load(json::begin_array_t)
{
    next(json::code::begin_array);
}

template <typename CharT>
void basic_iarchive<CharT>::load(json::end_array_t)
{
    next(json::code::end_array);
}

template <typename CharT>
bool basic_iarchive<CharT>::at_end_array() const
{
    switch (reader.code())
    {
    case json::code::end_array:
        return true;

    case json::code::end_object:
        throw json::error(make_error_code(json::expected_end_array));

    case json::code::end:
        throw json::error(make_error_code(json::unexpected_token));

    default:
        return false;
    }
}

template <typename CharT>
void basic_iarchive<CharT>::load(json::begin_object_t)
{
    next(json::code::begin_object);
}

template <typename CharT>
void basic_iarchive<CharT>::load(json::end_object_t)
{
    next(json::code::end_object);
}

template <typename CharT>
bool basic_iarchive<CharT>::at_end_object() const
{
    switch (reader.code())
    {
    case json::code::end_object:
        return true;

    case json::code::end_array:
        throw json::error(make_error_code(json::expected_end_object));

    case json::code::end:
        throw json::error(make_error_code(json::unexpected_token));

    default:
        return false;
    }
}

template <typename CharT>
json::code::value basic_iarchive<CharT>::code() const
{
    return reader.code();
}

template <typename CharT>
void basic_iarchive<CharT>::next()
{
    if (!reader.next() && (reader.symbol() == symbol::error))
    {
        throw json::error(reader.error());
    }
}

template <typename CharT>
void basic_iarchive<CharT>::next(code::value expect)
{
    if (!reader.next(expect) && (reader.symbol() == symbol::error))
    {
        throw json::error(reader.error());
    }
}

} // namespace json
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_JSON_SERIALIZATION_DETAIL_IARCHIVE_IPP
