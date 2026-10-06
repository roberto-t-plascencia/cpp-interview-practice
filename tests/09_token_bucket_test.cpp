#include "09_token_bucket.hpp"

#include <gtest/gtest.h>

TEST(TokenBucket, StartsFullAndAllowsBurstUpToCapacity) {
    TokenBucket bucket(3, 1);
    EXPECT_TRUE(bucket.allow(0.0));
    EXPECT_TRUE(bucket.allow(0.0));
    EXPECT_TRUE(bucket.allow(0.0));
    EXPECT_FALSE(bucket.allow(0.0));
}

TEST(TokenBucket, RefillsOverTime) {
    TokenBucket bucket(2, 2);  // 2 tokens per second
    EXPECT_TRUE(bucket.allow(0.0));
    EXPECT_TRUE(bucket.allow(0.0));
    EXPECT_FALSE(bucket.allow(0.0));
    EXPECT_FALSE(bucket.allow(0.25));  // only 0.5 tokens back
    EXPECT_TRUE(bucket.allow(0.5));    // 1 token back
    EXPECT_FALSE(bucket.allow(0.5));
}

TEST(TokenBucket, NeverExceedsCapacity) {
    TokenBucket bucket(2, 10);
    EXPECT_TRUE(bucket.allow(0.0));
    // A long idle period refills only up to capacity (2), not 1000 tokens.
    EXPECT_TRUE(bucket.allow(100.0));
    EXPECT_TRUE(bucket.allow(100.0));
    EXPECT_FALSE(bucket.allow(100.0));
}

TEST(TokenBucket, CostGreaterThanOne) {
    TokenBucket bucket(5, 1);
    EXPECT_TRUE(bucket.allow(0.0, 4));
    EXPECT_FALSE(bucket.allow(0.0, 2));  // only 1 left, and nothing is spent
    EXPECT_TRUE(bucket.allow(0.0, 1));
}

TEST(TokenBucket, FractionalRefillRate) {
    TokenBucket bucket(1, 0.5);  // one token every 2 seconds
    EXPECT_TRUE(bucket.allow(0.0));
    EXPECT_FALSE(bucket.allow(1.0));
    EXPECT_TRUE(bucket.allow(2.0));
}

TEST(TokenBucket, TimeGoingBackwardsDoesNotAddTokens) {
    TokenBucket bucket(1, 1);
    EXPECT_TRUE(bucket.allow(10.0));
    EXPECT_FALSE(bucket.allow(5.0));
    EXPECT_FALSE(bucket.allow(10.5));
    EXPECT_TRUE(bucket.allow(11.0));
}
