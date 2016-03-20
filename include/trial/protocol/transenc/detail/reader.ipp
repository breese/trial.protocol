#ifndef TRIAL_PROTOCOL_TRANSENC_READER_IPP
#define TRIAL_PROTOCOL_TRANSENC_READER_IPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2015 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <limits>
#include <vector>
#include <boost/static_assert.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/common_type.hpp>
#include <boost/type_traits/is_arithmetic.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <trial/protocol/detail/type_traits.hpp>
#include <trial/protocol/transenc/token.hpp>

namespace trial
{
namespace protocol
{
namespace transenc
{

//-----------------------------------------------------------------------------
// reader::overloader
//-----------------------------------------------------------------------------

template <typename ReturnType, typename Enable>
struct reader::overloader
{
    BOOST_STATIC_ASSERT_MSG(sizeof(ReturnType) == 0, "Cannot convert type");
};

// Tags

template <typename Tag>
struct reader::overloader<Tag,
                          typename boost::enable_if< token::is_tag<Tag> >::type>
{
    typedef typename token::type_cast<Tag>::type return_type;

    static return_type convert(const reader& self)
    {
        if (!Tag::same(self.code()))
            throw transenc::error(incompatible_type);
        return self.decoder.value<Tag>();
    }
};

// Booleans

template <>
struct reader::overloader<bool>
{
    static bool convert(const reader& self)
    {
        switch (self.code())
        {
        case token::code::true_value:
            return true;

        case token::code::false_value:
            return false;

        default:
            throw transenc::error(incompatible_type);
        }
    }
};

// Numbers

template <typename ReturnType>
struct reader::overloader<ReturnType,
                          typename boost::enable_if_c< boost::is_arithmetic<ReturnType>::value &&
                                                       !boost::is_same<ReturnType, bool>::value >::type>
{
    static ReturnType convert(const reader& self)
    {
        switch (self.code())
        {
        case token::int8::code:
            {
                token::int8::type result = self.decoder.value<token::int8>();
                typedef typename boost::common_type<ReturnType, token::int8::type>::type widest_type;
                if (widest_type(result) > widest_type(std::numeric_limits<ReturnType>::max()))
                    throw transenc::error(overflow);
                return ReturnType(result);
            }

        case token::int16::code:
            {
                token::int16::type result = self.decoder.value<token::int16>();
                typedef typename boost::common_type<ReturnType, token::int16::type>::type widest_type;
                if (widest_type(result) > widest_type(std::numeric_limits<ReturnType>::max()))
                    throw transenc::error(overflow);
                return ReturnType(result);
            }

        case token::int32::code:
            {
                token::int32::type result = self.decoder.value<token::int32>();
                typedef typename boost::common_type<ReturnType, token::int32::type>::type widest_type;
                if (widest_type(result) > widest_type(std::numeric_limits<ReturnType>::max()))
                    throw transenc::error(overflow);
                return ReturnType(result);
            }

        case token::int64::code:
            {
                token::int64::type result = self.decoder.value<token::int64>();
                typedef typename boost::common_type<ReturnType, token::int64::type>::type widest_type;
                if (widest_type(result) > widest_type(std::numeric_limits<ReturnType>::max()))
                    throw transenc::error(overflow);
                return ReturnType(result);
            }

        case token::float32::code:
            {
                token::float32::type result = self.decoder.value<token::float32>();
                if (result > std::numeric_limits<ReturnType>::max())
                    throw transenc::error(overflow);
                return ReturnType(result);
            }

        case token::float64::code:
            {
                token::float64::type result = self.decoder.value<token::float64>();
                if (result > std::numeric_limits<ReturnType>::max())
                    throw transenc::error(overflow);
                return ReturnType(result);
            }

        default:
            throw transenc::error(invalid_value);
        }
    }
};

// Strings

template <>
struct reader::overloader<std::string>
{
    typedef std::string return_type;

    static return_type convert(const reader& self)
    {
        switch (self.code())
        {
        case token::code::string8:
        case token::code::string16:
        case token::code::string32:
        case token::code::string64:
            return return_type(self.literal().begin(), self.literal().end());
            break;

        default:
            throw transenc::error(invalid_value);
        }
    }
};

// Binary

template <>
struct reader::overloader< std::vector<boost::uint8_t> >
{
    typedef view_type return_type;

    static return_type convert(const reader& self)
    {
        switch (self.code())
        {
        case token::code::binary8:
        case token::code::binary16:
        case token::code::binary32:
        case token::code::binary64:
            return self.literal();
            break;

        default:
            throw transenc::error(invalid_value);
        }
    }
};

//-----------------------------------------------------------------------------
// reader
//-----------------------------------------------------------------------------

template <typename T>
reader::reader(const T& input)
    : decoder(input)
{
    stack.push(token::code::end);
}

inline token::code::value reader::code() const BOOST_NOEXCEPT
{
    return decoder.code();
}

inline token::symbol::value reader::symbol() const BOOST_NOEXCEPT
{
    return decoder.symbol();
}

inline token::category::value reader::category() const BOOST_NOEXCEPT
{
    return decoder.category();
}

inline boost::system::error_code reader::error() const BOOST_NOEXCEPT
{
    return decoder.error();
}

inline reader::size_type reader::level() const BOOST_NOEXCEPT
{
    assert(stack.size() > 0);
    return stack.size() - 1;
}

inline bool reader::next() BOOST_NOEXCEPT
{
    const token::code::value current = decoder.code();
    switch (current)
    {
    case token::code::begin_record:
        stack.push(token::code::end_record);
        break;

    case token::code::begin_array:
        stack.push(token::code::end_array);
        break;

    case token::code::begin_assoc_array:
        stack.push(token::code::end_assoc_array);
        break;

    default:
        break;
    }

    decoder.next();

    switch (current)
    {
    case token::code::end_record:
        if (stack.top() != token::code::end_record)
        {
            decoder.code(token::code::error_expected_end_record);
            return false;
        }
        stack.pop();
        break;

    case token::code::end_array:
        if (stack.top() != token::code::end_array)
        {
            decoder.code(token::code::error_expected_end_array);
            return false;
        }
        stack.pop();
        break;

    case token::code::end_assoc_array:
        if (stack.top() != token::code::end_assoc_array)
        {
            decoder.code(token::code::error_expected_end_assoc_array);
            return false;
        }
        stack.pop();
        break;

    default:
        break;
    }

    return (category() != token::category::status);
}

inline bool reader::next(token::code::value expect) BOOST_NOEXCEPT
{
    const token::code::value current = decoder.code();
    if (current != expect)
    {
        decoder.code(token::code::error_unexpected_token);
        return false;
    }
    return next();
}

template <typename ReturnType>
typename token::type_cast<ReturnType>::type reader::value() const
{
    typedef typename boost::remove_const<ReturnType>::type return_type;
    return overloader<return_type>::convert(*this);
}

inline const reader::view_type& reader::literal() const BOOST_NOEXCEPT
{
    return decoder.literal();
}

} // namespace transenc
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_TRANSENC_READER_IPP
