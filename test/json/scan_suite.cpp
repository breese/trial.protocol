///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2020 Vinícius dos Santos Oliveira <vini.ipsmaker@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <trial/protocol/json/scan.hpp>
#include <trial/protocol/core/detail/lightweight_test.hpp>

using namespace trial::protocol;
namespace token = json::token;
namespace hana = boost::hana;

void test_plain_assignment()
{
    auto input = R"({"foo": 42, "bar": "baz", "else": null, "aboolean": true})";
    int foo = 0;
    std::string bar;
    bool aboolean = false;
    json::scan(
        input,
        hana::make_map(
            hana::make_pair(BOOST_HANA_STRING("foo"), std::ref(foo)),
            hana::make_pair(BOOST_HANA_STRING("bar"), std::ref(bar)),
            hana::make_pair(BOOST_HANA_STRING("aboolean"), std::ref(aboolean))
        )
    );
    TRIAL_PROTOCOL_TEST_EQUAL(foo, 42);
    TRIAL_PROTOCOL_TEST_EQUAL(bar, std::string{"baz"});
    TRIAL_PROTOCOL_TEST_EQUAL(aboolean, true);
}

void test_nested_assignment()
{
    auto input = R"({"foo": {"bar": 3, "baz": 4}, "bar": 5})";
    int bar = 0;
    int baz = 0;
    int qux = 0;
    json::scan(
        input,
        hana::make_map(
            hana::make_pair(
                BOOST_HANA_STRING("foo"),
                hana::make_map(
                    hana::make_pair(BOOST_HANA_STRING("bar"), std::ref(bar)),
                    hana::make_pair(BOOST_HANA_STRING("baz"), std::ref(baz))
                )),
            hana::make_pair(BOOST_HANA_STRING("bar"), std::ref(qux))
        )
    );
    TRIAL_PROTOCOL_TEST_EQUAL(bar, 3);
    TRIAL_PROTOCOL_TEST_EQUAL(baz, 4);
    TRIAL_PROTOCOL_TEST_EQUAL(qux, 5);
}

void test_nested_assignment2()
{
    // Not supported. Check
    // https://github.com/boostorg/hana/issues/451#issuecomment-643647418
#if 0
    auto input = R"({"foo": {"bar": 3, "baz": 4, "qux": 5}, "foobar": 6})";
    int bar = 0;
    int baz = 0;
    int qux = 0;
    int foobar = 0;
    json::scan(
        input,
        hana::make_map(
            hana::make_pair(
                hana::make_tuple(
                    BOOST_HANA_STRING("foo"), BOOST_HANA_STRING("bar")),
                std::ref(bar)
            ),
            hana::make_pair(
                hana::make_tuple(
                    BOOST_HANA_STRING("foo"), BOOST_HANA_STRING("baz")),
                std::ref(baz)
            ),
            hana::make_pair(
                BOOST_HANA_STRING("foo"),
                hana::make_map(
                    hana::make_pair(BOOST_HANA_STRING("qux"), std::ref(qux))
                )
            ),
            hana::make_pair(
                hana::make_tuple(BOOST_HANA_STRING("foobar")), std::ref(foobar)
            )
        )
    );
    TRIAL_PROTOCOL_TEST_EQUAL(bar, 3);
    TRIAL_PROTOCOL_TEST_EQUAL(baz, 4);
    TRIAL_PROTOCOL_TEST_EQUAL(qux, 5);
    TRIAL_PROTOCOL_TEST_EQUAL(foobar, 6);
#endif
}

void test_callback()
{
    auto input = R"({"foo": 42, "bar": "baz", "else": null, "aboolean": true})";
    json::scan(
        input,
        hana::make_map(
            hana::make_pair(
                BOOST_HANA_STRING("foo"),
                [](json::reader& reader) {
                    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<int>(), 42);
                    reader.next();
                }),
            hana::make_pair(
                BOOST_HANA_STRING("bar"),
                [](json::reader& reader) {
                    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(),
                                              std::string{"baz"});
                    reader.next();
                }),
            hana::make_pair(
                BOOST_HANA_STRING("aboolean"),
                [](json::reader& reader) {
                    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<bool>(), true);
                    reader.next();
                })
        )
    );
}

