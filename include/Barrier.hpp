#ifndef HPP_BARRIER_DEFINED
#define HPP_BARRIER_DEFINED

// Standard headers
#include <pthread.h>

class Barrier {
 public:
  explicit Barrier(unsigned int num_threads);
  ~Barrier();

  void wait();

 private:
  pthread_barrier_t barrier;
};

#endif
