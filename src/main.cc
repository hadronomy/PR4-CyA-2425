/** 
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingenierıa Informática
 * Asignatura: Computabilidad y Algoritmia
 * Curso: 2º
 * Práctica 3: Calculadora de Lenguajes Formales Curso 2022-2023
 * Grado en Ingeniería Informática Computabilidad y Algoritmia
 * Autor: Pablo Hernández Jiménez
 * Correo: alu0101495934@ull.edu.es
 * Fecha: 17/10/2022
 * Archivo main.cc: client program.
 * Referencias:
 */

#include <iostream>
#include <regex>

#include "cya/code_analyzer.h"
#include "cya/token_definition.h"

int main(int argc, const char* argv[]) {
  std::cout << "Hello World" << std::endl;
  TokenDefinition statement_definition("STATEMENT", std::regex("lines\\..*"), [](std::map<std::string, std::string>& value_map) {

  });
  TokenDefinition comment_definition("COMMENT", std::regex(""), [](std::map<std::string, std::string>& value_map) {

  });
  cya::CodeAnalyzer code_analyzer(statement_definition, comment_definition);
  std::vector<std::string> lines {
    "lines.git",
    "hey.no",
    "lines.txt"
  };
  code_analyzer.Analyze(lines);
  std::cout << code_analyzer.GetTokens("STATEMENT").size() << std::endl;
}
