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

#include <type_traits>
#include <trial/protocol/json/error.hpp>

namespace trial
{
namespace protocol
{
namespace json
{

//-----------------------------------------------------------------------------
// writer::overloader
//-----------------------------------------------------------------------------

template <typename CharT>
template <typename T, typename Enable>
struct basic_writer<CharT>::overloader
{
};

template <typename CharT>
template <typename T>
struct basic_writer<CharT>::overloader<
    T,
    typename std::enable_if<std::is_same<T, token::null>::value>::type>
{
    using size_type = typename basic_writer<CharT>::size_type;

    inline static size_type value(basic_writer<CharT>& self)
    {
        return self.null_value();
    }
};

template <typename CharT>
template <typename T>
struct basic_writer<CharT>::overloader<
    T,
    typename std::enable_if<std::is_same<T, token::begin_array>::value>::type>
{
    using size_type = typename basic_writer<CharT>::size_type;

    inline static size_type value(basic_writer<CharT>& self)
    {
        return self.begin_array_value();
    }
};

template <typename CharT>
template <typename T>
struct basic_writer<CharT>::overloader<
    T,
    typename std::enable_if<std::is_same<T, token::end_array>::value>::type>
{
    using size_type = typename basic_writer<CharT>::size_type;

    inline static size_type value(basic_writer<CharT>& self)
    {
        return self.end_array_value();
    }
};

template <typename CharT>
template <typename T>
struct basic_writer<CharT>::overloader<
    T,
    typename std::enable_if<std::is_same<T, token::begin_object>::value>::type>
{
    using size_type = typename basic_writer<CharT>::size_type;

    inline static size_type value(basic_writer<CharT>& self)
    {
        return self.begin_object_value();
    }
};

template <typename CharT>
template <typename T>
struct basic_writer<CharT>::overloader<
    T,
    typename std::enable_if<std::is_same<T, token::end_object>::value>::type>
{
    using size_type = typename basic_writer<CharT>::size_type;

    inline static size_type value(basic_writer<CharT>& self)
    {
        return self.end_object_value();
    }
};

//-----------------------------------------------------------------------------
// writer
//-----------------------------------------------------------------------------

template <typename CharT>
template <typename T>
basic_writer<CharT>::basic_writer(T& buffer)
    : encoder(buffer)
{
    // Push outermost scope
    stack.push(frame(encoder, token::code::end_array));
}

template <typename CharT>
std::error_code basic_writer<CharT>::error() const BOOST_NOEXCEPT
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
basic_writer<CharT>::value()
{
    return basic_writer<CharT>::overloader<T>::value(*this);
}

template <typename CharT>
template <typename T>
typename basic_writer<CharT>::size_type
basic_writer<CharT>::value(T&& data)
{
    validate_scope();

    stack.top().write_separator();
    return encoder.value(std::forward<T>(data));
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
void basic_writer<CharT>::validate_scope(token::code::value code,
                                         enum json::errc e)
{
    if ((stack.size() < 2) || (stack.top().code != code))
    {
        last_error = e;
        throw json::error(error());
    }
}

template <typename CharT>
typename basic_writer<CharT>::size_type
basic_writer<CharT>::null_value()
{
    validate_scope();

    stack.top().write_separator();
    return encoder.template value<token::null>();
}

template <typename CharT>
typename basic_writer<CharT>::size_type
basic_writer<CharT>::begin_array_value()
{
    validate_scope();

    stack.top().write_separator();
    stack.push(frame(encoder, token::code::end_array));
    return encoder.template value<token::begin_array>();
}

template <typename CharT>
typename basic_writer<CharT>::size_type
basic_writer<CharT>::end_array_value()
{
    validate_scope(token::code::end_array, json::unexpected_token);

    size_type result = encoder.template value<token::end_array>();
    stack.pop();
    return result;
}

template <typename CharT>
typename basic_writer<CharT>::size_type
basic_writer<CharT>::begin_object_value()
{
    validate_scope();

    stack.top().write_separator();
    stack.push(frame(encoder, token::code::end_object));
    return encoder.template value<token::begin_object>();
}

template <typename CharT>
typename basic_writer<CharT>::size_type
basic_writer<CharT>::end_object_value()
{
    validate_scope(token::code::end_object, json::unexpected_token);

    size_type result = encoder.template value<token::end_object>();
    stack.pop();
    return result;
}

//-----------------------------------------------------------------------------
// frame
//-----------------------------------------------------------------------------

template <typename CharT>
basic_writer<CharT>::frame::frame(encoder_type& encoder,
                                  token::code::value code)
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
        case token::code::end_array:
            encoder.template value<token::detail::value_separator>();
            break;

        case token::code::end_object:
            if (counter % 2 == 0)
            {
                encoder.template value<token::detail::value_separator>();
            }
            else
            {
                encoder.template value<token::detail::name_separator>();
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
