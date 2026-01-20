#ifndef TRIAL_PROTOCOL_JSON_SCAN_HPP
#define TRIAL_PROTOCOL_JSON_SCAN_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2020 Vinícius dos Santos Oliveira <vini.ipsmaker@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <functional>

#include <boost/optional.hpp>
#include <boost/variant.hpp>
#include <boost/hana.hpp>
#include <boost/none.hpp>

#include <trial/protocol/json/partial/skip.hpp>
#include <trial/protocol/json/reader.hpp>
#include <trial/protocol/json/parse.hpp>

namespace trial
{
namespace protocol
{
namespace json
{
namespace partial
{

template<class CharT, class Xs>
void scan(basic_reader<CharT>& reader, Xs&& xs);

namespace detail
{

template<class CharT, std::size_t capacity>
struct ScanCollector
{
    using view_type = typename basic_reader<CharT>::view_type;
    using size_type = typename basic_reader<CharT>::size_type;

    void push_back(CharT v)
    {
        if (size == capacity) return;

        storage[size++] = v;
    }

    void append(const CharT *data, size_type size)
    {
        if (this->size == capacity) return;

        if (size + this->size > capacity) {
            this->size = capacity;
            return;
        }

        std::copy(data, data + size, storage.begin() + this->size);
        this->size += size;
    }

    void clear()
    {
        size = 0;
    }

    template<class Xs>
    bool equals(const Xs& hana_str) const
    {
        BOOST_HANA_CONSTANT_ASSERT(
            boost::hana::size_c<capacity> > boost::hana::size(hana_str));
        view_type str{hana_str.c_str(), boost::hana::size(hana_str)};
        return as_view() == str;
    }

    view_type as_view() const
    {
        return view_type{storage.data(), size};
    }

