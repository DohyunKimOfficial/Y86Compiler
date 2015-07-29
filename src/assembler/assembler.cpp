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

void
Y86Assembler::deassemble() {
  std::string dump = "";

  while (!this->scanner->is_eof()) {
    dump += this->scanner->get_line();
  }

  while (dump.length() > 0) {
    Y86Assembly assembly(dump);
    std::cout << assembly.to_string() << std::endl;

    dump.erase(0, assembly.get_hex_length());
  }
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
