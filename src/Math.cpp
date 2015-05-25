// Standard headers
#include <cmath>
#include <thread>
#include <iostream>
#include <algorithm>

// Local headers
#include "Math.hpp"
#include "Barrier.hpp"

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

  // if (stop_criteria == 'f') {
  //   if (abs(aux) < precision) break;
  // } else if (stop_criteria == 'm') {
  //   if (abs(aux) < precision) break;
  // }

  for (unsigned int n = 0; true; n++) {
    aux = std::move(calculateTerm(radians, n));
    cos += aux;
    if (abs(aux) < precision) break;
  }

  return cos;
}

///////////////////////////////////////////////////////////////////////////////

Cosine::Cosine(const mpf& radians,
               const mpf& precision,
               char stop_criteria,
               unsigned int num_threads)
    : radians(radians),
      precision(precision),
      stop_criteria(stop_criteria),
      num_threads(num_threads),
      terms(num_threads, 0),
      barrier(num_threads) {
}

void Cosine::worker(unsigned int offset) {
  terms[offset] = std::move(calculateTerm(radians, iteration * terms.size() + offset));
}

bool Cosine::coordinator() {
  mpf aux = 0;
  for (auto &term : terms) aux += term;

  cos += aux;

  if (stop_criteria == 'f') {
    if (abs(aux) < precision) return true;
  } else if (stop_criteria == 'm') {
    if (std::any_of(terms.begin(), terms.end(), 
                    [this] (const mpf& t) { return abs(t) < precision; })) 
      return true;
  }
  return false;
}

void Cosine::asyncCalculateTerm(unsigned int offset,
                                bool is_coordinator) {
  while (!stop) {
    worker(offset);
    barrier.wait();

    if (is_coordinator) {
      stop = coordinator();
      iteration++;
    }
    barrier.wait();
  }
}

mpf Cosine::multiThreadedCosine() {

  mpf fixed_radians { fixRadians(radians) };

  std::vector<std::thread> threads;

  for (unsigned int offset = 0; offset < num_threads-1; offset++) {
    threads.emplace_back(&Cosine::asyncCalculateTerm, this, offset, false);
  }

  asyncCalculateTerm(num_threads-1, true);

  for (auto &thread : threads) thread.join();

  return cos;
}
