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
delete_comment(std::string str) {
  std::string comment_indicator = "//";
  std::size_t loc = str.find(comment_indicator);
  if (loc != std::string::npos) {
    str.erase(loc, str.length() - loc);
  }

  return str;
}

static std::string
trim(std::string str) {
  if (str.empty()) {
    return str;
  } else {
    std::size_t firstScan = str.find_first_not_of(" \t\n");
    std::size_t first     = firstScan == std::string::npos ? str.length() : firstScan;
    std::size_t last      = str.find_last_not_of(" \t\n");

    return str.substr(first, last-first+1);
  }
}

static void
deassemble_block(std::string hex_str, address_t byte_address) {
  while (hex_str.length() > 0) {
    Y86Assembly assembly(hex_str, byte_address);
#ifdef SHOW_ADDRESS
    std::cout << byte_address << ":" << assembly.to_string() << std::endl;
#else
    std::cout << assembly.to_string() << std::endl;
#endif

    hex_str.erase(0, assembly.get_hex_length());
    byte_address += assembly.get_byte_size();
  }
}

void
Y86Assembler::deassemble() {
  address_t byte_address = 0;
  address_t block_address = 0;
  std::string dump = "";

  while (!this->scanner->is_eof()) {
    std::string line = trim(delete_comment(this->scanner->get_line()));

    if (line[0] != '@') {
      dump += line;
    } else {
      deassemble_block(dump, byte_address);

      sscanf(line.substr(1, line.length()-1).c_str(), "%lx", &block_address);
      byte_address = block_address * 4;
      std::cout << std::endl << line << "(" << byte_address  << ")" << std::endl;
      dump = "";
    }
  }

  deassemble_block(dump, byte_address);
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
