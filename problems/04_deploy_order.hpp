#pragma once
// ============================================================================
// 04 - Service Deployment Order                             Difficulty: Medium
// ============================================================================
// You are rolling out a set of microservices. Some services depend on others
// and can only be deployed after their dependencies. Return a valid
// deployment order, or std::nullopt if the dependencies contain a cycle.
//
//   services: list of service names (every service appears here)
//   deps:     pairs {service, dependsOn}, meaning dependsOn must deploy first
//
// To keep the answer deterministic: whenever more than one service is ready
// to deploy, pick the alphabetically smallest one first.
//
//   deployOrder({"api","db","web"}, {{"api","db"},{"web","api"}})
//     -> {"db","api","web"}
//
// Concepts: topological sort (Kahn's algorithm), in-degree counting,
//           std::priority_queue with std::greater, std::optional.
// ============================================================================
#include <optional>
#include <string>
#include <utility>
#include <vector>

using Dependency = std::pair<std::string, std::string>;  // {service, dependsOn}

inline std::optional<std::vector<std::string>> deployOrder(
    const std::vector<std::string>& services, const std::vector<Dependency>& deps) {
    // TODO: implement
    (void)services;
    (void)deps;
    return std::vector<std::string>{};
}
