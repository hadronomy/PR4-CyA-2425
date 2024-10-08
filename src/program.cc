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
#include <ostream>

#include "cya/code_analyzer.h"
#include "cya/command.h"
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
  Command cli = GetCli();
  cli.Parse(argc, argv);
  const auto& input_path = cli.GetPositionalArg(0);
  const auto& output_path = cli.GetPositionalArg(1);
  CodeAnalyzer code_analyzer(kTokenDefinitions);
  const auto& input_text = ReadFile(input_path);
  code_analyzer.Analyze(input_text);
  std::ofstream output_file = std::ofstream(output_path);
  PrintResults(code_analyzer, output_file, cli);
}

void PrintResults(CodeAnalyzer& code_analyzer, std::ostream& output_file,
                  const Command& cli) {
  const auto& input_path = cli.GetPositionalArg(0);
  output_file << "PROGRAM: " << input_path << std::endl;
  const auto& comment_tokens = code_analyzer.GetTokens("COMMENTS");
  auto blocks = cya::ParseMultiline(comment_tokens);
  const bool has_description = code_analyzer.HasTokens("COMMENTS") &&
                               comment_tokens.front().GetLine() == 1;
  code_analyzer.RemoveTokens("COMMENTS");
  if (has_description) {
    output_file << "DESCRIPTION: " << std::endl;
    for (const auto& token : blocks.at(0)) {
      output_file << token << std::endl;
    }
    output_file << std::endl;
  }
  for (const auto& pair : code_analyzer.GetAllTokens()) {
    const auto& kTokens = pair.second;
    output_file << pair.first << ":" << std::endl;
    for (const auto& token : kTokens) {
      output_file << token << std::endl;
    }
    output_file << std::endl;
  }
  output_file << "COMMENTS: " << std::endl;
  if (has_description) {
    auto description_block = blocks.at(0);
    auto position = description_block.front().GetPosition();
    auto start_line = position.start_line;
    auto end_line = position.end_line;
    output_file << LineIdicatorFromPosition(position) << std::endl;
    output_file << "DESCRIPTION" << std::endl;
    blocks = std::vector<std::vector<Token>>(blocks.begin() + 1, blocks.end());
  }
  cya::PrintMultilineBlocks(output_file, blocks);
}

}  // namespace cya