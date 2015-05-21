// Standard headers
#include <thread>
#include <iostream>

// Internal headers
#include "InputArgs.hpp"

int main(int argc, char **argv)
{
  unsigned int n = std::thread::hardware_concurrency();
  std::cout << n << " concurrent threads are supported.\n";

  InputArgs input_args;

  std::cout << input_args.n_threads << std::endl;

  return 0;
}
