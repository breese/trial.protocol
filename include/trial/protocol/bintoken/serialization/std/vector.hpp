#ifndef TRIAL_PROTOCOL_BINTOKEN_SERIALIZATION_STD_VECTOR_HPP
#define TRIAL_PROTOCOL_BINTOKEN_SERIALIZATION_STD_VECTOR_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2015 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <trial/protocol/bintoken/serialization/serialization.hpp>
#include <trial/protocol/bintoken/serialization/boost/optional.hpp>
#include <trial/protocol/core/serialization/std/vector.hpp>

namespace trial
{
namespace protocol
{
namespace serialization
{

template <typename T, typename Allocator>
struct save_overloader< bintoken::oarchive,
                        typename std::vector<T, Allocator> >
{
    static void save(bintoken::oarchive& ar,
                     const std::vector<T, Allocator>& data,
                     const unsigned int protocol_version)
    {
        ar.save<bintoken::token::begin_array>();
        ar.save<std::size_t>(data.size());
        for (typename std::vector<T, Allocator>::const_iterator it = data.begin();
             it != data.end();
             ++it)
        {
            ar.save_override(*it, protocol_version);
        }
        ar.save<bintoken::token::end_array>();
    }
};

template <typename T, typename Allocator>
struct load_overloader< bintoken::iarchive,
                        typename std::vector<T, Allocator> >
{
    static void load(bintoken::iarchive& ar,
                     std::vector<T, Allocator>& data,
                     const unsigned int protocol_version)
    {
        ar.load<bintoken::token::begin_array>();

        boost::optional<std::size_t> count;
        ar.load_override(count, protocol_version);
        if (count)
        {
            data.reserve(*count);
        }

        while (!ar.at<bintoken::token::end_array>())
        {
            T value;
            ar >> value;
            data.push_back(value);
        }
        ar.load<bintoken::token::end_array>();
    }
};

// Specialization for compact arrays

template <typename Allocator>
struct save_overloader< bintoken::oarchive,
                        typename std::vector<std::int8_t, Allocator> >
{
    static void save(bintoken::oarchive& ar,
                     const std::vector<std::int8_t, Allocator>& data,
                     const unsigned int /* protocol_version */)
    {
        ar.save_array(data.data(), data.size());
    }
};

template <typename Allocator>
struct load_overloader< bintoken::iarchive,
                        typename std::vector<std::int8_t, Allocator> >
{
    static void load(bintoken::iarchive& ar,
                     std::vector<std::int8_t, Allocator>& data,
                     const unsigned int /* protocol_version */)
    {
        switch (ar.code())
        {
        case bintoken::token::code::array8_int8:
        case bintoken::token::code::array16_int8:
        case bintoken::token::code::array32_int8:
        case bintoken::token::code::array64_int8:
            data.assign(ar.length(), {});
            ar.load_array(data.data(), data.size());
            break;

        default:
            throw bintoken::error(bintoken::incompatible_type);
        }
    }
};

template <typename Allocator>
struct save_overloader< bintoken::oarchive,
                        typename std::vector<std::uint8_t, Allocator> >
{
    static void save(bintoken::oarchive& ar,
                     const std::vector<std::uint8_t, Allocator>& data,
                     const unsigned int /* protocol_version */)
    {
        ar.save_array(reinterpret_cast<const std::int8_t *>(data.data()),
                      data.size());
    }
};

template <typename Allocator>
struct load_overloader< bintoken::iarchive,
                        typename std::vector<std::uint8_t, Allocator> >
{
    static void load(bintoken::iarchive& ar,
                     std::vector<std::uint8_t, Allocator>& data,
                     const unsigned int /* protocol_version */)
    {
        switch (ar.code())
        {
        case bintoken::token::code::array8_int8:
        case bintoken::token::code::array16_int8:
        case bintoken::token::code::array32_int8:
        case bintoken::token::code::array64_int8:
            data.assign(ar.length(), {});
            ar.load_array(data.data(), data.size());
            break;

        default:
            throw bintoken::error(bintoken::incompatible_type);
        }
    }
};

template <typename Allocator>
struct save_overloader< bintoken::oarchive,
                        typename std::vector<std::int16_t, Allocator> >
{
    static void save(bintoken::oarchive& ar,
                     const std::vector<std::int16_t, Allocator>& data,
                     const unsigned int /* protocol_version */)
    {
        ar.save_array(data.data(), data.size());
    }
};

template <typename Allocator>
struct load_overloader< bintoken::iarchive,
                        typename std::vector<std::int16_t, Allocator> >
{
    static void load(bintoken::iarchive& ar,
                     std::vector<std::int16_t, Allocator>& data,
                     const unsigned int /* protocol_version */)
    {
        switch (ar.code())
        {
        case bintoken::token::code::array8_int16:
        case bintoken::token::code::array16_int16:
        case bintoken::token::code::array32_int16:
        case bintoken::token::code::array64_int16:
            data.assign(ar.length(), {});
            ar.load_array(data.data(), data.size());
            break;

        default:
            throw bintoken::error(bintoken::incompatible_type);
        }
    }
};

template <typename Allocator>
struct save_overloader< bintoken::oarchive,
                        typename std::vector<std::uint16_t, Allocator> >
{
    static void save(bintoken::oarchive& ar,
                     const std::vector<std::uint16_t, Allocator>& data,
                     const unsigned int /* protocol_version */)
    {
        ar.save_array(reinterpret_cast<const std::int16_t *>(data.data()),
                      data.size());
    }
};

template <typename Allocator>
struct load_overloader< bintoken::iarchive,
                        typename std::vector<std::uint16_t, Allocator> >
{
    static void load(bintoken::iarchive& ar,
                     std::vector<std::uint16_t, Allocator>& data,
                     const unsigned int /* protocol_version */)
    {
        switch (ar.code())
        {
        case bintoken::token::code::array8_int16:
        case bintoken::token::code::array16_int16:
        case bintoken::token::code::array32_int16:
        case bintoken::token::code::array64_int16:
            data.assign(ar.length(), {});
            ar.load_array(data.data(), data.size());
            break;

        default:
            throw bintoken::error(bintoken::incompatible_type);
        }
    }
};

template <typename Allocator>
struct save_overloader< bintoken::oarchive,
                        typename std::vector<std::int32_t, Allocator> >
{
    static void save(bintoken::oarchive& ar,
                     const std::vector<std::int32_t, Allocator>& data,
                     const unsigned int /* protocol_version */)
    {
        ar.save_array(data.data(), data.size());
    }
};

template <typename Allocator>
struct load_overloader< bintoken::iarchive,
                        typename std::vector<std::int32_t, Allocator> >
{
    static void load(bintoken::iarchive& ar,
                     std::vector<std::int32_t, Allocator>& data,
                     const unsigned int /* protocol_version */)
    {
        switch (ar.code())
        {
        case bintoken::token::code::array8_int32:
        case bintoken::token::code::array16_int32:
        case bintoken::token::code::array32_int32:
        case bintoken::token::code::array64_int32:
            data.assign(ar.length(), {});
            ar.load_array(data.data(), data.size());
            break;

        default:
            throw bintoken::error(bintoken::incompatible_type);
        }
    }
};

template <typename Allocator>
struct save_overloader< bintoken::oarchive,
                        typename std::vector<std::uint32_t, Allocator> >
{
    static void save(bintoken::oarchive& ar,
                     const std::vector<std::uint32_t, Allocator>& data,
                     const unsigned int /* protocol_version */)
    {
        ar.save_array(reinterpret_cast<const std::int32_t *>(data.data()),
                      data.size());
    }
};

template <typename Allocator>
struct load_overloader< bintoken::iarchive,
                        typename std::vector<std::uint32_t, Allocator> >
{
    static void load(bintoken::iarchive& ar,
                     std::vector<std::uint32_t, Allocator>& data,
                     const unsigned int /* protocol_version */)
    {
        switch (ar.code())
        {
        case bintoken::token::code::array8_int32:
        case bintoken::token::code::array16_int32:
        case bintoken::token::code::array32_int32:
        case bintoken::token::code::array64_int32:
            data.assign(ar.length(), {});
            ar.load_array(data.data(), data.size());
            break;

        default:
            throw bintoken::error(bintoken::incompatible_type);
        }
    }
};

template <typename Allocator>
struct save_overloader< bintoken::oarchive,
                        typename std::vector<std::int64_t, Allocator> >
{
    static void save(bintoken::oarchive& ar,
                     const std::vector<std::int64_t, Allocator>& data,
                     const unsigned int /* protocol_version */)
    {
        ar.save_array(data.data(), data.size());
    }
};

template <typename Allocator>
struct load_overloader< bintoken::iarchive,
                        typename std::vector<std::int64_t, Allocator> >
{
    static void load(bintoken::iarchive& ar,
                     std::vector<std::int64_t, Allocator>& data,
                     const unsigned int /* protocol_version */)
    {
        switch (ar.code())
        {
        case bintoken::token::code::array8_int64:
        case bintoken::token::code::array16_int64:
        case bintoken::token::code::array32_int64:
        case bintoken::token::code::array64_int64:
            data.assign(ar.length(), {});
            ar.load_array(data.data(), data.size());
            break;

        default:
            throw bintoken::error(bintoken::incompatible_type);
        }
    }
};

template <typename Allocator>
struct save_overloader< bintoken::oarchive,
                        typename std::vector<std::uint64_t, Allocator> >
{
    static void save(bintoken::oarchive& ar,
                     const std::vector<std::uint64_t, Allocator>& data,
                     const unsigned int /* protocol_version */)
    {
        ar.save_array(reinterpret_cast<const std::int64_t *>(data.data()),
                      data.size());
    }
};

template <typename Allocator>
struct load_overloader< bintoken::iarchive,
                        typename std::vector<std::uint64_t, Allocator> >
{
    static void load(bintoken::iarchive& ar,
                     std::vector<std::uint64_t, Allocator>& data,
                     const unsigned int /* protocol_version */)
    {
        switch (ar.code())
        {
        case bintoken::token::code::array8_int64:
        case bintoken::token::code::array16_int64:
        case bintoken::token::code::array32_int64:
        case bintoken::token::code::array64_int64:
            data.assign(ar.length(), {});
            ar.load_array(data.data(), data.size());
            break;

        default:
            throw bintoken::error(bintoken::incompatible_type);
        }
    }
};

template <typename Allocator>
struct save_overloader< bintoken::oarchive,
                        typename std::vector<typename bintoken::token::float32::type, Allocator> >
{
    static void save(bintoken::oarchive& ar,
                     const std::vector<typename bintoken::token::float32::type, Allocator>& data,
                     const unsigned int /* protocol_version */)
    {
        ar.save_array(data.data(), data.size());
    }
};

template <typename Allocator>
struct load_overloader< bintoken::iarchive,
                        typename std::vector<bintoken::token::float32::type, Allocator> >
{
    static void load(bintoken::iarchive& ar,
                     std::vector<bintoken::token::float32::type, Allocator>& data,
                     const unsigned int /* protocol_version */)
    {
        switch (ar.code())
        {
        case bintoken::token::code::array8_float32:
        case bintoken::token::code::array16_float32:
        case bintoken::token::code::array32_float32:
        case bintoken::token::code::array64_float32:
            data.assign(ar.length(), {});
            ar.load_array(data.data(), data.size());
            break;

        default:
            throw bintoken::error(bintoken::incompatible_type);
        }
    }
};

template <typename Allocator>
struct save_overloader< bintoken::oarchive,
                        typename std::vector<typename bintoken::token::float64::type, Allocator> >
{
    static void save(bintoken::oarchive& ar,
                     const std::vector<typename bintoken::token::float64::type, Allocator>& data,
                     const unsigned int /* protocol_version */)
    {
        ar.save_array(data.data(), data.size());
    }
};

template <typename Allocator>
struct load_overloader< bintoken::iarchive,
                        typename std::vector<bintoken::token::float64::type, Allocator> >
{
    static void load(bintoken::iarchive& ar,
                     std::vector<bintoken::token::float64::type, Allocator>& data,
                     const unsigned int /* protocol_version */)
    {
        switch (ar.code())
        {
        case bintoken::token::code::array8_float64:
        case bintoken::token::code::array16_float64:
        case bintoken::token::code::array32_float64:
        case bintoken::token::code::array64_float64:
            data.assign(ar.length(), {});
            ar.load_array(data.data(), data.size());
            break;

        default:
            throw bintoken::error(bintoken::incompatible_type);
        }
    }
};

// Specialization for std::vector<bool>

template <typename Allocator>
struct save_overloader< bintoken::oarchive,
                        typename std::vector<bool, Allocator> >
{
    static void save(bintoken::oarchive& ar,
                     const std::vector<bool, Allocator>& data,
                     const unsigned int protocol_version)
    {
        ar.save<bintoken::token::begin_array>();
        ar.save<std::size_t>(data.size());
        for (typename std::vector<bool, Allocator>::const_iterator it = data.begin();
             it != data.end();
             ++it)
        {
            bool value = *it;
            ar.save_override(value, protocol_version);
        }
        ar.save<bintoken::token::end_array>();
    }
};

} // namespace serialization
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_BINTOKEN_SERIALIZATION_STD_VECTOR_HPP
