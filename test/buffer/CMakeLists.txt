###############################################################################
#
# Copyright (C) 2015 Bjorn Reese <breese@users.sourceforge.net>
#
# Distributed under the Boost Software License, Version 1.0.
#    (See accompanying file LICENSE_1_0.txt or copy at
#          http://www.boost.org/LICENSE_1_0.txt)
#
###############################################################################

add_executable(test_buffer
  runner.cpp
  container_suite.cpp
  vector_suite.cpp
)

target_link_libraries(test_buffer ${TRIAL_PROTOCOL_DEPENDENT_LIBRARIES})
