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
    next(json::token::null);
}

template <typename CharT>
void basic_iarchive<CharT>::load(json::array_open_t)
{
    next(json::token::array_open);
}

template <typename CharT>
void basic_iarchive<CharT>::load(json::array_close_t)
{
    next(json::token::array_close);
}

template <typename CharT>
bool basic_iarchive<CharT>::at_array_end() const
{
    switch (reader.type())
    {
    case json::token::array_close:
        return true;

    case json::token::object_close:
        throw boost::system::system_error(make_error_code(json::expected_array_end_bracket));

    case json::token::end:
        throw boost::system::system_error(make_error_code(json::unexpected_token));

    default:
        return false;
    }
}

template <typename CharT>
void basic_iarchive<CharT>::load(json::object_open_t)
{
    next(json::token::object_open);
}

template <typename CharT>
void basic_iarchive<CharT>::load(json::object_close_t)
{
    next(json::token::object_close);
}

template <typename CharT>
bool basic_iarchive<CharT>::at_map_end() const
{
    switch (reader.type())
    {
    case json::token::object_close:
        return true;

    case json::token::array_close:
        throw boost::system::system_error(make_error_code(json::expected_object_end_bracket));

    case json::token::end:
        throw boost::system::system_error(make_error_code(json::unexpected_token));

    default:
        return false;
    }
}

template <typename CharT>
json::token::value basic_iarchive<CharT>::type() const
{
    return reader.type();
}

template <typename CharT>
void basic_iarchive<CharT>::next()
{
    if (!reader.next() && (reader.type() == token::error))
    {
        throw boost::system::system_error(reader.error());
    }
}

template <typename CharT>
void basic_iarchive<CharT>::next(token::value expect)
{
    if (!reader.next(expect) && (reader.type() == token::error))
    {
        throw boost::system::system_error(reader.error());
    }
}

} // namespace json
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_JSON_SERIALIZATION_DETAIL_IARCHIVE_IPP
