// Standard headers
#include <memory>
#include <iostream>

// External headers
#include "gmock/gmock.h"

// Internal headers
#include "InputArgs.hpp"

// Alias
using ::testing::DoubleNear;

const double PI = 3.141592653589793238462643;

class ASetOfInputArguments : public testing::Test {
};

TEST_F(ASetOfInputArguments, NonZeroNumberOfThreads) {
  std::unique_ptr<const char *[]> argv (
    new const char *[6] { "Cosine", "2", "f", "10", "1", "d" }
  );

  InputArgs args(6, argv.get());

  ASSERT_TRUE(args.n_threads == 2
    and args.stop_criteria   == 'f'
    and args.precision       == 10
    and args.angle           == 1
    and args.operation_mode  == 'd');
}

TEST_F(ASetOfInputArguments, ZeroNumberOfThreads) {
  std::unique_ptr<const char *[]> argv (
    new const char *[6] { "Cosine", "0", "f", "10", "1", "d" }
  );

  InputArgs args(6, argv.get());

  ASSERT_TRUE(args.n_threads == std::thread::hardware_concurrency()
    and args.stop_criteria   == 'f'
    and args.precision       == 10
    and args.angle           == 1
    and args.operation_mode  == 'd');
}
