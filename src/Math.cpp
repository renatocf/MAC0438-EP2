// Standard headers
#include <cmath>
#include <iostream>

// Libraries
#include "Math.hpp"

unsigned long int factorial (unsigned long int n) {
  return (n == 1 || n == 0) ? 1 : factorial(n - 1) * n;
}

double calculateCosine(double radians) {
  double cos = 0;
  
  for (int n = 0; n < 10; n++) {
    int signal = n % 2 == 0 ? 1 : -1;
    cos += signal * (std::pow(radians, 2*n) / factorial(2*n));
  }

  return cos;
}
