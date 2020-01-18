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
# if __cplusplus >= 201803L
#  define TRIAL_LIKELY(x) [[likely]] (x)
#  define TRIAL_UNLIKELY(x) [[unlikely]] (x)
# elif defined(__GNUC__) || defined(__clang__)
#  define TRIAL_LIKELY(x) __builtin_expect(bool(x), 1)
#  define TRIAL_UNLIKELY(x) __builtin_expect(bool(x), 0)
# else
#  define TRIAL_LIKELY(x) x
#  define TRIAL_UNLIKELY(x) x
# endif
#endif

#endif // TRIAL_PROTOCOL_CORE_DETAIL_CONFIG_HPP
