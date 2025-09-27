#include <bit>
#include <print>

#include "offsetAllocator.hpp"

using namespace OffsetAllocator;

struct TestCase {
  ~TestCase() {
    if (!passed) std::println("FAILED");
  }
  bool passed{true};
};

#define TEST_CASE(name)                                                   \
  if (bool _tc_guard = (std::print("Test: {}\t", name), true); _tc_guard) \
    for (TestCase _test_case_instance; _tc_guard; _tc_guard = false)

#define ASSERT_TRUE(cond)                                    \
  do {                                                       \
    if (!(cond)) {                                           \
      _test_case_instance.passed = false;                    \
      std::println("\tExpected true, was false: {}", #cond); \
    }                                                        \
  } while (0);

#define ASSERT_FALSE(cond)                                   \
  do {                                                       \
    if ((cond)) {                                            \
      _test_case_instance.passed = false;                    \
      std::println("\tExpected false, was true: {}", #cond); \
    }                                                        \
  } while (0);

int main() {
  TEST_CASE("grow") {
    const uint32_t n = 128;
    Allocator a{n};
    auto r1 = a.allocate(n);
    ASSERT_TRUE(r1.offset == 0);
    ASSERT_TRUE(a.grow(n, 0));
    auto r2 = a.allocate(n);
    ASSERT_TRUE(r2.offset == n);
    a.free(r1);
    auto r3 = a.allocate(n / 2);
    ASSERT_TRUE(r3.offset == 0);
    auto r4 = a.allocate(n / 2);
    ASSERT_TRUE(r4.offset == n / 2);
    a.free(r2);
    auto sr = a.storageReport();
    ASSERT_TRUE(sr.totalFreeSpace == n);
    auto r5 = a.allocate(n / 2);
    ASSERT_TRUE(r5.offset == n);
    auto r6 = a.allocate(n / 2);
    ASSERT_TRUE(r6.offset == n / 2 + n);
  }
  TEST_CASE("grow 2") {
    const uint32_t n = 481191;
    Allocator a{static_cast<uint32>(std::bit_ceil(n))};
    auto r1 = a.allocate(n);
    ASSERT_TRUE(r1.offset == 0);
  }
}