void test_wildcard_match()
{
    auto input = R"({"foo": 42, "bar": "baz", "baz": null})";
    int foo = 0;
    bool seen_bar = false;
    bool seen_baz = false;
    json::scan(
        input,
        hana::make_map(
            hana::make_pair(BOOST_HANA_STRING("foo"), std::ref(foo)),
            hana::make_pair(
                hana::type_c<void>,
                [&seen_bar,&seen_baz](json::reader& reader) {
                    auto key = reader.value<std::string>();
                    TRIAL_PROTOCOL_TEST_NE(key, std::string{"foo"});
                    if (key == "bar") {
                        auto has_next = reader.next();
                        assert(has_next);
                        TRIAL_PROTOCOL_TEST_EQUAL(reader.literal(), "\"baz\"");
                        seen_bar = true;
                    } else if (key == "baz") {
                        auto has_next = reader.next();
                        assert(has_next);
                        TRIAL_PROTOCOL_TEST_EQUAL(reader.literal(), "null");
                        seen_baz = true;
                    } else {
                        assert(false);
                    }
                    json::partial::skip(reader);
                })
        )
    );
    TRIAL_PROTOCOL_TEST_EQUAL(foo, 42);
    TRIAL_PROTOCOL_TEST(seen_bar);
    TRIAL_PROTOCOL_TEST(seen_baz);
}

void test_missing_field()
{
    auto input = R"({"foo": 42, "baz": null})";
    int foo = 0;
    std::string bar;
    auto spec = hana::make_map(
        hana::make_pair(BOOST_HANA_STRING("foo"), std::ref(foo)),
        hana::make_pair(BOOST_HANA_STRING("bar"), std::ref(bar))
    );
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(
        json::scan(input, spec), json::error, "request field(s) not found");
}

void test_missing_field2()
{
    auto input = R"({"foo": {"bar": 44}, "baz": 22})";
    int foo;
    int bar;
    int baz;
    auto spec = hana::make_map(
        hana::make_pair(BOOST_HANA_STRING("baz"), std::ref(baz)),
        hana::make_pair(
            BOOST_HANA_STRING("foo"),
            hana::make_map(
                hana::make_pair(BOOST_HANA_STRING("foo"), std::ref(foo)),
                hana::make_pair(BOOST_HANA_STRING("bar"), std::ref(bar))
            )
        )
    );
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(
        json::scan(input, spec), json::error, "request field(s) not found");
}

void test_literal()
{
    auto input = R"({"foo": 42, "bar": [1, 2]})";
    boost::string_view bar;
    json::scan(
        input,
        hana::make_map(
            hana::make_pair(BOOST_HANA_STRING("bar"), std::ref(bar))
        ));
    TRIAL_PROTOCOL_TEST_EQUAL(bar, "[1, 2]");
}

void test_subtree()
{
    auto input = R"({"foo": null, "bar": [1, 2]})";
    trial::dynamic::variable foo = 33;
    trial::dynamic::variable bar;
    trial::dynamic::variable baz;
    auto spec = hana::make_map(
        hana::make_pair(BOOST_HANA_STRING("foo"), std::ref(foo)),
        hana::make_pair(BOOST_HANA_STRING("bar"), std::ref(bar)),
        hana::make_pair(BOOST_HANA_STRING("baz"), std::ref(baz))
    );
    TRIAL_PROTOCOL_TEST_NO_THROW(json::scan(input, spec));
    TRIAL_PROTOCOL_TEST(foo.is<trial::dynamic::nullable>());
    TRIAL_PROTOCOL_TEST_EQUAL(bar.size(), 2);
    TRIAL_PROTOCOL_TEST(bar[0] == 1);
    TRIAL_PROTOCOL_TEST(bar[1] == 2);
}

void test_optional()
{
    auto input = R"({"foo": 42, "bar": "bar"})";
    boost::optional<int> foo;
    boost::optional<std::string> bar;
    boost::optional<int> qux;
    json::scan(
        input,
        hana::make_map(
            hana::make_pair(BOOST_HANA_STRING("foo"), std::ref(foo)),
            hana::make_pair(BOOST_HANA_STRING("bar"), std::ref(bar)),
            hana::make_pair(BOOST_HANA_STRING("qux"), std::ref(qux))
        ));
    TRIAL_PROTOCOL_TEST(foo);
    TRIAL_PROTOCOL_TEST_EQUAL(*foo, 42);
    TRIAL_PROTOCOL_TEST(bar);
    TRIAL_PROTOCOL_TEST_EQUAL(*bar, "bar");
    TRIAL_PROTOCOL_TEST(!qux);
}

