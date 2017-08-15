#ifndef TRIAL_PROTOCOL_JSON_DETAIL_DECODER_HPP
#define TRIAL_PROTOCOL_JSON_DETAIL_DECODER_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2015 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <cstddef> // std::size_t
#include <cstdint>
#include <string>
#include <boost/config.hpp>
#include <trial/protocol/core/detail/string_view.hpp>
#include <trial/protocol/json/token.hpp>
#include <trial/protocol/json/error.hpp>

namespace trial
{
namespace protocol
{
namespace json
{
namespace detail
{

template <typename CharT>
class basic_decoder
{
public:
    using size_type = std::size_t;
    using value_type = CharT;
    using view_type = core::detail::basic_string_view<CharT>;

    basic_decoder(const view_type& input);

    void next() BOOST_NOEXCEPT;

    void code(token::detail::code::value) BOOST_NOEXCEPT;
    token::detail::code::value code() const BOOST_NOEXCEPT;
    std::error_code error() const BOOST_NOEXCEPT;
    const view_type& literal() const BOOST_NOEXCEPT;
    const view_type& tail() const BOOST_NOEXCEPT;
    template <typename ReturnType> ReturnType value() const;

private:
    token::detail::code::value next_token(token::detail::code::value) BOOST_NOEXCEPT;
    token::detail::code::value next_f_keyword() BOOST_NOEXCEPT;
    token::detail::code::value next_n_keyword() BOOST_NOEXCEPT;
    token::detail::code::value next_t_keyword() BOOST_NOEXCEPT;
    token::detail::code::value next_number() BOOST_NOEXCEPT;
    token::detail::code::value next_string() BOOST_NOEXCEPT;

    void skip_whitespaces() BOOST_NOEXCEPT;
    bool at_keyword_end() const BOOST_NOEXCEPT;

    template <typename ReturnType, typename Enable = void>
    struct overloader;
    template <typename ReturnType> ReturnType integer_value() const;
    template <typename ReturnType> ReturnType number_value() const;
    std::basic_string<CharT> string_value() const;

private:
    view_type input;
    struct
    {
        mutable token::detail::code::value code;
        view_type view;
    } current;
};

} // namespace detail
} // namespace json
} // namespace protocol
} // namespace trial

#include <trial/protocol/json/detail/decoder.ipp>

#endif /* TRIAL_PROTOCOL_JSON_DETAIL_DECODER_HPP */
