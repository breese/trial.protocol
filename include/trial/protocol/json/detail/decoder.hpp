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

#include <string>
#include <boost/cstdint.hpp>
#include <boost/config.hpp>
#include <boost/system/error_code.hpp>
#include <boost/utility/string_ref.hpp>
#include <trial/protocol/json/detail/token.hpp>
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
    typedef const CharT value_type;
    typedef boost::basic_string_ref<CharT> view_type;

    basic_decoder(const view_type& input);

    void next() BOOST_NOEXCEPT;

    token::value type() const BOOST_NOEXCEPT;
    boost::system::error_code error() const BOOST_NOEXCEPT;
    const view_type& literal() const BOOST_NOEXCEPT;
    template <typename ReturnType> ReturnType value() const;

private:
    token::value next_f_keyword() BOOST_NOEXCEPT;
    token::value next_n_keyword() BOOST_NOEXCEPT;
    token::value next_t_keyword() BOOST_NOEXCEPT;
    token::value next_number() BOOST_NOEXCEPT;
    token::value next_string() BOOST_NOEXCEPT;

    void skip_whitespaces() BOOST_NOEXCEPT;
    bool at_keyword_end() const BOOST_NOEXCEPT;

private:
    template <typename C, typename T, typename Enable> friend struct basic_decoder_functor;

    view_type input;
    struct
    {
        token::value type;
        view_type view;
        mutable json::errc error;
    } current;
};

typedef basic_decoder<char> decoder;
typedef basic_decoder<wchar_t> wdecoder;

} // namespace detail
} // namespace json
} // namespace protocol
} // namespace trial

#include <trial/protocol/json/detail/decoder.ipp>

#endif /* TRIAL_PROTOCOL_JSON_DETAIL_DECODER_HPP */
