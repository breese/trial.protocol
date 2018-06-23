###############################################################################
#
# Copyright (C) 2015 Bjorn Reese <breese@users.sourceforge.net>
#
# Distributed under the Boost Software License, Version 1.0.
#    (See accompanying file LICENSE_1_0.txt or copy at
#          http://www.boost.org/LICENSE_1_0.txt)
#
###############################################################################

cmake_minimum_required(VERSION 3.8)

set(TRIAL_PROTOCOL_BUILD_DIR ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${TRIAL_PROTOCOL_BUILD_DIR}/lib)
set(EXECUTABLE_OUTPUT_PATH ${TRIAL_PROTOCOL_BUILD_DIR}/bin)

enable_testing()

add_subdirectory(cmake)
add_subdirectory(test)
add_subdirectory(example/json)
