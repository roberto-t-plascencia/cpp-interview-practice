#pragma once
// Reference solution - 05 Config Propagation Delay
// Dijkstra from the source; the answer is the largest shortest-path distance.
// Skips stale heap entries instead of using decrease-key. O(E log V).
#include <algorithm>
#include <functional>
#include <limits>
#include <queue>
#include <tuple>
#include <utility>
#include <vector>

using Link = std::tuple<int, int, int>;  // from, to, latencyMs

inline int propagationDelay(int n, const std::vector<Link>& links, int source) {
    if (n <= 0 || source < 0 || source >= n) return -1;

    std::vector<std::vector<std::pair<int, int>>> adj(static_cast<std::size_t>(n));
    for (const auto& [from, to, latency] : links)
        adj[static_cast<std::size_t>(from)].emplace_back(to, latency);

    constexpr int kInf = std::numeric_limits<int>::max();
    std::vector<int> dist(static_cast<std::size_t>(n), kInf);
    using State = std::pair<int, int>;  // distance, node
    std::priority_queue<State, std::vector<State>, std::greater<>> pq;

    dist[static_cast<std::size_t>(source)] = 0;
    pq.emplace(0, source);
    while (!pq.empty()) {
        auto [d, node] = pq.top();
        pq.pop();
        if (d > dist[static_cast<std::size_t>(node)]) continue;  // stale entry
        for (auto [next, latency] : adj[static_cast<std::size_t>(node)]) {
            int candidate = d + latency;
            if (candidate < dist[static_cast<std::size_t>(next)]) {
                dist[static_cast<std::size_t>(next)] = candidate;
                pq.emplace(candidate, next);
            }
        }
    }

    int worst = *std::max_element(dist.begin(), dist.end());
    return worst == kInf ? -1 : worst;
}
