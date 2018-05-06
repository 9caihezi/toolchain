#ifndef SRC_INTERPRETER_PROGRAM_H
#define SRC_INTERPRETER_PROGRAM_H

#include <map>
#include <memory>
#include <sstream>
#include <string>

#include "program_state.h"

namespace interpreter {

class Program {
public:
  explicit Program(std::istream&);
  ~Program() = default;
  void Run(std::istream&, std::ostream&);
private:
  std::unique_ptr<ProgramState> state_;
  std::string program_;
  size_t cursor_ = 0;
  std::map<size_t, size_t> jump_table_;
};

} // namespace interpreter

#endif
