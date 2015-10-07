#ifndef TRIAL_PROTOCOL_TRANSENC_DETAIL_DECODER_HPP
#define TRIAL_PROTOCOL_TRANSENC_DETAIL_DECODER_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2015 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <boost/config.hpp>
#include <boost/cstdint.hpp>
#include <boost/array.hpp>
#include <boost/utility/string_ref.hpp>
#include <trial/protocol/transenc/token.hpp>
#include <trial/protocol/transenc/error.hpp>

namespace trial
{
namespace protocol
{
namespace transenc
{
namespace detail
{

class decoder
{
public:
    typedef boost::uint8_t value_type;
    typedef boost::basic_string_ref<value_type> view_type;

    template <typename T>
    decoder(const T& input);

    void next() BOOST_NOEXCEPT;

    void code(token::code::value) BOOST_NOEXCEPT;
    token::code::value code() const BOOST_NOEXCEPT;
    token::symbol::value symbol() const BOOST_NOEXCEPT;
    token::category::value category() const BOOST_NOEXCEPT;
    boost::system::error_code error() const BOOST_NOEXCEPT;

    const view_type& literal() const BOOST_NOEXCEPT;
    template <typename Tag> typename Tag::type value() const;

private:
    token::code::value next(value_type, boost::int64_t) BOOST_NOEXCEPT;
    token::code::value next_string(value_type) BOOST_NOEXCEPT;
    token::code::value next_binary(value_type) BOOST_NOEXCEPT;

    template <typename Tag>
    token::code::value advance() BOOST_NOEXCEPT;

    template <typename Tag>
    token::code::value advance(value_type) BOOST_NOEXCEPT;

private:
    template <typename ReturnType> struct overloader;

    view_type input;
    struct
    {
        mutable token::code::value code;
        view_type view;
    } current;
};

} // namespace detail
} // namespace transenc
} // namespace protocol
} // namespace trial

#include <trial/protocol/transenc/detail/decoder.ipp>

#endif // TRIAL_PROTOCOL_TRANSENC_DETAIL_DECODER_HPP
