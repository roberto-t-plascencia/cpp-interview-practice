#pragma once
// ============================================================================
// 03 - Merge Maintenance Windows                              Difficulty: Easy
// ============================================================================
// Each maintenance window is a closed interval [start, end] in minutes.
// Merge all overlapping windows and return them sorted by start time.
// Windows that touch (one ends exactly when the next starts) also merge.
//
//   merge({{1,3},{2,6},{8,10},{15,18}}) -> {{1,6},{8,10},{15,18}}
//   merge({{1,4},{4,5}})                -> {{1,5}}
//
// Concepts: std::sort with a lambda, structured bindings, pass-by-value + move.
// ============================================================================
#include <utility>
#include <vector>

using Interval = std::pair<int, int>;

inline std::vector<Interval> merge(std::vector<Interval> windows) {
    // TODO: implement
    (void)windows;
    return {};
}
