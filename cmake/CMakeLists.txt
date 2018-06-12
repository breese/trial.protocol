###############################################################################
#
# Copyright (C) 2018 Bjorn Reese <breese@users.sourceforge.net>
#
# Distributed under the Boost Software License, Version 1.0.
#    (See accompanying file LICENSE_1_0.txt or copy at
#          http://www.boost.org/LICENSE_1_0.txt)
#
###############################################################################

cmake_minimum_required(VERSION 3.8)
project(trial.protocol)

set(TRIAL_PROTOCOL_BUILD_DIR ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${TRIAL_PROTOCOL_BUILD_DIR}/lib)
set(EXECUTABLE_OUTPUT_PATH ${TRIAL_PROTOCOL_BUILD_DIR}/bin)

###############################################################################
# Boost package
###############################################################################

set(Boost_COMPONENTS serialization system)
find_package(Boost 1.55.0 COMPONENTS ${Boost_COMPONENTS})
if (NOT ${Boost_FOUND})
  message(FATAL_ERROR "${Boost_ERROR_REASON}")
endif()

###############################################################################
# Trial.Protocol package
###############################################################################

add_library(trial-protocol INTERFACE)
target_compile_features(trial-protocol INTERFACE cxx_std_11)
target_include_directories(trial-protocol INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/../include" ${Boost_INCLUDE_DIR})
target_link_libraries(trial-protocol INTERFACE ${Boost_SERIALIZATION_LIBRARY} ${Boost_SYSTEM_LIBRARY})
