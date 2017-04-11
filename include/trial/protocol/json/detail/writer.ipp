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

template <typename CharT, std::size_t N>
template <typename T, typename Enable>
struct basic_writer<CharT, N>::overloader
{
};

template <typename CharT, std::size_t N>
template <typename T>
struct basic_writer<CharT, N>::overloader<
    T,
    typename std::enable_if<std::is_same<T, token::null>::value>::type>
{
    using size_type = typename basic_writer<CharT, N>::size_type;

    inline static size_type value(basic_writer<CharT, N>& self)
    {
        return self.null_value();
    }
};

template <typename CharT, std::size_t N>
template <typename T>
struct basic_writer<CharT, N>::overloader<
    T,
    typename std::enable_if<std::is_same<T, token::begin_array>::value>::type>
{
    using size_type = typename basic_writer<CharT, N>::size_type;

    inline static size_type value(basic_writer<CharT, N>& self)
    {
        return self.begin_array_value();
    }
};

template <typename CharT, std::size_t N>
template <typename T>
struct basic_writer<CharT, N>::overloader<
    T,
    typename std::enable_if<std::is_same<T, token::end_array>::value>::type>
{
    using size_type = typename basic_writer<CharT, N>::size_type;

    inline static size_type value(basic_writer<CharT, N>& self)
    {
        return self.end_array_value();
    }
};

template <typename CharT, std::size_t N>
template <typename T>
struct basic_writer<CharT, N>::overloader<
    T,
    typename std::enable_if<std::is_same<T, token::begin_object>::value>::type>
{
    using size_type = typename basic_writer<CharT, N>::size_type;

    inline static size_type value(basic_writer<CharT, N>& self)
    {
        return self.begin_object_value();
    }
};

template <typename CharT, std::size_t N>
template <typename T>
struct basic_writer<CharT, N>::overloader<
    T,
    typename std::enable_if<std::is_same<T, token::end_object>::value>::type>
{
    using size_type = typename basic_writer<CharT, N>::size_type;

    inline static size_type value(basic_writer<CharT, N>& self)
    {
        return self.end_object_value();
    }
};

//-----------------------------------------------------------------------------
// writer
//-----------------------------------------------------------------------------

template <typename CharT, std::size_t N>
template <typename T>
basic_writer<CharT, N>::basic_writer(T& buffer)
    : encoder(buffer)
{
    // Push outermost scope
    stack.push(frame(encoder, token::code::end_array));
}

template <typename CharT, std::size_t N>
std::error_code basic_writer<CharT, N>::error() const BOOST_NOEXCEPT
{
    return make_error_code(last_error);
}

template <typename CharT, std::size_t N>
typename basic_writer<CharT, N>::size_type
basic_writer<CharT, N>::level() const BOOST_NOEXCEPT
{
    return stack.size() - 1;
}

template <typename CharT, std::size_t N>
template <typename T>
typename basic_writer<CharT, N>::size_type
basic_writer<CharT, N>::value()
{
    return basic_writer<CharT, N>::overloader<T>::value(*this);
}

template <typename CharT, std::size_t N>
template <typename T>
typename basic_writer<CharT, N>::size_type
basic_writer<CharT, N>::value(T&& data)
{
    validate_scope();

    stack.top().write_separator();
    return encoder.value(std::forward<T>(data));
}

template <typename CharT, std::size_t N>
typename basic_writer<CharT, N>::size_type
basic_writer<CharT, N>::literal(const view_type& data) BOOST_NOEXCEPT
{
    return encoder.literal(data);
}

template <typename CharT, std::size_t N>
void basic_writer<CharT, N>::validate_scope()
{
    if (stack.empty())
    {
        last_error = unexpected_token;
        throw json::error(error());
    }
}

template <typename CharT, std::size_t N>
void basic_writer<CharT, N>::validate_scope(token::code::value code,
                                         enum json::errc e)
{
    if ((stack.size() < 2) || (stack.top().code != code))
    {
        last_error = e;
        throw json::error(error());
    }
}

template <typename CharT, std::size_t N>
typename basic_writer<CharT, N>::size_type
basic_writer<CharT, N>::null_value()
{
    validate_scope();

    stack.top().write_separator();
    return encoder.template value<token::null>();
}

template <typename CharT, std::size_t N>
typename basic_writer<CharT, N>::size_type
basic_writer<CharT, N>::begin_array_value()
{
    validate_scope();

    stack.top().write_separator();
    stack.push(frame(encoder, token::code::end_array));
    return encoder.template value<token::begin_array>();
}

template <typename CharT, std::size_t N>
typename basic_writer<CharT, N>::size_type
basic_writer<CharT, N>::end_array_value()
{
    validate_scope(token::code::end_array, json::unexpected_token);

    size_type result = encoder.template value<token::end_array>();
    stack.pop();
    return result;
}

template <typename CharT, std::size_t N>
typename basic_writer<CharT, N>::size_type
basic_writer<CharT, N>::begin_object_value()
{
    validate_scope();

    stack.top().write_separator();
    stack.push(frame(encoder, token::code::end_object));
    return encoder.template value<token::begin_object>();
}

template <typename CharT, std::size_t N>
typename basic_writer<CharT, N>::size_type
basic_writer<CharT, N>::end_object_value()
{
    validate_scope(token::code::end_object, json::unexpected_token);

    size_type result = encoder.template value<token::end_object>();
    stack.pop();
    return result;
}

//-----------------------------------------------------------------------------
// frame
//-----------------------------------------------------------------------------

template <typename CharT, std::size_t N>
basic_writer<CharT, N>::frame::frame(encoder_type& encoder,
                                     token::code::value code)
    : encoder(encoder),
      code(code),
      counter(0)
{
}

template <typename CharT, std::size_t N>
void basic_writer<CharT, N>::frame::write_separator()
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
