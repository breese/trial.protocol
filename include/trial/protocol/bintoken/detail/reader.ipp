#ifndef TRIAL_PROTOCOL_BINTOKEN_READER_IPP
#define TRIAL_PROTOCOL_BINTOKEN_READER_IPP

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
#include <cmath>
#include <limits>
#include <vector>
#include <trial/protocol/core/detail/type_traits.hpp>
#include <trial/protocol/bintoken/token.hpp>

namespace trial
{
namespace protocol
{
namespace bintoken
{

//-----------------------------------------------------------------------------
// reader::overloader
//-----------------------------------------------------------------------------

template <typename ReturnType, typename Enable>
struct reader::overloader
{
    static_assert(sizeof(ReturnType) == 0, "Cannot convert type");
};

// Tags

template <typename Tag>
struct reader::overloader<
    Tag,
    typename std::enable_if<token::is_tag<Tag>::value>::type>
{
    using return_type = typename token::type_cast<Tag>::type;

    static return_type convert(const reader& self)
    {
        if (!Tag::same(self.code()))
            throw bintoken::error(incompatible_type);
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
            throw bintoken::error(incompatible_type);
        }
    }

    static size_type convert(const reader& self,
                             bool *output,
                             size_type output_length)
    {
        switch (self.code())
        {
        case token::code::true_value:
        case token::code::false_value:
            if (self.length() > output_length)
                throw bintoken::error(overflow);
            *output = convert(self);
            return size_type(1);

        default:
            throw bintoken::error(incompatible_type);
        }
            
    }
};

// Numbers

template <typename ReturnType>
struct reader::overloader<
    ReturnType,
    typename std::enable_if<std::is_arithmetic<ReturnType>::value &&
                            !std::is_unsigned<ReturnType>::value &&
                            !core::detail::is_bool<ReturnType>::value>::type>
{
    static ReturnType convert(const reader& self)
    {
        switch (self.code())
        {
        case token::int8::code:
            {
                token::int8::type result = self.decoder.value<token::int8>();
                using widest_type = typename std::common_type<ReturnType, token::int8::type>::type;
                if (widest_type(result) > widest_type(std::numeric_limits<ReturnType>::max()))
                    throw bintoken::error(overflow);
                return ReturnType(result);
            }

        case token::int16::code:
            {
                token::int16::type result = self.decoder.value<token::int16>();
                using widest_type = typename std::common_type<ReturnType, token::int16::type>::type;
                if (widest_type(result) > widest_type(std::numeric_limits<ReturnType>::max()))
                    throw bintoken::error(overflow);
                return ReturnType(result);
            }

        case token::int32::code:
            {
                token::int32::type result = self.decoder.value<token::int32>();
                using widest_type = typename std::common_type<ReturnType, token::int32::type>::type;
                if (widest_type(result) > widest_type(std::numeric_limits<ReturnType>::max()))
                    throw bintoken::error(overflow);
                return ReturnType(result);
            }

        case token::int64::code:
            {
                token::int64::type result = self.decoder.value<token::int64>();
                using widest_type = typename std::common_type<ReturnType, token::int64::type>::type;
                if (widest_type(result) > widest_type(std::numeric_limits<ReturnType>::max()))
                    throw bintoken::error(overflow);
                return ReturnType(result);
            }

        case token::float32::code:
            {
                token::float32::type result = self.decoder.value<token::float32>();
                if (result > std::numeric_limits<ReturnType>::max())
                    throw bintoken::error(overflow);
                return ReturnType(result);
            }

        case token::float64::code:
            {
                token::float64::type result = self.decoder.value<token::float64>();
                if (result > std::numeric_limits<ReturnType>::max())
                    throw bintoken::error(overflow);
                return ReturnType(result);
            }

        default:
            throw bintoken::error(invalid_value);
        }
    }

    static size_type convert(const reader& self,
                              ReturnType *output,
                              size_type output_length)
    {
        switch (self.code())
        {
        case token::code::int8:
        case token::code::int16:
        case token::code::int32:
        case token::code::int64:
        case token::code::float32:
        case token::code::float64:
            if (self.length() > output_length)
                throw bintoken::error(overflow);
            return self.decoder.array(output, output_length);

        case token::code::array8_int8:
        case token::code::array16_int8:
        case token::code::array32_int8:
        case token::code::array64_int8:
            assert(sizeof(ReturnType) == token::int8::size);
            if (self.length() > output_length)
                throw bintoken::error(overflow);
            return self.decoder.array(output, output_length);

        case token::code::array8_int16:
        case token::code::array16_int16:
        case token::code::array32_int16:
        case token::code::array64_int16:
            assert(sizeof(ReturnType) == token::int16::size);
            if (self.length() > output_length)
                throw bintoken::error(overflow);
            return self.decoder.array(output, output_length);

        case token::code::array8_int32:
        case token::code::array16_int32:
        case token::code::array32_int32:
        case token::code::array64_int32:
            assert(sizeof(ReturnType) == token::int32::size);
            if (self.length() > output_length)
                throw bintoken::error(overflow);
            return self.decoder.array(output, output_length);

        case token::code::array8_int64:
        case token::code::array16_int64:
        case token::code::array32_int64:
        case token::code::array64_int64:
            assert(sizeof(ReturnType) == token::int64::size);
            if (self.length() > output_length)
                throw bintoken::error(overflow);
            return self.decoder.array(output, output_length);

        case token::code::array8_float32:
        case token::code::array16_float32:
        case token::code::array32_float32:
        case token::code::array64_float32:
            assert(sizeof(ReturnType) == token::float32::size);
            if (self.length() > output_length)
                throw bintoken::error(overflow);
            return self.decoder.array(output, output_length);

        case token::code::array8_float64:
        case token::code::array16_float64:
        case token::code::array32_float64:
        case token::code::array64_float64:
            assert(sizeof(ReturnType) == token::float64::size);
            if (self.length() > output_length)
                throw bintoken::error(overflow);
            return self.decoder.array(output, output_length);

        default:
            throw bintoken::error(incompatible_type);
        }
    }
};

template <typename ReturnType>
struct reader::overloader<
    ReturnType,
    typename std::enable_if<std::is_arithmetic<ReturnType>::value &&
                            std::is_unsigned<ReturnType>::value &&
                            !core::detail::is_bool<ReturnType>::value>::type>
{
    static ReturnType convert(const reader& self)
    {
        switch (self.code())
        {
        case token::int8::code:
            {
                token::int8::type result = self.decoder.value<token::int8>();
                using unsigned_type = typename std::make_unsigned<token::int8::type>::type;
                using widest_type = typename std::common_type<ReturnType, unsigned_type>::type;
                const widest_type wide = widest_type(result) & std::numeric_limits<unsigned_type>::max();
                if (wide > widest_type(std::numeric_limits<ReturnType>::max()))
                    throw bintoken::error(overflow);
                return ReturnType(wide);
            }

        case token::int16::code:
            {
                token::int16::type result = self.decoder.value<token::int16>();
                using unsigned_type = typename std::make_unsigned<token::int16::type>::type;
                using widest_type = typename std::common_type<ReturnType, unsigned_type>::type;
                const widest_type wide = widest_type(result) & std::numeric_limits<unsigned_type>::max();
                if (wide > widest_type(std::numeric_limits<ReturnType>::max()))
                    throw bintoken::error(overflow);
                return ReturnType(wide);
            }

        case token::int32::code:
            {
                token::int32::type result = self.decoder.value<token::int32>();
                using unsigned_type = typename std::make_unsigned<token::int32::type>::type;
                using widest_type = typename std::common_type<ReturnType, unsigned_type>::type;
                const widest_type wide = widest_type(result) & std::numeric_limits<unsigned_type>::max();
                if (wide > widest_type(std::numeric_limits<ReturnType>::max()))
                    throw bintoken::error(overflow);
                return ReturnType(wide);
            }

        case token::int64::code:
            {
                token::int64::type result = self.decoder.value<token::int64>();
                using unsigned_type = typename std::make_unsigned<token::int64::type>::type;
                using widest_type = typename std::common_type<ReturnType, unsigned_type>::type;
                const widest_type wide = widest_type(result) & std::numeric_limits<unsigned_type>::max();
                if (wide > widest_type(std::numeric_limits<ReturnType>::max()))
                    throw bintoken::error(overflow);
                return ReturnType(wide);
            }

        default:
            throw bintoken::error(invalid_value);
        }
    }

    static size_type convert(const reader& self,
                             ReturnType *output,
                             size_type output_length)
    {
        switch (self.code())
        {
        case token::code::array8_int8:
        case token::code::array16_int8:
        case token::code::array32_int8:
        case token::code::array64_int8:
            assert(sizeof(ReturnType) == token::int8::size);
            if (self.length() > output_length)
                throw bintoken::error(overflow);
            return self.decoder.array(reinterpret_cast<typename std::make_signed<ReturnType>::type *>(output),
                                      output_length);

        case token::code::array8_int16:
        case token::code::array16_int16:
        case token::code::array32_int16:
        case token::code::array64_int16:
            assert(sizeof(ReturnType) == token::int16::size);
            if (self.length() > output_length)
                throw bintoken::error(overflow);
            return self.decoder.array(reinterpret_cast<typename std::make_signed<ReturnType>::type *>(output),
                                      output_length);

        case token::code::array8_int32:
        case token::code::array16_int32:
        case token::code::array32_int32:
        case token::code::array64_int32:
            assert(sizeof(ReturnType) == token::int32::size);
            if (self.length() > output_length)
                throw bintoken::error(overflow);
            return self.decoder.array(reinterpret_cast<typename std::make_signed<ReturnType>::type *>(output),
                                      output_length);

        case token::code::array8_int64:
        case token::code::array16_int64:
        case token::code::array32_int64:
        case token::code::array64_int64:
            assert(sizeof(ReturnType) == token::int64::size);
            if (self.length() > output_length)
                throw bintoken::error(overflow);
            return self.decoder.array(reinterpret_cast<typename std::make_signed<ReturnType>::type *>(output),
                                      output_length);

        default:
            throw bintoken::error(incompatible_type);
        }
    }
};

// Strings

template <>
struct reader::overloader<std::string>
{
    using return_type = std::string;

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
            throw bintoken::error(invalid_value);
        }
    }
};

