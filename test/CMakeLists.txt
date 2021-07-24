###############################################################################
#
# Copyright (C) 2018 Bjorn Reese <breese@users.sourceforge.net>
#
# Distributed under the Boost Software License, Version 1.0.
#    (See accompanying file LICENSE_1_0.txt or copy at
#          http://www.boost.org/LICENSE_1_0.txt)
#
###############################################################################

if (MSVC)
  set(TRIAL_PROTOCOL_WARNING_FLAGS /W4)
else()
  set(TRIAL_PROTOCOL_WARNING_FLAGS -Wall -Wextra -pedantic -Werror=return-type)
endif()

###############################################################################
# Boost package
###############################################################################

set(Boost_COMPONENTS filesystem serialization system)
find_package(Boost 1.55.0 QUIET COMPONENTS ${Boost_COMPONENTS})
if (NOT ${Boost_FOUND})
  message(FATAL_ERROR "${Boost_ERROR_REASON}")
endif()

###############################################################################
# Trial.Protocol package
###############################################################################

function(trial_add_test name)
  add_executable(${name} ${ARGN})
  target_compile_options(${name} PRIVATE ${TRIAL_PROTOCOL_WARNING_FLAGS})
  target_link_libraries(${name} trial-protocol)
  add_test(${name} ${EXECUTABLE_OUTPUT_PATH}/${name})
endfunction()

trial_add_test(tribool_suite tribool_suite.cpp)

add_subdirectory(core)
add_subdirectory(buffer)
add_subdirectory(dynamic)
add_subdirectory(json)
add_subdirectory(bintoken)
