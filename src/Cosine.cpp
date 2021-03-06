// Standard headers
#include <cstdlib>
#include <iostream>

// Internal headers
#include "InputArgs.hpp"
#include "CosineCalculator.hpp"

int main(int argc, char **argv)
{
  if (argc != 5 and argc != 6) {
    std::cerr << "USAGE: "
              << argv[0]
              << " [0|n] [f|m] p x [d|s]"
              << std::endl;
    return EXIT_FAILURE;
  }

  InputArgs input_args(argc, argv);

  CosineCalculator calculator(
    mpf(input_args.angle),
    input_args.precision,
    input_args.stop_criteria,
    input_args.operation_mode,
    input_args.n_threads
  );

  calculator.calculateCosine();

  return EXIT_SUCCESS;
}
