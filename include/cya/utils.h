
#ifndef CYA_UTILS_H_
#define CYA_UTILS_H_

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>

namespace cya {

/**
 * @brief Returns the uppercase version of the provided input_string
 * @param input_string The string to be converted
 * @return
 */
inline std::string ToUpper(std::string input_string) {
  std::transform(input_string.begin(), input_string.end(), input_string.begin(), ::toupper);
  return input_string;
}

/**
 * @brief Returns a vector with all the lines of the file at the provided input_file_path
 * @param input_file_path
 * @return
 */
inline std::vector<std::string> ReadFileLines(const std::string& input_file_path) {
  std::ifstream input_file(input_file_path);
  if (!input_file.is_open()) {
    std::cerr << "The file at " << input_file_path << " could not be opened" << std::endl;
    exit(EXIT_FAILURE);
  }
  std::vector<std::string> lines;
  std::string current_line;
  while (!input_file.eof()) {
    std::getline(input_file, current_line);
    lines.emplace_back(current_line);
  }
  return lines;
}

}

#endif //CYA_UTILS_H_
