#include "05_network_delay.hpp"

#include <gtest/gtest.h>

TEST(PropagationDelay, PicksShortestPaths) {
    EXPECT_EQ(propagationDelay(4, {{0, 1, 1}, {0, 2, 4}, {1, 2, 2}, {2, 3, 1}}, 0), 4);
}

TEST(PropagationDelay, UnreachableNodeReturnsMinusOne) {
    EXPECT_EQ(propagationDelay(3, {{0, 1, 5}}, 0), -1);
}

TEST(PropagationDelay, LinksAreOneWay) {
    EXPECT_EQ(propagationDelay(2, {{1, 0, 1}}, 0), -1);
    EXPECT_EQ(propagationDelay(2, {{1, 0, 1}}, 1), 1);
}

TEST(PropagationDelay, SingleNodeIsInstant) {
    EXPECT_EQ(propagationDelay(1, {}, 0), 0);
}

TEST(PropagationDelay, ParallelLinksUseFastest) {
    EXPECT_EQ(propagationDelay(2, {{0, 1, 9}, {0, 1, 3}, {0, 1, 7}}, 0), 3);
}

TEST(PropagationDelay, LongerHopCountCanBeFaster) {
    // direct 0->3 costs 10, but 0->1->2->3 costs 3
    EXPECT_EQ(propagationDelay(4, {{0, 3, 10}, {0, 1, 1}, {1, 2, 1}, {2, 3, 1}}, 0), 3);
}
