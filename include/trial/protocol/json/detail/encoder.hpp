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

struct value_separator_t {};
const value_separator_t value_separator = value_separator_t();

struct name_separator_t {};
const name_separator_t name_separator = name_separator_t();

template <typename CharT>
class basic_encoder
{
public:
    typedef CharT value_type;
    typedef std::size_t size_type;
    typedef buffer::base<CharT> buffer_type;
    typedef boost::basic_string_ref<CharT> view_type;

    basic_encoder(buffer_type&);

    //! @brief Write value
    //!
    //! Type U can be an integral type (except bool), a floating-point type, a
    //! string, or a string view.
    template <typename U> size_type value(const U&);
    //! @brief Write boolean value
    size_type value(bool);
    //! @brief Write string literal
    size_type value(const CharT *);
    //! @brief Write null type
    size_type value(json::null_t);
    //! @brief Write opening of array
    size_type value(json::array_open_t);
    //! @brief Write closing of array
    size_type value(json::array_close_t);
    //! @brief Write openting of object
    size_type value(json::object_open_t);
    //! @brief Write closing of object
    size_type value(json::object_close_t);
    size_type value(json::detail::value_separator_t);
    size_type value(json::detail::name_separator_t);

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
