#ifndef HPP_INPUT_ARGS_DEFINED
#define HPP_INPUT_ARGS_DEFINED

// Standard headers
#include <thread>
#include <iostream>

struct InputArgs {
 public:
  unsigned int n_threads;
  char         stop_criteria;
  int          precision;
  double       cosine;
  char         debug_level;

  InputArgs();

 private:
  void process_input();
  void read_input();
};

#endif
