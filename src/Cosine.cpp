// Standard headers
#include <cstdlib>
#include <iostream>

// Internal headers
#include "InputArgs.hpp"

int main(int argc, char **argv)
{
  if (argc != 6) {
    std::cerr << "USAGE: "
              << argv[0]
              << "[0|n] [f|m] p x [d|s]"
              << std::endl;
    return EXIT_FAILURE;
  }

  InputArgs input_args(argc, argv);

  return EXIT_SUCCESS;
}
