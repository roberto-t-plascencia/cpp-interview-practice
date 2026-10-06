#pragma once
// Reference solution - 03 Merge Maintenance Windows
// Sort by start, then sweep once, extending the last merged window whenever the
// next one starts at or before its end. O(n log n).
#include <algorithm>
#include <utility>
#include <vector>

using Interval = std::pair<int, int>;

inline std::vector<Interval> merge(std::vector<Interval> windows) {
    std::sort(windows.begin(), windows.end());  // pairs compare by first, then second

    std::vector<Interval> merged;
    merged.reserve(windows.size());
    for (const auto& [start, end] : windows) {
        if (!merged.empty() && start <= merged.back().second) {
            merged.back().second = std::max(merged.back().second, end);
        } else {
            merged.emplace_back(start, end);
        }
    }
    return merged;
}
