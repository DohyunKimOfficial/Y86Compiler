#ifndef ASSEMBLER_ASSEMBLER_H_
#define ASSEMBLER_ASSEMBLER_H_

#include <cstdint>
#include <fstream>
#include <string>

#include "../common/common.h"
#include "../scanner/scanner.h"
#include "../common/y86.h"

namespace y86compiler {
class Y86Assembler {
 private:
  Scanner *scanner;
  std::string in_file;
 public:
  Y86Assembler (std::string in_file);
  ~Y86Assembler ();

  void deassemble();
};
}  // namespace y86compiler

#endif  // ASSEMBLER_ASSEMBLER_H_
