#ifndef SRC_INTERPRETER_PROGRAM_STATE_H
#define SRC_INTERPRETER_PROGRAM_STATE_H

#include <sstream>
#include <string>

namespace interpreter {

class ProgramState {
public:
  ProgramState();
  ~ProgramState() = default;

  void IncCursor();
  void DecCursor();
  void IncData();
  void DecData();
  void Output(std::ostream& output) const;
  void Input(std::istream& input);
  bool IsZero() const { return Current() == 0; };
private:
  char& Current();
  const char& Current() const;
  int LeftIndex() const { return -cursor_ - 1; }
  std::string data_right_;
  std::string data_left_;
  int cursor_ = 0;
};

} // namespace interpreter

#endif
