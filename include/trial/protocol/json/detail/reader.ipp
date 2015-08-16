#ifndef TRIAL_PROTOCOL_JSON_DETAIL_READER_IPP
#define TRIAL_PROTOCOL_JSON_DETAIL_READER_IPP

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
#include <boost/math/special_functions/round.hpp>

namespace trial
{
namespace protocol
{
namespace json
{

//-----------------------------------------------------------------------------
// detail::basic_reader_functor
//-----------------------------------------------------------------------------

namespace detail
{

template <typename T>
struct integer_to_floating
{
    // This is a crude approximation
    typedef typename boost::conditional<
        sizeof(T) <= sizeof(float),
            float, typename boost::conditional<
            sizeof(T) <= sizeof(double),
                double,
                long double
                >::type
            >::type type;
};

template <typename T>
struct floating_to_integer
{
    // This is a crude approximation
    typedef typename boost::conditional<
        sizeof(T) <= sizeof(boost::int32_t),
            boost::int32_t, typename boost::conditional<
            sizeof(T) <= sizeof(boost::int64_t),
                boost::int64_t,
                boost::intmax_t
                >::type
        >::type type;
};

template <typename CharT, typename ReturnType, typename Enable = void>
struct basic_reader_functor
{
    static ReturnType convert(const basic_reader<CharT>&);
};

// Integers (not booleans)

template <typename CharT, typename ReturnType>
struct basic_reader_functor<CharT,
                            ReturnType,
                            typename boost::enable_if_c< boost::is_integral<ReturnType>::value && !boost::is_same<ReturnType, bool>::value >::type>
{
    static ReturnType convert(const basic_reader<CharT>& self)
    {
        switch (self.decoder.type())
        {
        case detail::token::integer:
            {
                // FIXME: Raise error if value is too large
                ReturnType result = self.decoder.template value<ReturnType>();
                if (self.decoder.error() != json::no_error)
                {
                    throw json::error(self.error());
                }
                return result;
            }

        case detail::token::floating:
            typedef typename integer_to_floating<typename boost::make_signed<ReturnType>::type>::type floating_return_type;
            return ReturnType(boost::math::round(self.decoder.template value<floating_return_type>()));

        default:
            self.last_error = json::invalid_value;
            throw json::error(self.error());
        }
    }
};

// Floating-point numbers

template <typename CharT, typename ReturnType>
struct basic_reader_functor<CharT,
                            ReturnType,
                            typename boost::enable_if< boost::is_floating_point<ReturnType> >::type>
{
    static ReturnType convert(const basic_reader<CharT>& self)
    {
        switch (self.decoder.type())
        {
        case detail::token::integer:
            typedef typename floating_to_integer<ReturnType>::type integer_return_type;
            return ReturnType(self.decoder.template value<integer_return_type>());

        case detail::token::floating:
            return self.decoder.template value<ReturnType>();

        default:
            self.last_error = json::invalid_value;
            throw json::error(self.error());
        }
    }
};

// Booleans

template <typename CharT, typename ReturnType>
struct basic_reader_functor<CharT,
                            ReturnType,
                            typename boost::enable_if< boost::is_same<ReturnType, bool> >::type>
{
    static ReturnType convert(const basic_reader<CharT>& self)
    {
        switch (self.decoder.type())
        {
        case detail::token::true_value:
            return true;

        case detail::token::false_value:
            return false;

        default:
            self.last_error = json::invalid_value;
            throw json::error(self.error());
        }
    }
};

// Strings

template <typename CharT, typename ReturnType>
struct basic_reader_functor<CharT,
                            ReturnType,
                            typename boost::enable_if< boost::is_same<ReturnType, std::basic_string<CharT> > >::type>
{
    static ReturnType convert(const basic_reader<CharT>& self)
    {
        switch (self.decoder.type())
        {
        case detail::token::string:
            return self.decoder.template value<ReturnType>();

        default:
            self.last_error = json::invalid_value;
            throw json::error(self.error());
        }
    }
};

} // namespace detail

//-----------------------------------------------------------------------------
// basic_reader
//-----------------------------------------------------------------------------

template <typename CharT>
template <typename ForwardIterator>
basic_reader<CharT>::basic_reader(ForwardIterator begin, ForwardIterator end)
    : decoder(view_type(begin, std::distance(begin, end))),
      last_error(json::no_error)
{
    stack.push(token::end);
}

template <typename CharT>
basic_reader<CharT>::basic_reader(const view_type& input)
    : decoder(input),
      last_error(json::no_error)
{
    stack.push(token::end);
}

template <typename CharT>
basic_reader<CharT>::basic_reader(const basic_reader& other)
    : decoder(other.decoder),
      last_error(json::no_error)
{
    stack.push(token::end);
}

template <typename CharT>
typename basic_reader<CharT>::size_type basic_reader<CharT>::level() const BOOST_NOEXCEPT
{
    assert(stack.size() > 0);
    return stack.size() - 1;
}

template <typename CharT>
token::value basic_reader<CharT>::type() const BOOST_NOEXCEPT
{
    if (last_error != json::no_error)
    {
        return token::error;
    }

    switch (decoder.type())
    {
    case detail::token::eof:
        return token::end;

    case detail::token::error:
        return token::error;

    case detail::token::null_value:
        return token::null;

    case detail::token::true_value:
    case detail::token::false_value:
        return token::boolean;

    case detail::token::integer:
        return token::integer;

    case detail::token::floating:
        return token::floating;

    case detail::token::string:
        return token::string;

    case detail::token::begin_array:
        return token::begin_array;

    case detail::token::end_array:
        return token::end_array;

    case detail::token::begin_object:
        return token::begin_object;

    case detail::token::end_object:
        return token::end_object;

    default:
        assert(last_error != json::no_error);
        return token::error;
    }
}

template <typename CharT>
boost::system::error_code basic_reader<CharT>::error() const BOOST_NOEXCEPT
{
    return make_error_code(last_error);
}

template <typename CharT>
bool basic_reader<CharT>::next()
{
    last_error = json::no_error;

    const detail::token::value current = decoder.type();
    switch (current)
    {
    case detail::token::begin_array:
        stack.push(token::end_array);
        break;

    case detail::token::end_array:
        if (stack.empty())
        {
            last_error = json::unbalanced_end_array;
            return false;
        }
        if (!stack.top().is_array())
        {
            last_error = json::expected_end_array;
            return false;
        }
        stack.pop();
        break;

    case detail::token::begin_object:
        stack.push(token::end_object);
        break;

    case detail::token::end_object:
        if (stack.empty())
        {
            last_error = json::unbalanced_end_object;
            return false;
        }
        if (!stack.top().is_object())
        {
            last_error = json::expected_end_object;
            return false;
        }
        stack.pop();
        break;

    default:
        break;
    }

    if (stack.empty())
    {
        last_error = json::unexpected_token;
    }
    else
    {
        last_error = stack.top().next(decoder);
    }
    if (last_error != json::no_error)
    {
        return false;
    }

    return ((type() != token::end) && (type() != token::error));
}

template <typename CharT>
bool basic_reader<CharT>::next(token::value expect)
{
    const token::value current = type();
    if (current != expect)
    {
        last_error = json::unexpected_token;
        return false;
    }
    return next();
}

template <typename CharT>
bool basic_reader<CharT>::next_sibling()
{
    // FIXME: Skip over children
    last_error = json::not_implemented;
    return false;
}

template <typename CharT>
template <typename T>
T basic_reader<CharT>::value() const
{
    typedef typename boost::remove_const<T>::type return_type;
    return detail::basic_reader_functor<CharT, return_type>::convert(*this);
}

template <typename CharT>
inline const typename basic_reader<CharT>::view_type&
basic_reader<CharT>::literal() const BOOST_NOEXCEPT
{
    return decoder.literal();
}

template <typename CharT>
basic_reader<CharT>::frame::frame(token::value scope)
    : scope(scope),
      counter(0)
{
}

template <typename CharT>
bool basic_reader<CharT>::frame::is_array() const
{
    return scope == token::end_array;
}

template <typename CharT>
bool basic_reader<CharT>::frame::is_object() const
{
    return scope == token::end_object;
}

template <typename CharT>
enum json::errc basic_reader<CharT>::frame::next(detail::basic_decoder<CharT>& decoder)
{
    decoder.next();

