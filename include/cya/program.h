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
 * Archivo program.h: Program definition
 * Referencias:
 */

#pragma once

#include <sstream>

#include "cya/code_analyzer.h"
#include "cya/command.h"

namespace cya {

/**
 * @brief Defines main program functionality
 */
class Program {
 public:
  Program() : command_("cya <input_file> <output_file>") {
    command_.SetPositionalArgumentsRange(2, 2);
    std::stringstream description;
    description << "Analyzes the given <input_file> and outputs a series of "
                   "tokens into the <output_file>"
                << std::endl;
    command_.SetLong(description.str());
  }

  /**
   * @brief Returns a modifiable reference of the cli
   * @return
   */
  inline Command& GetCli() { return command_; }

  void Run(const int argc, const char* argv[]);

 private:
  Command command_;
};

void PrintResults(CodeAnalyzer& code_analyzer, std::ostream& output_file,
                  const Command& cli);

}  // namespace cya
