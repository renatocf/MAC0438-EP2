#ifndef HPP_MATH_DEFINED
#define HPP_MATH_DEFINED

// GMP headers
#include <gmpxx.h>

// Local headers
#include "Barrier.hpp"

// Alias
using mpz = mpz_class;
using mpf = mpf_class;

mpf calculatePrecision(int exponent);

mpz factorial(const mpz& n);

mpf singleThreadedCosine(const mpf& radians,
                         char stop_criteria,
                         const mpf& precision);

class Cosine {
 public:
  Cosine(const mpf& radians,
         const mpf& precision,
         char stop_criteria,
         unsigned int num_threads);

  mpf multiThreadedCosine();

 private:
  // Concrete attributes
  Barrier barrier;

  mpf radians;
  mpf precision;

  char stop_criteria;

  mpf cos = 0;
  unsigned int iteration = 0;
  unsigned int num_threads = 0;

  bool stop = false;

  std::vector<mpf> terms;

  // Concrete methods
  void worker(unsigned int offset);
  bool coordinator();
  void asyncCalculateTerm(unsigned int offset,
                          bool is_coordinator);
};

#endif
