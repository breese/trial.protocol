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

#include <boost/system/system_error.hpp>
#include <trial/protocol/json/error.hpp>

namespace trial
{
namespace protocol
{
namespace json
{

template <typename CharT>
basic_writer<CharT>::basic_writer(buffer_type& buffer)
    : encoder(buffer)
{
    // Push outermost scope
    stack.push(frame(encoder, token::array_close));
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
basic_writer<CharT>::value(json::array_open_t)
{
    validate_scope();

    stack.top().write_separator();
    stack.push(frame(encoder, token::array_close));
    return encoder.value(json::array_open);
}

template <typename CharT>
typename basic_writer<CharT>::size_type
basic_writer<CharT>::value(json::array_close_t)
{
    validate_scope(token::array_close, json::unexpected_token);

    size_type result = encoder.value(json::array_close);
    stack.pop();
    return result;
}

template <typename CharT>
typename basic_writer<CharT>::size_type
basic_writer<CharT>::value(json::object_open_t)
{
    validate_scope();

    stack.top().write_separator();
    stack.push(frame(encoder, token::object_close));
    return encoder.value(json::object_open);
}

template <typename CharT>
typename basic_writer<CharT>::size_type
basic_writer<CharT>::value(json::object_close_t)
{
    validate_scope(token::object_close, json::unexpected_token);

    size_type result = encoder.value(json::object_close);
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
        throw boost::system::system_error(error());
    }
}

template <typename CharT>
void basic_writer<CharT>::validate_scope(token::value type,
                                         enum json::errors e)
{
    if ((stack.size() < 2) || (stack.top().type != type))
    {
        last_error = e;
        throw boost::system::system_error(error());
    }
}

//-----------------------------------------------------------------------------
// frame
//-----------------------------------------------------------------------------

template <typename CharT>
basic_writer<CharT>::frame::frame(detail::encoder& encoder, token::value type)
    : encoder(encoder),
      type(type),
      counter(0)
{
}

template <typename CharT>
void basic_writer<CharT>::frame::write_separator()
{
    if (counter != 0)
    {
        switch (type)
        {
        case token::array_close:
            encoder.value(detail::value_separator);
            break;

        case token::object_close:
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
