#ifndef TRIAL_PROTOCOL_BINTOKEN_DETAIL_FORMAT_IPP
#define TRIAL_PROTOCOL_BINTOKEN_DETAIL_FORMAT_IPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2018 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <trial/protocol/bintoken/error.hpp>
#include <trial/protocol/bintoken/writer.hpp>

namespace trial
{
namespace protocol
{
namespace bintoken
{
namespace detail
{

template <template <typename> class Allocator>
struct basic_formatter
{
    using variable_type = trial::dynamic::basic_variable<Allocator>;

    basic_formatter(bintoken::writer& writer)
        : writer(writer)
    {}

    template <typename T>
    void operator()(const T& value)
    {
        writer.value(value);
    }

    void operator()(const trial::dynamic::nullable&)
    {
        writer.template value<bintoken::token::null>();
    }

    void operator()(const long double&)
    {
        throw bintoken::error(bintoken::incompatible_type);
    }

    void operator()(const typename variable_type::wstring_type&)
    {
        throw bintoken::error(bintoken::incompatible_type);
    }

    void operator()(const typename variable_type::u16string_type&)
    {
        throw bintoken::error(bintoken::incompatible_type);
    }

    void operator()(const typename variable_type::u32string_type&)
    {
        throw bintoken::error(bintoken::incompatible_type);
    }

    void operator()(const typename variable_type::array_type& array)
    {
        writer.template value<bintoken::token::begin_array>();
        for (const auto& item : array)
        {
            trial::dynamic::visit(*this, item);
        }
        writer.template value<bintoken::token::end_array>();
    }

    void operator()(const typename variable_type::map_type& map)
    {
        writer.template value<bintoken::token::begin_assoc_array>();
        for (const auto& item : map)
        {
            trial::dynamic::visit(*this, item.first);
            trial::dynamic::visit(*this, item.second);
        }
        writer.template value<bintoken::token::end_assoc_array>();
    }

    bintoken::writer& writer;
};

} // namespace detail
} // namespace bintoken
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_BINTOKEN_DETAIL_FORMAT_IPP
