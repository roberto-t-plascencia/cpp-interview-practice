#pragma once
// ============================================================================
// 08 - Thread-Safe Bounded Work Queue                         Difficulty: Hard
// ============================================================================
// Build the queue that sits between producers and a pool of worker threads.
//
//   - push(item): blocks while the queue is full. Returns false (and does not
//     enqueue) if the queue has been closed, true otherwise.
//   - pop(): blocks while the queue is empty. Returns the oldest item, or
//     std::nullopt once the queue is closed AND drained.
//   - tryPop(): never blocks; returns std::nullopt if empty.
//   - close(): wakes every waiting thread. Pending items can still be popped.
//   - size(): current number of items.
//
// Real-world tie-in: the health monitor project uses exactly this pattern to
// hand probe jobs to worker threads.
//
// Concepts: std::mutex, std::condition_variable (wait with a predicate),
//           std::unique_lock vs std::lock_guard, spurious wakeups,
//           notify_one vs notify_all, move-only items.
// ============================================================================
#include <condition_variable>
#include <cstddef>
#include <deque>
#include <mutex>
#include <optional>

template <typename T>
class BoundedQueue {
public:
    explicit BoundedQueue(std::size_t capacity) : capacity_(capacity) {}

    bool push(T item) {
        // TODO: implement
        (void)item;
        return false;
    }

    std::optional<T> pop() {
        // TODO: implement
        return std::nullopt;
    }

    std::optional<T> tryPop() {
        // TODO: implement
        return std::nullopt;
    }

    void close() {
        // TODO: implement
    }

    std::size_t size() const {
        // TODO: implement
        return 0;
    }

private:
    std::size_t capacity_;
    // TODO: add a mutex, condition variable(s), storage and a closed flag
};
