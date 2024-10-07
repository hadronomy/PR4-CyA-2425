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
 * Archivo program.cc: Program implementation
 * Referencias:
 */

#include <fstream>

#include "cya/code_analyzer.h"
#include "cya/program.h"
#include "cya/token_definitions.h"
#include "cya/utils.h"

namespace cya {

/**
 * @brief Executes the program
 * @param argc
 * @param argv
 */
void Program::Run(const int argc, const char* argv[]) {
  GetCli().Parse(argc, argv);
  CodeAnalyzer code_analyzer(kTokenDefinitions);
  std::vector<std::string> lines = ReadFileLines(GetCli().GetPositionalArg(0));
  code_analyzer.Analyze(lines);
  std::ofstream output_file(GetCli().GetPositionalArg(1));
  output_file << "PROGRAM: " << GetCli().GetPositionalArg(0) << std::endl;
  auto blocks = cya::ParseMultiline(code_analyzer.GetTokens("COMMENTS"));
  const bool kHasDescription =
      code_analyzer.HasTokens("COMMENTS") &&
      code_analyzer.GetTokens("COMMENTS").front().GetLine() == 1;
  code_analyzer.RemoveTokens("COMMENTS");
  if (kHasDescription) {
    output_file << "DESCRIPTION: " << std::endl;
    for (const auto& token : blocks.at(0)) {
      output_file << token << std::endl;
    }
    output_file << std::endl;
  }
  for (const auto& pair : code_analyzer.GetAllTokens()) {
    const auto& kTokens = pair.second;
    output_file << pair.first << ":" << std::endl;
    if (code_analyzer.IsMultiline(pair.first)) {
      cya::PrintMultiline(output_file, pair.second);
    } else {
      for (const auto& token : kTokens) {
        output_file << token << std::endl;
      }
    }
    output_file << std::endl;
  }
  output_file << "COMMENTS: " << std::endl;
  if (kHasDescription) {
    auto description_block = blocks.at(0);
    output_file << "[Line " << description_block.front().GetLine() << "-"
                << description_block.back().GetLine() << "] ";
    output_file << "DESCRIPTION" << std::endl;
    blocks = std::vector<std::vector<Token>>(blocks.begin() + 1, blocks.end());
  }
  cya::PrintMultilineBlocks(output_file, blocks);
}

}  // namespace cya