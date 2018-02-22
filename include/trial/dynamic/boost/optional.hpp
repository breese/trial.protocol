#ifndef TRIAL_DYNAMIC_BOOST_OPTIONAL_HPP
#define TRIAL_DYNAMIC_BOOST_OPTIONAL_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2018 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <boost/optional/optional.hpp>
#include <trial/dynamic/variable.hpp>
#include <trial/dynamic/convert.hpp>

namespace trial
{
namespace dynamic
{
namespace detail
{

template <template <typename> class Allocator, typename T>
struct convert_overloader<basic_variable<Allocator>,
                          boost::optional<T>>
{
    using variable_type = basic_variable<Allocator>;

    static variable_type convert(const boost::optional<T>& value,
                                 std::error_code&)
    {
        if (!value)
            return dynamic::null;

        return *value;
    }
};

template <template <typename> class Allocator, typename T>
struct convert_overloader<boost::optional<T>,
                          basic_variable<Allocator>>
{
    using variable_type = basic_variable<Allocator>;

    static boost::optional<T> convert(const basic_variable<Allocator>& data,
                                      std::error_code& error)
    {
        error.clear();

        if (data.template is<nullable>())
            return boost::none;

        if (data.template is<T>())
            return data.template value<T>();

        error = dynamic::make_error_code(incompatible_type);
        return {};
    }
};

} // namespace detail
} // namespace dynamic
} // namespace trial

#endif // TRIAL_DYNAMIC_BOOST_OPTIONAL_HPP
