###############################################################################
#
# Copyright (C) 2019 Bjorn Reese <breese@users.sourceforge.net>
#
# Distributed under the Boost Software License, Version 1.0.
#    (See accompanying file LICENSE_1_0.txt or copy at
#          http://www.boost.org/LICENSE_1_0.txt)
#
###############################################################################

include(GoogleBenchmark.cmake)

add_custom_target(benchmark)

function(trial_protocol_add_benchmark name)
  add_executable(${name} ${ARGN})
  target_link_libraries(${name} trial-protocol Google::benchmark)
  target_compile_features(${name} PRIVATE ${TRIAL_PROTOCOL_FEATURES})
  target_compile_options(${name} PRIVATE ${TRIAL_PROTOCOL_WARNING_FLAGS})
  add_dependencies(benchmark ${name})
endfunction()

# bintoken
trial_protocol_add_benchmark(benchmark_bintoken_reader bintoken/benchmark_reader.cpp)

# json
trial_protocol_add_benchmark(benchmark_json_reader json/benchmark_reader.cpp)
trial_protocol_add_benchmark(benchmark_json_push_parser json/benchmark_push_parser.cpp)
