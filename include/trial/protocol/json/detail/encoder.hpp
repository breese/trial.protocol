#ifndef TRIAL_PROTOCOL_JSON_DETAIL_ENCODER_HPP
#define TRIAL_PROTOCOL_JSON_DETAIL_ENCODER_HPP

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
#include <boost/none.hpp>
#include <boost/utility/string_ref.hpp>
#include <trial/protocol/buffer/base.hpp>
#include <trial/protocol/json/types.hpp>

namespace trial
{
namespace protocol
{
namespace json
{
namespace detail
{

struct comma_t {};
const comma_t comma = comma_t();

struct colon_t {};
const colon_t colon = colon_t();

template <typename CharT>
class basic_encoder
{
public:
    typedef CharT value_type;
    typedef std::size_t size_type;
    typedef buffer::base<CharT> buffer_type;
    typedef boost::basic_string_ref<CharT> view_type;

    basic_encoder(buffer_type&);

    template <typename U> size_type value(const U&);
    size_type value(bool);
    size_type value(const CharT *);
    size_type value(json::null_t);
    size_type value(json::array_open_t);
    size_type value(json::array_close_t);
    size_type value(json::object_open_t);
    size_type value(json::object_close_t);
    size_type value(json::detail::comma_t);
    size_type value(json::detail::colon_t);

    size_type literal(const view_type&);

private:
    template <typename C, typename T, typename Enable> friend struct basic_encoder_functor;

    buffer_type& buffer;
};

typedef basic_encoder<char> encoder;

} // namespace detail
} // namespace json
} // namespace protocol
} // namespace trial

#include <trial/protocol/json/detail/encoder.ipp>

#endif // TRIAL_PROTOCOL_JSON_DETAIL_ENCODER_HPP
