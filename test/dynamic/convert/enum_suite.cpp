///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2018 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <trial/protocol/core/detail/lightweight_test.hpp>
#include <trial/dynamic/convert/enum.hpp>

using namespace trial::dynamic;

//-----------------------------------------------------------------------------

namespace trial
{
namespace dynamic
{

} // namespace dynamic
} // namespace trial

namespace enum_suite
{

enum enumeration
{
    alpha = 42
};

using underlying_type = typename std::underlying_type<enumeration>::type;

void from_enum()
{
    variable result = convert::into<variable>(alpha);
    TRIAL_PROTOCOL_TEST(result.same<underlying_type>());
    TRIAL_PROTOCOL_TEST(result.value<underlying_type>() == static_cast<underlying_type>(alpha));
}

void to_enum()
{
    variable input = underlying_type{alpha};
    auto result = convert::into<enumeration>(input);
    TRIAL_PROTOCOL_TEST_EQUAL(result, alpha);
}

void run()
{
    from_enum();
    to_enum();
}

} // namespace enum_suite

namespace trial
{
namespace dynamic
{
namespace convert
{
template <>
struct use_underlying_type<enum_suite::enumeration> : std::true_type {};
} // namespace convert
} // namespace dynamic
} // namespace trial

//-----------------------------------------------------------------------------

namespace enum_class_suite
{

enum class enumeration
{
    alpha = 42
};

using underlying_type = typename std::underlying_type<enumeration>::type;

void from_enum()
{
    variable result = convert::into<variable>(enumeration::alpha);
    TRIAL_PROTOCOL_TEST(result.same<underlying_type>());
    TRIAL_PROTOCOL_TEST(result.value<underlying_type>() == static_cast<underlying_type>(enumeration::alpha));
}

void to_enum()
{
    variable input = static_cast<underlying_type>(enumeration::alpha);
    auto result = convert::into<enumeration>(input);
    TRIAL_PROTOCOL_TEST(result == enumeration::alpha);
}

void run()
{
    from_enum();
    to_enum();
}

} // namespace enum_class_suite

namespace trial
{
namespace dynamic
{
namespace convert
{
template <>
struct use_underlying_type<enum_class_suite::enumeration> : std::true_type {};
} // namespace convert
} // namespace dynamic
} // namespace trial

//-----------------------------------------------------------------------------

enum class string_enumeration
{
    alpha = 42
};

namespace trial
{
namespace dynamic
{
namespace convert
{

template <>
struct overloader<variable, string_enumeration>
{
    static variable into(string_enumeration data,
                         std::error_code& error)
    {
        switch (data)
        {
        case string_enumeration::alpha:
            return "alpha";
        }

        error = dynamic::incompatible_type;
        return {};
    }
};

template <>
struct overloader<string_enumeration, variable>
{
    static string_enumeration into(const variable& data,
                                   std::error_code& error)
    {
        if (data == "alpha")
            return string_enumeration::alpha;

        error = dynamic::incompatible_type;
        return {};
    }
};

} // namespace convert
} // namespace dynamic
} // namespace trial

namespace custom_suite
{

void from_enum()
{
    auto result = convert::into<variable>(string_enumeration::alpha);
    TRIAL_PROTOCOL_TEST(result.same<std::string>());
    TRIAL_PROTOCOL_TEST_EQUAL(result.value<string>(), "alpha");
}

void to_enum()
{
    variable input = "alpha";
    auto result = convert::into<string_enumeration>(input);
    TRIAL_PROTOCOL_TEST(result == string_enumeration::alpha);
}

void run()
{
    from_enum();
    to_enum();
}

} // namespace custom_suite

//-----------------------------------------------------------------------------
// main
//-----------------------------------------------------------------------------

int main()
{
    enum_suite::run();
    enum_class_suite::run();
    custom_suite::run();

    return boost::report_errors();
}
