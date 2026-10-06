#include "01_lru_cache.hpp"

#include <gtest/gtest.h>

TEST(LRUCache, ReturnsNulloptForMissingKey) {
    LRUCache cache(2);
    EXPECT_FALSE(cache.get(42).has_value());
}

TEST(LRUCache, StoresAndRetrievesValues) {
    LRUCache cache(2);
    cache.put(1, 100);
    cache.put(2, 200);
    EXPECT_EQ(cache.get(1), 100);
    EXPECT_EQ(cache.get(2), 200);
    EXPECT_EQ(cache.size(), 2u);
}

TEST(LRUCache, EvictsLeastRecentlyUsed) {
    LRUCache cache(2);
    cache.put(1, 1);
    cache.put(2, 2);
    cache.put(3, 3);  // evicts 1
    EXPECT_FALSE(cache.get(1).has_value());
    EXPECT_EQ(cache.get(2), 2);
    EXPECT_EQ(cache.get(3), 3);
    EXPECT_EQ(cache.size(), 2u);
}

TEST(LRUCache, GetRefreshesRecency) {
    LRUCache cache(2);
    cache.put(1, 1);
    cache.put(2, 2);
    ASSERT_EQ(cache.get(1), 1);  // 1 is now most recent, so 2 is LRU
    cache.put(3, 3);             // evicts 2
    EXPECT_EQ(cache.get(1), 1);
    EXPECT_FALSE(cache.get(2).has_value());
    EXPECT_EQ(cache.get(3), 3);
}

TEST(LRUCache, UpdateExistingKeyDoesNotEvictAndRefreshes) {
    LRUCache cache(2);
    cache.put(1, 1);
    cache.put(2, 2);
    cache.put(1, 10);  // update, 2 becomes LRU
    EXPECT_EQ(cache.size(), 2u);
    cache.put(3, 3);   // evicts 2
    EXPECT_EQ(cache.get(1), 10);
    EXPECT_FALSE(cache.get(2).has_value());
}

TEST(LRUCache, ZeroCapacityStoresNothing) {
    LRUCache cache(0);
    cache.put(1, 1);
    EXPECT_FALSE(cache.get(1).has_value());
    EXPECT_EQ(cache.size(), 0u);
}
