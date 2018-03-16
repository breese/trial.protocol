###############################################################################
#
# Copyright (C) 2015 Bjorn Reese <breese@users.sourceforge.net>
#
# Distributed under the Boost Software License, Version 1.0.
#    (See accompanying file LICENSE_1_0.txt or copy at
#          http://www.boost.org/LICENSE_1_0.txt)
#
###############################################################################

# Pull processing
trial_add_test(bintoken_decoder_suite decoder_suite.cpp)
trial_add_test(bintoken_encoder_suite encoder_suite.cpp)
trial_add_test(bintoken_reader_suite reader_suite.cpp)
trial_add_test(bintoken_writer_suite writer_suite.cpp)

# Serialization
trial_add_test(bintoken_iarchive_suite iarchive_suite.cpp)
trial_add_test(bintoken_iarchive_std_suite iarchive_std_suite.cpp)
trial_add_test(bintoken_iarchive_boost_suite iarchive_boost_suite.cpp)
trial_add_test(bintoken_oarchive_suite oarchive_suite.cpp)
trial_add_test(bintoken_oarchive_std_suite oarchive_std_suite.cpp)
trial_add_test(bintoken_oarchive_boost_suite oarchive_boost_suite.cpp)

# Tree processing
trial_add_test(bintoken_parse_suite parse_suite.cpp)
trial_add_test(bintoken_format_suite format_suite.cpp)
