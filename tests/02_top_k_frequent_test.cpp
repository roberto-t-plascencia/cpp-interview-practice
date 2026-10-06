#include "02_top_k_frequent.hpp"

#include <gtest/gtest.h>

using Codes = std::vector<std::string>;

TEST(TopKFrequent, BasicExample) {
    Codes codes{"E500", "E404", "E500", "E503", "E404", "E500"};
    EXPECT_EQ(topKFrequent(codes, 2), (Codes{"E500", "E404"}));
}

TEST(TopKFrequent, TiesBrokenAlphabetically) {
    Codes codes{"B", "A", "C", "B", "A", "C"};
    EXPECT_EQ(topKFrequent(codes, 2), (Codes{"A", "B"}));
    EXPECT_EQ(topKFrequent(codes, 3), (Codes{"A", "B", "C"}));
}

TEST(TopKFrequent, KLargerThanDistinctReturnsAll) {
    Codes codes{"X", "Y", "X"};
    EXPECT_EQ(topKFrequent(codes, 10), (Codes{"X", "Y"}));
}

TEST(TopKFrequent, EmptyInputOrZeroK) {
    EXPECT_TRUE(topKFrequent({}, 3).empty());
    EXPECT_TRUE(topKFrequent({"A", "B"}, 0).empty());
}

TEST(TopKFrequent, OrderedByCountDescending) {
    Codes codes{"timeout", "dns", "timeout", "tls", "timeout", "dns", "refused"};
    EXPECT_EQ(topKFrequent(codes, 4), (Codes{"timeout", "dns", "refused", "tls"}));
}
