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
 * Archivo token.h: cya::Token definition
 * Referencias:
 */

#pragma once

#include <functional>
#include <map>
#include <optional>
#include <ostream>
#include <string>

namespace cya {

struct TokenPosition {
  int start_line;
  std::optional<int> end_line;
  int start_column;
  int end_column;
};

/**
 * @brief Stores information about a token found within a text
 */
class Token {
 public:
  Token(const int line, const int position,
        const std::map<std::string, std::string>& values,
        const std::function<std::string(const Token&)>& to_string_func)
      : position_{TokenPosition{line, std::nullopt, position, position}},
        values_(values),
        to_string_func_(to_string_func) {}

  Token(const TokenPosition& position,
        const std::map<std::string, std::string>& values,
        const std::function<std::string(const Token&)>& to_string_func)
      : position_(position), values_(values), to_string_func_(to_string_func) {}

  inline int GetLine() const { return position_.start_line; }
  inline TokenPosition GetPosition() const { return position_; }

  inline std::string GetValue(const std::string& value_name) const {
    return values_.at(value_name);
  }

  inline std::map<std::string, std::string> GetValues() const {
    return values_;
  }

  inline std::function<std::string(const Token&)> GetToString() const {
    return to_string_func_;
  }

  inline std::string ToString() const { return to_string_func_(*this); }

  friend std::ostream& operator<<(std::ostream& out, const Token& input_token);

 private:
  TokenPosition position_;
  std::map<std::string, std::string> values_;
  std::function<std::string(const Token&)> to_string_func_;
};

}  // namespace cya
