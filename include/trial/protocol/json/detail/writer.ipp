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
typename basic_writer<CharT>::size_type
basic_writer<CharT>::size() const
{
    return stack.size() - 1;
}

template <typename CharT>
template <typename T>
typename basic_writer<CharT>::size_type
basic_writer<CharT>::value(BOOST_FWD_REF(T) value)
{
    if (validate_scope())
    {
        stack.top().write_separator();
        return encoder.value(boost::forward<T>(value));
    }
    return size_type();
}

template <typename CharT>
typename basic_writer<CharT>::size_type
basic_writer<CharT>::value(json::null_t)
{
    if (validate_scope())
    {
        stack.top().write_separator();
        return encoder.value(json::null);
    }
    return size_type();
}

template <typename CharT>
typename basic_writer<CharT>::size_type
basic_writer<CharT>::value(json::array_open_t)
{
    if (validate_scope())
    {
        stack.top().write_separator();
        stack.push(frame(encoder, token::array_close));
        return encoder.value(json::array_open);
    }
    return size_type();
}

template <typename CharT>
typename basic_writer<CharT>::size_type
basic_writer<CharT>::value(json::array_close_t)
{
    if (validate_scope())
    {
        if (!stack.top().is_array())
        {
            last_error = json::expected_array_end_bracket;
            return size_type();
        }
        size_type result = encoder.value(json::array_close);
        stack.pop();
        return result;
    }
    return size_type();
}

template <typename CharT>
typename basic_writer<CharT>::size_type
basic_writer<CharT>::value(json::object_open_t)
{
    if (validate_scope())
    {
        stack.top().write_separator();
        stack.push(frame(encoder, token::object_close));
        return encoder.value(json::object_open);

    }
    return size_type();
}

template <typename CharT>
typename basic_writer<CharT>::size_type
basic_writer<CharT>::value(json::object_close_t)
{
    if (validate_scope())
    {
        if (!stack.top().is_object())
        {
            last_error = json::expected_object_end_bracket;
            return size_type();
        }
        size_type result = encoder.value(json::object_close);
        stack.pop();
        return result;
    }
    return size_type();
}

template <typename CharT>
typename basic_writer<CharT>::size_type
basic_writer<CharT>::literal(const view_type& data)
{
    return encoder.literal(data);
}

template <typename CharT>
bool basic_writer<CharT>::validate_scope()
{
    if (stack.empty())
    {
        last_error = unexpected_token;
        return false;
    }
    return true;
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
bool basic_writer<CharT>::frame::is_array() const
{
    return type == token::array_close;
}

template <typename CharT>
bool basic_writer<CharT>::frame::is_object() const
{
    return type == token::object_close;
}

template <typename CharT>
void basic_writer<CharT>::frame::write_separator()
{
    if (counter != 0)
    {
        if (is_array())
        {
            // FIXME: Propagate error
            encoder.value(detail::value_separator);
        }
        else if (is_object())
        {
            if (counter % 2 == 0)
            {
                encoder.value(detail::value_separator);
            }
            else
            {
                encoder.value(detail::name_separator);
            }
        }
    }
    ++counter;
}

} // namespace json
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_JSON_DETAIL_WRITER_IPP
