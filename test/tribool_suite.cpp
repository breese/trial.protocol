///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2020 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <trial/protocol/core/detail/lightweight_test.hpp>
#include <trial/tribool.hpp>

//-----------------------------------------------------------------------------

namespace api_suite
{

void api_ctor_default()
{
    trial::tribool value;
    TRIAL_PROTOCOL_TEST((value != true).empty());
    TRIAL_PROTOCOL_TEST((value != false).empty());
    TRIAL_PROTOCOL_TEST(value.empty());
}

void api_ctor_copy()
{
    trial::tribool value;
    trial::tribool copy(value);
    TRIAL_PROTOCOL_TEST(copy.empty());
}

void api_ctor_move()
{
    trial::tribool value;
    trial::tribool copy(std::move(value));
    TRIAL_PROTOCOL_TEST(copy.empty());
}

void api_ctor_value()
{
    {
        trial::tribool value(false);
        TRIAL_PROTOCOL_TEST(value == false);
    }
    {
        trial::tribool value(true);
        TRIAL_PROTOCOL_TEST(value == true);
    }
}

void api_operator_not()
{
    {
        trial::tribool value;
        TRIAL_PROTOCOL_TEST(value.empty());
        TRIAL_PROTOCOL_TEST((!value).empty());
    }
    {
        trial::tribool value(false);
        TRIAL_PROTOCOL_TEST(value == false);
        TRIAL_PROTOCOL_TEST(!value == true);
    }
    {
        trial::tribool value(true);
        TRIAL_PROTOCOL_TEST(value == true);
        TRIAL_PROTOCOL_TEST(!value == false);
    }
}

void api_operator_and()
{
    trial::tribool empty_value;
    trial::tribool false_value(false);
    trial::tribool true_value(true);

    TRIAL_PROTOCOL_TEST(bool(true_value && true_value));
    TRIAL_PROTOCOL_TEST(bool(true_value && true));
    TRIAL_PROTOCOL_TEST(bool(true && true_value));

    TRIAL_PROTOCOL_TEST(!bool(true_value && false_value));
    TRIAL_PROTOCOL_TEST(!bool(true_value && false));
    TRIAL_PROTOCOL_TEST(!bool(true && false_value));

    TRIAL_PROTOCOL_TEST(!bool(false_value && true_value));
    TRIAL_PROTOCOL_TEST(!bool(false_value && true));
    TRIAL_PROTOCOL_TEST(!bool(false && true_value));

    TRIAL_PROTOCOL_TEST(!bool(false_value && false_value));
    TRIAL_PROTOCOL_TEST(!bool(false_value && false));
    TRIAL_PROTOCOL_TEST(!bool(false && false_value));

    TRIAL_PROTOCOL_TEST((empty_value && true_value).empty());
    TRIAL_PROTOCOL_TEST(!(empty_value && false_value).empty());
    TRIAL_PROTOCOL_TEST((empty_value && empty_value).empty());
    TRIAL_PROTOCOL_TEST((true_value && empty_value).empty());
    TRIAL_PROTOCOL_TEST(!(false_value && empty_value).empty());
}

void api_operator_or()
{
    trial::tribool empty_value;
    trial::tribool false_value(false);
    trial::tribool true_value(true);

    TRIAL_PROTOCOL_TEST(bool(true_value || true_value));
    TRIAL_PROTOCOL_TEST(bool(true_value || true));
    TRIAL_PROTOCOL_TEST(bool(true || true_value));

    TRIAL_PROTOCOL_TEST(bool(true_value || false_value));
    TRIAL_PROTOCOL_TEST(bool(true_value || false));
    TRIAL_PROTOCOL_TEST(bool(true || false_value));

    TRIAL_PROTOCOL_TEST(bool(false_value || true_value));
    TRIAL_PROTOCOL_TEST(bool(false_value || true));
    TRIAL_PROTOCOL_TEST(bool(false || true_value));

    TRIAL_PROTOCOL_TEST(!bool(false_value || false_value));
    TRIAL_PROTOCOL_TEST(!bool(false_value || false));
    TRIAL_PROTOCOL_TEST(!bool(false || false_value));

    TRIAL_PROTOCOL_TEST(!(empty_value || true_value).empty());
    TRIAL_PROTOCOL_TEST((empty_value || false_value).empty());
    TRIAL_PROTOCOL_TEST((empty_value || empty_value).empty());
    TRIAL_PROTOCOL_TEST(!(true_value || empty_value).empty());
    TRIAL_PROTOCOL_TEST((false_value || empty_value).empty());
}

void run()
{
    api_ctor_default();
    api_ctor_copy();
    api_ctor_move();
    api_ctor_value();
    api_operator_not();
    api_operator_and();
    api_operator_or();
}

} // namespace api_suite

//-----------------------------------------------------------------------------
// main
//-----------------------------------------------------------------------------

int main()
{
    api_suite::run();
    return boost::report_errors();
}
