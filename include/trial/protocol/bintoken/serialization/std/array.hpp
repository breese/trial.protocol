#ifndef TRIAL_PROTOCOL_BINTOKEN_SERIALIZATION_STD_ARRAY_HPP
#define TRIAL_PROTOCOL_BINTOKEN_SERIALIZATION_STD_ARRAY_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2017 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <trial/protocol/bintoken/serialization/serialization.hpp>
#include <trial/protocol/serialization/std/array.hpp>

//-----------------------------------------------------------------------------
// By-pass Boost.Serialization which has its own std::array specialization
//-----------------------------------------------------------------------------

namespace boost
{
namespace serialization
{

template <typename T, std::size_t N>
void save(trial::protocol::bintoken::oarchive& ar,
          const std::array<T, N>& data,
          const unsigned int version)
{
    using namespace trial::protocol::serialization;
    save_overloader<trial::protocol::bintoken::oarchive, std::array<T, N>>::
        save(ar, data, version);
}

template <typename T, std::size_t N>
void serialize(trial::protocol::bintoken::oarchive& ar,
               const std::array<T, N>& data,
               const unsigned int version)
{
    using namespace trial::protocol::serialization;
    serialize_overloader<trial::protocol::bintoken::oarchive, std::array<T, N>>::
        serialize(ar, data, version);
}

template <typename T, std::size_t N>
void serialize(trial::protocol::bintoken::oarchive& ar,
               std::array<T, N>& data,
               const unsigned int version)
{
    using namespace trial::protocol::serialization;
    serialize_overloader<trial::protocol::bintoken::oarchive, std::array<T, N>>::
        serialize(ar, data, version);
}

template <typename T, std::size_t N>
void load(trial::protocol::bintoken::iarchive& ar,
          std::array<T, N>& data,
          const unsigned int version)
{
    using namespace trial::protocol::serialization;
    load_overloader<trial::protocol::bintoken::iarchive, std::array<T, N>>::
        load(ar, data, version);
}

template <typename T, std::size_t N>
void serialize(trial::protocol::bintoken::iarchive& ar,
               std::array<T, N>& data,
               const unsigned int version)
{
    using namespace trial::protocol::serialization;
    serialize_overloader<trial::protocol::bintoken::iarchive, std::array<T, N>>::
        serialize(ar, data, version);
}

} // namespace serialization
} // namespace boost

//-----------------------------------------------------------------------------
// std::array
//-----------------------------------------------------------------------------

namespace trial
{
namespace protocol
{
namespace serialization
{

template <typename T, std::size_t N>
struct save_overloader< protocol::bintoken::oarchive,
                        typename std::array<T, N> >
{
    static void save(protocol::bintoken::oarchive& ar,
                     const std::array<T, N>& data,
                     const unsigned int protocol_version)
    {
        ar.save<bintoken::token::begin_array>();
        ar.save<std::size_t>(N);
        for (std::size_t i = 0; i < N; ++i)
        {
            ar.save_override(data[i], protocol_version);
        }
        ar.save<bintoken::token::end_array>();
    }
};

template <typename T, std::size_t N>
struct load_overloader< protocol::bintoken::iarchive,
                        typename std::array<T, N> >
{
    static void load(protocol::bintoken::iarchive& ar,
                     std::array<T, N>& data,
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
struct save_overloader< protocol::bintoken::oarchive,
                        typename std::array<std::int8_t, N> >
{
    static void save(protocol::bintoken::oarchive& ar,
                     const std::array<std::int8_t, N>& data,
                     const unsigned int /* protocol_version */)
    {
        ar.save_array(data.data(), data.size());
    }
};

template <std::size_t N>
struct load_overloader< bintoken::iarchive,
                        std::array<std::int8_t, N> >
{
    static void load(bintoken::iarchive& ar,
                     std::array<std::int8_t, N>& data,
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
                ar.load_array(data.data(), length);
            }
            break;

        default:
            throw bintoken::error(bintoken::incompatible_type);
        }
    }
};

template <std::size_t N>
struct save_overloader< protocol::bintoken::oarchive,
                        typename std::array<std::uint8_t, N> >
{
    static void save(protocol::bintoken::oarchive& ar,
                     const std::array<std::uint8_t, N>& data,
                     const unsigned int /* protocol_version */)
    {
        ar.save_array(data.data(), data.size());
    }
};

template <std::size_t N>
struct load_overloader< bintoken::iarchive,
                        std::array<std::uint8_t, N> >
{
    static void load(bintoken::iarchive& ar,
                     std::array<std::uint8_t, N>& data,
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
                ar.load_array(data.data(), length);
            }
            break;

        default:
            throw bintoken::error(bintoken::incompatible_type);
        }
    }
};

template <std::size_t N>
struct save_overloader< protocol::bintoken::oarchive,
                        typename std::array<std::int16_t, N> >
{
    static void save(protocol::bintoken::oarchive& ar,
                     const std::array<std::int16_t, N>& data,
                     const unsigned int /* protocol_version */)
    {
        ar.save_array(data.data(), data.size());
    }
};

template <std::size_t N>
struct load_overloader< bintoken::iarchive,
                        std::array<std::int16_t, N> >
{
    static void load(bintoken::iarchive& ar,
                     std::array<std::int16_t, N>& data,
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
                ar.load_array(data.data(), length);
            }
            break;

        default:
            throw bintoken::error(bintoken::incompatible_type);
        }
    }
};

