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
 * Archivo args.h: Args definition
 * Referencias:
 */

#ifndef CYA_ARGS_H_
#define CYA_ARGS_H_

#include <map>
#include <string>

namespace cya {

template<class TType>
struct ArgumentTypeDefinition { };
struct ArgumentTypeBool : ArgumentTypeDefinition<bool> { };
struct ArgumentTypeLiteral : ArgumentTypeDefinition<std::string> { };
struct ArgumentTypeInt : ArgumentTypeDefinition<int> { };

struct ArgumentData {
};

class Args {
 public:
  Args() { }
 private:
  std::map<std::string, bool> bool_args_;
  std::map<std::string, std::string> literal_args_;
  std::map<std::string, std::string> int_args_;
};

}

#endif // CYA_ARGS_H_
