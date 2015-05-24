// Standard headers
#include <cmath>
#include <iostream>

// Local headers
#include "Math.hpp"

const double PI = 3.141592653589793238462643;

mpf calculatePrecision(int exponent) {
  mpf epsilon;
  mpf_pow_ui(epsilon.get_mpf_t(), mpf(0.1).get_mpf_t(), exponent);
  return epsilon;
}

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

mpf singleThreadedCosine(const mpf& radians,
                         char stop_criteria,
                         const mpf& precision) {
  mpf cos = 0, aux = 0;

  mpf fixed_radians { fixRadians(radians) };

  if (stop_criteria == 'f') {
  } else if (stop_criteria == 'm') {
  }

  for (unsigned int n = 0; n < 100; n++) {
    aux = std::move(calculateTerm(radians, n));
    cos += aux;
  }

  return cos;
}
