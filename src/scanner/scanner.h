#ifndef SCANNER_SCANNER_H_
#define SCANNER_SCANNER_H_

#include <cstdint>
#include <fstream>
#include <string>

namespace y86compiler {
//----------------------------------------------------------------------------
/// @brief Simple reader gets line by line
///
class Scanner {
 private:
   std::ifstream fin;
   uint32_t line_number;
 public:
  Scanner(std::string in_file);
  std::string get_line();
  uint32_t get_lineno();
  bool is_eof();
  void close();
};
}  /// y86compiler

#endif  // SCANNER_SCANNER_H_
