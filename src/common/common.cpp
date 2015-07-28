#include <string>

#include "./common.h"

namespace y86compiler {
void
tokenize_string (const std::string& str,
                 std::vector<std::string>& tokens,
                 const std::string& delimiters) {
  std::string::size_type last_pos = str.find_first_not_of(delimiters, 0);
  std::string::size_type pos = str.find_first_of(delimiters, last_pos);

  while (std::string::npos != pos || std::string::npos != last_pos) {
    tokens.push_back(str.substr(last_pos, pos - last_pos));
    last_pos = str.find_first_not_of(delimiters, pos);
    pos = str.find_first_of(delimiters, last_pos);
  }
}
}  // namespace y86compiler
