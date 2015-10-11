###############################################################################
#
# Copyright (C) 2015 Bjorn Reese <breese@users.sourceforge.net>
#
# Distributed under the Boost Software License, Version 1.0.
#    (See accompanying file LICENSE_1_0.txt or copy at
#          http://www.boost.org/LICENSE_1_0.txt)
#
###############################################################################

trial_add_test(json_decoder_suite decoder_suite.cpp)
trial_add_test(json_encoder_suite encoder_suite.cpp)
trial_add_test(json_reader_suite reader_suite.cpp)
trial_add_test(json_writer_suite writer_suite.cpp)
trial_add_test(json_iarchive_suite iarchive_suite.cpp)
trial_add_test(json_oarchive_suite oarchive_suite.cpp)
