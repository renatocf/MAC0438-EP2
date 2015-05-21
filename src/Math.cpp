// Standard headers
#include <cmath>
#include <iostream>

// Local headers
#include "Math.hpp"

const double PI = 3.141592653589793238462643;

mpz factorial(mpz n) {
  return (n == 1 || n == 0) ? mpz(1) : factorial(n - 1) * n;
}

mpf fixRadians_impl(mpf radians) {
  if (radians > 2*PI)
    return fixRadians_impl(radians - 2*PI);
  return radians;
}

mpf fixRadians(mpf radians) {
  return fixRadians_impl(abs(radians));
}

mpf singleThreadedCosine(mpf radians) {
  mpf cos = 0;
  mpf aux = 0;

  radians = fixRadians(radians);

  for (int n = 0; n < 100; n++) {
    int signal = n % 2 == 0 ? 1 : -1;
    mpf_pow_ui(aux.get_mpf_t(), radians.get_mpf_t(), 2*n);
    cos += signal * (aux / factorial(2*n));
  }

  return cos;
}
