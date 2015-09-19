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

#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_same.hpp>
#include <trial/protocol/json/error.hpp>

namespace trial
{
namespace protocol
{
namespace json
{

//-----------------------------------------------------------------------------
// basic_writer::type_matcher
//-----------------------------------------------------------------------------

template <typename CharT>
template <typename T, typename Enable>
struct basic_writer<CharT>::type_matcher
{
};

template <typename CharT>
template <typename T>
struct basic_writer<CharT>::type_matcher<T,
                                         typename boost::enable_if< boost::is_same<T, token::null> >::type>
{
    static basic_writer<CharT>::size_type value(basic_writer<CharT>& self)
    {
        self.validate_scope();
        self.stack.top().write_separator();
        return self.encoder.template value<T>();
    }
};

template <typename CharT>
template <typename T>
struct basic_writer<CharT>::type_matcher<T,
                                         typename boost::enable_if< boost::is_same<T, token::begin_array> >::type>
{
    typedef basic_writer<CharT>::size_type size_type;

    static size_type value(basic_writer<CharT>& self)
    {
        self.validate_scope();
        self.stack.top().write_separator();
        self.stack.push(frame(self.encoder, token::code::end_array));
        return self.encoder.template value<T>();
    }
};

template <typename CharT>
template <typename T>
struct basic_writer<CharT>::type_matcher<T,
                                         typename boost::enable_if< boost::is_same<T, token::end_array> >::type>
{
    typedef basic_writer<CharT>::size_type size_type;

    static size_type value(basic_writer<CharT>& self)
    {
        self.validate_scope(token::code::end_array, json::unexpected_token);

        size_type result = self.encoder.template value<T>();
        self.stack.pop();
        return result;
    }
};

template <typename CharT>
template <typename T>
struct basic_writer<CharT>::type_matcher<T,
                                         typename boost::enable_if< boost::is_same<T, token::begin_object> >::type>
{
    typedef basic_writer<CharT>::size_type size_type;

    static size_type value(basic_writer<CharT>& self)
    {
        self.validate_scope();
        self.stack.top().write_separator();
        self.stack.push(frame(self.encoder, token::code::end_object));
        return self.encoder.template value<T>();
    }
};

template <typename CharT>
template <typename T>
struct basic_writer<CharT>::type_matcher<T,
                                         typename boost::enable_if< boost::is_same<T, token::end_object> >::type>
{
    typedef basic_writer<CharT>::size_type size_type;

    static size_type value(basic_writer<CharT>& self)
    {
        self.validate_scope(token::code::end_object, json::unexpected_token);

        size_type result = self.encoder.template value<T>();
        self.stack.pop();
        return result;
    }
};

//-----------------------------------------------------------------------------
// basic_writer
//-----------------------------------------------------------------------------

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
    stack.push(frame(encoder, token::code::end_array));
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
basic_writer<CharT>::value()
{
    return type_matcher<T>::value(*this);
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

//-----------------------------------------------------------------------------
// frame
//-----------------------------------------------------------------------------

template <typename CharT>
basic_writer<CharT>::frame::frame(detail::basic_encoder<CharT>& encoder,
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
            encoder.template value<token::value_separator>();
            break;

        case token::code::end_object:
            if (counter % 2 == 0)
            {
                encoder.template value<token::value_separator>();
            }
            else
            {
                encoder.template value<token::name_separator>();
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
