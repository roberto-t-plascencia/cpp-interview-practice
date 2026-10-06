#pragma once
// ============================================================================
// 07 - Write Your Own unique_ptr                             Difficulty: Medium
// ============================================================================
// Implement a simplified std::unique_ptr<T> to practice RAII, move semantics
// and the rule of five. This is a favorite C++ interview question.
//
// Requirements:
//   - Owns at most one heap object; deletes it in the destructor.
//   - NOT copyable (copy constructor / copy assignment deleted).
//   - Movable: moving transfers ownership and leaves the source empty.
//     Move assignment must delete the object the target currently owns.
//     Self-move-assignment must be safe.
//   - get(), release() (give up ownership without deleting), reset(p = nullptr)
//     (delete the current object, then own p), operator*, operator->,
//     explicit operator bool.
//   - makeUnique<T>(args...) helper that forwards constructor arguments.
//
// Concepts: RAII, rule of five, rvalue references, std::exchange,
//           std::forward / perfect forwarding, noexcept.
// ============================================================================
#include <utility>

template <typename T>
class UniquePtr {
public:
    UniquePtr() noexcept = default;
    explicit UniquePtr(T* ptr) noexcept : ptr_(ptr) {}

    ~UniquePtr() {
        // TODO: release the owned object
    }

    UniquePtr(const UniquePtr&) = delete;
    UniquePtr& operator=(const UniquePtr&) = delete;

    UniquePtr(UniquePtr&& other) noexcept {
        // TODO: take ownership from other
        (void)other;
    }

    UniquePtr& operator=(UniquePtr&& other) noexcept {
        // TODO: implement (watch out for self-assignment)
        (void)other;
        return *this;
    }

    T* get() const noexcept { return ptr_; }

    T* release() noexcept {
        // TODO: implement
        return nullptr;
    }

    void reset(T* ptr = nullptr) noexcept {
        // TODO: implement
        (void)ptr;
    }

    T& operator*() const { return *ptr_; }
    T* operator->() const noexcept { return ptr_; }
    explicit operator bool() const noexcept { return ptr_ != nullptr; }

private:
    T* ptr_ = nullptr;
};

template <typename T, typename... Args>
UniquePtr<T> makeUnique(Args&&... args) {
    // TODO: construct a T from args (perfect-forward them)
    return UniquePtr<T>();
}
