// Standard headers
#include <cmath>
#include <thread>
#include <iomanip>
#include <iostream>
#include <algorithm>

// Local headers
#include "Math.hpp"
#include "Barrier.hpp"

const double PI = 3.141592653589793238462643;

mpz factorial(const mpz& n) {
  return (n == 1 || n == 0) ? mpz(1) : factorial(n - 1) * n;
}

mpf CosineCalculator::calculateCosine() {
  if (operation_mode == 's')
    return std::move(singleThreadedCosine());
  return std::move(multiThreadedCosine());
}

mpf CosineCalculator::calculatePrecision(int exponent) {
  mpf epsilon(0, exponent);
  mpf_pow_ui(epsilon.get_mpf_t(), mpf(exponent >= 0 ? 0.1 : 10).get_mpf_t(), std::abs(exponent));
  return epsilon;
}

mpf CosineCalculator::fixRadians_impl(const mpf& radians) {
  if (radians > 2*PI)
    return fixRadians_impl(radians - 2*PI);
  return radians;
}

mpf CosineCalculator::fixRadians(const mpf& radians) {
  return fixRadians_impl(abs(radians));
}

mpf CosineCalculator::calculateTerm(const mpf& radians, unsigned int n) {
  mpf aux(0, exponent); 
  int signal = n % 2 == 0 ? 1 : -1;
  mpf_pow_ui(aux.get_mpf_t(), radians.get_mpf_t(), 2*n);
  return signal * (aux / factorial(2*n));
}

mpf CosineCalculator::singleThreadedCosine() {
  mpf cos(0, exponent); 
  mpf aux(0, exponent);
  unsigned int singleIterations = 0;

  while (true) {
    aux = std::move(calculateTerm(radians, singleIterations));
    cos = cos + aux;
    singleIterations++;
    if (abs(aux) < precision) break;
    gmp_printf("Partial cosine value: %.*Ff\n", exponent, cos.get_mpf_t());
  }

  gmp_printf("Final cosine value: %.*Ff\n", exponent, cos.get_mpf_t());
  std::cout << "Number of different calculated terms: " << singleIterations << std::endl;

  return cos;
}

///////////////////////////////////////////////////////////////////////////////

CosineCalculator::CosineCalculator(const mpf& radians,
                                   int exponent,
                                   char stop_criteria,
                                   char operation_mode,
                                   unsigned int num_threads)
    : radians(fixRadians(radians), exponent),
      precision(calculatePrecision(exponent), exponent),
      exponent(exponent),
      stop_criteria(stop_criteria),
      operation_mode(operation_mode),
      num_threads(num_threads),
      terms(num_threads, 0),
      barrier(num_threads),
      cos(0, exponent) {
}

void CosineCalculator::worker(unsigned int offset) {
  terms[offset] = std::move(calculateTerm(radians, iteration * terms.size() + offset));
  if (operation_mode == 'd')
    std::cout << "Thread number " << offset
              << " has reached the barrier!" << std::endl;
}

bool CosineCalculator::coordinator() {
  mpf aux(0, exponent);
  for (auto &term : terms) aux += term;

  cos += aux;

  if (operation_mode == 'd') {
    gmp_printf("Partial cosine value: %.*Ff\n", exponent, cos.get_mpf_t());
  }

  if (stop_criteria == 'f') {
    if (abs(aux) < precision) return true;
  } else if (stop_criteria == 'm') {
    if (std::any_of(terms.begin(), terms.end(), 
                    [this] (const mpf& t) { return abs(t) < precision; })) 
      return true;
  }
  return false;
}

void CosineCalculator::asyncCalculateTerm(unsigned int offset,
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

mpf CosineCalculator::multiThreadedCosine() {

  std::vector<std::thread> threads;

  for (unsigned int offset = 0; offset < num_threads-1; offset++) {
    threads.emplace_back(&CosineCalculator::asyncCalculateTerm, this, offset, false);
  }

  asyncCalculateTerm(num_threads-1, true);

  for (auto &thread : threads) thread.join();

  std::cout << "Number of iterations: " << iteration << std::endl;
  gmp_printf("Cosine value: %.*Ff\n", exponent, cos.get_mpf_t());

  return cos;
}