template <std::size_t N>
struct save_overloader< protocol::bintoken::oarchive,
                        typename std::array<std::uint16_t, N> >
{
    static void save(protocol::bintoken::oarchive& ar,
                     const std::array<std::uint16_t, N>& data,
                     const unsigned int /* protocol_version */)
    {
        ar.save_array(data.data(), data.size());
    }
};

template <std::size_t N>
struct load_overloader< bintoken::iarchive,
                        std::array<std::uint16_t, N> >
{
    static void load(bintoken::iarchive& ar,
                     std::array<std::uint16_t, N>& data,
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
                ar.load_array(data.data(), length);
            }
            break;

        default:
            throw bintoken::error(bintoken::incompatible_type);
        }
    }
};

template <std::size_t N>
struct save_overloader< protocol::bintoken::oarchive,
                        typename std::array<std::int32_t, N> >
{
    static void save(protocol::bintoken::oarchive& ar,
                     const std::array<std::int32_t, N>& data,
                     const unsigned int /* protocol_version */)
    {
        ar.save_array(data.data(), data.size());
    }
};

template <std::size_t N>
struct load_overloader< bintoken::iarchive,
                        std::array<std::int32_t, N> >
{
    static void load(bintoken::iarchive& ar,
                     std::array<std::int32_t, N>& data,
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
                ar.load_array(data.data(), length);
            }
            break;

        default:
            throw bintoken::error(bintoken::incompatible_type);
        }
    }
};

template <std::size_t N>
struct save_overloader< protocol::bintoken::oarchive,
                        typename std::array<std::uint32_t, N> >
{
    static void save(protocol::bintoken::oarchive& ar,
                     const std::array<std::uint32_t, N>& data,
                     const unsigned int /* protocol_version */)
    {
        ar.save_array(data.data(), data.size());
    }
};

template <std::size_t N>
struct load_overloader< bintoken::iarchive,
                        std::array<std::uint32_t, N> >
{
    static void load(bintoken::iarchive& ar,
                     std::array<std::uint32_t, N>& data,
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
                ar.load_array(data.data(), length);
            }
            break;

        default:
            throw bintoken::error(bintoken::incompatible_type);
        }
    }
};

template <std::size_t N>
struct save_overloader< protocol::bintoken::oarchive,
                        typename std::array<std::int64_t, N> >
{
    static void save(protocol::bintoken::oarchive& ar,
                     const std::array<std::int64_t, N>& data,
                     const unsigned int /* protocol_version */)
    {
        ar.save_array(data.data(), data.size());
    }
};

template <std::size_t N>
struct load_overloader< bintoken::iarchive,
                        std::array<std::int64_t, N> >
{
    static void load(bintoken::iarchive& ar,
                     std::array<std::int64_t, N>& data,
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
                ar.load_array(data.data(), length);
            }
            break;

        default:
            throw bintoken::error(bintoken::incompatible_type);
        }
    }
};

template <std::size_t N>
struct save_overloader< protocol::bintoken::oarchive,
                        typename std::array<std::uint64_t, N> >
{
    static void save(protocol::bintoken::oarchive& ar,
                     const std::array<std::uint64_t, N>& data,
                     const unsigned int /* protocol_version */)
    {
        ar.save_array(data.data(), data.size());
    }
};

template <std::size_t N>
struct load_overloader< bintoken::iarchive,
                        std::array<std::uint64_t, N> >
{
    static void load(bintoken::iarchive& ar,
                     std::array<std::uint64_t, N>& data,
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
                ar.load_array(data.data(), length);
            }
            break;

        default:
            throw bintoken::error(bintoken::incompatible_type);
        }
    }
};

template <std::size_t N>
struct save_overloader< protocol::bintoken::oarchive,
                        typename std::array<bintoken::token::float32::type, N> >
{
    static void save(protocol::bintoken::oarchive& ar,
                     const std::array<bintoken::token::float32::type, N>& data,
                     const unsigned int /* protocol_version */)
    {
        ar.save_array(data.data(), data.size());
    }
};

template <std::size_t N>
struct load_overloader< bintoken::iarchive,
                        std::array<bintoken::token::float32::type, N> >
{
    static void load(bintoken::iarchive& ar,
                     std::array<bintoken::token::float32::type, N>& data,
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
                ar.load_array(data.data(), length);
            }
            break;

        default:
            throw bintoken::error(bintoken::incompatible_type);
        }
    }
};

template <std::size_t N>
struct save_overloader< protocol::bintoken::oarchive,
                        typename std::array<bintoken::token::float64::type, N> >
{
    static void save(protocol::bintoken::oarchive& ar,
                     const std::array<bintoken::token::float64::type, N>& data,
                     const unsigned int /* protocol_version */)
    {
        ar.save_array(data.data(), data.size());
    }
};

template <std::size_t N>
struct load_overloader< bintoken::iarchive,
                        std::array<bintoken::token::float64::type, N> >
{
    static void load(bintoken::iarchive& ar,
                     std::array<bintoken::token::float64::type, N>& data,
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
                ar.load_array(data.data(), length);
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

#endif // TRIAL_PROTOCOL_BINTOKEN_SERIALIZATION_STD_ARRAY_HPP
