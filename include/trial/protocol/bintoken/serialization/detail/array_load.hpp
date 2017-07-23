#ifndef TRIAL_PROTOCOL_BINTOKEN_SERIALIZATION_DETAIL_ARRAY_LOAD_HPP
#define TRIAL_PROTOCOL_BINTOKEN_SERIALIZATION_DETAIL_ARRAY_LOAD_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2015 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <cstring>
#include <trial/protocol/bintoken/serialization/serialization.hpp>
#include <trial/protocol/core/serialization/array.hpp>

//-----------------------------------------------------------------------------
// By-pass Boost.Serialization which has its own array formatting
//-----------------------------------------------------------------------------

namespace boost
{
namespace serialization
{

template <typename T, std::size_t N>
void load(trial::protocol::bintoken::iarchive& ar,
          T (&data)[N],
          const unsigned int version)
{
    using namespace trial::protocol::serialization;
    load_overloader<trial::protocol::bintoken::iarchive, T[N]>::load(ar, data, version);
}

template <typename T, std::size_t N>
void serialize(trial::protocol::bintoken::iarchive& ar,
               T (&data)[N],
               const unsigned int version)
{
    using namespace trial::protocol::serialization;
    serialize_overloader<trial::protocol::bintoken::iarchive, T[N]>::serialize(ar, data, version);
}

} // namespace serialization
} // namespace boost

//-----------------------------------------------------------------------------
// T[N]
//-----------------------------------------------------------------------------

