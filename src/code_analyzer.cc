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
 * Archivo code_analyzer.cc: cya::CodeAnalyzer implementation
 * Referencias:
 */

#include <map>
#include <regex>
#include <string>

#include "cya/code_analyzer.h"
#include "cya/token.h"

namespace cya {

/**
 * @brief Analyzes the given lines and saves the resulting tokens
 * @param lines
 */
void CodeAnalyzer::Analyze(const std::string& text) {
  for (const auto& definition : token_definitions_) {
    std::smatch match;
    const std::regex& regex = definition.GetRegex();
    std::sregex_iterator end;
    std::sregex_iterator iter(text.begin(), text.end(), regex);
    int current_line = 1;
    std::string::const_iterator current_line_start = text.begin();
    for (; iter != end; ++iter) {
      std::smatch match = *iter;
      auto match_start = match.position();
      auto match_lenght = match.length();
      auto match_end = match_start + match_lenght;

      int start_line = current_line;
      std::string::const_iterator temp_line_start = current_line_start;

      while (text.begin() + match_start >= current_line_start &&
             current_line_start != text.end()) {
        if (*current_line_start == '\n') {
          current_line++;
        }
        current_line_start++;
      }

      int start_column = match_start - (current_line_start - text.begin());
      int end_line = start_line;
      int end_column = start_column;

      for (auto it = text.begin() + match_start; it != text.begin() + match_end;
           ++it) {
        if (*it == '\n') {
          end_line++;
          temp_line_start = it + 1;
        }
      }

      if (end_line > start_line) {
        end_column = match_end - (temp_line_start - text.begin());
      }

      std::map<std::string, std::string> values =
          definition.GetSerializer()(match);

      std::optional<int> optional_end_line =
          end_line == start_line ? std::optional<int>(std::nullopt) : end_line;

      TokenPosition token_position{current_line, optional_end_line,
                                   start_column, end_column};
      Token token(token_position, values, definition.GetToString());
      AddToken(definition.GetName(), token);
    }
  }
}

}  // namespace cya
