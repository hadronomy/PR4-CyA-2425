/** 
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingenierıa Informática
 * Asignatura: Computabilidad y Algoritmia
 * Curso: 2º
 * Práctica 4: Regex Curso 2022-2023
 * Grado en Ingeniería Informática Computabilidad y Algoritmia
 * Autor: Pablo Hernández Jiménez
 * Correo: alu0101495934@ull.edu.es
 * Fecha: 17/10/2022
 * Archivo main.cc: client program.
 * Referencias:
 */

#include <iostream>

#include "cya/code_analyzer.h"
#include "cya/command.h"
#include "cya/token_definitions.h"
#include "cya/utils.h"

void PrintMultiline(std::ostream& out, const std::vector<cya::Token>& tokens) {
  if (tokens.front().GetLine() == tokens.back().GetLine()) {
    out << "[Line " << tokens.front().GetLine() << "]" << std::endl;
  } else {
    out << "[Line " << tokens.front().GetLine() << "-" << tokens.back().GetLine() << "]" << std::endl;
  }
  for (const auto& token : tokens) {
    out << token << std::endl;
  }
}

void PrintMultilineBlocks(std::ostream& out, const std::vector<std::vector<cya::Token>>& blocks) {
  for (const auto& block : blocks) {
    PrintMultiline(out, block);
  }
}

std::vector<std::vector<cya::Token>> ParseMultiline(const std::vector<cya::Token>& tokens) {
  std::vector<std::vector<cya::Token>> blocks;
  if (tokens.empty()) return blocks;
  std::vector<cya::Token> contiguous_tokens;
  contiguous_tokens.push_back(tokens.front());
  for (int i = 1; i < tokens.size(); ++i) {
    const auto& kToken = tokens[i];
    if (contiguous_tokens.front().GetLine() + contiguous_tokens.size() != kToken.GetLine()) {
      blocks.emplace_back(contiguous_tokens);
      contiguous_tokens = std::vector<cya::Token>();
    }
    contiguous_tokens.push_back(kToken);
  }
  if (contiguous_tokens.empty()) return blocks;
  blocks.emplace_back(contiguous_tokens);
  return blocks;
}

int main(int argc, const char* argv[]) {
  cya::Command root_cmd = cya::Command("cya <input_file> <output_file>")
          .SetPositionalArgumentsRange(2, 2)
          .Parse(argc, argv);
  cya::CodeAnalyzer code_analyzer(cya::kTokenDefinitions);
  std::vector<std::string> lines = cya::ReadFileLines(root_cmd.GetPositionalArg(0));
  code_analyzer.Analyze(lines);
  std::ofstream output_file(root_cmd.GetPositionalArg(1));
  output_file << "PROGRAM: " << root_cmd.GetPositionalArg(0) << std::endl;
  auto blocks = ParseMultiline(code_analyzer.GetTokens("COMMENTS"));
  const bool kHasDescription = code_analyzer.HasTokens("COMMENTS") &&
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
      PrintMultiline(output_file, pair.second);
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
    output_file << "[Line " << description_block.front().GetLine() << "-" << description_block.back().GetLine() << "] ";
    output_file << "DESCRIPTION" << std::endl;
    blocks = std::vector<std::vector<cya::Token>>(blocks.begin() + 1, blocks.end());
  }
  PrintMultilineBlocks(output_file, blocks);
  return 0;
}
