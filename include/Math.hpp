#ifndef HPP_MATH_DEFINED
#define HPP_MATH_DEFINED

// GMP headers
#include <gmpxx.h>

// Alias
using mpz = mpz_class;
using mpf = mpf_class;

mpz factorial(mpz n);

mpf calculateCosine(mpf radians);

#endif
