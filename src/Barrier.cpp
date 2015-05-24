#include <iostream>

// Internal headers
#include "Barrier.hpp"

Barrier::Barrier(unsigned int num_threads) {
  pthread_barrier_init(&barrier, NULL, num_threads);
}

Barrier::~Barrier() {
  pthread_barrier_destroy(&barrier);
}

void Barrier::wait() {
  pthread_barrier_wait(&barrier);
}
