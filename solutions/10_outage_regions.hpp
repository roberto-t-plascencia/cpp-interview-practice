#pragma once
// Reference solution - 10 Count Outage Regions
// Iterative BFS (no recursion, so a huge region cannot overflow the stack).
// Works on a copy of the grid and flips visited cells to '.'.
// O(cells) time and space.
#include <array>
#include <cstddef>
#include <queue>
#include <string>
#include <utility>
#include <vector>

inline int countOutageRegions(const std::vector<std::string>& grid) {
    std::vector<std::string> g = grid;
    constexpr std::array<std::pair<int, int>, 4> kDirs{{{1, 0}, {-1, 0}, {0, 1}, {0, -1}}};

    auto isDown = [&](int r, int c) {
        return r >= 0 && r < static_cast<int>(g.size()) && c >= 0 &&
               c < static_cast<int>(g[static_cast<std::size_t>(r)].size()) &&
               g[static_cast<std::size_t>(r)][static_cast<std::size_t>(c)] == 'X';
    };
    auto mark = [&](int r, int c) {
        g[static_cast<std::size_t>(r)][static_cast<std::size_t>(c)] = '.';
    };

    int regions = 0;
    for (int r = 0; r < static_cast<int>(g.size()); ++r) {
        for (int c = 0; c < static_cast<int>(g[static_cast<std::size_t>(r)].size()); ++c) {
            if (!isDown(r, c)) continue;
            ++regions;
            std::queue<std::pair<int, int>> frontier;
            frontier.emplace(r, c);
            mark(r, c);
            while (!frontier.empty()) {
                auto [cr, cc] = frontier.front();
                frontier.pop();
                for (auto [dr, dc] : kDirs) {
                    if (isDown(cr + dr, cc + dc)) {
                        mark(cr + dr, cc + dc);
                        frontier.emplace(cr + dr, cc + dc);
                    }
                }
            }
        }
    }
    return regions;
}
