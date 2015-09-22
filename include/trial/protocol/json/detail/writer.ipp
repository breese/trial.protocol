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
// writer::type_matcher
//-----------------------------------------------------------------------------

template <typename T, typename Enable>
struct writer::type_matcher
{
};

template <>
struct writer::type_matcher<token::null>
{
    static size_type value(writer& self)
    {
        self.validate_scope();
        self.stack.top().write_separator();
        return self.encoder.template value<token::null>();
    }
};

template <>
struct writer::type_matcher<token::begin_array>
{
    static size_type value(writer& self)
    {
        self.validate_scope();
        self.stack.top().write_separator();
        self.stack.push(frame(self.encoder, token::code::end_array));
        return self.encoder.template value<token::begin_array>();
    }
};

template <>
struct writer::type_matcher<token::end_array>
{
    static size_type value(writer& self)
    {
        self.validate_scope(token::code::end_array, json::unexpected_token);

        size_type result = self.encoder.template value<token::end_array>();
        self.stack.pop();
        return result;
    }
};

template <>
struct writer::type_matcher<token::begin_object>
{
    static size_type value(writer& self)
    {
        self.validate_scope();
        self.stack.top().write_separator();
        self.stack.push(frame(self.encoder, token::code::end_object));
        return self.encoder.template value<token::begin_object>();
    }
};

template <>
struct writer::type_matcher<token::end_object>
{
    static size_type value(writer& self)
    {
        self.validate_scope(token::code::end_object, json::unexpected_token);

        size_type result = self.encoder.template value<token::end_object>();
        self.stack.pop();
        return result;
    }
};

//-----------------------------------------------------------------------------
// writer
//-----------------------------------------------------------------------------

template <typename T>
writer::writer(T& buffer)
    : encoder(buffer)
{
    // Push outermost scope
    stack.push(frame(encoder, token::code::end_array));
}

inline boost::system::error_code writer::error() const BOOST_NOEXCEPT
{
    return make_error_code(last_error);
}

inline writer::size_type writer::level() const BOOST_NOEXCEPT
{
    return stack.size() - 1;
}

template <typename T>
writer::size_type writer::value()
{
    return type_matcher<T>::value(*this);
}

template <typename T>
writer::size_type writer::value(BOOST_FWD_REF(T) value)
{
    validate_scope();

    stack.top().write_separator();
    return encoder.value(boost::forward<T>(value));
}

inline writer::size_type writer::literal(const view_type& data) BOOST_NOEXCEPT
{
    return encoder.literal(data);
}

inline void writer::validate_scope()
{
    if (stack.empty())
    {
        last_error = unexpected_token;
        throw json::error(error());
    }
}

inline void writer::validate_scope(token::code::value code,
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

inline writer::frame::frame(detail::encoder& encoder,
                            token::code::value code)
    : encoder(encoder),
      code(code),
      counter(0)
{
}

inline void writer::frame::write_separator()
{
    if (counter != 0)
    {
        switch (code)
        {
        case token::code::end_array:
            encoder.value<token::value_separator>();
            break;

        case token::code::end_object:
            if (counter % 2 == 0)
            {
                encoder.value<token::value_separator>();
            }
            else
            {
                encoder.value<token::name_separator>();
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
