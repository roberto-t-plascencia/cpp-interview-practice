#pragma once
// Reference solution - 04 Service Deployment Order
// Kahn's algorithm: repeatedly deploy a service with no undeployed
// dependencies. A min-heap picks the alphabetically smallest ready service.
// If we cannot deploy everything, the remaining services form a cycle.
// O((V + E) log V).
#include <functional>
#include <optional>
#include <queue>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

using Dependency = std::pair<std::string, std::string>;  // {service, dependsOn}

inline std::optional<std::vector<std::string>> deployOrder(
    const std::vector<std::string>& services, const std::vector<Dependency>& deps) {
    std::unordered_map<std::string, int> in_degree;
    std::unordered_map<std::string, std::vector<std::string>> dependents;
    for (const auto& s : services) in_degree.emplace(s, 0);

    for (const auto& [service, depends_on] : deps) {
        dependents[depends_on].push_back(service);  // edge: depends_on -> service
        ++in_degree[service];
        in_degree.try_emplace(depends_on, 0);
    }

    std::priority_queue<std::string, std::vector<std::string>, std::greater<>> ready;
    for (const auto& [s, degree] : in_degree)
        if (degree == 0) ready.push(s);

    std::vector<std::string> order;
    order.reserve(in_degree.size());
    while (!ready.empty()) {
        std::string current = ready.top();
        ready.pop();
        order.push_back(current);
        for (const auto& next : dependents[current])
            if (--in_degree[next] == 0) ready.push(next);
    }

    if (order.size() != in_degree.size()) return std::nullopt;  // cycle
    return order;
}
