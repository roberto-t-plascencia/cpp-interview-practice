#pragma once
// Reference solution - 06 Latency Percentiles from Access Logs
// Tokenize with string_view (no allocations per field), validate numbers with
// from_chars, group latencies per endpoint, then pick the nearest-rank element
// with nth_element (average O(N) instead of a full sort).
#include <algorithm>
#include <array>
#include <charconv>
#include <cmath>
#include <cstddef>
#include <map>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

namespace detail {

inline std::optional<int> parseInt(std::string_view text) {
    int value = 0;
    auto [ptr, ec] = std::from_chars(text.data(), text.data() + text.size(), value);
    if (ec != std::errc{} || ptr != text.data() + text.size()) return std::nullopt;
    return value;
}

// Splits on single spaces; returns false unless there are exactly N fields.
template <std::size_t N>
bool splitExactly(std::string_view line, std::array<std::string_view, N>& out) {
    std::size_t count = 0;
    while (!line.empty()) {
        auto space = line.find(' ');
        auto token = line.substr(0, space);
        if (token.empty() || count == N) return false;
        out[count++] = token;
        if (space == std::string_view::npos) break;
        line.remove_prefix(space + 1);
    }
    return count == N;
}

}  // namespace detail

inline std::map<std::string, int> percentileByEndpoint(const std::vector<std::string>& lines,
                                                       double p) {
    std::map<std::string, std::vector<int>> latencies;

    for (const auto& raw : lines) {
        std::array<std::string_view, 5> f{};
        if (!detail::splitExactly(raw, f)) continue;

        std::string_view latency = f[4];
        if (latency.size() < 3 || latency.substr(latency.size() - 2) != "ms") continue;
        latency.remove_suffix(2);

        auto status = detail::parseInt(f[3]);
        auto ms = detail::parseInt(latency);
        if (!status || !ms) continue;

        std::string key;
        key.reserve(f[1].size() + 1 + f[2].size());
        key.append(f[1]).append(" ").append(f[2]);
        latencies[std::move(key)].push_back(*ms);
    }

    std::map<std::string, int> result;
    for (auto& [endpoint, values] : latencies) {
        auto n = values.size();
        auto rank = static_cast<std::size_t>(std::ceil(p / 100.0 * static_cast<double>(n)));
        rank = std::clamp<std::size_t>(rank, 1, n);
        auto nth = values.begin() + static_cast<std::ptrdiff_t>(rank - 1);
        std::nth_element(values.begin(), nth, values.end());
        result[endpoint] = *nth;
    }
    return result;
}