//-----------------------------------------------------------------------------
// reader
//-----------------------------------------------------------------------------

inline reader::reader(view_type view)
    : decoder(std::move(view))
{
    stack.push(token::code::end);
}

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

inline std::error_code reader::error() const BOOST_NOEXCEPT
{
    return decoder.error();
}

inline auto reader::length() const -> size_type
{
    switch (code())
    {
    case token::code::end:
    case token::code::null:
        return 0;

    case token::code::true_value:
    case token::code::false_value:
    case token::code::int8:
    case token::code::int16:
    case token::code::int32:
    case token::code::int64:
    case token::code::float32:
    case token::code::float64:
        return 1;

    case token::code::array8_int8:
    case token::code::array16_int8:
    case token::code::array32_int8:
    case token::code::array64_int8:
        return decoder.literal().size();

    case token::code::array8_int16:
    case token::code::array16_int16:
    case token::code::array32_int16:
    case token::code::array64_int16:
        return decoder.literal().size() / token::int16::size;

    case token::code::array8_int32:
    case token::code::array16_int32:
    case token::code::array32_int32:
    case token::code::array64_int32:
        return decoder.literal().size() / token::int32::size;

    case token::code::array8_int64:
    case token::code::array16_int64:
    case token::code::array32_int64:
    case token::code::array64_int64:
        return decoder.literal().size() / token::int64::size;

    case token::code::array8_float32:
    case token::code::array16_float32:
    case token::code::array32_float32:
    case token::code::array64_float32:
        return decoder.literal().size() / token::float32::size;

    case token::code::array8_float64:
    case token::code::array16_float64:
    case token::code::array32_float64:
    case token::code::array64_float64:
        return decoder.literal().size() / token::float64::size;

    case token::code::string8:
    case token::code::string16:
    case token::code::string32:
    case token::code::string64:
        return decoder.literal().size();

    default:
        throw bintoken::error(unknown_token);
    }
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
    using return_type = typename std::remove_const<ReturnType>::type;
    return overloader<return_type>::convert(*this);
}

template <typename T>
auto reader::array(T* output,
                   size_type output_length) const -> size_type
{
    using type = typename std::remove_const<T>::type;
    return overloader<type>::convert(*this, output, output_length);
}

inline const reader::view_type& reader::literal() const BOOST_NOEXCEPT
{
    return decoder.literal();
}

inline auto reader::tail() const BOOST_NOEXCEPT -> const view_type&
{
    return decoder.tail();
}

} // namespace bintoken
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_BINTOKEN_READER_IPP
