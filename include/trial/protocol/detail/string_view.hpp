#ifndef TRIAL_PROTOCOL_DETAIL_STRING_VIEW_HPP
#define TRIAL_PROTOCOL_DETAIL_STRING_VIEW_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright © 2017 Vinícius dos Santos Oliveira <vini.ipsmaker@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <boost/version.hpp>

#if BOOST_VERSION < 106100
#include <boost/utility/string_ref.hpp>
#else
#include <boost/utility/string_view.hpp>
#endif

namespace trial
{
namespace protocol
{
namespace detail
{

#if BOOST_VERSION < 106100
template<class T>
using basic_string_view = boost::basic_string_ref<T>;
#else
template<class T>
using basic_string_view = boost::basic_string_view<T>;
#endif

using string_view = basic_string_view<char>;

} // namespace detail
} // namespace protocol
} // namespace trial


#endif // TRIAL_PROTOCOL_DETAIL_STRING_VIEW_HPP
