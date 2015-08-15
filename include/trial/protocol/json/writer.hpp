#ifndef TRIAL_PROTOCOL_JSON_WRITER_HPP
#define TRIAL_PROTOCOL_JSON_WRITER_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2015 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <stack>
#include <boost/move/move.hpp>
#include <trial/protocol/buffer/base.hpp>
#include <trial/protocol/json/error.hpp>
#include <trial/protocol/json/token.hpp>
#include <trial/protocol/json/detail/encoder.hpp>

namespace trial
{
namespace protocol
{
namespace json
{

template <typename CharT>
class basic_writer
{
public:
    typedef std::size_t size_type;
    typedef typename detail::basic_encoder<CharT>::view_type view_type;

    basic_writer(const basic_writer<CharT>&);
    template <typename T> basic_writer(T&);

    boost::system::error_code error() const BOOST_NOEXCEPT;
    size_type level() const BOOST_NOEXCEPT;

    template <typename T>
    size_type value(BOOST_FWD_REF(T) value);

    size_type value(json::null_t);
    size_type value(json::begin_array_t);
    size_type value(json::end_array_t);
    size_type value(json::begin_object_t);
    size_type value(json::end_object_t);

    size_type literal(const view_type&) BOOST_NOEXCEPT;

private:
    void validate_scope();
    void validate_scope(token::value, enum json::errc);

private:
    detail::basic_encoder<CharT> encoder;
    mutable enum json::errc last_error;

    struct frame
    {
        frame(detail::basic_encoder<CharT>& encoder, token::value);

        void write_separator();

        detail::basic_encoder<CharT>& encoder;
        token::value type;
        std::size_t counter;
    };
    std::stack<frame> stack;
};

typedef basic_writer<char> writer;

} // namespace json
} // namespace protocol
} // namespace trial

#include <trial/protocol/json/detail/writer.ipp>

#endif // TRIAL_PROTOCOL_JSON_WRITER_HPP