    switch (scope)
    {
    case token::end:
        return check_outer(decoder);

    case token::end_array:
        return check_array(decoder);

    case token::end_object:
        return check_object(decoder);

    default:
        return json::unexpected_token;
    }
}

template <typename CharT>
enum json::errc basic_reader<CharT>::frame::check_outer(detail::basic_decoder<CharT>& decoder)
{
    // RFC 7159, section 2
    //
    // JSON-text = value

    switch (decoder.type())
    {
    case detail::token::value_separator:
    case detail::token::name_separator:
        return json::unexpected_token;

    default:
        return json::no_error;
    }
}

template <typename CharT>
enum json::errc basic_reader<CharT>::frame::check_array(detail::basic_decoder<CharT>& decoder)
{
    // RFC 7159, section 5
    //
    // array = begin-array [ value *( value-separator value ) ] end-array

    const detail::token::value current = decoder.type();

    ++counter;
    if (counter % 2 == 0)
    {
        // Expect separator
        switch (current)
        {
        case detail::token::end_array:
            return json::no_error;

        case detail::token::value_separator:
            // Skip over separator
            decoder.next();
            ++counter;
            // Prohibit trailing separator
            if (decoder.type() == detail::token::end_array)
                return json::unexpected_token;
            return json::no_error;

        default:
            return json::expected_end_array;
        }
    }
    else
    {
        // Expect value
        switch (current)
        {
        case detail::token::value_separator:
            return json::unexpected_token;

        case detail::token::name_separator:
            return json::unexpected_token;

        case detail::token::end_array:
            return json::no_error;

        case detail::token::end_object:
            return json::expected_end_array;

        default:
            break;
        }
        return json::no_error;
    }
    return json::unexpected_token;
}

template <typename CharT>
enum json::errc basic_reader<CharT>::frame::check_object(detail::basic_decoder<CharT>& decoder)
{
    // RFC 7159, section 4
    //
    // object = begin-object [ member *( value-separator member ) ]
    //          end-object
    //
    // member = string name-separator value

