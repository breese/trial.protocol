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

#if !defined(TRIAL_PROTOCOL_USE_BOOST_STRING_REF)
# if BOOST_VERSION < 106100
#  define TRIAL_PROTOCOL_USE_BOOST_STRING_REF 1
# endif
#endif

#if TRIAL_PROTOCOL_USE_BOOST_STRING_REF
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

#if TRIAL_PROTOCOL_USE_BOOST_STRING_REF
template<class CharT, typename Traits = std::char_traits<CharT>>
using basic_string_view = boost::basic_string_ref<CharT, Traits>;
#else
template<class CharT, typename Traits = std::char_traits<CharT>>
using basic_string_view = boost::basic_string_view<CharT, Traits>;
#endif

using string_view = basic_string_view<char>;

} // namespace detail
} // namespace protocol
} // namespace trial


#endif // TRIAL_PROTOCOL_DETAIL_STRING_VIEW_HPP
