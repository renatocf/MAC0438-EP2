// Standard headers
#include <cmath>
#include <iostream>

// Libraries
#include "Math.hpp"

const double PI = 3.141592653589793238462643;

unsigned long int factorial (unsigned long int n) {
  return (n == 1 || n == 0) ? 1 : factorial(n - 1) * n;
}

double fixRadians_impl(double radians) {
  if (radians > 2*PI)
    return fixRadians_impl(radians - 2*PI);
  return radians;
}

double fixRadians(double radians) {
  return fixRadians_impl(std::abs(radians));
}

double calculateCosine(double radians) {
  double cos = 0;  
  radians = fixRadians(radians);

  for (int n = 0; n < 10; n++) {
    int signal = n % 2 == 0 ? 1 : -1;
    cos += signal * (std::pow(radians, 2*n) / factorial(2*n));
  }

  return cos;
}
