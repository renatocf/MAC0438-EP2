#ifndef HPP_INPUT_ARGS_DEFINED
#define HPP_INPUT_ARGS_DEFINED

// Standard headers
#include <thread>
#include <vector>
#include <sstream>

struct InputArgs {
 public:
  unsigned int n_threads;
  char         stop_criteria;
  int          precision;
  double       angle;
  char         operation_mode = 'n';

  InputArgs(int argc, char const *const *argv);

 private:
  std::vector<std::stringstream> argstream;

  void process_input();
  void read_input();
};

#endif
