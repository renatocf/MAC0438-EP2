#ifndef HPP_MATH_DEFINED
#define HPP_MATH_DEFINED

// GMP headers
#include <gmpxx.h>

// Local headers
#include "Barrier.hpp"

// Alias
using mpz = mpz_class;
using mpf = mpf_class;

mpz factorial(const mpz& n);

class CosineCalculator {
 public:
  CosineCalculator(const mpf& radians,
         int exponent,
         char stop_criteria,
         unsigned int num_threads);

  mpf multiThreadedCosine();
  mpf singleThreadedCosine();

 private:
  // Concrete attributes
  Barrier barrier;

  mpf radians;
  mpf precision;

  char stop_criteria;

  mpf cos = 0;
  int exponent;
  unsigned int iteration = 0;
  unsigned int num_threads = 0;

  bool stop = false;

  std::vector<mpf> terms;

  // Concrete methods
  mpf fixRadians(const mpf& radians);
  mpf fixRadians_impl(const mpf& radians);

  void asyncCalculateTerm(unsigned int offset,
                          bool is_coordinator);
  mpf calculateTerm(const mpf& radians,
                    unsigned int n);
  mpf calculatePrecision(int exponent);

  void worker(unsigned int offset);
  bool coordinator();
};

#endif
