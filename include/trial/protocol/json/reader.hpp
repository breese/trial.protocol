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

class reader
{
public:
    typedef std::size_t size_type;
    typedef const char value_type;
    typedef value_type * pointer;
    typedef detail::decoder::view_type view_type;

    reader(const view_type&);
    reader(const reader&);

    //! @brief Advance to the next token.
    bool next();

    //! @brief Advance to the next token if current token has a given value.
    //! @param[in] expect Expected value of current token.
    //! @throws system_error If current token does not have the expected value.
    bool next(token::code::value expect);

    bool next_sibling();

    //! @brief Returns the current nesting level.
    size_type level() const BOOST_NOEXCEPT;

    //! @brief Returns the current token.
    token::code::value code() const BOOST_NOEXCEPT;

    //! @brief Returns the symbol of the current token.
    token::symbol::value symbol() const BOOST_NOEXCEPT;

    //! @brief Returns the category of the current token.
    token::category::value category() const BOOST_NOEXCEPT;

    //! @brief Returns the last error code.
    boost::system::error_code error() const BOOST_NOEXCEPT;

    //! @brief Return the current value.
    //! @throws system_error If requested type is incompatible with the current token.
    template <typename ReturnType> ReturnType value() const;

    //! @brief Return a view of the current value before it is converted into its type.
    const view_type& literal() const BOOST_NOEXCEPT;

#ifndef BOOST_DOXYGEN_INVOKED
private:
    template <typename T, typename Enable = void> struct type_matcher;
    mutable detail::decoder decoder;

    struct frame
    {
        frame(token::code::value);

        bool is_array() const;
        bool is_object() const;

        token::code::value next(detail::decoder&);
        token::code::value check_outer(detail::decoder&);
        token::code::value check_array(detail::decoder&);
        token::code::value check_object(detail::decoder&);

        token::code::value scope;
        std::size_t counter;
    };
    std::stack<frame> stack;
#endif
};

} // namespace json
} // namespace protocol
} // namespace trial

#include <trial/protocol/json/detail/reader.ipp>

namespace boost
{
template<typename ReturnType>
inline ReturnType get(const trial::protocol::json::reader& reader)
{
    return reader.value<ReturnType>();
}
} // namespace boost

#endif // TRIAL_PROTOCOL_JSON_READER_HPP
