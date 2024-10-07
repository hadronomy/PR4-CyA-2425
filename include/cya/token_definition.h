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
 * Archivo token_definition: cya::TokenDefinition definition
 * Referencias:
 */

#pragma once

#include <functional>
#include <regex>
#include <string>

namespace cya {

class Token;

/**
 * @brief Defines all the properties required to find and work
 * with tokens within a text
 */
class TokenDefinition {
 public:
  TokenDefinition(const std::string& name, const std::regex& regex,
                  const std::function<std::map<std::string, std::string>(
                      const std::smatch&)>& serializer,
                  const std::function<std::string(const Token&)>& to_string,
                  const bool is_multiline = false)
      : name_(name),
        regex_(regex),
        serializer_(serializer),
        to_string_func_(to_string),
        is_multiline_(is_multiline) {}

  inline std::string GetName() const { return name_; }
  inline std::regex GetRegex() const { return regex_; }

  inline std::function<std::map<std::string, std::string>(const std::smatch&)>
  GetSerializer() const {
    return serializer_;
  }

  inline std::function<std::string(const Token&)> GetToString() const {
    return to_string_func_;
  }

  inline bool IsMultiline() const { return is_multiline_; }

 private:
  std::string name_;
  std::regex regex_;
  std::function<std::map<std::string, std::string>(const std::smatch&)>
      serializer_;
  std::function<std::string(const Token&)> to_string_func_;
  bool is_multiline_;
};

}  // namespace cya
