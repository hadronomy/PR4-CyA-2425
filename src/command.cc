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
 * Archivo command.cc: Command implementation
 * Referencias:
 */

#include <iostream>
#include <regex>
#include <vector>

#include "cya/command.h"

namespace cya {

/**
 * @brief Parses the command line arguments
 * @param argc
 * @param argv
 * @return
 */
Command& Command::Parse(const int argc, const char* argv[]) {
  std::vector<std::string> arguments(argv + 1, argv + argc);
  return Parse(arguments);
}

/**
 * @brief Parses the command line arguments
 * @param arguments
 * @return
 */
Command& Command::Parse(const std::vector<std::string>& arguments) {
  std::vector<std::string> positional_arguments;
  for (int i = 0; i < arguments.size(); ++i) {
    const auto& argument = arguments[i];
    if (subcommands_.count(argument)) {
      subcommands_.at(argument)->Parse(
          std::vector<std::string>(arguments.begin() + 1, arguments.end()));
      return static_cast<Command&>(*this);
    }
    if (argument[0] != '-') {
      if (positional_arguments.size() + 1 > max_positional_) {
        std::cerr << "Provided more positional arguments than expected"
                  << std::endl;
        std::cerr << "Run with the --help flag for more information"
                  << std::endl;
        exit(EXIT_FAILURE);
      }
      positional_arguments.emplace_back(argument);
      continue;
    }
    std::smatch match;
    if (std::regex_search(argument, match, std::regex(R"(--?(\S+))"))) {
      args_.Parse(match[1], "");  // TODO: Parse arguments with values
      if (args_.IsBool("help")) {
        ShowHelp();
        exit(EXIT_SUCCESS);
      }
    } else {
      std::cerr << "Malformed argument: " << argument;
      exit(EXIT_FAILURE);
    }
    return static_cast<Command&>(*this);
  }
  if (positional_arguments.size() < min_positional_) {
    std::cerr << "Provided less positional arguments than expected"
              << std::endl;
    std::cerr << "Run with the --help flag for more information" << std::endl;
    exit(EXIT_FAILURE);
  }
  std::cout << std::endl;
  positional_args_ = positional_arguments;
  return static_cast<Command&>(*this);
}

void Command::ShowHelp() const {
  std::cout << std::endl;
  std::cout << "COMMAND" << std::endl;
  std::cout << GetUsage() << std::endl;
  std::cout << std::endl;
  if (!GetLong().empty()) {
    std::cout << "DESCRIPTION" << std::endl;
    std::cout << GetLong() << std::endl;
  }
  std::cout << "FLAGS" << std::endl;
  std::cout << "--help, -h\tShows helpful information about this command"
            << std::endl;
  std::cout << std::endl;
}

}  // namespace cya
