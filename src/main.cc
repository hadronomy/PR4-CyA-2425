/** 
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingenierıa Informática
 * Asignatura: Computabilidad y Algoritmia
 * Curso: 2º
 * Práctica 4: Regex Curso 2022-2023
 * Grado en Ingeniería Informática Computabilidad y Algoritmia
 * Autor: Pablo Hernández Jiménez
 * Correo: alu0101495934@ull.edu.es
 * Fecha: 17/10/2022
 * Archivo main.cc: client program.
 * Referencias:
 */

#include <iostream>
#include <regex>
#include <sstream>

#include "cya/code_analyzer.h"
#include "cya/token_definition.h"
#include "cya/command.h"

int main(int argc, const char* argv[]) {
  cya::Command root_cmd("cya <input_file>");
  root_cmd.Parse(argc, argv);
  cya::TokenDefinition statement_definition("STATEMENTS", std::regex(R"((while|for) \(.*\))"),[](const std::smatch& match) {
    std::map<std::string, std::string> values;
    values.emplace("type", match[1]);
    return values;
  }, [](const cya::Token& token) -> std::string {
    std::stringstream result;
    result << "[Line " << token.GetLine() << "] LOOP: " << token.GetValues().at("type");
    return result.str();
  });
  cya::TokenDefinition variable_definition("VARIABLES", std::regex(R"((int|double) +(.*) += +([0-9]+))"), [](const std::smatch& match) {
    std::map<std::string, std::string> values;
    values.emplace("type", match[1]);
    values.emplace("name", match[2]);
    values.emplace("value", match[3]);
    return values;
  }, [](const cya::Token& token) {
    std::stringstream result;
    result << "[Line " << token.GetLine() << "] " << token.GetValues().at("type") << ": ";
    result << token.GetValues().at("name");
    return result.str();
  });
  cya::TokenDefinition comment_definition("COMMENT", std::regex(R"((/\*\*( |.)*)|( *\*( |.)*)|( *\*/))"), [](const std::smatch& match) {
    std::map<std::string, std::string> values;
    values.emplace("value", match[0]);
    return values;
  }, [](const cya::Token& token) {
    std::stringstream result;
    result << token.GetValue("value");
    return result.str();
  });
  cya::CodeAnalyzer code_analyzer(statement_definition, variable_definition, comment_definition);
  std::vector<std::string> lines {
    "/** Holis",
    "  * Pepe",
    "  */",
    "while (true)",
    "hey.no",
    "for (true)",
    "int holi = 10"
  };
  code_analyzer.Analyze(lines);
  for (const auto& pair : code_analyzer.GetAllTokens()) {
    std::cout << pair.first << std::endl;
    for (const auto& token : pair.second) {
      std::cout << token << std::endl;
    }
  }
  return 0;
}
