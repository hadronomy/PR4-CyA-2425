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
 * Archivo utils.h: utility functions definitions
 * Referencias:
 */

#ifndef CYA_UTILS_H_
#define CYA_UTILS_H_

#include <string>
#include <vector>

namespace cya {

class Token;

std::string ToUpper(std::string input_string);
std::vector<std::string> ReadFileLines(const std::string& input_file_path);
void PrintMultiline(std::ostream& out, const std::vector<Token>& tokens);
void PrintMultilineBlocks(std::ostream& out,
                          const std::vector<std::vector<Token>>& blocks);
std::vector<std::vector<Token>> ParseMultiline(
    const std::vector<Token>& tokens);

}  // namespace cya

#endif  //CYA_UTILS_H_
