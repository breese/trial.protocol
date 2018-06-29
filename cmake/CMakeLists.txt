###############################################################################
#
# Copyright (C) 2018 Bjorn Reese <breese@users.sourceforge.net>
#
# Distributed under the Boost Software License, Version 1.0.
#    (See accompanying file LICENSE_1_0.txt or copy at
#          http://www.boost.org/LICENSE_1_0.txt)
#
###############################################################################

cmake_minimum_required(VERSION 3.7)
project(trial.protocol)

set(TRIAL_PROTOCOL_BUILD_DIR ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${TRIAL_PROTOCOL_BUILD_DIR}/lib)
set(EXECUTABLE_OUTPUT_PATH ${TRIAL_PROTOCOL_BUILD_DIR}/bin)

if (${CMAKE_VERSION} VERSION_LESS 3.8)
  set(TRIAL_PROTOCOL_PROPERTIES CXX_STANDARD 11)
else()
  set(TRIAL_PROTOCOL_FEATURES cxx_std_11)
endif()

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
target_compile_features(trial-protocol INTERFACE ${TRIAL_PROTOCOL_FEATURES})
if (TRIAL_PROTOCOL_PROPERTIES)
  set_target_properties(trial-protocol PROPERTIES ${TRIAL_PROTOCOL_PROPERTIES})
endif()
target_include_directories(trial-protocol INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/../include" ${Boost_INCLUDE_DIR})
target_link_libraries(trial-protocol INTERFACE ${Boost_SERIALIZATION_LIBRARY} ${Boost_SYSTEM_LIBRARY})
