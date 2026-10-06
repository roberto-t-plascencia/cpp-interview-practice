#pragma once
// ============================================================================
// 06 - Latency Percentiles from Access Logs                 Difficulty: Medium
// ============================================================================
// Parse access-log lines and compute a latency percentile per endpoint.
// Each valid line has exactly five space-separated fields:
//
//   <timestamp> <method> <path> <status> <latency>ms
//   2026-10-06T12:00:00Z GET /api/users 200 123ms
//
// The endpoint key is "<method> <path>", e.g. "GET /api/users".
// Skip malformed lines (wrong field count, non-numeric status or latency,
// missing "ms" suffix). Use the NEAREST-RANK percentile:
//
//   rank = ceil(p / 100 * N), result = sorted_latencies[rank - 1]
//   (for p = 0, use the smallest value)
//
// Concepts: std::string_view (parse without copying), std::from_chars,
//           std::map, std::nth_element or std::sort, std::ceil.
// ============================================================================
#include <map>
#include <string>
#include <vector>

inline std::map<std::string, int> percentileByEndpoint(const std::vector<std::string>& lines,
                                                       double p) {
    // TODO: implement
    (void)lines;
    (void)p;
    return {};
}