    const detail::token::value current = decoder.type();

    ++counter;
    if (counter % 4 == 0)
    {
        // Expect value separator
        switch (current)
        {
        case detail::token::end_object:
            return json::no_error;

        case detail::token::value_separator:
            decoder.next();
            ++counter;
            // Prohibit trailing separator
            if (decoder.type() == detail::token::end_object)
                return json::unexpected_token;
            return json::no_error;

        default:
            return json::expected_end_object;
        }
    }
    else if (counter % 4 == 2)
    {
        // Expect name separator
        if (current == detail::token::name_separator)
        {
            decoder.next();
            ++counter;
            switch (decoder.type())
            {
            case detail::token::end_array:
            case detail::token::end_object:
                return json::unexpected_token;

            default:
                return json::no_error;
            }
        }
    }
    else
    {
        // Expect value
        switch (current)
        {
        case detail::token::value_separator:
            return json::unexpected_token;

        case detail::token::name_separator:
            return json::unexpected_token;

        case detail::token::end_array:
            return json::expected_end_object;

        case detail::token::end_object:
            return json::no_error;

        default:
            // Key must be string type
            if ((counter % 4 == 1) && (current != detail::token::string))
                return json::invalid_key;
            return json::no_error;
        }
    }

    return json::unexpected_token;
}

} // namespace json
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_JSON_DETAIL_READER_IPP
