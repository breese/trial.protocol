###############################################################################
#
# Copyright (C) 2019 Bjorn Reese <breese@users.sourceforge.net>
#
# Distributed under the Boost Software License, Version 1.0.
#    (See accompanying file LICENSE_1_0.txt or copy at
#          http://www.boost.org/LICENSE_1_0.txt)
#
###############################################################################

# Download benchmark framework.
#
# Using ExternalProject over git submodules to defer git fetching until
# actually needed.

include(ExternalProject)

find_package(Threads REQUIRED)

ExternalProject_Add(project-google-test
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG master
  GIT_SHALLOW 1
  UPDATE_COMMAND ""
  PATCH_COMMAND ""
  CMAKE_ARGS
    -DCMAKE_BUILD_TYPE=Release
    -DCMAKE_INSTALL_PREFIX=${CMAKE_CURRENT_BINARY_DIR}
    -DCMAKE_INSTALL_LIBDIR=lib
    -DCMAKE_INSTALL_MESSAGE=NEVER
  )

ExternalProject_Add(project-google-benchmark
  GIT_REPOSITORY https://github.com/google/benchmark.git
  GIT_TAG master
  GIT_SHALLOW 1
  UPDATE_COMMAND ""
  PATCH_COMMAND ""
  CMAKE_ARGS
    -DCMAKE_BUILD_TYPE=Release
    -DCMAKE_INSTALL_PREFIX=${CMAKE_CURRENT_BINARY_DIR}
    -DCMAKE_INSTALL_MESSAGE=NEVER
    -DBENCHMARK_ENABLE_TESTING=OFF
  )

file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/include)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib)

add_library(Google::test STATIC IMPORTED GLOBAL)
add_dependencies(Google::test project-google-test)
set_target_properties(Google::test PROPERTIES
  INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_BINARY_DIR}/include
  INTERFACE_LINK_LIBRARIES "${CMAKE_THREAD_LIBS_INIT}"
  IMPORTED_LOCATION ${CMAKE_CURRENT_BINARY_DIR}/lib/libgtest.a
  )

add_library(Google::benchmark STATIC IMPORTED GLOBAL)
add_dependencies(Google::benchmark project-google-benchmark)
set_target_properties(Google::benchmark PROPERTIES
  INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_BINARY_DIR}/include
  INTERFACE_LINK_LIBRARIES Google::test
  IMPORTED_LOCATION ${CMAKE_CURRENT_BINARY_DIR}/lib/libbenchmark.a
  )
