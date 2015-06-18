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
    typedef typename detail::basic_encoder<CharT>::buffer_type buffer_type;
    typedef typename detail::basic_encoder<CharT>::view_type view_type;

    basic_writer(buffer_type&);

    boost::system::error_code error() const BOOST_NOEXCEPT;
    size_type level() const BOOST_NOEXCEPT;

    template <typename T>
    size_type value(BOOST_FWD_REF(T) value);

    size_type value(json::null_t);
    size_type value(json::array_open_t);
    size_type value(json::array_close_t);
    size_type value(json::object_open_t);
    size_type value(json::object_close_t);

    size_type literal(const view_type&) BOOST_NOEXCEPT;

private:
    void validate_scope();
    void validate_scope(token::value, enum json::errors);

private:
    detail::encoder encoder;
    mutable enum json::errors last_error;

    struct frame
    {
        frame(detail::encoder& encoder, token::value);

        void write_separator();

        detail::encoder& encoder;
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
