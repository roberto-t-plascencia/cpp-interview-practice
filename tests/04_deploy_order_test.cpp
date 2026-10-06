#include "04_deploy_order.hpp"

#include <gtest/gtest.h>

using Names = std::vector<std::string>;

TEST(DeployOrder, SimpleChain) {
    auto order = deployOrder({"api", "db", "web"}, {{"api", "db"}, {"web", "api"}});
    ASSERT_TRUE(order.has_value());
    EXPECT_EQ(*order, (Names{"db", "api", "web"}));
}

TEST(DeployOrder, IndependentServicesAreAlphabetical) {
    auto order = deployOrder({"payments", "auth", "search"}, {});
    ASSERT_TRUE(order.has_value());
    EXPECT_EQ(*order, (Names{"auth", "payments", "search"}));
}

TEST(DeployOrder, DiamondDependencies) {
    // gateway needs users and orders; both need db
    auto order = deployOrder({"gateway", "users", "orders", "db"},
                             {{"gateway", "users"}, {"gateway", "orders"},
                              {"users", "db"}, {"orders", "db"}});
    ASSERT_TRUE(order.has_value());
    EXPECT_EQ(*order, (Names{"db", "orders", "users", "gateway"}));
}

TEST(DeployOrder, DetectsCycle) {
    auto order = deployOrder({"a", "b", "c"}, {{"a", "b"}, {"b", "c"}, {"c", "a"}});
    EXPECT_FALSE(order.has_value());
}

TEST(DeployOrder, SelfDependencyIsACycle) {
    EXPECT_FALSE(deployOrder({"a"}, {{"a", "a"}}).has_value());
}

TEST(DeployOrder, EmptyInput) {
    auto order = deployOrder({}, {});
    ASSERT_TRUE(order.has_value());
    EXPECT_TRUE(order->empty());
}
