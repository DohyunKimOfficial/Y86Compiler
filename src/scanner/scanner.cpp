#include "../common/common.h"
#include "./scanner.h"

#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>

namespace y86compiler {
Scanner::Scanner(std::string in_file) {
  this->fin.open(in_file, std::ifstream::in);
  this->line_number = 0;
}

std::string
Scanner::get_line() {
  char line_buffer[MAX_LINE_LENGTH] = "\0";

  std::string line = "";
  if (this->fin.is_open()) {
    this->fin.getline(line_buffer, MAX_LINE_LENGTH);
    this->line_number++;
  }
  return std::string(line_buffer);
}

uint32_t
Scanner::get_lineno() {
  return this->line_number;
}

void
Scanner::close() {
  if (this->fin.is_open()) {
    this->fin.close();
  }
}

bool
Scanner::is_eof() {
  if (this->fin.is_open()) {
    return this->fin.eof();
  } else {
    return true;
  }
}
}
