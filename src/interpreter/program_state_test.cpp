#include "program_state.h"

#include <sstream>
#include "gtest/gtest.h"

namespace {

using std::istringstream;
using std::ostringstream;
using std::string;
using interpreter::ProgramState;

string CharString(char c) {
  string result;
  result.push_back(c);
  return result;
}

TEST(ProgramStateTest, Initialization) {
  ProgramState state;
  ostringstream os;

  for (int i = 0; i < 10; i++) {
    state.Output(os);
    EXPECT_EQ(os.str(), CharString('\0'));
    os.str("");
    state.IncCursor();
  }
}

TEST(ProgramStateTest, Initialization2) {
  ProgramState state;
  ostringstream os;

  for (int i = 0; i < 10; i++) {
    state.Output(os);
    EXPECT_EQ(os.str(), CharString('\0'));
    os.str("");
    state.DecCursor();
  }
}

TEST(ProgramStateTest, ModifyData) {
  ProgramState state;
  ostringstream os;
  string expected = "Hello";

  for (int i = 0; i < expected.size(); i++) {
    for (char c = 0; c < expected[i]; c++) {
      state.IncData();
    }
    state.Output(os);
    state.IncCursor();
  }
  EXPECT_EQ(os.str(), expected);

  os.str("");
  for (int i = 0; i < expected.size(); i++) {
    state.DecCursor();
  }
  for (int i = 0; i < expected.size(); i++) {
    state.Output(os);
    state.IncCursor();
  }
  EXPECT_EQ(os.str(), expected);
}

TEST(ProgramStateTest, ModifyLeftData) {
  ProgramState state;
  ostringstream os;
  string expected = "Hello";

  for (int i = 0; i < expected.size(); i++) {
    for (char c = 0; c < expected[i]; c++) {
      state.IncData();
    }
    state.Output(os);
    state.DecCursor();
  }
  EXPECT_EQ(os.str(), expected);

  os.str("");
  for (int i = 0; i < expected.size(); i++) {
    state.IncCursor();
  }
  for (int i = 0; i < expected.size(); i++) {
    state.Output(os);
    state.DecCursor();
  }
  EXPECT_EQ(os.str(), expected);
}

TEST(ProgramStateTest, Input) {
  ProgramState state;
  string expected = "Hello";
  istringstream iss(expected);
  ostringstream os;

  for (int i = 0; i < expected.size(); i++) {
    state.Input(iss);
    state.IncCursor();
  }
  for (int i = 0; i < expected.size(); i++) {
    state.DecCursor();
  }
  for (int i = 0; i < expected.size(); i++) {
    state.Output(os);
    state.IncCursor();
  }
  EXPECT_EQ(os.str(), expected);
}

TEST(ProgramStateTest, DecData) {
  ProgramState state;
  string expected = "Hello";
  istringstream iss(expected);
  ostringstream os;

  for (int i = 0; i < expected.size(); i++) {
    state.Input(iss);
    state.Output(os);
    state.IncCursor();
  }
  EXPECT_EQ(os.str(), expected);

  os.str("");
  for (int i = 0; i < expected.size(); i++) {
    state.DecCursor();
  }
  for (int i = 0; i < expected.size(); i++) {
    state.DecData();
    state.DecData();
    --expected[i];
    --expected[i];
    state.Output(os);
    state.IncCursor();
  }
  EXPECT_EQ(os.str(), expected);
}

} // namespace
