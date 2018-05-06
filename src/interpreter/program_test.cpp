#include "program.h"

#include <sstream>
#include "gtest/gtest.h"

const char HELLO_WORLD_PROGRAM[] = "++++++++++[>+++++++>++++++++++>+++>+<<<<-]>++.>+.+++++++..+++.>++.<<+++++++++++++++.>.+++.------.--------.>+.>.";

namespace {

TEST(ProgramTest, HelloWorld) {
  std::istringstream iss(HELLO_WORLD_PROGRAM);
  interpreter::Program program(iss);
  std::istringstream input;
  std::ostringstream output;

  program.Run(input, output);

  EXPECT_TRUE(static_cast<bool>(input));
  EXPECT_EQ(output.str(), "Hello World!\n");
}

} // namespace
