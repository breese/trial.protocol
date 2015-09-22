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

class writer
{
public:
    typedef std::size_t size_type;
    typedef detail::encoder::view_type view_type;

    template <typename T> writer(T&);

    boost::system::error_code error() const BOOST_NOEXCEPT;
    size_type level() const BOOST_NOEXCEPT;

    template <typename T>
    size_type value();

    template <typename T>
    size_type value(BOOST_FWD_REF(T) value);

    size_type literal(const view_type&) BOOST_NOEXCEPT;

private:
    void validate_scope();
    void validate_scope(token::code::value, enum json::errc);

private:
    template <typename T, typename Enable = void> struct type_matcher;
    detail::encoder encoder;
    mutable enum json::errc last_error;

    struct frame
    {
        frame(detail::encoder& encoder, token::code::value);

        void write_separator();

        detail::encoder& encoder;
        token::code::value code;
        std::size_t counter;
    };
    std::stack<frame> stack;
};

} // namespace json
} // namespace protocol
} // namespace trial

#include <trial/protocol/json/detail/writer.ipp>

#endif // TRIAL_PROTOCOL_JSON_WRITER_HPP
