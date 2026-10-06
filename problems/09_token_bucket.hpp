#pragma once
// ============================================================================
// 09 - Token Bucket Rate Limiter                            Difficulty: Medium
// ============================================================================
// Implement a token bucket, the algorithm behind most API gateway rate limits.
//
//   - The bucket holds at most `capacity` tokens and starts FULL.
//   - Tokens refill continuously at `refillPerSecond` (fractional tokens are
//     allowed), never exceeding capacity.
//   - allow(nowSeconds, cost = 1): refill based on time elapsed since the last
//     call, then if at least `cost` tokens are available, spend them and
//     return true; otherwise return false and spend nothing.
//   - Time is passed in explicitly (seconds as a double) so the class is
//     deterministic and easy to unit test. If time goes backwards, treat the
//     elapsed time as zero.
//
// Concepts: dependency injection of time, floating-point care, std::min/max.
// Stretch: make it thread-safe, or rewrite it using std::chrono types.
// ============================================================================

class TokenBucket {
public:
    TokenBucket(double capacity, double refillPerSecond)
        : capacity_(capacity), refillPerSecond_(refillPerSecond) {}

    bool allow(double nowSeconds, double cost = 1.0) {
        // TODO: implement
        (void)nowSeconds;
        (void)cost;
        return false;
    }

private:
    double capacity_;
    double refillPerSecond_;
    // TODO: add state (current tokens, time of last refill)
};
