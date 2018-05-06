#include "program.h"

#include <cassert>
#include <iostream>
#include <vector>

namespace interpreter {

using std::cerr;
using std::endl;
using std::istream;
using std::ostream;
using std::vector;

Program::Program(istream& input) {
  size_t row = 0;
  size_t column = 1;
  char ch;
  vector<size_t> stack;
  while (input.get(ch)) {
    if (ch == '\n') {
      ++row;
      column = 1;
    } else {
      ++column;
    }

    switch(ch) {
    case '<':
    case '>':
    case '+':
    case '-':
    case '.':
    case ',':
      program_.push_back(ch);
      break;
    case '[':
      stack.push_back(program_.size());
      program_.push_back(ch);
      break;
    case ']':
    {
      if (stack.empty()) {
        cerr << "Cannot find '[' for ']' at row " << row
             << ", column " << column << endl;
        exit(1);
      }
      size_t begin = stack.back();
      size_t end = program_.size();
      stack.pop_back();
      jump_table_[begin] = end;
      jump_table_[end] = begin;
      program_.push_back(ch);
      break;
    }
    default:
      break; // ignore comments
    }
  }
  if (!stack.empty()) {
    cerr << "More '[' than ']'" << endl;
    exit(1);
  }
}

void Program::Run(istream& input, ostream& output) {
  state_ = std::unique_ptr<ProgramState>(new ProgramState());
  cursor_ = 0;
  while (cursor_ < program_.size()) {
    // program_[cursor_] is valid
    switch(program_[cursor_]) {
    case '>':
      state_->IncCursor();
      break;
    case '<':
      state_->DecCursor();
      break;
    case '+':
      state_->IncData();
      break;
    case '-':
      state_->DecData();
      break;
    case '.':
      state_->Output(output);
      break;
    case ',':
      state_->Input(input);
      break;
    case '[':
      if (state_->IsZero()) {
        cursor_ = jump_table_[cursor_];
      }
      break;
    case ']':
      if (!state_->IsZero()) {
        cursor_ = jump_table_[cursor_];
      }
      break;
    default:
      assert(!"Unsupported command");
    }
    ++cursor_;
  }
}

} // namespace interpreter
