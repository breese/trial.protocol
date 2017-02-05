#ifndef TRIAL_PROTOCOL_BUFFER_STRING_HPP
#define TRIAL_PROTOCOL_BUFFER_STRING_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2015 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <string>
#include <type_traits>
#include <trial/protocol/buffer/base.hpp>

namespace trial
{
namespace protocol
{
namespace buffer
{

template <typename CharT, typename Super = base<CharT> >
class basic_string : public Super
{
public:
    using value_type = typename Super::value_type;
    using size_type = typename Super::size_type;
    using view_type = typename Super::view_type;

    basic_string(std::basic_string<CharT>& output)
        : content(output)
    {
    }

protected:
    virtual bool grow(size_type delta)
    {
        const size_type size = content.size() + delta + 1;
        if (size > content.capacity())
        {
            if (size > content.max_size())
                return false;
            content.reserve(size);
        }
        return true;
    }

    virtual void write(value_type value)
    {
        content.push_back(value);
    }

    virtual void write(const view_type& view)
    {
        content.append(view.begin(), view.size());
    }

private:
    std::basic_string<CharT>& content;
};

template <typename CharT>
struct traits< std::basic_string<CharT> >
{
    using buffer_type = buffer::basic_string<CharT>;
};

template <typename T>
struct is_text<T,
               typename std::enable_if< std::is_same<typename std::decay<T>::type,
                                                     char *>::value >::type>
{
    static const bool value = true;
};

template <typename T>
struct is_text<T,
               typename std::enable_if< std::is_same<typename std::decay<T>::type,
                                                     const char *>::value >::type>
{
    static const bool value = true;
};

} // namespace buffer
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_BUFFER_STRING_HPP
