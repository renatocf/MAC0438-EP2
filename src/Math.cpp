// Standard headers
#include <cmath>
#include <iostream>

// Local headers
#include "Math.hpp"

const double PI = 3.141592653589793238462643;

mpz factorial(const mpz& n) {
  return (n == 1 || n == 0) ? mpz(1) : factorial(n - 1) * n;
}

mpf fixRadians_impl(const mpf& radians) {
  if (radians > 2*PI)
    return fixRadians_impl(radians - 2*PI);
  return radians;
}

mpf fixRadians(const mpf& radians) {
  return fixRadians_impl(abs(radians));
}

mpf calculateTerm(const mpf& radians, unsigned int n) {
  mpf aux = 0; int signal = n % 2 == 0 ? 1 : -1;
  mpf_pow_ui(aux.get_mpf_t(), radians.get_mpf_t(), 2*n);
  return signal * (aux / factorial(2*n));
}

mpf singleThreadedCosine(const mpf& radians) {
  mpf cos = 0, aux = 0;

  mpf fixed_radians { fixRadians(radians) };

  for (unsigned int n = 0; n < 100; n++)
    cos += calculateTerm(radians, n);

  return cos;
}
