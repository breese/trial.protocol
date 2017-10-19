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
trial_add_test(dynamic_variable_concept_suite variable_concept_suite.cpp)
trial_add_test(dynamic_variable_capacity_suite variable_capacity_suite.cpp)
trial_add_test(dynamic_variable_modifier_suite variable_modifier_suite.cpp)
trial_add_test(dynamic_variable_operator_suite variable_operator_suite.cpp)
trial_add_test(dynamic_variable_comparison_suite variable_comparison_suite.cpp)
trial_add_test(dynamic_variable_iterator_suite variable_iterator_suite.cpp)
trial_add_test(dynamic_variable_io_suite variable_io_suite.cpp)

trial_add_test(dynamic_algorithm_count_suite algorithm/count_suite.cpp)
trial_add_test(dynamic_algorithm_find_suite algorithm/find_suite.cpp)
trial_add_test(dynamic_algorithm_visit_suite algorithm/visit_suite.cpp)

# <algorithm>
trial_add_test(dynamic_std_adjacent_find_suite std/adjacent_find_suite.cpp)
trial_add_test(dynamic_std_all_of_suite std/all_of_suite.cpp)
trial_add_test(dynamic_std_any_of_suite std/any_of_suite.cpp)
trial_add_test(dynamic_std_binary_search_suite std/binary_search_suite.cpp)
trial_add_test(dynamic_std_copy_suite std/copy_suite.cpp)
trial_add_test(dynamic_std_copy_backward_suite std/copy_backward_suite.cpp)
trial_add_test(dynamic_std_count_suite std/count_suite.cpp)
trial_add_test(dynamic_std_count_if_suite std/count_if_suite.cpp)
trial_add_test(dynamic_std_equal_suite std/equal_suite.cpp)
trial_add_test(dynamic_std_equal_range_suite std/equal_range_suite.cpp)
trial_add_test(dynamic_std_find_suite std/find_suite.cpp)
trial_add_test(dynamic_std_find_if_suite std/find_if_suite.cpp)
trial_add_test(dynamic_std_insert_iterator_suite std/insert_iterator_suite.cpp)
trial_add_test(dynamic_std_is_partitioned_suite std/is_partitioned_suite.cpp)
trial_add_test(dynamic_std_is_sorted_suite std/is_sorted_suite.cpp)
trial_add_test(dynamic_std_lexicographical_compare_suite std/lexicographical_compare_suite.cpp)
trial_add_test(dynamic_std_lower_bound_suite std/lower_bound_suite.cpp)
trial_add_test(dynamic_std_max_element_suite std/max_element_suite.cpp)
trial_add_test(dynamic_std_mismatch_suite std/mismatch_suite.cpp)
trial_add_test(dynamic_std_move_suite std/move_suite.cpp)
trial_add_test(dynamic_std_move_backward_suite std/move_backward_suite.cpp)
trial_add_test(dynamic_std_none_of_suite std/none_of_suite.cpp)
trial_add_test(dynamic_std_partition_suite std/partition_suite.cpp)
trial_add_test(dynamic_std_partition_point_suite std/partition_point_suite.cpp)
trial_add_test(dynamic_std_remove_suite std/remove_suite.cpp)
trial_add_test(dynamic_std_replace_suite std/replace_suite.cpp)
trial_add_test(dynamic_std_reverse_suite std/reverse_suite.cpp)
trial_add_test(dynamic_std_rotate_suite std/rotate_suite.cpp)
trial_add_test(dynamic_std_search_suite std/search_suite.cpp)
trial_add_test(dynamic_std_stable_partition_suite std/stable_partition_suite.cpp)
trial_add_test(dynamic_std_swap_ranges_suite std/swap_ranges_suite.cpp)
trial_add_test(dynamic_std_transform_suite std/transform_suite.cpp)
trial_add_test(dynamic_std_unique_suite std/unique_suite.cpp)
trial_add_test(dynamic_std_upper_bound_suite std/upper_bound_suite.cpp)

# <numeric>
trial_add_test(dynamic_std_accumulate_suite std/accumulate_suite.cpp)
trial_add_test(dynamic_std_iota_suite std/iota_suite.cpp)
trial_add_test(dynamic_std_partial_sum_suite std/partial_sum_suite.cpp)

trial_add_test(dynamic_std_convert_suite std/convert_suite.cpp)
trial_add_test(dynamic_boost_convert_suite boost/convert_suite.cpp)
