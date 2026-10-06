#pragma once
// ============================================================================
// 10 - Count Outage Regions                                 Difficulty: Medium
// ============================================================================
// A datacenter floor is a grid of racks. 'X' marks a rack that is down and
// '.' marks a healthy rack. Down racks that touch horizontally or vertically
// (not diagonally) belong to the same outage region. Return the number of
// distinct outage regions. Rows may have different lengths.
//
//   countOutageRegions({"XX..",
//                       "X..X",
//                       "..XX"}) -> 2
//
// Concepts: BFS/DFS on a grid, std::queue, bounds checking, visited marking.
// Stretch: solve it again with a union-find (disjoint set) structure.
// ============================================================================
#include <string>
#include <vector>

inline int countOutageRegions(const std::vector<std::string>& grid) {
    // TODO: implement
    (void)grid;
    return 0;
}