    std::array<CharT, capacity> storage;
    std::size_t size;
};

template<class T>
boost::hana::true_ scan_required_arg(const T&) { return {}; }

inline
boost::hana::false_ scan_required_arg(std::reference_wrapper<dynamic::variable>)
{ return {}; }

template<class T>
boost::hana::false_
scan_required_arg(std::reference_wrapper<boost::optional<T>>)
{ return {}; }

template<class... Ts>
std::enable_if_t<
    boost::hana::contains(
        boost::hana::make_tuple(boost::hana::type_c<Ts>...),
        boost::hana::type_c<boost::none_t>),
    boost::hana::false_
>
scan_required_arg(std::reference_wrapper<boost::variant<Ts...>>)
{ return {}; }

// scan_action(reference_wrapper<T>) OVERLOAD DECLARATIONS
// These are needed because overloads might reference each other recursively

template<class CharT, class T>
void scan_action(basic_reader<CharT>& reader, std::reference_wrapper<T> action);

template<class CharT>
void scan_action(basic_reader<CharT>& reader,
                 std::reference_wrapper<boost::basic_string_view<CharT>>);

inline void scan_action(reader& reader,
                        std::reference_wrapper<dynamic::variable> action);

template<class CharT, class T>
void scan_action(basic_reader<CharT>& reader,
                 std::reference_wrapper<boost::optional<T>> action);

template<class CharT, class... Ts>
void scan_action(basic_reader<CharT>& reader,
                 std::reference_wrapper<boost::variant<Ts...>> action);

template<class CharT, class T>
void scan_action(basic_reader<CharT>& reader,
                 std::reference_wrapper<std::vector<T>> action);

template<class CharT>
void scan_action(basic_reader<CharT>& reader,
                 std::reference_wrapper<std::vector<bool>> action);

// scan_action() OVERLOAD DEFINITIONS

template<class CharT, class Xs>
std::enable_if_t<boost::hana::is_a<boost::hana::map_tag, Xs>>
scan_action(basic_reader<CharT>& reader, Xs&& xs)
{
    scan(reader, std::forward<Xs>(xs));
}

template<class CharT, class F>
auto scan_action(basic_reader<CharT>& reader, F&& f) -> decltype(f(reader))
{
    return f(reader);
}

template<class CharT, class T>
void scan_action(basic_reader<CharT>& reader, std::reference_wrapper<T> action)
{
    auto& output = action.get();
    auto ec = reader.value(output);
    if (ec) throw json::error(ec);
    skip(reader);
}

template<class CharT>
void scan_action(basic_reader<CharT>& reader,
                 std::reference_wrapper<boost::basic_string_view<CharT>> action)
{
    action.get() = skip(reader);
}

inline void scan_action(reader& reader,
                        std::reference_wrapper<dynamic::variable> action)
{
    action.get() = parse(reader);
}

template<class CharT, class T>
void scan_action(basic_reader<CharT>& reader,
                 std::reference_wrapper<boost::optional<T>> action)
{
    if (reader.symbol() == token::symbol::null) {
        action.get().reset();
        if (!reader.next()) throw json::error(reader.error());
        return;
    }
    auto& output = action.get();
    output.emplace();
    scan_action(reader, std::ref(*output));
}

template<class CharT, class... Ts>
void scan_action(basic_reader<CharT>& reader,
                 std::reference_wrapper<boost::variant<Ts...>> action)
{
    namespace hana = boost::hana;

    auto& output = action.get();
    switch (reader.symbol()) {
    case token::symbol::null:
        hana::eval_if(
            !hana::contains(
                hana::make_tuple(hana::type_c<Ts>...),
                hana::type_c<boost::none_t>),
            []() { throw json::error(errc::incompatible_type); },
            [&](auto _) { _(output) = boost::none; }
        );
        break;
    case token::symbol::boolean:
        hana::eval_if(
            !hana::contains(
                hana::make_tuple(hana::type_c<Ts>...),
                hana::type_c<bool>),
            []() { throw json::error(errc::incompatible_type); },
            [&](auto _) { _(output) = reader.template value<bool>(); }
        );
        break;
    case token::symbol::integer: {
        auto target = hana::filter(
            hana::make_tuple(
                hana::type_c<long long>,
                hana::type_c<long>,
                hana::type_c<int>,
                hana::type_c<short>,
                hana::type_c<long double>,
                hana::type_c<double>,
                hana::type_c<float>),
            [](auto&& e) {
                return hana::contains(
                    hana::make_tuple(hana::type_c<Ts>...),
                    e);
            });
        hana::eval_if(
            hana::size(target) == hana::size_c<0>,
            []() { throw json::error(errc::incompatible_type); },
            [&](auto _) {
                using T = typename decltype(+hana::at_c<0>(_(target)))::type;
                _(output) = reader.template value<T>();
            }
        );
        break;
    }
    case token::symbol::real: {
        auto target = hana::filter(
            hana::make_tuple(
                hana::type_c<long double>,
                hana::type_c<double>,
                hana::type_c<float>,
                hana::type_c<long long>,
                hana::type_c<long>,
                hana::type_c<int>,
                hana::type_c<short>),
            [](auto&& e) {
                return hana::contains(
                    hana::make_tuple(hana::type_c<Ts>...),
                    e);
            });
        hana::eval_if(
            hana::size(target) == hana::size_c<0>,
            []() { throw json::error(errc::incompatible_type); },
            [&](auto _) {
                using T = typename decltype(+hana::at_c<0>(_(target)))::type;
                _(output) = reader.template value<T>();
            }
        );
        break;
    }
    case token::symbol::string:
        hana::eval_if(
            !hana::contains(
                hana::make_tuple(hana::type_c<Ts>...),
                hana::type_c<std::string>),
            []() { throw json::error(errc::incompatible_type); },
            [&](auto _) { _(output) = reader.template value<std::string>(); }
        );
        break;
    case token::symbol::begin_array:
    case token::symbol::begin_object:
        throw json::error(errc::incompatible_type);
    default:
        assert(false);
    }
    if (!reader.next()) throw json::error(reader.error());
}

template<class CharT, class T>
void scan_action(basic_reader<CharT>& reader,
                 std::reference_wrapper<std::vector<T>> action)
{
    if (reader.symbol() != token::symbol::begin_array)
        throw json::error(errc::incompatible_type);

    if (!reader.next())
        throw json::error(reader.error());

    auto& output = action.get();

    for (;;) {
        if (reader.symbol() == token::symbol::end_array) {
            if (!reader.next())
                throw json::error(reader.error());
            break;
        }

        output.emplace_back();
        scan_action(reader, std::ref(output.back()));
    }
}

template<class CharT>
void scan_action(basic_reader<CharT>& reader,
                 std::reference_wrapper<std::vector<bool>> action)
{
    if (reader.symbol() != token::symbol::begin_array)
        throw json::error(errc::incompatible_type);

    if (!reader.next())
        throw json::error(reader.error());

    auto& output = action.get();

    for (;;) {
        if (reader.symbol() == token::symbol::end_array) {
            if (!reader.next())
                throw json::error(reader.error());
            break;
        }

        output.emplace_back(reader.template value<bool>());
        if (!reader.next())
            throw json::error(reader.error());
    }
}

} // namespace detail

template<class CharT, class Xs>
void scan(basic_reader<CharT>& reader, Xs&& xs)
{
    namespace hana = boost::hana;
    using hana::literals::operator""_c;

    // Given this spec:
    //
    // { (("foo", "bar"), action1),
    //   (("foo", "baz"), action2),
    //   (("qux")       , action3) }
    //
    // This spec is returned:
    //
    // { ("foo", { (("bar"), action1)
    //             (("baz"), action2) })
    //   ("qux", action3               ) }
    auto normalize_root = [](auto&& xs) {
        return std::forward<decltype(xs)>(xs);
        // Not supported. Check
        // https://github.com/boostorg/hana/issues/451#issuecomment-643647418
#if 0
        return hana::fold(
            std::forward<decltype(xs)>(xs),
            hana::make_map(),
            [](auto&& acc, auto&& rule) {
                auto& pattern = hana::first(rule);
                auto& action = hana::second(rule);

                auto& key = hana::eval_if(
                    hana::is_a<hana::string_tag>(pattern),
                    [&pattern]() { return pattern; },
                    [&pattern](auto _) { return _(pattern)[0_c]; }
                );

                auto value = hana::eval_if(
                    (hana::is_a<hana::string_tag>(pattern) ||
                     (hana::is_a<hana::tuple_tag>(pattern) &&
                      hana::size(pattern) == hana::size_c<1>)),
                    [&action]() { return action; },
                    [&pattern,&action](auto _) {
                        return hana::make_map(hana::make_pair(
                            hana::drop_front(_(pattern)),
                            action
                        ));
                    }
                );

                return hana::if_(
                    hana::contains(acc, key),
                    hana::transform(
                        acc,
                        [&key,&value](auto&& e) {
                            return hana::eval_if(
                                hana::first(e) != key,
                                [&e]() { return std::forward<decltype(e)>(e); },
                                [&e,&value](auto _) {
                                    return hana::union_(
                                        _(value),
                                        _(hana::second(e))
                                    );
                                }
                            );
                        }),
                    hana::insert(acc, hana::make_pair(key, value))
                );
            }
        );
#endif
    };

    if (reader.symbol() != token::symbol::begin_object)
        throw json::error(json::incompatible_type);

    auto spec = hana::insert(
        normalize_root(std::forward<Xs>(xs)),
        hana::make_pair(
            hana::type_c<void>,
            [](basic_reader<CharT>& reader) {
                // Skip key
                if (!reader.next()) throw json::error(reader.error());
                // Skip value
                skip(reader);
            }));
    auto wildcard = std::move(spec[hana::type_c<void>]);
    auto seen_table = hana::fold(
        spec,
        hana::make_map(),
        [](auto&& acc, const auto& e) {
            return hana::if_(
                hana::first(e) == hana::type_c<void> ||
                !detail::scan_required_arg(hana::second(e)),
                acc,
                hana::insert(acc, hana::make_pair(hana::first(e), false)));
        }
    );
    auto collector_capacity = hana::size_c<1> + hana::maximum(
        hana::transform(hana::remove(hana::keys(spec), hana::type_c<void>),
                        hana::size));
    detail::ScanCollector<CharT, collector_capacity> current_key;

    if (!reader.next())
        throw json::error(reader.error());

    auto loop_body = hana::fold_right(
        hana::erase_key(std::move(spec), hana::type_c<void>),
        std::move(wildcard),
        [&seen_table,&current_key](auto&& rule, auto&& acc) {
            return [
                rule=std::forward<decltype(rule)>(rule),
                acc=std::forward<decltype(acc)>(acc),
                &seen_table,&current_key
            ](basic_reader<CharT>& reader) {
                // Key
                if (!current_key.equals(/*pattern=*/hana::first(rule)))
                    return acc(reader);

                if (!reader.next())
                    throw json::error(reader.error());

                // Value
                detail::scan_action(reader, /*action=*/hana::second(rule));
                hana::eval_if(
                    !detail::scan_required_arg(hana::second(rule)),
                    []() {},
                    [&seen_table,&rule](auto _) {
                        _(seen_table)[hana::first(rule)] = true;
                    });
            };
        }
    );

    for (;;) {
        if (reader.symbol() == token::symbol::end_object) {
            reader.next();
            auto ec = reader.error();
            if (ec) throw json::error(ec);
            break;
        }

        // Key
        assert(reader.symbol() == token::symbol::string);
        current_key.clear();
        auto ec = reader.string(current_key);
        assert(!ec); (void)ec;

        // Value
        loop_body(reader);
    }

    if (hana::fold(
        seen_table,
        hana::false_c,
        [](auto&& acc, auto&& e) { return acc || !hana::second(e); }
    )) {
        throw json::error(errc::field_not_found);
    }
}

} // namespace partial

template<class CharT, class... Args>
void scan(boost::basic_string_view<CharT> input, Args&&... args)
{
    basic_reader<CharT> reader(input);
    partial::scan(reader, std::forward<Args>(args)...);
    if (reader.symbol() != token::symbol::end)
        throw json::error(json::unexpected_token);
}

template<class... Args>
void scan(const char input[], Args&&... args)
{
    scan(boost::string_view(input), std::forward<Args>(args)...);
}

} // namespace json
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_JSON_SCAN_HPP
