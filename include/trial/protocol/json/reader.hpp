#ifndef TRIAL_PROTOCOL_JSON_READER_HPP
#define TRIAL_PROTOCOL_JSON_READER_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2015 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <cstddef> // std::size_t
#include <string>
#include <stack>
#include <boost/config.hpp>
#include <boost/utility/string_ref.hpp>
#include <trial/protocol/json/error.hpp>
#include <trial/protocol/json/token.hpp>
#include <trial/protocol/json/detail/decoder.hpp>

namespace trial
{
namespace protocol
{
namespace json
{

namespace detail { template <typename C, typename T, typename Enable> struct basic_reader_functor; }

template <typename CharT>
class basic_reader
{
public:
    typedef std::size_t size_type;
    typedef const CharT value_type;
    typedef value_type * pointer;
    typedef typename detail::basic_decoder<CharT>::view_type view_type;

    template <typename ForwardIterator>
    basic_reader(ForwardIterator begin, ForwardIterator end);
    basic_reader(const view_type&);
    basic_reader(const basic_reader&);

    //! @brief Advance to the next token.
    bool next();

    //! @brief Advance to the next token if current token has a given value.
    //! @param[in] expect Expected value of current token.
    //! @throws system_error If current token does not have the expected value.
    bool next(token::value expect);

    bool next_sibling();

    //! @brief Returns the current nesting level.
    size_type level() const BOOST_NOEXCEPT;

    //! @brief Return the current token.
    token::value type() const BOOST_NOEXCEPT;

    //! @brief Returns the last error code.
    boost::system::error_code error() const BOOST_NOEXCEPT;

    //! @brief Return the current value.
    //! @throws system_error If requested type is incompatible with the current token.
    template <typename ReturnType> ReturnType value() const;

    //! @brief Return a view of the current value before it is converted into its type.
    const view_type& literal() const BOOST_NOEXCEPT;

private:
    template <typename C, typename T, typename Enable> friend struct detail::basic_reader_functor;

    detail::basic_decoder<CharT> decoder;
    mutable enum json::errc last_error;

    struct frame
    {
        frame(token::value);

        bool is_array() const;
        bool is_object() const;

        enum json::errc next(detail::basic_decoder<CharT>&);
        enum json::errc check_outer(detail::basic_decoder<CharT>&);
        enum json::errc check_array(detail::basic_decoder<CharT>&);
        enum json::errc check_object(detail::basic_decoder<CharT>&);

        token::value scope;
        std::size_t counter;
    };
    std::stack<frame> stack;
};

} // namespace json
} // namespace protocol
} // namespace trial

#include <trial/protocol/json/detail/reader.ipp>

// Specializations

namespace trial
{
namespace protocol
{
namespace json
{

typedef basic_reader<char> reader;

} // namespace json
} // namespace protocol
} // namespace trial

namespace boost
{
template<typename ReturnType>
inline ReturnType get(const trial::protocol::json::reader& reader)
{
    return reader.value<ReturnType>();
}
} // namespace boost

#endif // TRIAL_PROTOCOL_JSON_READER_HPP
