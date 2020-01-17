#ifndef TRIAL_PROTOCOL_CORE_DETAIL_CONFIG_HPP
#define TRIAL_PROTOCOL_CORE_DETAIL_CONFIG_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2020 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#if !defined(TRIAL_LIKELY)
# if defined(__GNUC__) || defined(__clang__)
#  define TRIAL_LIKELY(x) __builtin_expect(bool(x), 1)
#  else
#  define TRIAL_LIKELY(x) x
# endif
#endif

#endif // TRIAL_PROTOCOL_CORE_DETAIL_CONFIG_HPP
