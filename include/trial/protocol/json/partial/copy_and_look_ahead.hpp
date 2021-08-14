#ifndef TRIAL_PROTOCOL_JSON_PARTIAL_COPY_AND_LOOK_AHEAD_HPP
#define TRIAL_PROTOCOL_JSON_PARTIAL_COPY_AND_LOOK_AHEAD_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2021 Vinícius dos Santos Oliveira <vini.ipsmaker@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <trial/protocol/json/partial/skip.hpp>

namespace trial
{
namespace protocol
{
namespace json
{
namespace partial
{

namespace detail {
template<class CharT>
struct copy_and_look_ahead_collector
{
    using view_type = typename basic_reader<CharT>::view_type;
    using size_type = typename basic_reader<CharT>::size_type;

    copy_and_look_ahead_collector(view_type key)
        : pattern{key}
    {}

    void push_back(CharT v)
    {
        if (!process) return;

        if (!pattern.starts_with(v)) {
            process = false;
            return;
        }

        pattern.remove_prefix(1);
    }

    void append(const CharT *data, size_type size)
    {
        if (!process) return;

        view_type run{data, size};
        if (!pattern.starts_with(run)) {
            process = false;
            return;
        }

        pattern.remove_prefix(size);
    }

    bool current_value_matches_pattern()
    {
        return process && pattern.size() == 0;
    }

    bool process = true;
    view_type pattern;
};
} // namespace detail

template<class CharT, class F>
auto/*=bool*/ copy_and_look_ahead(basic_reader<CharT> reader,
                                  typename basic_reader<CharT>::view_type key,
                                  F&& on_value, std::error_code &ec)
    -> decltype(on_value(reader), true)
{
    assert(!ec);

    if (reader.symbol() != json::token::symbol::begin_object) {
        ec = errc::expected_begin_object;
        return false;
    }

    if (!reader.next()) {
        ec = reader.error();
        return false;
    }

    for (;;) {
        if (reader.symbol() == json::token::symbol::end_object) {
            ec = errc::field_not_found;
            return false;
        }

        // Key
        assert(reader.symbol() == json::token::symbol::key);
        detail::copy_and_look_ahead_collector<CharT> collector{/*pattern=*/key};
        {
            auto ec = reader.string(collector);
            assert(!ec); (void)ec;
        }
        if (!reader.next()) {
            ec = reader.error();
            return false;
        }

        // Value
        if (!collector.current_value_matches_pattern()) {
            skip(reader, ec);
            if (ec)
                return false;
            continue;
        }

        on_value(reader);
        return true;
    }
}

template<class CharT, class F>
auto/*=bool*/ copy_and_look_ahead(basic_reader<CharT> reader,
                                  typename basic_reader<CharT>::view_type key,
                                  F&& on_value)
    -> decltype(on_value(const_cast<basic_reader<CharT>&>(reader)), true)
{
    std::error_code ec;
    bool ret = copy_and_look_ahead(std::move(reader), key,
                                   std::forward<F>(on_value), ec);
    if (ec)
        throw json::error(ec);
    return ret;
}

template<class CharT>
bool copy_and_look_ahead(basic_reader<CharT> reader,
                         const typename basic_reader<CharT>::view_type key,
                         const typename basic_reader<CharT>::view_type value,
                         std::error_code &ec)
{
    bool ret = false;
    auto on_value = [&value,&ec,&ret](basic_reader<CharT> &reader) {
        if (reader.symbol() != json::token::symbol::string)
            return;

        detail::copy_and_look_ahead_collector<CharT>
            collector{/*pattern=*/value};
        {
            auto ec = reader.string(collector);
            assert(!ec); (void)ec;
        }
        ret = collector.current_value_matches_pattern();
        if (!ret)
            ec = errc::field_not_found;
    };
    copy_and_look_ahead(std::move(reader), key, on_value, ec);
    return ret;
}

template<class CharT>
bool copy_and_look_ahead(basic_reader<CharT> reader,
                         const typename basic_reader<CharT>::view_type key,
                         const typename basic_reader<CharT>::view_type value)
{
    std::error_code ec;
    bool ret = copy_and_look_ahead(std::move(reader), key, value, ec);
    if (ec)
        throw json::error(ec);
    return ret;
}

} // namespace partial
} // namespace json
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_JSON_PARTIAL_COPY_AND_LOOK_AHEAD_HPP
