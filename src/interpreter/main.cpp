#include <iostream>
#include <fstream>
#include <string>

#include "program.h"

int main() {
  std::ifstream infile("program.in");
  interpreter::Program program(infile);
  program.Run(std::cin, std::cout);
  return 0;
}
