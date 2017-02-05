#ifndef TRIAL_PROTOCOL_BUFFER_OSTREAM_HPP
#define TRIAL_PROTOCOL_BUFFER_OSTREAM_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2015 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <ostream>
#include <type_traits>
#include <trial/protocol/buffer/base.hpp>

namespace trial
{
namespace protocol
{
namespace buffer
{

template <typename CharT, typename Super = base<CharT> >
class basic_ostream : public Super
{
public:
    using value_type = typename Super::value_type;
    using size_type = typename Super::size_type;
    using view_type = typename Super::view_type;

    basic_ostream(std::basic_ostream<CharT>& stream) : content(stream) {}

protected:
    virtual bool grow(size_type)
    {
        return content.good();
    }

    virtual void write(value_type value)
    {
        content << value;
    }

    virtual void write(const view_type& view)
    {
        content << view;
    }

private:
    std::basic_ostream<CharT>& content;
};

// Specialization for basic_ostream
template <template <typename, typename> class T,
          typename CharT,
          typename Traits>
struct traits<T<CharT, Traits>,
              typename std::enable_if< std::is_base_of<std::basic_ostream<CharT, Traits>,
                                                       T<CharT, Traits> >::value >::type>
{
    using buffer_type = buffer::basic_ostream<CharT>;
};

// Specialization for C++11 basic_ostringstream with allocator
template <template <typename, typename, typename> class T,
          typename CharT,
          typename Traits,
          typename Allocator>
struct traits<T<CharT, Traits, Allocator>,
              typename std::enable_if< std::is_base_of<std::basic_ostream<CharT, Traits>,
                                                       T<CharT, Traits, Allocator> >::value >::type>
{
    using buffer_type = buffer::basic_ostream<CharT>;
};

} // namespace buffer
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_BUFFER_OSTREAM_HPP
