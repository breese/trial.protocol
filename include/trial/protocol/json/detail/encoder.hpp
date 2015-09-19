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
#include <boost/scoped_ptr.hpp>
#include <boost/utility/string_ref.hpp>
#include <trial/protocol/buffer/base.hpp>

namespace trial
{
namespace protocol
{
namespace json
{
namespace detail
{

template <typename CharT>
class basic_encoder
{
public:
    typedef CharT value_type;
    typedef std::size_t size_type;
    typedef buffer::base<CharT> buffer_type;
    typedef boost::basic_string_ref<CharT> view_type;

    template <typename T>
    basic_encoder(T&);

    //! @brief Write value
    //!
    //! Type U can be an integral type (except bool), a floating-point type, a
    //! string, or a string view.
    template <typename U> size_type value(const U&);
    template <typename U> size_type value();
    //! @brief Write boolean value
    size_type value(bool);
    //! @brief Write string literal
    size_type value(const CharT *);

    size_type literal(const view_type&);

private:
    template <typename T, typename Enable = void> struct type_matcher;

    boost::scoped_ptr<buffer_type> buffer;
};

typedef basic_encoder<char> encoder;

} // namespace detail
} // namespace json
} // namespace protocol
} // namespace trial

#include <trial/protocol/json/detail/encoder.ipp>

#endif // TRIAL_PROTOCOL_JSON_DETAIL_ENCODER_HPP
