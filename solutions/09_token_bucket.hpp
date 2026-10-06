#pragma once
// Reference solution - 09 Token Bucket Rate Limiter
// Lazy refill: instead of a background timer, top up the bucket on each call
// based on elapsed time. O(1) per request and no threads needed.
#include <algorithm>
#include <optional>

class TokenBucket {
public:
    TokenBucket(double capacity, double refillPerSecond)
        : capacity_(capacity), refillPerSecond_(refillPerSecond), tokens_(capacity) {}

    bool allow(double nowSeconds, double cost = 1.0) {
        if (lastSeconds_) {
            double elapsed = std::max(0.0, nowSeconds - *lastSeconds_);
            tokens_ = std::min(capacity_, tokens_ + elapsed * refillPerSecond_);
        }
        lastSeconds_ = std::max(nowSeconds, lastSeconds_.value_or(nowSeconds));

        constexpr double kEpsilon = 1e-9;  // absorb floating-point rounding
        if (tokens_ + kEpsilon >= cost) {
            tokens_ -= cost;
            return true;
        }
        return false;
    }

private:
    double capacity_;
    double refillPerSecond_;
    double tokens_;
    std::optional<double> lastSeconds_;
};
