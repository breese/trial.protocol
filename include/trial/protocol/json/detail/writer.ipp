#ifndef TRIAL_PROTOCOL_JSON_DETAIL_WRITER_IPP
#define TRIAL_PROTOCOL_JSON_DETAIL_WRITER_IPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2015 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <trial/protocol/json/error.hpp>

namespace trial
{
namespace protocol
{
namespace json
{

template <typename CharT>
basic_writer<CharT>::basic_writer(const basic_writer<CharT>& other)
    : encoder(other.encoder),
      stack(other.stack)
{
}

template <typename CharT>
template <typename T>
basic_writer<CharT>::basic_writer(T& buffer)
    : encoder(buffer)
{
    // Push outermost scope
    stack.push(frame(encoder, code::end_array));
}

template <typename CharT>
boost::system::error_code basic_writer<CharT>::error() const BOOST_NOEXCEPT
{
    return make_error_code(last_error);
}

template <typename CharT>
typename basic_writer<CharT>::size_type
basic_writer<CharT>::level() const BOOST_NOEXCEPT
{
    return stack.size() - 1;
}

template <typename CharT>
template <typename T>
typename basic_writer<CharT>::size_type
basic_writer<CharT>::value(BOOST_FWD_REF(T) value)
{
    validate_scope();

    stack.top().write_separator();
    return encoder.value(boost::forward<T>(value));
}

template <typename CharT>
typename basic_writer<CharT>::size_type
basic_writer<CharT>::value(json::null_t)
{
    validate_scope();

    stack.top().write_separator();
    return encoder.value(json::null);
}

template <typename CharT>
typename basic_writer<CharT>::size_type
basic_writer<CharT>::value(json::begin_array_t)
{
    validate_scope();

    stack.top().write_separator();
    stack.push(frame(encoder, code::end_array));
    return encoder.value(json::begin_array);
}

template <typename CharT>
typename basic_writer<CharT>::size_type
basic_writer<CharT>::value(json::end_array_t)
{
    validate_scope(code::end_array, json::unexpected_token);

    size_type result = encoder.value(json::end_array);
    stack.pop();
    return result;
}

template <typename CharT>
typename basic_writer<CharT>::size_type
basic_writer<CharT>::value(json::begin_object_t)
{
    validate_scope();

    stack.top().write_separator();
    stack.push(frame(encoder, code::end_object));
    return encoder.value(json::begin_object);
}

template <typename CharT>
typename basic_writer<CharT>::size_type
basic_writer<CharT>::value(json::end_object_t)
{
    validate_scope(code::end_object, json::unexpected_token);

    size_type result = encoder.value(json::end_object);
    stack.pop();
    return result;
}

template <typename CharT>
typename basic_writer<CharT>::size_type
basic_writer<CharT>::literal(const view_type& data) BOOST_NOEXCEPT
{
    return encoder.literal(data);
}

template <typename CharT>
void basic_writer<CharT>::validate_scope()
{
    if (stack.empty())
    {
        last_error = unexpected_token;
        throw json::error(error());
    }
}

template <typename CharT>
void basic_writer<CharT>::validate_scope(code::value code,
                                         enum json::errc e)
{
    if ((stack.size() < 2) || (stack.top().code != code))
    {
        last_error = e;
        throw json::error(error());
    }
}

//-----------------------------------------------------------------------------
// frame
//-----------------------------------------------------------------------------

template <typename CharT>
basic_writer<CharT>::frame::frame(detail::basic_encoder<CharT>& encoder,
                                  json::code::value code)
    : encoder(encoder),
      code(code),
      counter(0)
{
}

template <typename CharT>
void basic_writer<CharT>::frame::write_separator()
{
    if (counter != 0)
    {
        switch (code)
        {
        case code::end_array:
            encoder.value(detail::value_separator);
            break;

        case code::end_object:
            if (counter % 2 == 0)
            {
                encoder.value(detail::value_separator);
            }
            else
            {
                encoder.value(detail::name_separator);
            }
            break;

        default:
            break;
        }
    }
    ++counter;
}

} // namespace json
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_JSON_DETAIL_WRITER_IPP
