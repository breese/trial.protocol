#ifndef TRIAL_PROTOCOL_CORE_DETAIL_STRING_VIEW_HPP
#define TRIAL_PROTOCOL_CORE_DETAIL_STRING_VIEW_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright © 2017 Vinícius dos Santos Oliveira <vini.ipsmaker@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#if __cpp_lib_string_view >= 201606L

#define TRIAL_PROTOCOL_USE_STD_STRING_VIEW 1

#else

#include <boost/version.hpp>

# if !defined(TRIAL_PROTOCOL_USE_BOOST_STRING_REF)
#  if BOOST_VERSION < 106200
#   define TRIAL_PROTOCOL_USE_BOOST_STRING_REF 1
#  endif
# endif

#endif

#if TRIAL_PROTOCOL_USE_STD_STRING_VIEW
# include <string_view>
# include <cstring>
#elif TRIAL_PROTOCOL_USE_BOOST_STRING_REF
# include <boost/utility/string_ref.hpp>
#else
 #include <boost/utility/string_view.hpp>
#endif

namespace trial
{
namespace protocol
{
namespace core
{
namespace detail
{

#if TRIAL_PROTOCOL_USE_STD_STRING_VIEW
template<class CharT, typename Traits = std::char_traits<CharT>>
using basic_string_view = std::basic_string_view<CharT, Traits>;
#elif TRIAL_PROTOCOL_USE_BOOST_STRING_REF
template<class CharT, typename Traits = std::char_traits<CharT>>
using basic_string_view = boost::basic_string_ref<CharT, Traits>;
#else
template<class CharT, typename Traits = std::char_traits<CharT>>
using basic_string_view = boost::basic_string_view<CharT, Traits>;
#endif

using string_view = basic_string_view<char>;

} // namespace core
} // namespace detail
} // namespace protocol
} // namespace trial


#endif // TRIAL_PROTOCOL_CORE_DETAIL_STRING_VIEW_HPP
