###############################################################################
#
# Copyright (C) 2015 Bjorn Reese <breese@users.sourceforge.net>
#
# Distributed under the Boost Software License, Version 1.0.
#    (See accompanying file LICENSE_1_0.txt or copy at
#          http://www.boost.org/LICENSE_1_0.txt)
#
###############################################################################

add_executable(test_json
  runner.cpp
  decoder_suite.cpp
  encoder_suite.cpp
)

target_link_libraries(test_json ${BOOST_PROTOCOL_DEPENDENT_LIBRARIES})
