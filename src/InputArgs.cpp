// Standard headers
#include "InputArgs.hpp"

InputArgs::InputArgs() {
  read_input();
  process_input();
}

void InputArgs::process_input() {
  if (n_threads == 0)
    n_threads = std::thread::hardware_concurrency();
}

void InputArgs::read_input() {
  InputArgs input_args;

  std::cin >> n_threads;
  std::cin >> stop_criteria;
  std::cin >> precision;
  std::cin >> cosine;

  if (!std::cin.eof())
    std::cin >> debug_level;
}
