// Standard headers
#include <cmath>
#include <iostream>

// Libraries
#include "Math.hpp"

const double PI = 3.141592653589793238462643;

// Alias
using mpz = unsigned long int;
using mpf = double;

mpz factorial (mpz n) {
  return (n == 1 || n == 0) ? 1 : factorial(n - 1) * n;
}

mpf fixRadians_impl(mpf radians) {
  if (radians > 2*PI)
    return fixRadians_impl(radians - 2*PI);
  return radians;
}

mpf fixRadians(mpf radians) {
  return fixRadians_impl(std::abs(radians));
}

mpf calculateCosine(mpf radians) {
  mpf cos = 0;
  radians = fixRadians(radians);

  for (int n = 0; n < 10; n++) {
    int signal = n % 2 == 0 ? 1 : -1;
    cos += signal * (std::pow(radians, 2*n) / factorial(2*n));
  }

  return cos;
}
