#ifndef HPP_MATH_DEFINED
#define HPP_MATH_DEFINED

// GMP headers
#include <gmpxx.h>

// Alias
using mpz = mpz_class;
using mpf = mpf_class;

mpz factorial(const mpz& n);

mpf singleThreadedCosine(const mpf& radians,
                         char stop_criteria,
                         int  precision);

#endif
