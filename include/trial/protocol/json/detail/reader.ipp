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

#include <boost/system/system_error.hpp>
#include <boost/mpl/logical.hpp>
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
                            typename boost::enable_if< boost::mpl::and_< boost::is_integral<ReturnType>, boost::mpl::not_< boost::is_same<ReturnType, bool> > > >::type>
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
                    throw boost::system::system_error(self.error());
                }
                return result;
            }

        case detail::token::floating:
            typedef typename integer_to_floating<typename boost::make_signed<ReturnType>::type>::type floating_return_type;
            return ReturnType(boost::math::round(self.decoder.template value<floating_return_type>()));

        default:
            self.last_error = json::invalid_value;
            throw boost::system::system_error(self.error());
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
            throw boost::system::system_error(self.error());
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
            throw boost::system::system_error(self.error());
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
            throw boost::system::system_error(self.error());
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
}

template <typename CharT>
basic_reader<CharT>::basic_reader(const view_type& input)
    : decoder(input),
      last_error(json::no_error)
{
}

template <typename CharT>
basic_reader<CharT>::basic_reader(const basic_reader& other)
    : decoder(other.decoder),
      last_error(json::no_error)
{
}

template <typename CharT>
typename basic_reader<CharT>::size_type basic_reader<CharT>::level() const BOOST_NOEXCEPT
{
    return stack.size();
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

    case detail::token::array_open:
        return token::array_open;

    case detail::token::array_close:
        return token::array_close;

    case detail::token::object_open:
        return token::object_open;

    case detail::token::object_close:
        return token::object_close;

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
    case detail::token::array_open:
        stack.push(token::array_close);
        break;

    case detail::token::array_close:
        if (stack.empty())
        {
            last_error = json::unbalanced_array_end_bracket;
            return false;
        }
        if (!stack.top().is_array())
        {
            last_error = json::expected_array_end_bracket;
            return false;
        }
        stack.pop();
        break;

    case detail::token::object_open:
        stack.push(token::object_close);
        break;

    case detail::token::object_close:
        if (stack.empty())
        {
            last_error = json::unbalanced_object_end_bracket;
            return false;
        }
        if (!stack.top().is_object())
        {
            last_error = json::expected_object_end_bracket;
            return false;
        }
        stack.pop();
        break;

    default:
        break;
    }

    if (stack.empty())
    {
        decoder.next();
    }
    else
    {
        last_error = stack.top().next(decoder);
        if (last_error != json::no_error)
        {
            return false;
        }
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
basic_reader<CharT>::frame::frame(token::value type)
    : type(type),
      counter(0)
{
}

template <typename CharT>
bool basic_reader<CharT>::frame::is_array() const
{
    return type == token::array_close;
}

template <typename CharT>
bool basic_reader<CharT>::frame::is_object() const
{
    return type == token::object_close;
}

template <typename CharT>
enum json::errors basic_reader<CharT>::frame::next(detail::decoder& decoder)
{
    //   container = array / object
    //   array = "[" *element "]"
    //   element = value *( "," value )
    //   object = "{" *member "}"
    //   member = pair *( "," pair )
    //   pair = string ":" value

    decoder.next();
    const detail::token::value current = decoder.type();

    // After the increment, odd tokens are values and even tokens are separators
    ++counter;
    if (counter % 2 != 0)
    {
        switch (current)
        {
        case detail::token::value_separator:
            return json::unexpected_token;

        case detail::token::name_separator:
            return json::unexpected_token;

        case detail::token::array_close:
            return is_object()
                ? json::expected_object_end_bracket
                : json::no_error;

        case detail::token::object_close:
            return is_array()
                ? json::expected_array_end_bracket
                : json::no_error;

        default:
            break;
        }
        return json::no_error;
    }

    if (type == token::array_close)
    {
        switch (current)
        {
        case detail::token::array_close:
            return json::no_error;

        case detail::token::value_separator:
            decoder.next();
            ++counter;
            switch (decoder.type())
            {
            case detail::token::array_close:
            case detail::token::object_close:
                return json::unexpected_token;
            default:
                return json::no_error;
            }

        default:
            return json::expected_array_end_bracket;
        }
    }
    else if (type == token::object_close)
    {
        if (counter % 4 == 0)
        {
            switch (current)
            {
            case detail::token::object_close:
                return json::no_error;

            case detail::token::value_separator:
                decoder.next();
                ++counter;
                return json::no_error;

            default:
                return json::expected_object_end_bracket;
            }
        }
        else if (counter % 4 == 2)
        {
            if (current == detail::token::name_separator)
            {
                decoder.next();
                ++counter;
                switch (decoder.type())
                {
                case detail::token::array_close:
                case detail::token::object_close:
                    return json::unexpected_token;

                default:
                    return json::no_error;
                }
            }
        }
    }
    return json::unexpected_token;
}

} // namespace json
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_JSON_DETAIL_READER_IPP
