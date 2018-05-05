#include "gtest/gtest.h"

namespace {

int Factorial(int n) {
  if (n <= 0) return 1;
  return n * Factorial(n - 1);
}

TEST(FactorialTest, Zero) {
  EXPECT_EQ(1, Factorial(0));
}

// Tests factorial of positive numbers.
TEST(FactorialTest, Positive) {
  EXPECT_EQ(1, Factorial(1));
  EXPECT_EQ(2, Factorial(2));
  EXPECT_EQ(6, Factorial(3));
  EXPECT_EQ(40320, Factorial(8));
}

TEST(FactorialTest, Failure) {
  EXPECT_EQ(2, Factorial(1));
}

}
