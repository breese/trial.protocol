###############################################################################
#
# Copyright (C) 2015 Bjorn Reese <breese@users.sourceforge.net>
#
# Distributed under the Boost Software License, Version 1.0.
#    (See accompanying file LICENSE_1_0.txt or copy at
#          http://www.boost.org/LICENSE_1_0.txt)
#
###############################################################################

cmake_minimum_required(VERSION 2.8)
project(trial.protocol)

set(TRIAL_PROTOCOL_BUILD_DIR ${CMAKE_BINARY_DIR})
set(TRIAL_PROTOCOL_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
set(LIBRARY_OUTPUT_PATH ${TRIAL_PROTOCOL_BUILD_DIR}/lib)
set(EXECUTABLE_OUTPUT_PATH ${TRIAL_PROTOCOL_BUILD_DIR}/bin)

set(CMAKE_CXX_STANDARD 11)

if (MSVC)
  set(TRIAL_PROTOCOL_WARNING_FLAGS /W4)
else()
  set(TRIAL_PROTOCOL_WARNING_FLAGS -Wall -Wextra -pedantic -Werror=return-type)
endif()

###############################################################################
# Boost package
###############################################################################

set(Boost_COMPONENTS filesystem serialization system)
find_package(Boost 1.55.0 COMPONENTS ${Boost_COMPONENTS})
if (NOT ${Boost_FOUND})
  message(FATAL_ERROR "${Boost_ERROR_REASON}")
endif()

include_directories(BEFORE ${Boost_INCLUDE_DIR})

set(TRIAL_PROTOCOL_DEPENDENT_LIBRARIES
  ${Boost_SERIALIZATION_LIBRARY}
  ${Boost_SYSTEM_LIBRARY})

###############################################################################
# Trial.Protocol package
###############################################################################

include_directories(BEFORE include)

install(DIRECTORY ${TRIAL_PROTOCOL_ROOT}/include/ DESTINATION include)

function(trial_add_test name)
  add_executable(${name} ${ARGN})
  target_link_libraries(${name} ${TRIAL_PROTOCOL_DEPENDENT_LIBRARIES})
  add_test(${name} ${EXECUTABLE_OUTPUT_PATH}/${name})
  target_compile_options(${name} PRIVATE ${TRIAL_PROTOCOL_WARNING_FLAGS})
endfunction()

enable_testing()

add_subdirectory(test/core)
add_subdirectory(test/buffer)
add_subdirectory(test/dynamic)
add_subdirectory(test/json)
add_subdirectory(test/bintoken)

add_subdirectory(doc)

###############################################################################
# Examples
###############################################################################

add_subdirectory(example/json EXCLUDE_FROM_ALL)
