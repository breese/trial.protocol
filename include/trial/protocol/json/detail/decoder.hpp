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
#include <string>
#include <boost/cstdint.hpp>
#include <boost/config.hpp>
#include <boost/system/error_code.hpp>
#include <boost/utility/string_ref.hpp>
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

class decoder
{
public:
    typedef std::size_t size_type;
    typedef const char value_type;
    typedef boost::basic_string_ref<char> view_type;

    decoder(const view_type& input);

    void next() BOOST_NOEXCEPT;

    void code(token::code::value) BOOST_NOEXCEPT;
    token::code::value code() const BOOST_NOEXCEPT;
    token::symbol::value symbol() const BOOST_NOEXCEPT;
    token::category::value category() const BOOST_NOEXCEPT;
    boost::system::error_code error() const BOOST_NOEXCEPT;
    const view_type& literal() const BOOST_NOEXCEPT;
    template <typename ReturnType> ReturnType value() const;

private:
    token::code::value next_token(token::code::value) BOOST_NOEXCEPT;
    token::code::value next_f_keyword() BOOST_NOEXCEPT;
    token::code::value next_n_keyword() BOOST_NOEXCEPT;
    token::code::value next_t_keyword() BOOST_NOEXCEPT;
    token::code::value next_number() BOOST_NOEXCEPT;
    token::code::value next_string() BOOST_NOEXCEPT;

    void skip_whitespaces() BOOST_NOEXCEPT;
    bool at_keyword_end() const BOOST_NOEXCEPT;

private:
    template <typename T, typename Enable = void> struct type_matcher;

    view_type input;
    struct
    {
        mutable token::code::value code;
        view_type view;
    } current;
};

} // namespace detail
} // namespace json
} // namespace protocol
} // namespace trial

#include <trial/protocol/json/detail/decoder.ipp>

#endif /* TRIAL_PROTOCOL_JSON_DETAIL_DECODER_HPP */
