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
 * Archivo command.cc: Command implementation
 * Referencias:
 */

#include <vector>
#include <iostream>

#include "cya/command.h"

namespace cya {

Command& Command::Parse(const int argc, const char *argv[]) {
  std::vector<std::string> arguments(argv + 1, argv + argc);
  return Parse(arguments);
}

Command& Command::Parse(const std::vector<std::string>& arguments) {
  std::vector<std::string> positional_arguments;
  for (const auto& argument : arguments) {
    if (subcommands_.count(argument)) {
      subcommands_.at(argument)->Parse(std::vector<std::string>(arguments.begin() + 1, arguments.end()));
      return static_cast<Command&>(*this);
    }
    if (argument[0] != '-') {
      if (positional_arguments.size() + 1 > max_positional_) {
        std::cerr << "Provided more positional arguments than expected" << std::endl;
        std::cerr << "Run with the --help flag for more information" << std::endl;
        exit(EXIT_FAILURE);
      }
      positional_arguments.emplace_back(argument);
    }
  }
  if (positional_arguments.size() < min_positional_) {
    std::cerr << "Provided less positional arguments than expected" << std::endl;
    std::cerr << "Run with the --help flag for more information" << std::endl;
    exit(EXIT_FAILURE);
  }
  std::cout << std::endl;
  positional_args_ = positional_arguments;
  return static_cast<Command&>(*this);
}

}
