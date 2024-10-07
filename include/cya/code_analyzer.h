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
 * Archivo code_analyzer.h: cya::CodeAnalyzer definition
 * Referencias:
 */

#pragma once

#include <map>
#include <set>
#include <string>
#include <vector>

#include "token.h"
#include "token_definition.h"

namespace cya {

/**
 * @brief Class that analyzes a set of lines and saves the resulting tokens
 */
class CodeAnalyzer {
 public:
  explicit CodeAnalyzer(const std::vector<TokenDefinition>& definitions)
      : token_definitions_(definitions), tokens_(), multiline_tokens_() {
    for (const auto& definition : definitions) {
      if (definition.IsMultiline()) {
        multiline_tokens_.emplace(definition.GetName());
      }
    }
  }

  template <class... TType>
  explicit CodeAnalyzer(TType... definition)
      : CodeAnalyzer(std::vector<TokenDefinition>{definition...}) {}

  inline std::vector<Token> GetTokens(const std::string& token_name) const {
    if (!tokens_.count(token_name))
      return std::vector<Token>();
    return tokens_.at(token_name);
  }

  inline std::map<std::string, std::vector<Token>> GetAllTokens() const {
    return tokens_;
  }

  inline bool HasTokens(const std::string& token_name) const {
    return tokens_.count(token_name);
  }

  inline bool IsMultiline(const std::string& token_name) const {
    return multiline_tokens_.count(token_name);
  }

  inline void AddToken(const std::string& token_name, const Token& token) {
    if (!tokens_.count(token_name)) {
      tokens_.emplace(token_name, std::vector<Token>());
    }
    tokens_.at(token_name).emplace_back(token);
  }

  inline void RemoveTokens(const std::string& token_name) {
    tokens_.erase(token_name);
  }

  void Analyze(const std::vector<std::string>& lines);

 private:
  std::vector<TokenDefinition> token_definitions_;
  std::map<std::string, std::vector<Token>> tokens_;
  std::set<std::string> multiline_tokens_;
};

}  // namespace cya
