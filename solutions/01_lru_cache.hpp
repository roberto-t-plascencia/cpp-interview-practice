#pragma once
// Reference solution - 01 LRU Cache
// O(1) get/put: a list keeps recency order (front = most recent) and a hash map
// points each key at its list node. list::splice moves a node without
// reallocating, so iterators stored in the map stay valid.
#include <cstddef>
#include <list>
#include <optional>
#include <unordered_map>
#include <utility>

class LRUCache {
public:
    explicit LRUCache(std::size_t capacity) : capacity_(capacity) {}

    std::optional<int> get(int key) {
        auto it = index_.find(key);
        if (it == index_.end()) return std::nullopt;
        order_.splice(order_.begin(), order_, it->second);  // mark as most recent
        return it->second->second;
    }

    void put(int key, int value) {
        if (capacity_ == 0) return;
        if (auto it = index_.find(key); it != index_.end()) {
            it->second->second = value;
            order_.splice(order_.begin(), order_, it->second);
            return;
        }
        if (order_.size() == capacity_) {
            index_.erase(order_.back().first);  // evict least recently used
            order_.pop_back();
        }
        order_.emplace_front(key, value);
        index_[key] = order_.begin();
    }

    std::size_t size() const { return order_.size(); }

private:
    using Entry = std::pair<int, int>;  // key, value
    std::size_t capacity_;
    std::list<Entry> order_;
    std::unordered_map<int, std::list<Entry>::iterator> index_;
};
