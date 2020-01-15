#ifndef TRIAL_PROTOCOL_JSON_PARTIAL_SKIP_HPP
#define TRIAL_PROTOCOL_JSON_PARTIAL_SKIP_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2018 Vinícius dos Santos Oliveira <vini.ipsmaker@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <trial/protocol/json/reader.hpp>

namespace trial
{
namespace protocol
{
namespace json
{
namespace partial
{

template<class CharT>
typename basic_reader<CharT>::view_type
skip(basic_reader<CharT> &reader, std::error_code &ec)
{
    using view_type = typename basic_reader<CharT>::view_type;
    using size_type = typename view_type::size_type;

    switch (reader.symbol()) {
    case token::symbol::end:
    case token::symbol::error:
    case token::symbol::end_array:
    case token::symbol::end_object:
        ec = errc::insufficient_tokens;
        break;
    case token::symbol::null:
    case token::symbol::boolean:
    case token::symbol::integer:
    case token::symbol::real:
    case token::symbol::string:
        {
            auto ret = reader.literal();
            if (!reader.next())
                ec = reader.error();
            return ret;
        }
    case token::symbol::begin_array:
        {
            const CharT * const head = reader.literal().data();
            const size_type current_level = reader.level();
            do
            {
                if (!reader.next())
                {
                    if (reader.code() == token::code::error_expected_end_array)
                        ec = errc::insufficient_tokens;
                    else
                        ec = reader.error();
                    return view_type(head, std::distance(head, reader.literal().begin()));
                }
            } while (reader.level() >= current_level);
            const CharT * const tail = reader.literal().end();
            if (!reader.next()) // Skip over end_array
                ec = reader.error();
            return view_type(head, std::distance(head, tail));
        }
    case token::symbol::begin_object:
        {
            const CharT * const head = reader.literal().data();
            const size_type current_level = reader.level();
            do
            {
                if (!reader.next())
                {
                    if (reader.code() == token::code::error_expected_end_object)
                        ec = errc::insufficient_tokens;
                    else
                        ec = reader.error();
                    return view_type(head, std::distance(head, reader.literal().begin()));
                }
            } while (reader.level() >= current_level);
            const CharT * const tail = reader.literal().end();
            if (!reader.next()) // Skip over end_object
                ec = reader.error();
            return view_type(head, std::distance(head, tail));
        }
    }
    return {};
}

template<class CharT>
typename basic_reader<CharT>::view_type
skip(basic_reader<CharT> &reader)
{
    std::error_code ec;
    auto ret = skip(reader, ec);
    if (ec)
        throw json::error(ec);
    return ret;
}

} // namespace partial
} // namespace json
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_JSON_PARTIAL_SKIP_HPP
