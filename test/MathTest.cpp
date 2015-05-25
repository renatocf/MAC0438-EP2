// Standard headers
#include <map>
#include <cmath>
#include <vector>

// External headers
#include "gmock/gmock.h"

// Internal headers
#include "Math.hpp"

// Alias
using ::testing::DoubleNear;

const double PI = 3.141592653589793238462643;

class ASingleThreadCosine : public testing::Test {
    
};

TEST_F(ASingleThreadCosine, ShouldCalculateFactorial) {
  std::map<unsigned int, unsigned long int> factorials {
      { 0, 1ul },
      { 1, 1ul },
      { 2, 2ul },
      { 3, 6ul },
      { 4, 24ul },
      { 5, 120ul },
      { 6, 720ul },
      { 7, 5040ul },
      { 8, 40320ul },
      { 9, 362880ul },
      { 10, 3628800ul },
      { 11, 39916800ul },
      { 12, 479001600ul },
      { 13, 6227020800ul },
      { 14, 87178291200ul },
      { 15, 1307674368000ul },
      { 16, 20922789888000ul },
      { 17, 355687428096000ul },
      { 18, 6402373705728000ul },
      { 19, 121645100408832000ul },
      { 20, 2432902008176640000ul }
  };

  for (auto fact : factorials)
    ASSERT_EQ(fact.second, factorial(mpz(fact.first)).get_ui());
}

TEST_F(ASingleThreadCosine, ShouldCalculateCanonicalCosines) {
  std::vector<double> angles {
    -3*PI, -2*PI, -3*PI/2, -PI, -PI/2, -PI/4,
     0, PI/4, PI/2, PI, 3*PI/2, 2*PI, 3*PI
  };

  for (auto angle : angles)
    ASSERT_NEAR(singleThreadedCosine(mpf(angle), 'f',
                calculatePrecision(100000)).get_d(),
                std::cos(angle), 10e-2);
}

TEST_F(ASingleThreadCosine, ShouldCalculateCanonicalCosinesWithMultipleThreadsInStopModeF) {
  std::vector<double> angles {
    -3*PI, -2*PI, -3*PI/2, -PI, -PI/2, -PI/4,
     0, PI/4, PI/2, PI, 3*PI/2, 2*PI, 3*PI
  };

  for (auto angle : angles) {
    Cosine calculator(mpf(angle), calculatePrecision(100000), 'f', 3);

    ASSERT_NEAR(calculator.multiThreadedCosine().get_d(),
                std::cos(angle), 10e-2);
  }
}

TEST_F(ASingleThreadCosine, ShouldCalculateCanonicalCosinesWithMultipleThreadsInStopModeM) {
  std::vector<double> angles {
    -3*PI, -2*PI, -3*PI/2, -PI, -PI/2, -PI/4,
     0, PI/4, PI/2, PI, 3*PI/2, 2*PI, 3*PI
  };

  for (auto angle : angles) {
    Cosine calculator(mpf(angle), calculatePrecision(100000), 'm', 3);

    ASSERT_NEAR(calculator.multiThreadedCosine().get_d(),
                std::cos(angle), 10e-2);
  }
}
