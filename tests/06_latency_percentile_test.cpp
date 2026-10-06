#include "06_latency_percentile.hpp"

#include <gtest/gtest.h>

#include <string>

namespace {
std::vector<std::string> tenUserRequests() {
    std::vector<std::string> lines;
    for (int ms = 10; ms <= 100; ms += 10)  // 10, 20, ..., 100
        lines.push_back("2026-10-06T12:00:00Z GET /api/users 200 " + std::to_string(ms) + "ms");
    return lines;
}
}  // namespace

TEST(LatencyPercentile, NearestRankP50AndP95) {
    auto lines = tenUserRequests();
    EXPECT_EQ(percentileByEndpoint(lines, 50).at("GET /api/users"), 50);
    EXPECT_EQ(percentileByEndpoint(lines, 95).at("GET /api/users"), 100);
    EXPECT_EQ(percentileByEndpoint(lines, 90).at("GET /api/users"), 90);
}

TEST(LatencyPercentile, P0AndP100) {
    auto lines = tenUserRequests();
    EXPECT_EQ(percentileByEndpoint(lines, 0).at("GET /api/users"), 10);
    EXPECT_EQ(percentileByEndpoint(lines, 100).at("GET /api/users"), 100);
}

TEST(LatencyPercentile, GroupsByMethodAndPath) {
    std::vector<std::string> lines{
        "t1 GET /api/orders 200 30ms",
        "t2 POST /api/orders 201 300ms",
        "t3 GET /api/orders 500 10ms",
        "t4 GET /health 200 1ms",
    };
    auto p100 = percentileByEndpoint(lines, 100);
    ASSERT_EQ(p100.size(), 3u);
    EXPECT_EQ(p100.at("GET /api/orders"), 30);
    EXPECT_EQ(p100.at("POST /api/orders"), 300);
    EXPECT_EQ(p100.at("GET /health"), 1);
}

TEST(LatencyPercentile, SkipsMalformedLines) {
    std::vector<std::string> lines{
        "t1 GET /ok 200 40ms",
        "t2 GET /ok 200 40",          // missing ms
        "t3 GET /ok abc 40ms",        // bad status
        "t4 GET /ok 200 4x0ms",       // bad latency
        "t5 GET /ok 200",             // too few fields
        "t6 GET /ok 200 40ms extra",  // too many fields
        "",
    };
    auto result = percentileByEndpoint(lines, 50);
    ASSERT_EQ(result.size(), 1u);
    EXPECT_EQ(result.at("GET /ok"), 40);
}

TEST(LatencyPercentile, EmptyInput) {
    EXPECT_TRUE(percentileByEndpoint({}, 95).empty());
}
