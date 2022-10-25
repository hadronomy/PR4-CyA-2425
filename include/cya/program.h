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
 * Archivo program.h: Program definition
 * Referencias:
 */

#ifndef CYA_PROGRAM_H_
#define CYA_PROGRAM_H_

#include "cya/command.h"

namespace cya {

class Program {
 public:
  Program() : command_("") {
    command_.SetPositionalArgumentsRange(2, 2);
  }

  inline Command& GetCli() { return command_; }

  void Run(const int argc, const char* argv[]);

 private:
  Command command_;
};

} // cya

#endif //CYA_PROGRAM_H_
