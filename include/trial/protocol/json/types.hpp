#ifndef TRIAL_PROTOCOL_JSON_TYPES_HPP
#define TRIAL_PROTOCOL_JSON_TYPES_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2015 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

namespace trial
{
namespace protocol
{
namespace json
{

struct null_t {};
const null_t null = null_t();

struct array_open_t {};
const array_open_t array_open = array_open_t();
struct array_close_t {};
const array_close_t array_close = array_close_t();

struct object_open_t {};
const object_open_t object_open = object_open_t();
struct object_close_t {};
const object_close_t object_close = object_close_t();

} // namespace json
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_JSON_TYPES_HPP
