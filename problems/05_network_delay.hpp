#pragma once
// ============================================================================
// 05 - Config Propagation Delay                             Difficulty: Medium
// ============================================================================
// A config change is pushed from one node and propagates across a network of
// n nodes (numbered 0..n-1). Each link {from, to, latencyMs} is one-way.
// Return the time until EVERY node has received the change, or -1 if some
// node can never receive it.
//
//   propagationDelay(4, {{0,1,1},{0,2,4},{1,2,2},{2,3,1}}, 0) -> 4
//     (0->1 = 1, 0->1->2 = 3, 0->1->2->3 = 4)
//
// Concepts: Dijkstra's shortest path, adjacency lists, std::priority_queue
//           with std::greater for a min-heap, std::numeric_limits.
// ============================================================================
#include <tuple>
#include <vector>

using Link = std::tuple<int, int, int>;  // from, to, latencyMs

inline int propagationDelay(int n, const std::vector<Link>& links, int source) {
    // TODO: implement
    (void)n;
    (void)links;
    (void)source;
    return 0;
}
