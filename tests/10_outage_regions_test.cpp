#include "10_outage_regions.hpp"

#include <gtest/gtest.h>

TEST(OutageRegions, Example) {
    EXPECT_EQ(countOutageRegions({"XX..", "X..X", "..XX"}), 2);
}

TEST(OutageRegions, DiagonalDoesNotConnect) {
    EXPECT_EQ(countOutageRegions({"X.X", ".X.", "X.X"}), 5);
}

TEST(OutageRegions, AllHealthyOrEmpty) {
    EXPECT_EQ(countOutageRegions({"...", "..."}), 0);
    EXPECT_EQ(countOutageRegions({}), 0);
    EXPECT_EQ(countOutageRegions({""}), 0);
}

TEST(OutageRegions, WholeFloorDownIsOneRegion) {
    EXPECT_EQ(countOutageRegions({"XXX", "XXX", "XXX"}), 1);
}

TEST(OutageRegions, SnakeShapedRegion) {
    EXPECT_EQ(countOutageRegions({"XXXXX", "....X", "XXXXX", "X....", "XXXXX"}), 1);
}

TEST(OutageRegions, RaggedRows) {
    EXPECT_EQ(countOutageRegions({"X", "XX.X", "", "X"}), 3);
}

TEST(OutageRegions, LargeGridDoesNotOverflowStack) {
    std::vector<std::string> big(500, std::string(500, 'X'));
    EXPECT_EQ(countOutageRegions(big), 1);
}
