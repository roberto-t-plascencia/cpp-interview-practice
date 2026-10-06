#pragma once
// ============================================================================
// 02 - Top K Frequent Errors                                Difficulty: Medium
// ============================================================================
// Given a list of error codes pulled from logs, return the k most frequent
// codes. Order the result by count (highest first); break ties alphabetically
// (lexicographically smallest first). If k is larger than the number of
// distinct codes, return all of them.
//
//   topKFrequent({"E500","E404","E500","E503","E404","E500"}, 2)
//     -> {"E500", "E404"}
//
// Concepts: std::unordered_map counting, custom comparators, lambdas,
//           std::priority_queue (min-heap of size k) or std::partial_sort.
// Stretch: do it in O(n log k) instead of O(n log n).
// ============================================================================
#include <string>
#include <vector>

inline std::vector<std::string> topKFrequent(const std::vector<std::string>& codes, int k) {
    // TODO: implement
    (void)codes;
    (void)k;
    return {};
}
