###############################################################################
#
# Copyright (C) 2017 Bjorn Reese <breese@users.sourceforge.net>
#
# Distributed under the Boost Software License, Version 1.0.
#    (See accompanying file LICENSE_1_0.txt or copy at
#          http://www.boost.org/LICENSE_1_0.txt)
#
###############################################################################

trial_add_test(dynamic_variable_suite variable_suite.cpp)
trial_add_test(dynamic_variable_comparison_suite variable_comparison_suite.cpp)
trial_add_test(dynamic_variable_iterator_suite variable_iterator_suite.cpp)
trial_add_test(dynamic_variable_io_suite variable_io_suite.cpp)

trial_add_test(dynamic_uvariable_suite uvariable_suite.cpp)

trial_add_test(dynamic_algorithm_key_suite algorithm/key_suite.cpp)

trial_add_test(dynamic_std_algorithm_suite std/algorithm_suite.cpp)
trial_add_test(dynamic_std_convert_suite std/convert_suite.cpp)
trial_add_test(dynamic_boost_convert_suite boost/convert_suite.cpp)
