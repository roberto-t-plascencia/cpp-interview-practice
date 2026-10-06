#pragma once
// Reference solution - 07 Write Your Own unique_ptr
// std::exchange makes the ownership transfers one-liners. reset() swaps in the
// new pointer BEFORE deleting the old one, so it stays correct even if the
// old object's destructor touches this UniquePtr. Self-move is handled by the
// `this != &other` check.
#include <utility>

template <typename T>
class UniquePtr {
public:
    UniquePtr() noexcept = default;
    explicit UniquePtr(T* ptr) noexcept : ptr_(ptr) {}

    ~UniquePtr() { delete ptr_; }

    UniquePtr(const UniquePtr&) = delete;
    UniquePtr& operator=(const UniquePtr&) = delete;

    UniquePtr(UniquePtr&& other) noexcept : ptr_(std::exchange(other.ptr_, nullptr)) {}

    UniquePtr& operator=(UniquePtr&& other) noexcept {
        if (this != &other) reset(other.release());
        return *this;
    }

    T* get() const noexcept { return ptr_; }

    T* release() noexcept { return std::exchange(ptr_, nullptr); }

    void reset(T* ptr = nullptr) noexcept {
        T* old = std::exchange(ptr_, ptr);
        delete old;
    }

    T& operator*() const { return *ptr_; }
    T* operator->() const noexcept { return ptr_; }
    explicit operator bool() const noexcept { return ptr_ != nullptr; }

private:
    T* ptr_ = nullptr;
};

template <typename T, typename... Args>
UniquePtr<T> makeUnique(Args&&... args) {
    return UniquePtr<T>(new T(std::forward<Args>(args)...));
}
