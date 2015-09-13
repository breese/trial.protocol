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
        switch (self.decoder.code())
        {
        case token::code::integer:
            {
                // FIXME: Raise error if value is too large
                ReturnType result = self.decoder.template value<ReturnType>();
                if (self.decoder.error() != json::no_error)
                {
                    throw json::error(self.error());
                }
                return result;
            }

        case token::code::floating:
            typedef typename integer_to_floating<typename boost::make_signed<ReturnType>::type>::type floating_return_type;
            return ReturnType(boost::math::round(self.decoder.template value<floating_return_type>()));

        default:
            self.decoder.code(token::code::error_invalid_value);
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
        switch (self.decoder.code())
        {
        case token::code::integer:
            typedef typename floating_to_integer<ReturnType>::type integer_return_type;
            return ReturnType(self.decoder.template value<integer_return_type>());

        case token::code::floating:
            return self.decoder.template value<ReturnType>();

        default:
            self.decoder.code(token::code::error_invalid_value);
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
        switch (self.decoder.code())
        {
        case token::code::true_value:
            return true;

        case token::code::false_value:
            return false;

        default:
            self.decoder.code(token::code::error_invalid_value);
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
        switch (self.decoder.code())
        {
        case token::code::string:
            return self.decoder.template value<ReturnType>();

        default:
            self.decoder.code(token::code::error_invalid_value);
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
    : decoder(view_type(&*begin, std::distance(begin, end)))
{
    stack.push(token::code::end);
}

template <typename CharT>
basic_reader<CharT>::basic_reader(const view_type& input)
    : decoder(input)
{
    stack.push(token::code::end);
}

template <typename CharT>
basic_reader<CharT>::basic_reader(const basic_reader& other)
    : decoder(other.decoder)
{
    stack.push(token::code::end);
}

template <typename CharT>
typename basic_reader<CharT>::size_type basic_reader<CharT>::level() const BOOST_NOEXCEPT
{
    assert(stack.size() > 0);
    return stack.size() - 1;
}

template <typename CharT>
token::code::value basic_reader<CharT>::code() const BOOST_NOEXCEPT
{
    return decoder.code();
}

template <typename CharT>
token::symbol::value basic_reader<CharT>::symbol() const BOOST_NOEXCEPT
{
    return decoder.symbol();
}

template <typename CharT>
token::category::value basic_reader<CharT>::category() const BOOST_NOEXCEPT
{
    return decoder.category();
}

template <typename CharT>
boost::system::error_code basic_reader<CharT>::error() const BOOST_NOEXCEPT
{
    return decoder.error();
}

template <typename CharT>
bool basic_reader<CharT>::next()
{
    const token::code::value current = decoder.code();
    switch (current)
    {
    case token::code::begin_array:
        stack.push(token::code::end_array);
        break;

    case token::code::end_array:
        if (stack.empty())
        {
            decoder.code(token::code::error_unbalanced_end_array);
            return false;
        }
        if (!stack.top().is_array())
        {
            decoder.code(token::code::error_expected_end_array);
            return false;
        }
        stack.pop();
        break;

    case token::code::begin_object:
        stack.push(token::code::end_object);
        break;

    case token::code::end_object:
        if (stack.empty())
        {
            decoder.code(token::code::error_unbalanced_end_object);
            return false;
        }
        if (!stack.top().is_object())
        {
            decoder.code(token::code::error_expected_end_object);
            return false;
        }
        stack.pop();
        break;

    default:
        break;
    }

    if (stack.empty())
    {
        decoder.code(token::code::error_unexpected_token);
    }
    else
    {
        decoder.code(stack.top().next(decoder));
    }

    return (category() != token::category::status);
}

template <typename CharT>
bool basic_reader<CharT>::next(token::code::value expect)
{
    const token::code::value current = code();
    if (current != expect)
    {
        decoder.code(token::code::error_unexpected_token);
        return false;
    }
    return next();
}

template <typename CharT>
bool basic_reader<CharT>::next_sibling()
{
    // FIXME: Skip over children
    decoder.code(token::code::error_not_implemented);
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
basic_reader<CharT>::frame::frame(token::code::value scope)
    : scope(scope),
      counter(0)
{
}

template <typename CharT>
bool basic_reader<CharT>::frame::is_array() const
{
    return scope == token::code::end_array;
}

template <typename CharT>
bool basic_reader<CharT>::frame::is_object() const
{
    return scope == token::code::end_object;
}

template <typename CharT>
token::code::value basic_reader<CharT>::frame::next(detail::basic_decoder<CharT>& decoder)
{
    decoder.next();

    switch (scope)
    {
    case token::code::end:
        return check_outer(decoder);

    case token::code::end_array:
        return check_array(decoder);

    case token::code::end_object:
        return check_object(decoder);

    default:
        return token::code::error_unexpected_token;
    }
}

template <typename CharT>
token::code::value basic_reader<CharT>::frame::check_outer(detail::basic_decoder<CharT>& decoder)
{
    // RFC 7159, section 2
    //
    // JSON-text = value

    switch (decoder.code())
    {
    case token::code::value_separator:
    case token::code::name_separator:
        return token::code::error_unexpected_token;

    default:
        return decoder.code();
    }
}

template <typename CharT>
token::code::value basic_reader<CharT>::frame::check_array(detail::basic_decoder<CharT>& decoder)
{
    // RFC 7159, section 5
    //
    // array = begin-array [ value *( value-separator value ) ] end-array

    const token::code::value current = decoder.code();

    ++counter;
    if (counter % 2 == 0)
    {
        // Expect separator
        switch (current)
        {
        case token::code::end_array:
            return current;

        case token::code::value_separator:
            // Skip over separator
            decoder.next();
            ++counter;
            // Prohibit trailing separator
            if (decoder.code() == token::code::end_array)
                return token::code::error_unexpected_token;
            return decoder.code();

        default:
            return token::code::error_expected_end_array;
        }
    }
    else
    {
        // Expect value
        switch (current)
        {
        case token::code::value_separator:
            return token::code::error_unexpected_token;

        case token::code::name_separator:
            return token::code::error_unexpected_token;

        case token::code::end_array:
            return current;

        case token::code::end_object:
            return token::code::error_expected_end_array;

        default:
            break;
        }
        return current;
    }
    return token::code::error_unexpected_token;
}

template <typename CharT>
token::code::value basic_reader<CharT>::frame::check_object(detail::basic_decoder<CharT>& decoder)
{
    // RFC 7159, section 4
    //
    // object = begin-object [ member *( value-separator member ) ]
    //          end-object
    //
    // member = string name-separator value

    const token::code::value current = decoder.code();

    ++counter;
    if (counter % 4 == 0)
    {
        // Expect value separator
        switch (current)
        {
        case token::code::end_object:
            return current;

        case token::code::value_separator:
            decoder.next();
            ++counter;
            // Prohibit trailing separator
            if (decoder.code() == token::code::end_object)
                return token::code::error_unexpected_token;
            return decoder.code();

        default:
            return token::code::error_expected_end_object;
        }
    }
    else if (counter % 4 == 2)
    {
        // Expect name separator
        if (current == token::code::name_separator)
        {
            decoder.next();
            ++counter;
            switch (decoder.code())
            {
            case token::code::end_array:
            case token::code::end_object:
                return token::code::error_unexpected_token;

            default:
                return decoder.code();
            }
        }
    }
    else
    {
        // Expect value
        switch (current)
        {
        case token::code::value_separator:
        case token::code::name_separator:
            return token::code::error_unexpected_token;

        case token::code::end_array:
            return token::code::error_expected_end_object;

        case token::code::end_object:
            return current;

        default:
            // Key must be string type
            if ((counter % 4 == 1) && (current != token::code::string))
                return token::code::error_invalid_key;
            return current;
        }
    }

    return token::code::error_unexpected_token;
}

} // namespace json
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_JSON_DETAIL_READER_IPP
