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
 * Archivo token.cc: cya::Token implementation
 * Referencias:
 */

#include "cya/token.h"

namespace cya {

std::ostream& operator<<(std::ostream& out, const Token& input_token) {
  out << input_token.to_string_func_(input_token);
  return out;
}

}  // namespace cya
