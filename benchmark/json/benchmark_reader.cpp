///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2019 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <array>
#include <benchmark/benchmark.h>
#include <trial/protocol/buffer/array.hpp>
#include <trial/protocol/json/reader.hpp>

namespace json = trial::protocol::json;

void parse_int16(benchmark::State& state)
{
    char input[] = "291";
    for (auto _ : state)
    {
        json::reader reader(input);
        benchmark::DoNotOptimize(reader.value<std::int16_t>());
    }
}

void parse_int32(benchmark::State& state)
{
    char input[] = "19088743";
    for (auto _ : state)
    {
        json::reader reader(input);
        benchmark::DoNotOptimize(reader.value<std::int32_t>());
    }
}

void parse_int64(benchmark::State& state)
{
    char input[] = "81985529216486895";
    for (auto _ : state)
    {
        json::reader reader(input);
        benchmark::DoNotOptimize(reader.value<std::int64_t>());
    }
}

BENCHMARK(parse_int16);
BENCHMARK(parse_int32);
BENCHMARK(parse_int64);

void value_int16(benchmark::State& state)
{
    char input[] = "291";
    json::reader reader(input);
    for (auto _ : state)
    {
        benchmark::DoNotOptimize(reader.value<std::int16_t>());
    }
}

void value_int32(benchmark::State& state)
{
    char input[] = "19088743";
    json::reader reader(input);
    for (auto _ : state)
    {
        benchmark::DoNotOptimize(reader.value<std::int32_t>());
    }
}

void value_int64(benchmark::State& state)
{
    char input[] = "81985529216486895";
    json::reader reader(input);
    for (auto _ : state)
    {
        benchmark::DoNotOptimize(reader.value<std::int64_t>());
    }
}

BENCHMARK(value_int16);
BENCHMARK(value_int32);
BENCHMARK(value_int64);

void parse_float(benchmark::State& state)
{
    char input[] = "291.192";
    for (auto _ : state)
    {
        json::reader reader(input);
        benchmark::DoNotOptimize(reader.value<float>());
    }
}

void parse_double(benchmark::State& state)
{
    char input[] = "291.192";
    for (auto _ : state)
    {
        json::reader reader(input);
        benchmark::DoNotOptimize(reader.value<double>());
    }
}

void parse_long_double(benchmark::State& state)
{
    char input[] = "291.192";
    for (auto _ : state)
    {
        json::reader reader(input);
        benchmark::DoNotOptimize(reader.value<long double>());
    }
}

BENCHMARK(parse_float);
BENCHMARK(parse_double);
BENCHMARK(parse_long_double);

void value_float(benchmark::State& state)
{
    char input[] = "291.192";
    json::reader reader(input);
    for (auto _ : state)
    {
        benchmark::DoNotOptimize(reader.value<float>());
    }
}

void value_double(benchmark::State& state)
{
    char input[] = "291.192";
    json::reader reader(input);
    for (auto _ : state)
    {
        benchmark::DoNotOptimize(reader.value<double>());
    }
}

void value_long_double(benchmark::State& state)
{
    char input[] = "291.192";
    json::reader reader(input);
    for (auto _ : state)
    {
        benchmark::DoNotOptimize(reader.value<long double>());
    }
}

BENCHMARK(value_float);
BENCHMARK(value_double);
BENCHMARK(value_long_double);

void value_float_fraction(benchmark::State& state)
{
    char input[] = "45.550544999999943";
    json::reader reader(input);
    for (auto _ : state)
    {
        benchmark::DoNotOptimize(reader.value<float>());
    }
}

void value_double_fraction(benchmark::State& state)
{
    char input[] = "45.550544999999943";
    json::reader reader(input);
    for (auto _ : state)
    {
        benchmark::DoNotOptimize(reader.value<double>());
    }
}

void value_long_double_fraction(benchmark::State& state)
{
    char input[] = "45.550544999999943";
    json::reader reader(input);
    for (auto _ : state)
    {
        benchmark::DoNotOptimize(reader.value<long double>());
    }
}

BENCHMARK(value_float_fraction);
BENCHMARK(value_double_fraction);
BENCHMARK(value_long_double_fraction);

void value_real_1(benchmark::State& state)
{
    char input[] = "0.1";
    json::reader reader(input);
    for (auto _ : state)
    {
        benchmark::DoNotOptimize(reader.value<double>());
    }
}

void value_real_2(benchmark::State& state)
{
    char input[] = "0.12";
    json::reader reader(input);
    for (auto _ : state)
    {
        benchmark::DoNotOptimize(reader.value<double>());
    }
}

void value_real_3(benchmark::State& state)
{
    char input[] = "0.123";
    json::reader reader(input);
    for (auto _ : state)
    {
        benchmark::DoNotOptimize(reader.value<double>());
    }
}