namespace trial
{
namespace protocol
{
namespace serialization
{

template <typename T, std::size_t N>
struct load_overloader< bintoken::iarchive,
                        T[N] >
{
    static void load(bintoken::iarchive& ar,
                     T (&data)[N],
                     const unsigned int protocol_version)
    {
        ar.load<bintoken::token::begin_array>();

        std::size_t count;
        ar.load_override(count, protocol_version);
        if (count != N)
            throw bintoken::error(bintoken::incompatible_type);

        for (std::size_t i = 0; i < N; ++i)
        {
            T value;
            ar >> value;
            data[i] = value;
        }
        if (!ar.at<bintoken::token::end_array>())
            throw bintoken::error(bintoken::expected_end_array);
        ar.load<bintoken::token::end_array>();
    }
};

// Specialization for compact arrays

template <std::size_t N>
struct load_overloader< bintoken::iarchive,
                        std::int8_t[N] >
{
    static void load(bintoken::iarchive& ar,
                     std::int8_t (&data)[N],
                     const unsigned int /* protocol_version */)
    {
        switch (ar.code())
        {
        case bintoken::token::code::array8_int8:
        case bintoken::token::code::array16_int8:
        case bintoken::token::code::array32_int8:
        case bintoken::token::code::array64_int8:
            {
                const auto length = ar.length();
                if (length > N)
                {
                    throw bintoken::error(bintoken::overflow);
                }
                ar.load_array(data, length);
            }
            break;

        default:
            throw bintoken::error(bintoken::incompatible_type);
        }
    }
};

template <std::size_t N>
struct load_overloader< bintoken::iarchive,
                        std::uint8_t[N] >
{
    static void load(bintoken::iarchive& ar,
                     std::uint8_t (&data)[N],
                     const unsigned int /* protocol_version */)
    {
        switch (ar.code())
        {
        case bintoken::token::code::array8_int8:
        case bintoken::token::code::array16_int8:
        case bintoken::token::code::array32_int8:
        case bintoken::token::code::array64_int8:
            {
                const auto length = ar.length();
                if (length > N)
                {
                    throw bintoken::error(bintoken::overflow);
                }
                ar.load_array(data, length);
            }
            break;

        default:
            throw bintoken::error(bintoken::incompatible_type);
        }
    }
};

template <std::size_t N>
struct load_overloader< bintoken::iarchive,
                        std::int16_t[N] >
{
    static void load(bintoken::iarchive& ar,
                     std::int16_t (&data)[N],
                     const unsigned int /* protocol_version */)
    {
        switch (ar.code())
        {
        case bintoken::token::code::array8_int16:
        case bintoken::token::code::array16_int16:
        case bintoken::token::code::array32_int16:
        case bintoken::token::code::array64_int16:
            {
                const auto length = ar.length();
                if (length > N)
                {
                    throw bintoken::error(bintoken::overflow);
                }
                ar.load_array(data, length);
            }
            break;

        default:
            throw bintoken::error(bintoken::incompatible_type);
        }
    }
};

template <std::size_t N>
struct load_overloader< bintoken::iarchive,
                        std::uint16_t[N] >
{
    static void load(bintoken::iarchive& ar,
                     std::uint16_t (&data)[N],
                     const unsigned int /* protocol_version */)
    {
        switch (ar.code())
        {
        case bintoken::token::code::array8_int16:
        case bintoken::token::code::array16_int16:
        case bintoken::token::code::array32_int16:
        case bintoken::token::code::array64_int16:
            {
                const auto length = ar.length();
                if (length > N)
                {
                    throw bintoken::error(bintoken::overflow);
                }
                ar.load_array(data, length);
            }
            break;

        default:
            throw bintoken::error(bintoken::incompatible_type);
        }
    }
};

template <std::size_t N>
struct load_overloader< bintoken::iarchive,
                        std::int32_t[N] >
{
    static void load(bintoken::iarchive& ar,
                     std::int32_t (&data)[N],
                     const unsigned int /* protocol_version */)
    {
        switch (ar.code())
        {
        case bintoken::token::code::array8_int32:
        case bintoken::token::code::array16_int32:
        case bintoken::token::code::array32_int32:
        case bintoken::token::code::array64_int32:
            {
                const auto length = ar.length();
                if (length > N)
                {
                    throw bintoken::error(bintoken::overflow);
                }
                ar.load_array(data, length);
            }
            break;

        default:
            throw bintoken::error(bintoken::incompatible_type);
        }
    }
};

template <std::size_t N>
struct load_overloader< bintoken::iarchive,
                        std::uint32_t[N] >
{
    static void load(bintoken::iarchive& ar,
                     std::uint32_t (&data)[N],
                     const unsigned int /* protocol_version */)
    {
        switch (ar.code())
        {
        case bintoken::token::code::array8_int32:
        case bintoken::token::code::array16_int32:
        case bintoken::token::code::array32_int32:
        case bintoken::token::code::array64_int32:
            {
                const auto length = ar.length();
                if (length > N)
                {
                    throw bintoken::error(bintoken::overflow);
                }
                ar.load_array(data, length);
            }
            break;

        default:
            throw bintoken::error(bintoken::incompatible_type);
        }
    }
};

template <std::size_t N>
struct load_overloader< bintoken::iarchive,
                        std::int64_t[N] >
{
    static void load(bintoken::iarchive& ar,
                     std::int64_t (&data)[N],
                     const unsigned int /* protocol_version */)
    {
        switch (ar.code())
        {
        case bintoken::token::code::array8_int64:
        case bintoken::token::code::array16_int64:
        case bintoken::token::code::array32_int64:
        case bintoken::token::code::array64_int64:
            {
                const auto length = ar.length();
                if (length > N)
                {
                    throw bintoken::error(bintoken::overflow);
                }
                ar.load_array(data, length);
            }
            break;

        default:
            throw bintoken::error(bintoken::incompatible_type);
        }
    }
};

template <std::size_t N>
struct load_overloader< bintoken::iarchive,
                        std::uint64_t[N] >
{
    static void load(bintoken::iarchive& ar,
                     std::uint64_t (&data)[N],
                     const unsigned int /* protocol_version */)
    {
        switch (ar.code())
        {
        case bintoken::token::code::array8_int64:
        case bintoken::token::code::array16_int64:
        case bintoken::token::code::array32_int64:
        case bintoken::token::code::array64_int64:
            {
                const auto length = ar.length();
                if (length > N)
                {
                    throw bintoken::error(bintoken::overflow);
                }
                ar.load_array(data, length);
            }
            break;

        default:
            throw bintoken::error(bintoken::incompatible_type);
        }
    }
};

template <std::size_t N>
struct load_overloader< bintoken::iarchive,
                        bintoken::token::float32::type[N] >
{
    static void load(bintoken::iarchive& ar,
                     bintoken::token::float32::type (&data)[N],
                     const unsigned int /* protocol_version */)
    {
        switch (ar.code())
        {
        case bintoken::token::code::array8_float32:
        case bintoken::token::code::array16_float32:
        case bintoken::token::code::array32_float32:
        case bintoken::token::code::array64_float32:
            {
                const auto length = ar.length();
                if (length > N)
                {
                    throw bintoken::error(bintoken::overflow);
                }
                ar.load_array(data, length);
            }
            break;

        default:
            throw bintoken::error(bintoken::incompatible_type);
        }
    }
};

template <std::size_t N>
struct load_overloader< bintoken::iarchive,
                        bintoken::token::float64::type[N] >
{
    static void load(bintoken::iarchive& ar,
                     bintoken::token::float64::type (&data)[N],
                     const unsigned int /* protocol_version */)
    {
        switch (ar.code())
        {
        case bintoken::token::code::array8_float64:
        case bintoken::token::code::array16_float64:
        case bintoken::token::code::array32_float64:
        case bintoken::token::code::array64_float64:
            {
                const auto length = ar.length();
                if (length > N)
                {
                    throw bintoken::error(bintoken::overflow);
                }
                ar.load_array(data, length);
            }
            break;

        default:
            throw bintoken::error(bintoken::incompatible_type);
        }
    }
};

} // namespace serialization
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_BINTOKEN_SERIALIZATION_DETAIL_ARRAY_LOAD_HPP
