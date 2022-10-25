/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingenierıa Informática
 * Asignatura: Computabilidad y Algoritmia
 * Curso: 2º
 * Práctica 4: Code Analyzer Curso 2022-2023
 * Grado en Ingeniería Informática Computabilidad y Algoritmia
 * Autor: Pablo Hernández Jiménez
 * Correo: alu0101495934@ull.edu.es
 * Fecha: 24/10/2022
 * Archivo code_analyzer.cc: cya::CodeAnalyzer implementation
 * Referencias:
 */

#include <regex>
#include <map>
#include <iostream>

#include "cya/code_analyzer.h"

namespace cya {

void CodeAnalyzer::Analyze(const std::vector<std::string>& lines) {
  for (int i = 0; i < lines.size(); ++i) {
    const auto& line = lines[i];
    for (const auto& definition : token_definitions_) {
      std::smatch match;
      if (std::regex_search(line, match, definition.GetRegex())) {
        std::map<std::string, std::string> values = definition.GetSerializer()(match);
        Token token(i + 1, 0, values, definition.GetToString());
        AddToken(definition.GetName(), token);
      }
    }
  }
}

}
