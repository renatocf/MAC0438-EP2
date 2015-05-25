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
                   char operation_mode,
                   unsigned int num_threads);

  mpf calculateCosine();

  mpf multiThreadedCosine();
  mpf singleThreadedCosine();

 private:
  // Concrete attributes
  mpf radians;
  mpf precision;

  int exponent;

  char stop_criteria;
  char operation_mode;

  unsigned int num_threads = 0;

  std::vector<mpf> terms;
  Barrier barrier;

  mpf cos = 0;
  bool stop = false;
  unsigned int iteration = 0;

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
