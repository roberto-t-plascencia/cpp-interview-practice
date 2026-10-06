#include "08_bounded_queue.hpp"

#include <gtest/gtest.h>

#include <atomic>
#include <chrono>
#include <memory>
#include <thread>
#include <vector>

using namespace std::chrono_literals;

TEST(BoundedQueue, FifoOrderSingleThread) {
    BoundedQueue<int> q(4);
    ASSERT_TRUE(q.push(1));
    ASSERT_TRUE(q.push(2));
    ASSERT_TRUE(q.push(3));
    EXPECT_EQ(q.size(), 3u);
    EXPECT_EQ(q.pop(), 1);
    EXPECT_EQ(q.pop(), 2);
    EXPECT_EQ(q.tryPop(), 3);
    EXPECT_FALSE(q.tryPop().has_value());
}

TEST(BoundedQueue, SupportsMoveOnlyTypes) {
    BoundedQueue<std::unique_ptr<int>> q(2);
    ASSERT_TRUE(q.push(std::make_unique<int>(9)));
    auto item = q.pop();
    ASSERT_TRUE(item.has_value());
    EXPECT_EQ(**item, 9);
}

TEST(BoundedQueue, CloseRejectsPushButDrainsPending) {
    BoundedQueue<int> q(4);
    ASSERT_TRUE(q.push(1));
    q.close();
    EXPECT_FALSE(q.push(2));
    EXPECT_EQ(q.pop(), 1);
    EXPECT_FALSE(q.pop().has_value());  // closed and drained: must not block
}

TEST(BoundedQueue, CloseWakesBlockedConsumer) {
    BoundedQueue<int> q(1);
    std::atomic<bool> returned{false};
    std::thread consumer([&] {
        auto item = q.pop();
        EXPECT_FALSE(item.has_value());
        returned = true;
    });
    std::this_thread::sleep_for(50ms);
    EXPECT_FALSE(returned.load());  // still blocked
    q.close();
    consumer.join();
    EXPECT_TRUE(returned.load());
}

TEST(BoundedQueue, PushBlocksWhenFull) {
    BoundedQueue<int> q(1);
    ASSERT_TRUE(q.push(1));
    std::atomic<bool> pushed{false};
    std::thread producer([&] {
        EXPECT_TRUE(q.push(2));
        pushed = true;
    });
    std::this_thread::sleep_for(50ms);
    EXPECT_FALSE(pushed.load());  // blocked on a full queue
    EXPECT_EQ(q.pop(), 1);
    producer.join();
    EXPECT_TRUE(pushed.load());
    EXPECT_EQ(q.pop(), 2);
}

TEST(BoundedQueue, ManyProducersManyConsumers) {
    constexpr int kProducers = 4, kConsumers = 4, kPerProducer = 2000;
    BoundedQueue<int> q(16);
    std::atomic<long long> sum{0};
    std::atomic<int> count{0};

    std::vector<std::thread> consumers;
    for (int c = 0; c < kConsumers; ++c) {
        consumers.emplace_back([&] {
            while (auto item = q.pop()) {
                sum += *item;
                ++count;
            }
        });
    }
    std::vector<std::thread> producers;
    for (int p = 0; p < kProducers; ++p) {
        producers.emplace_back([&] {
            for (int i = 1; i <= kPerProducer; ++i) ASSERT_TRUE(q.push(i));
        });
    }
    for (auto& t : producers) t.join();
    q.close();
    for (auto& t : consumers) t.join();

    constexpr long long kExpectedPerProducer = 1LL * kPerProducer * (kPerProducer + 1) / 2;
    EXPECT_EQ(count.load(), kProducers * kPerProducer);
    EXPECT_EQ(sum.load(), kProducers * kExpectedPerProducer);
}
