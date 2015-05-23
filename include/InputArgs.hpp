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
  double       cosine;
  char         debug_level;

  InputArgs(int argc, char const *const *argv);

 private:
  std::vector<std::stringstream> argstream;

  void process_input();
  void read_input();
};

#endif
