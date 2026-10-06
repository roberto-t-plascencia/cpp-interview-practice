#pragma once
// ============================================================================
// 01 - LRU Cache                                            Difficulty: Medium
// ============================================================================
// Build a fixed-capacity cache that evicts the Least Recently Used entry when
// it is full. Both get() and put() must run in O(1) average time.
//
//   - get(key): returns the value if present (and marks it most recently
//     used), or std::nullopt if missing.
//   - put(key, value): inserts or updates the key and marks it most recently
//     used. If inserting a NEW key would exceed capacity, evict the least
//     recently used key first.
//   - size(): number of entries currently stored.
//
// Real-world tie-in: this is the same idea as the Redis page cache you built
// at Squarecoil, just in-process.
//
// Concepts: std::list + std::unordered_map, iterators, list::splice.
// Hint: keep a list ordered from most- to least-recently used, and a map from
//       key to the list iterator so you can move a node to the front in O(1).
// ============================================================================
#include <cstddef>
#include <list>
#include <optional>
#include <unordered_map>
#include <utility>

class LRUCache {
public:
    explicit LRUCache(std::size_t capacity) : capacity_(capacity) {}

    std::optional<int> get(int key) {
        // TODO: implement
        (void)key;
        return std::nullopt;
    }

    void put(int key, int value) {
        // TODO: implement
        (void)key;
        (void)value;
    }

    std::size_t size() const {
        // TODO: implement
        return 0;
    }

private:
    std::size_t capacity_;
    // TODO: add your data members here
};
