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
 * Archivo token_definitions.h: Contains all the token definitions
 * Referencias:
 */

#ifndef CYA_TOKEN_DEFINITIONS_H_
#define CYA_TOKEN_DEFINITIONS_H_

#include "token_definition.h"
#include "token.h"
#include "utils.h"

namespace cya {

const TokenDefinition kCommentDefinition("COMMENTS", std::regex(R"((/\*\*( |.)*)|(^ *\*( |.)*)|(( |.)*\*/)|(//( |.)*))"),
  [](const std::smatch& match) {
    std::map<std::string, std::string> values;
    values.emplace("value", match[0]);
    return values;
  }, [](const Token& token) {
    std::stringstream result;
    result << token.GetValue("value");
    return result.str();
  }, true);

const TokenDefinition kStatementDefinition("STATEMENTS", std::regex(R"((while|for) \(.*\))"),
  [](const std::smatch& match) {
    std::map<std::string, std::string> values;
    values.emplace("type", match[1]);
    return values;
  }, [](const Token& token) {
    std::stringstream result;
    result << "[Line " << token.GetLine() << "] LOOP: " << token.GetValues().at("type");
    return result.str();
  }
);

const TokenDefinition kVariableDefinition("VARIABLES", std::regex(R"(^ *(int|double) +(\S*) *(= *(\S*))?;)"),
  [](const std::smatch& match) {
    std::map<std::string, std::string> values;
    values.emplace("type", match[1]);
    values.emplace("name", match[2]);
    if (match[3] != match[4]) {
      values.emplace("value", match[4]);
    }
    return values;
  }, [](const Token& token) {
    std::stringstream result;
    result << "[Line " << token.GetLine() << "] " << ToUpper(token.GetValues().at("type")) << ": ";
    result << token.GetValue("name");
    if (token.GetValues().count("value")) {
      result << " = " << token.GetValue("value");
    }
    return result.str();
  }
);

const TokenDefinition kIdentifierDefinition("IDENTIFIERS", std::regex(R"( *[<]?([^0-9 ">]+)[(;>])"),
  [](const std::smatch& match) {
    std::map<std::string, std::string> values;
    values.emplace("value", match[1]);
    return values;
  }, [](const Token& token) {
    std::stringstream result;
    result << "[Line " << token.GetLine() << "] " << token.GetValues().at("value");
    return result.str();
  }
);

const std::vector<TokenDefinition> kTokenDefinitions{
  kCommentDefinition,
  kStatementDefinition,
  kVariableDefinition,
  kIdentifierDefinition
};

}

#endif //CYA_TOKEN_DEFINITIONS_H_
