#ifndef TRIAL_PROTOCOL_TRANSENC_DETAIL_ENCODER_IPP
#define TRIAL_PROTOCOL_TRANSENC_DETAIL_ENCODER_IPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2015 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <limits>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_integral.hpp>
#include <boost/utility/enable_if.hpp>
#include <trial/protocol/buffer/base.hpp>
#include <trial/protocol/transenc/token.hpp>
#include <trial/protocol/transenc/error.hpp>

namespace trial
{
namespace protocol
{
namespace transenc
{
namespace detail
{

template <typename T>
encoder::encoder(T& output)
    : buffer(new typename buffer::traits<T>::buffer_type(output))
{
}

template <typename T>
encoder::size_type encoder::value()
{
    BOOST_STATIC_ASSERT_MSG(sizeof(T) == 0, "Type not supported");
    throw transenc::error(incompatible_type);
}

template <>
inline encoder::size_type encoder::value<token::null>()
{
    return write(token::null::code);
}

template <>
inline encoder::size_type encoder::value<token::begin_record>()
{
    return write(token::begin_record::code);
}

template <>
inline encoder::size_type encoder::value<token::end_record>()
{
    return write(token::end_record::code);
}

template <>
inline encoder::size_type encoder::value<token::begin_array>()
{
    return write(token::begin_array::code);
}

template <>
inline encoder::size_type encoder::value<token::end_array>()
{
    return write(token::end_array::code);
}

template <>
inline encoder::size_type encoder::value<token::begin_assoc_array>()
{
    return write(token::begin_assoc_array::code);
}

template <>
inline encoder::size_type encoder::value<token::end_assoc_array>()
{
    return write(token::end_assoc_array::code);
}

inline encoder::size_type encoder::value(bool data)
{
    return write(data ? token::code::true_value : token::code::false_value);
}

inline encoder::size_type encoder::value(token::int8::type data)
{
    if (data >= -32)
    {
        return write(data);
    }
    else
    {
        const value_type token(token::int8::code);
        const size_type size = sizeof(token) + sizeof(boost::int8_t);
        if (buffer->grow(size))
        {
            buffer->write(token);
            buffer->write(data);
            return size;
        }
    }
    return 0;
}

inline encoder::size_type encoder::value(token::int16::type data)
{
    const value_type token(token::int16::code);
    const size_type size = sizeof(token) + sizeof(boost::int16_t);
    if (buffer->grow(size))
    {
        const boost::uint16_t endian = UINT16_C(0x0100);
        value_type *data_buffer = (value_type *)&data;
        buffer->write(token);
        buffer->write(static_cast<value_type>(data_buffer[((value_type *)&endian)[0]]));
        buffer->write(static_cast<value_type>(data_buffer[((value_type *)&endian)[1]]));
        return size;
    }
    return 0;
}

inline encoder::size_type encoder::value(token::int32::type data)
{
    const value_type token(token::int32::code);
    const size_type size = sizeof(token) + sizeof(boost::int32_t);
    if (buffer->grow(size))
    {
        const boost::uint32_t endian = UINT32_C(0x03020100);
        value_type *data_buffer = (value_type *)&data;
        buffer->write(token);
        buffer->write(static_cast<value_type>(data_buffer[((value_type *)&endian)[0]]));
        buffer->write(static_cast<value_type>(data_buffer[((value_type *)&endian)[1]]));
        buffer->write(static_cast<value_type>(data_buffer[((value_type *)&endian)[2]]));
        buffer->write(static_cast<value_type>(data_buffer[((value_type *)&endian)[3]]));
        return size;
    }
    return 0;
}

inline encoder::size_type encoder::value(token::int64::type data)
{
    const value_type token(token::int64::code);
    const size_type size = sizeof(token) + sizeof(boost::int64_t);
    if (buffer->grow(size))
    {
        const boost::uint64_t endian = UINT64_C(0x0706050403020100);
        value_type *data_buffer = (value_type *)&data;
        buffer->write(token);
        buffer->write(static_cast<value_type>(data_buffer[((value_type *)&endian)[0]]));
        buffer->write(static_cast<value_type>(data_buffer[((value_type *)&endian)[1]]));
        buffer->write(static_cast<value_type>(data_buffer[((value_type *)&endian)[2]]));
        buffer->write(static_cast<value_type>(data_buffer[((value_type *)&endian)[3]]));
        buffer->write(static_cast<value_type>(data_buffer[((value_type *)&endian)[4]]));
        buffer->write(static_cast<value_type>(data_buffer[((value_type *)&endian)[5]]));
        buffer->write(static_cast<value_type>(data_buffer[((value_type *)&endian)[6]]));
        buffer->write(static_cast<value_type>(data_buffer[((value_type *)&endian)[7]]));
        return size;
    }
    return 0;
}

inline encoder::size_type encoder::value(token::float32::type data)
{
    // IEEE 754 single precision
    const value_type token(token::float32::code);
    const size_type size = sizeof(token) + sizeof(token::float32::type);
    if (buffer->grow(size))
    {
        const boost::uint32_t endian = UINT32_C(0x03020100);
        value_type *data_buffer = (value_type *)&data;
        buffer->write(token);
        buffer->write(static_cast<value_type>(data_buffer[((value_type *)&endian)[0]]));
        buffer->write(static_cast<value_type>(data_buffer[((value_type *)&endian)[1]]));
        buffer->write(static_cast<value_type>(data_buffer[((value_type *)&endian)[2]]));
        buffer->write(static_cast<value_type>(data_buffer[((value_type *)&endian)[3]]));
        return size;
    }
    return 0;
}

inline encoder::size_type encoder::value(token::float64::type data)
{
    // IEEE 754 double precision
    const value_type token(token::float64::code);
    const size_type size = sizeof(token) + sizeof(token::float64::type);
    if (buffer->grow(size))
    {
        const boost::uint64_t endian = UINT64_C(0x0706050403020100);
        value_type *data_buffer = (value_type *)&data;
        buffer->write(token);
        buffer->write(static_cast<value_type>(data_buffer[((value_type *)&endian)[0]]));
        buffer->write(static_cast<value_type>(data_buffer[((value_type *)&endian)[1]]));
        buffer->write(static_cast<value_type>(data_buffer[((value_type *)&endian)[2]]));
        buffer->write(static_cast<value_type>(data_buffer[((value_type *)&endian)[3]]));
        buffer->write(static_cast<value_type>(data_buffer[((value_type *)&endian)[4]]));
        buffer->write(static_cast<value_type>(data_buffer[((value_type *)&endian)[5]]));
        buffer->write(static_cast<value_type>(data_buffer[((value_type *)&endian)[6]]));
        buffer->write(static_cast<value_type>(data_buffer[((value_type *)&endian)[7]]));
        return size;
    }
    return 0;
}

inline encoder::size_type encoder::value(const string_view_type& data)
{
    const std::string::size_type length = data.size();
    size_type size = 0;

    if (length < static_cast<std::string::size_type>(std::numeric_limits<boost::uint8_t>::max()))
    {
        if (!buffer->grow(sizeof(value_type) + sizeof(boost::uint8_t) + length))
            return 0;
        buffer->write(token::code::string8);
        size = write_length(static_cast<boost::uint8_t>(length));
    }
    else if (length < static_cast<std::string::size_type>(std::numeric_limits<boost::uint16_t>::max()))
    {
        if (!buffer->grow(sizeof(value_type) + sizeof(boost::uint16_t) + length))
            return 0;
        buffer->write(token::code::string16);
        size = write_length(static_cast<boost::uint16_t>(length));
    }
    else if (length < static_cast<std::string::size_type>(std::numeric_limits<boost::uint32_t>::max()))
    {
        if (!buffer->grow(sizeof(value_type) + sizeof(boost::uint32_t) + length))
            return 0;
        buffer->write(token::code::string32);
        size = write_length(static_cast<boost::uint32_t>(length));
    }
    else
    {
        if (!buffer->grow(sizeof(value_type) + sizeof(boost::uint64_t) + length))
            return 0;
        buffer->write(token::code::string64);
        size = write_length(static_cast<boost::uint64_t>(length));
    }

    buffer->write(view_type(reinterpret_cast<const value_type *>(data.data()),
                            data.size()));
    return sizeof(value_type) + size + length;
}

inline encoder::size_type encoder::value(const char *data,
                                         size_type size)
{
    return value(string_view_type(data, size));
}

inline encoder::size_type encoder::value(const char *data)
{
    return value(string_view_type(data));
}

inline encoder::size_type encoder::binary(const value_type *data,
                                          size_type length)
{
    size_type size = 0;

    if (length < static_cast<std::string::size_type>(std::numeric_limits<boost::uint8_t>::max()))
    {
        if (!buffer->grow(sizeof(value_type) + sizeof(boost::uint8_t) + length))
            return 0;
        buffer->write(token::code::binary8);
        size = write_length(static_cast<boost::uint8_t>(length));
        if (length == 0)
            return sizeof(value_type) + size;
    }
    else if (length < static_cast<std::string::size_type>(std::numeric_limits<boost::uint16_t>::max()))
    {
        if (!buffer->grow(sizeof(value_type) + sizeof(boost::uint16_t) + length))
            return 0;
        buffer->write(token::code::binary16);
        size = write_length(static_cast<boost::uint16_t>(length));
    }
    else if (length < static_cast<std::string::size_type>(std::numeric_limits<boost::uint32_t>::max()))
    {
        if (!buffer->grow(sizeof(value_type) + sizeof(boost::uint32_t) + length))
            return 0;
        buffer->write(token::code::binary32);
        size = write_length(static_cast<boost::uint32_t>(length));
    }
    else
    {
        if (!buffer->grow(sizeof(value_type) + sizeof(boost::uint64_t) + length))
            return 0;
        buffer->write(token::code::binary64);
        size = write_length(static_cast<boost::uint64_t>(length));
    }

    buffer->write(view_type(data, length));
    return sizeof(value_type) + size + length;
}

inline encoder::size_type encoder::binary(const view_type& data)
{
    return binary(data.data(), data.size());
}

inline encoder::size_type encoder::write_length(boost::uint8_t data)
{
    return write(data);
}

inline encoder::size_type encoder::write_length(boost::uint16_t data)
{
    const size_type size = sizeof(boost::int16_t);
    if (buffer->grow(size))
    {
        const boost::uint16_t endian = UINT16_C(0x0100);
        value_type *data_buffer = (value_type *)&data;
        buffer->write(static_cast<value_type>(data_buffer[((value_type *)&endian)[0]]));
        buffer->write(static_cast<value_type>(data_buffer[((value_type *)&endian)[1]]));
        return size;
    }
    return 0;
}

inline encoder::size_type encoder::write_length(boost::uint32_t data)
{
    const size_type size = sizeof(boost::int32_t);
    if (buffer->grow(size))
    {
        const boost::uint32_t endian = UINT32_C(0x03020100);
        value_type *data_buffer = (value_type *)&data;
        buffer->write(static_cast<value_type>(data_buffer[((value_type *)&endian)[0]]));
        buffer->write(static_cast<value_type>(data_buffer[((value_type *)&endian)[1]]));
        buffer->write(static_cast<value_type>(data_buffer[((value_type *)&endian)[2]]));
        buffer->write(static_cast<value_type>(data_buffer[((value_type *)&endian)[3]]));
        return size;
    }
    return 0;
}

inline encoder::size_type encoder::write_length(boost::uint64_t data)
{
    const size_type size = sizeof(boost::int64_t);
    if (buffer->grow(size))
    {
        const boost::uint64_t endian = UINT64_C(0x0706050403020100);
        value_type *data_buffer = (value_type *)&data;
        buffer->write(static_cast<value_type>(data_buffer[((value_type *)&endian)[0]]));
        buffer->write(static_cast<value_type>(data_buffer[((value_type *)&endian)[1]]));
        buffer->write(static_cast<value_type>(data_buffer[((value_type *)&endian)[2]]));
        buffer->write(static_cast<value_type>(data_buffer[((value_type *)&endian)[3]]));
        buffer->write(static_cast<value_type>(data_buffer[((value_type *)&endian)[4]]));
        buffer->write(static_cast<value_type>(data_buffer[((value_type *)&endian)[5]]));
        buffer->write(static_cast<value_type>(data_buffer[((value_type *)&endian)[6]]));
        buffer->write(static_cast<value_type>(data_buffer[((value_type *)&endian)[7]]));
        return size;
    }
    return 0;
}

inline encoder::size_type encoder::write(value_type data)
{
    const size_type size = sizeof(data);
    if (buffer->grow(size))
    {
        buffer->write(data);
        return size;
    }
    return 0;
}

inline encoder::size_type encoder::write(const view_type& data)
{
    const size_type size = data.size();
    if (buffer->grow(size))
    {
        buffer->write(data);
        return size;
    }
    return 0;
}

} // namespace detail
} // namespace transenc
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_TRANSENC_DETAIL_ENCODER_IPP
