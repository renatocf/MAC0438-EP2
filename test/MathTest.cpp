// Standard headers
#include <cmath>

// External headers
#include "gmock/gmock.h"

// Internal headers
#include "Math.hpp"

// Alias
using ::testing::DoubleNear;

const double PI = 3.141592653589793238462643;

class ASingleThreadCosine : public testing::Test {
    
};

TEST_F(ASingleThreadCosine, ShouldCalculateCanonicalCosines){
  std::vector<double> angles {
    -PI, 0, PI, 2*PI, 3*PI
  };

  for (auto angle : angles)
    ASSERT_THAT(calculateCosine(angle), DoubleNear(std::cos(angle), 1e-2));
}
