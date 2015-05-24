// Standard headers
#include <thread>
#include <future>

// External headers
#include "gmock/gmock.h"

// Internal headers
#include "Barrier.hpp"

static unsigned int kNumThreads = std::thread::hardware_concurrency()-1;
static unsigned int kNumCycles = 100;

static void WaitForBarrier(Barrier *barrier,
                           unsigned int n_cycles) {
  for (int i = 0; i < n_cycles; ++i)
    barrier->wait();
}

class  ABarrierRun : public testing::Test {
  
};

TEST_F(ABarrierRun, waitForBarrierOnce) {
  Barrier barrier(kNumThreads);
  std::vector<std::thread> threads;

  for (unsigned int i = 0; i < kNumThreads; i++)
    threads.emplace_back(WaitForBarrier, &barrier, 1);

  for (auto &thread : threads)
    thread.join();
}

TEST_F(ABarrierRun, waitForBarrierManyTimes) {
  Barrier barrier(kNumThreads);
  std::vector<std::thread> threads;

  for (unsigned int i = 0; i < kNumThreads; i++)
    threads.emplace_back(WaitForBarrier, &barrier, kNumCycles);

  for (auto &thread : threads)
    thread.join();
}
