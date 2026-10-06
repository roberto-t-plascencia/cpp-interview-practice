#pragma once
// Reference solution - 02 Top K Frequent Errors
// Count with a hash map, then keep a min-heap of size k whose "smallest"
// element is the one we would drop first (lowest count, then alphabetically
// largest). O(n log k) time, O(n) space.
#include <queue>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

inline std::vector<std::string> topKFrequent(const std::vector<std::string>& codes, int k) {
    if (k <= 0) return {};

    std::unordered_map<std::string, int> counts;
    for (const auto& code : codes) ++counts[code];

    using Item = std::pair<int, std::string>;  // count, code
    // Comparator returns true when a should sit BELOW b in the heap, so the top
    // is the "worst" item: lowest count, ties broken by larger string.
    auto worse_on_top = [](const Item& a, const Item& b) {
        if (a.first != b.first) return a.first > b.first;
        return a.second < b.second;
    };
    std::priority_queue<Item, std::vector<Item>, decltype(worse_on_top)> heap(worse_on_top);

    for (const auto& [code, count] : counts) {
        heap.emplace(count, code);
        if (static_cast<int>(heap.size()) > k) heap.pop();
    }

    std::vector<std::string> result(heap.size());
    for (auto i = static_cast<int>(result.size()) - 1; i >= 0; --i) {
        result[static_cast<std::size_t>(i)] = heap.top().second;
        heap.pop();
    }
    return result;
}
