#include <cstdint>
#include <iostream>
#include <fstream>
#include <string>

#include "../common/common.h"
#include "../scanner/scanner.h"
#include "../common/y86.h"
#include "./assembler.h"

namespace y86compiler {
Y86Assembler::Y86Assembler(std::string in_file)
: in_file(in_file), scanner(new Scanner(in_file)) {}

Y86Assembler::~Y86Assembler() {
  this->scanner->close();
  delete this->scanner;
}

static std::string
trim(std::string str) {
  if (str.empty()) {
    return str;
  } else {
    std::size_t firstScan = str.find_first_not_of(' ');
    std::size_t first     = firstScan == std::string::npos ? str.length() : firstScan;
    std::size_t last      = str.find_last_not_of(' ');

    return str.substr(first, last-first+1);
  }
}

static void
deassemble_block(std::string hex_str) {
  while (hex_str.length() > 0) {
    Y86Assembly assembly(hex_str);
    std::cout << assembly.to_string() << std::endl;

    hex_str.erase(0, assembly.get_hex_length());
  }
}

void
Y86Assembler::deassemble() {
  std::string dump = "";

  while (!this->scanner->is_eof()) {
    std::string line = trim(this->scanner->get_line());

    if (line[0] != '@') {
      dump += line;
    } else {
      deassemble_block(dump);
      std::cout << std::endl << line << std::endl;

      dump = "";
    }
  }

  deassemble_block(dump);
}
}  // namespace y86compiler

int main(int32_t argc, const char** argv) {
  std::string in_file = "input.txt";

  if (argc >= 2) {
    in_file = std::string(argv[1]);
  }

  y86compiler::Y86Assembler assembler(in_file);
  assembler.deassemble();
}
