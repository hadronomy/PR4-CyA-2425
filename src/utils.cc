/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingenierıa Informática
 * Asignatura: Computabilidad y Algoritmia
 * Curso: 4º
 * Práctica 4: Code Analyzer Curso 2024-2025
 * Grado en Ingeniería Informática Computabilidad y Algoritmia
 * Autor: Pablo Hernández Jiménez
 * Correo: alu0101495934@ull.edu.es
 * Fecha: 07/10/2024
 * Archivo utils.cc: utility functions implementations
 * Referencias:
 */

#include <algorithm>
#include <fstream>
#include <iostream>

#include "cya/token.h"
#include "cya/utils.h"

namespace cya {

/**
 * @brief Returns the uppercase version of the provided input_string
 * @param input_string The string to be converted
 * @return
 */
std::string ToUpper(std::string input_string) {
  std::transform(input_string.begin(), input_string.end(), input_string.begin(),
                 ::toupper);
  return input_string;
}

/**
 * @brief Returns a vector with all the lines of the file at the provided input_file_path
 * @param input_file_path
 * @return
 */
std::vector<std::string> ReadFileLines(const std::string& input_file_path) {
  std::ifstream input_file(input_file_path);
  if (!input_file.is_open()) {
    std::cerr << "The file at " << input_file_path << " cannot be opened"
              << std::endl;
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

std::string ReadFile(const std::string& input_file_path) {
  std::ifstream input_file(input_file_path);
  if (!input_file.is_open()) {
    std::cerr << "The file at " << input_file_path << " cannot be opened"
              << std::endl;
    exit(EXIT_FAILURE);
  }
  std::string file_content((std::istreambuf_iterator<char>(input_file)),
                           std::istreambuf_iterator<char>());
  return file_content;
}

/**
 * @brief Prints a multiline representation of the given tokens
 * @param out
 * @param tokens
 */
void PrintMultiline(std::ostream& out, const std::vector<Token>& tokens) {
  if (tokens.front().GetLine() == tokens.back().GetLine()) {
    out << "[Line " << tokens.front().GetLine() << "]" << std::endl;
  } else {
    out << "[Line " << tokens.front().GetLine() << "-"
        << tokens.back().GetLine() << "]" << std::endl;
  }
  for (const auto& token : tokens) {
    out << token << std::endl;
  }
}

/**
 * @brief Prints all the multiline blocks within the given blocks
 * @param out
 * @param blocks
 */
void PrintMultilineBlocks(std::ostream& out,
                          const std::vector<std::vector<Token>>& blocks) {
  for (const auto& block : blocks) {
    PrintMultiline(out, block);
  }
}

/**
 * @brief Parses a list of tokens and returns a list of vectors containing
 * the continuous lines
 * @param tokens
 * @return
 */
std::vector<std::vector<cya::Token>> ParseMultiline(
    const std::vector<cya::Token>& tokens) {
  std::vector<std::vector<cya::Token>> blocks;
  if (tokens.empty())
    return blocks;
  std::vector<cya::Token> contiguous_tokens;
  contiguous_tokens.push_back(tokens.front());
  for (int i = 1; i < tokens.size(); ++i) {
    const auto& kToken = tokens[i];
    if (contiguous_tokens.front().GetLine() + contiguous_tokens.size() !=
        kToken.GetLine()) {
      blocks.emplace_back(contiguous_tokens);
      contiguous_tokens = std::vector<cya::Token>();
    }
    contiguous_tokens.push_back(kToken);
  }
  if (contiguous_tokens.empty())
    return blocks;
  blocks.emplace_back(contiguous_tokens);
  return blocks;
}

std::string LineIdicatorFromPosition(const TokenPosition& position) {
  if (position.end_line) {
    std::string line = "[Line " + std::to_string(position.start_line) + "-" +
                       std::to_string(position.end_line.value()) + "]";
    return line;
  }
  return "[Line " + std::to_string(position.start_line) + "]";
}

}  // namespace cya
