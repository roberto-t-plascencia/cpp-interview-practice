#include "03_merge_intervals.hpp"

#include <gtest/gtest.h>

using V = std::vector<Interval>;

TEST(MergeIntervals, MergesOverlapping) {
    EXPECT_EQ(merge({{1, 3}, {2, 6}, {8, 10}, {15, 18}}), (V{{1, 6}, {8, 10}, {15, 18}}));
}

TEST(MergeIntervals, MergesTouching) {
    EXPECT_EQ(merge({{1, 4}, {4, 5}}), (V{{1, 5}}));
}

TEST(MergeIntervals, HandlesUnsortedInput) {
    EXPECT_EQ(merge({{8, 10}, {1, 3}, {2, 6}}), (V{{1, 6}, {8, 10}}));
}

TEST(MergeIntervals, ContainedIntervalDoesNotShrink) {
    EXPECT_EQ(merge({{1, 10}, {2, 3}, {4, 5}}), (V{{1, 10}}));
}

TEST(MergeIntervals, EmptyAndSingle) {
    EXPECT_TRUE(merge({}).empty());
    EXPECT_EQ(merge({{5, 7}}), (V{{5, 7}}));
}