void value_real_4(benchmark::State& state)
{
    char input[] = "0.1234";
    json::reader reader(input);
    for (auto _ : state)
    {
        benchmark::DoNotOptimize(reader.value<double>());
    }
}

void value_real_5(benchmark::State& state)
{
    char input[] = "0.12345";
    json::reader reader(input);
    for (auto _ : state)
    {
        benchmark::DoNotOptimize(reader.value<double>());
    }
}

void value_real_6(benchmark::State& state)
{
    char input[] = "0.123456";
    json::reader reader(input);
    for (auto _ : state)
    {
        benchmark::DoNotOptimize(reader.value<double>());
    }
}

void value_real_7(benchmark::State& state)
{
    char input[] = "0.1234567";
    json::reader reader(input);
    for (auto _ : state)
    {
        benchmark::DoNotOptimize(reader.value<double>());
    }
}

void value_real_8(benchmark::State& state)
{
    char input[] = "0.12345678";
    json::reader reader(input);
    for (auto _ : state)
    {
        benchmark::DoNotOptimize(reader.value<double>());
    }
}

void value_real_9(benchmark::State& state)
{
    char input[] = "0.123456789";
    json::reader reader(input);
    for (auto _ : state)
    {
        benchmark::DoNotOptimize(reader.value<double>());
    }
}

void value_real_10(benchmark::State& state)
{
    char input[] = "0.1234567890";
    json::reader reader(input);
    for (auto _ : state)
    {
        benchmark::DoNotOptimize(reader.value<double>());
    }
}

void value_real_11(benchmark::State& state)
{
    char input[] = "0.12345678901";
    json::reader reader(input);
    for (auto _ : state)
    {
        benchmark::DoNotOptimize(reader.value<double>());
    }
}

void value_real_12(benchmark::State& state)
{
    char input[] = "0.123456789012";
    json::reader reader(input);
    for (auto _ : state)
    {
        benchmark::DoNotOptimize(reader.value<double>());
    }
}

void value_real_13(benchmark::State& state)
{
    char input[] = "0.1234567890123";
    json::reader reader(input);
    for (auto _ : state)
    {
        benchmark::DoNotOptimize(reader.value<double>());
    }
}

void value_real_14(benchmark::State& state)
{
    char input[] = "0.12345678901234";
    json::reader reader(input);
    for (auto _ : state)
    {
        benchmark::DoNotOptimize(reader.value<double>());
    }
}

void value_real_15(benchmark::State& state)
{
    char input[] = "0.123456789012345";
    json::reader reader(input);
    for (auto _ : state)
    {
        benchmark::DoNotOptimize(reader.value<double>());
    }
}

void value_real_16(benchmark::State& state)
{
    char input[] = "0.1234567890123456";
    json::reader reader(input);
    for (auto _ : state)
    {
        benchmark::DoNotOptimize(reader.value<double>());
    }
}

void value_real_17(benchmark::State& state)
{
    char input[] = "0.12345678901234567";
    json::reader reader(input);
    for (auto _ : state)
    {
        benchmark::DoNotOptimize(reader.value<double>());
    }
}

void value_real_18(benchmark::State& state)
{
    char input[] = "0.123456789012345678";
    json::reader reader(input);
    for (auto _ : state)
    {
        benchmark::DoNotOptimize(reader.value<double>());
    }
}

BENCHMARK(value_real_1);
BENCHMARK(value_real_2);
BENCHMARK(value_real_3);
BENCHMARK(value_real_4);
BENCHMARK(value_real_5);
BENCHMARK(value_real_6);
BENCHMARK(value_real_7);
BENCHMARK(value_real_8);
BENCHMARK(value_real_9);
BENCHMARK(value_real_10);
BENCHMARK(value_real_11);
BENCHMARK(value_real_12);
BENCHMARK(value_real_13);
BENCHMARK(value_real_14);
BENCHMARK(value_real_15);
BENCHMARK(value_real_16);
BENCHMARK(value_real_17);
BENCHMARK(value_real_18);

void parse_string8(benchmark::State& state)
{
    char input[] = "\"ABCDEFGH\"";
    for (auto _ : state)
    {
        json::reader reader(input);
        benchmark::DoNotOptimize(reader.value<std::string>());
    }
}

BENCHMARK(parse_string8);

void value_string8(benchmark::State& state)
{
    char input[] = "\"ABCDEFGH\"";
    json::reader reader(input);
    for (auto _ : state)
    {
        benchmark::DoNotOptimize(reader.value<std::string>());
    }
}

BENCHMARK(value_string8);

void parse_whitespaces(benchmark::State& state)
{
    char input[] = "                                                                                                                   291";
    for (auto _ : state)
    {
        json::reader reader(input);
        benchmark::DoNotOptimize(reader.value<std::uint16_t>());
    }
}

BENCHMARK(parse_whitespaces);

BENCHMARK_MAIN();
