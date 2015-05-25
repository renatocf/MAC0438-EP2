// Standard headers
#include "InputArgs.hpp"

InputArgs::InputArgs(int argc, char const *const *argv)
    : argstream(argv, argv + argc) {
  read_input();
  process_input();
}

void InputArgs::process_input() {
  if (n_threads == 0)
    n_threads = std::thread::hardware_concurrency();
}

void InputArgs::read_input() {
  argstream[1] >> n_threads;
  argstream[2] >> stop_criteria;
  argstream[3] >> precision;
  argstream[4] >> angle;

  if (argstream.size() > 5)
    argstream[5] >> operation_mode;
}