void test_variant()
{
    auto input = R"({"foo": "hello", "baz": null, "foobar": 3.5,
                     "qux": 3, "qux2": 3.4})";
    boost::variant<bool, std::string> foo;
    boost::variant<bool, std::string, boost::none_t> bar = boost::none;
    boost::variant<boost::none_t, int> baz = 33;
    boost::variant<int, double> foobar;
    boost::variant<int, double> qux;
    boost::variant<int, boost::none_t> qux2;
    json::scan(
        input,
        hana::make_map(
            hana::make_pair(BOOST_HANA_STRING("foo"), std::ref(foo)),
            hana::make_pair(BOOST_HANA_STRING("bar"), std::ref(bar)),
            hana::make_pair(BOOST_HANA_STRING("baz"), std::ref(baz)),
            hana::make_pair(BOOST_HANA_STRING("foobar"), std::ref(foobar)),
            hana::make_pair(BOOST_HANA_STRING("qux"), std::ref(qux)),
            hana::make_pair(BOOST_HANA_STRING("qux2"), std::ref(qux2))
        ));
    TRIAL_PROTOCOL_TEST_EQUAL(boost::get<std::string>(foo), "hello");
    TRIAL_PROTOCOL_TEST_NO_THROW(boost::get<boost::none_t>(bar));
    TRIAL_PROTOCOL_TEST_NO_THROW(boost::get<boost::none_t>(baz));
    TRIAL_PROTOCOL_TEST_EQUAL(boost::get<double>(foobar), 3.5);
    TRIAL_PROTOCOL_TEST_EQUAL(boost::get<int>(qux), 3);
    TRIAL_PROTOCOL_TEST_EQUAL(boost::get<int>(qux2), 3);
}

void test_variant2()
{
    auto input = R"({"baz": null})";
    boost::variant<bool, std::string> foo;
    auto spec = hana::make_map(
        hana::make_pair(BOOST_HANA_STRING("foo"), std::ref(foo))
    );
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(
        json::scan(input, spec), json::error, "request field(s) not found");
}

void test_array()
{
    auto input = R"({"foo": [1, 2, 3],
                     "bar": [[], [15], [16, 17]],
                     "baz": [null, false, true],
                     "qux": [false]})";
    std::vector<int> foo;
    std::vector<std::vector<int>> bar;
    std::vector<boost::optional<bool>> baz;
    boost::optional<std::vector<bool>> qux;
    json::scan(
        input,
        hana::make_map(
            hana::make_pair(BOOST_HANA_STRING("foo"), std::ref(foo)),
            hana::make_pair(BOOST_HANA_STRING("bar"), std::ref(bar)),
            hana::make_pair(BOOST_HANA_STRING("baz"), std::ref(baz)),
            hana::make_pair(BOOST_HANA_STRING("qux"), std::ref(qux))
        ));
    std::vector<int> foo_expected{1, 2, 3};
    std::vector<boost::optional<bool>> baz_expected;
    baz_expected.push_back(boost::none);
    baz_expected.push_back(false);
    baz_expected.push_back(true);
    TRIAL_PROTOCOL_TEST_ALL_WITH(foo.begin(), foo.end(),
                                 foo_expected.begin(), foo_expected.end(),
                                 std::equal_to<int>());
    TRIAL_PROTOCOL_TEST_EQUAL(bar.size(), 3);
    TRIAL_PROTOCOL_TEST_EQUAL(bar[0].size(), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(bar[1].size(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(bar[2].size(), 2);
    TRIAL_PROTOCOL_TEST_EQUAL(bar[1][0], 15);
    TRIAL_PROTOCOL_TEST_EQUAL(bar[2][0], 16);
    TRIAL_PROTOCOL_TEST_EQUAL(bar[2][1], 17);
    TRIAL_PROTOCOL_TEST_ALL_WITH(baz.begin(), baz.end(),
                                 baz_expected.begin(), baz_expected.end(),
                                 std::equal_to<boost::optional<bool>>());
    TRIAL_PROTOCOL_TEST(qux);
    TRIAL_PROTOCOL_TEST_EQUAL(qux->size(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL((*qux)[0], false);
}

//-----------------------------------------------------------------------------
// main
//-----------------------------------------------------------------------------

int main()
{
    test_plain_assignment();
    test_nested_assignment();
    test_nested_assignment2();
    test_callback();
    test_wildcard_match();
    test_missing_field();
    test_missing_field2();
    test_literal();
    test_subtree();
    test_optional();
    test_variant();
    test_variant2();
    test_array();

    return boost::report_errors();
}
