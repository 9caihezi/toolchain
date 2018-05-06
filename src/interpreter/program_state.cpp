#include "program_state.h"

namespace interpreter {

ProgramState::ProgramState() {
  data_right_.push_back(0);
}

void ProgramState::IncCursor() {
  ++cursor_;
  if (cursor_ > 0) {
    while(cursor_ >= data_right_.size()) {
      data_right_.push_back(0);
    }
  }
}

void ProgramState::DecCursor() {
  --cursor_;
  if (cursor_ < 0) {
    while(LeftIndex() >= data_left_.size()) {
      data_left_.push_back(0);
    }
  }
}

char& ProgramState::Current() {
  if (cursor_ >= 0) {
    return data_right_[cursor_];
  } else {
    return data_left_[LeftIndex()];
  }
}

const char& ProgramState::Current() const {
  if (cursor_ >= 0) {
    return data_right_[cursor_];
  } else {
    return data_left_[LeftIndex()];
  }
}

void ProgramState::IncData() {
  ++Current();
}
void ProgramState::DecData() {
  --Current();
}

void ProgramState::Output(std::ostream& output) const {
  output << Current();
}

void ProgramState::Input(std::istream& input) {
  input.get(Current());
}

} // namespace interpreter


