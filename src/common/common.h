#ifndef COMMON_COMMON_H_
#define COMMON_COMMON_H_

#include <cstdint>
#include <string>
#include <vector>

#ifdef y86_32
typedef int32_t data_t;
#else
typedef int64_t data_t;
#endif  // 32BIT

#define MAX_LINE_LENGTH 1024

namespace y86compiler {
void tokenize_string(const std::string& str,
                     std::vector<std::string>& tokens,
                     const std::string& delimiters);
}  // namespace y86compiler

#endif  // COMMON_COMMON_H_
