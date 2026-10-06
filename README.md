# C++ Interview Practice

[![CI](https://github.com/roberto-t-plascencia/cpp-interview-practice/actions/workflows/ci.yml/badge.svg)](https://github.com/roberto-t-plascencia/cpp-interview-practice/actions/workflows/ci.yml)

Ten modern C++ (C++20) practice problems with unit tests. The problems are set in cloud and platform engineering: caches, deployment ordering, log percentiles, rate limiting, and worker queues.

Each problem has three parts:

| Folder | What's in it |
|---|---|
| `problems/` | A starter header with the problem description and a stub. **This is where you write your code.** |
| `tests/` | GoogleTest unit tests. Don't edit these. |
| `solutions/` | Reference solutions with explanations. Check them only after you've made an attempt. |

## Problems

| # | Problem | Level | Concepts |
|---|---|---|---|
| 01 | [LRU Cache](problems/01_lru_cache.hpp) | Medium | `std::list` + `std::unordered_map`, `splice`, O(1) design |
| 02 | [Top K Frequent Errors](problems/02_top_k_frequent.hpp) | Medium | Hash counting, custom comparators, `priority_queue` |
| 03 | [Merge Maintenance Windows](problems/03_merge_intervals.hpp) | Easy | `std::sort` with lambdas, structured bindings |
| 04 | [Service Deployment Order](problems/04_deploy_order.hpp) | Medium | Topological sort (Kahn), cycle detection, `std::optional` |
| 05 | [Config Propagation Delay](problems/05_network_delay.hpp) | Medium | Dijkstra, adjacency lists, min-heaps |
| 06 | [Latency Percentiles from Logs](problems/06_latency_percentile.hpp) | Medium | `std::string_view`, `std::from_chars`, `nth_element` |
| 07 | [Write Your Own unique_ptr](problems/07_unique_ptr.hpp) | Medium | RAII, rule of five, move semantics, perfect forwarding |
| 08 | [Thread-Safe Bounded Queue](problems/08_bounded_queue.hpp) | Hard | `mutex`, `condition_variable`, shutdown semantics |
| 09 | [Token Bucket Rate Limiter](problems/09_token_bucket.hpp) | Medium | Injected time, lazy refill, floating-point care |
| 10 | [Count Outage Regions](problems/10_outage_regions.hpp) | Medium | BFS on a grid, iterative traversal |

A suggested order: 03 → 01 → 02 → 10 → 04 → 05 → 06 → 09 → 07 → 08.

## Build and run

You need CMake 3.20+, Git, and a C++20 compiler (GCC 11+, Clang 14+, or Visual Studio 2022). GoogleTest is downloaded automatically the first time you configure.

```bash
# Test YOUR code in problems/
cmake --preset practice
cmake --build --preset practice
ctest --preset practice

# Run just one problem's tests
./build/practice/01_lru_cache_test          # Linux / macOS / WSL
.\build\practice\Debug\01_lru_cache_test.exe # Windows (Visual Studio generator)

# Check that the reference solutions pass
cmake --preset solutions
cmake --build --preset solutions
ctest --preset solutions
```

**Windows:** open the folder in Visual Studio 2022 (File → Open → Folder) or VS Code with the CMake Tools extension, then pick the **Practice** preset. Running the commands above from WSL (Ubuntu) works too.

### Optional: check for memory and threading bugs (Linux/WSL)

```bash
cmake -S . -B build/asan -DCMAKE_CXX_FLAGS="-fsanitize=address,undefined -g"
cmake --build build/asan && (cd build/asan && ctest)

cmake -S . -B build/tsan -DCMAKE_CXX_FLAGS="-fsanitize=thread -g -O1"
cmake --build build/tsan --target 08_bounded_queue_test && ./build/tsan/08_bounded_queue_test
```

## Workflow

1. Read the comment block at the top of the problem file.
2. Say the approach and its time/space complexity out loud, the way you would in an interview.
3. Write the code and run that problem's test binary until it passes.
4. Compare with `solutions/` and note anything you'd do differently.
