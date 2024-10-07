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
 * Archivo token_definitions.h: Contains all the token definitions
 * Referencias:
 */

#pragma once

#include "token.h"
#include "token_definition.h"
#include "utils.h"

namespace cya {

const TokenDefinition kCommentDefinition(
    "COMMENTS",
    std::regex(R"((/\*\*( |.)*)|(^ *\*( |.)*)|(( |.)*\*/)|(//( |.)*))"),
    [](const std::smatch& match) {
      std::map<std::string, std::string> values;
      values.emplace("value", match[0]);
      return values;
    },
    [](const Token& token) {
      std::stringstream result;
      result << token.GetValue("value");
      return result.str();
    },
    true);

const TokenDefinition kStatementDefinition(
    "STATEMENTS", std::regex(R"((while|for) \(.*\))"),
    [](const std::smatch& match) {
      std::map<std::string, std::string> values;
      values.emplace("type", match[1]);
      return values;
    },
    [](const Token& token) {
      std::stringstream result;
      result << "[Line " << token.GetLine()
             << "] LOOP: " << token.GetValues().at("type");
      return result.str();
    });

const TokenDefinition kVariableDefinition(
    "VARIABLES", std::regex(R"(^ *(int|double) +(\S*) *(= *(\S*))?;)"),
    [](const std::smatch& match) {
      std::map<std::string, std::string> values;
      values.emplace("type", match[1]);
      values.emplace("name", match[2]);
      if (match[3] != match[4]) {
        values.emplace("value", match[4]);
      }
      return values;
    },
    [](const Token& token) {
      std::stringstream result;
      result << "[Line " << token.GetLine() << "] "
             << ToUpper(token.GetValues().at("type")) << ": ";
      result << token.GetValue("name");
      if (token.GetValues().count("value")) {
        result << " = " << token.GetValue("value");
      }
      return result.str();
    });

const TokenDefinition kMainIdentifierDefinition(
    "MAIN", std::regex(R"(int +main *\( *\))"),
    [](const std::smatch& match) {
      std::map<std::string, std::string> values;
      return values;
    },
    [](const Token& token) {
      std::stringstream result;
      result << "True";
      return result.str();
    });

const std::vector<TokenDefinition> kTokenDefinitions{
    kCommentDefinition, kStatementDefinition, kVariableDefinition,
    kMainIdentifierDefinition};

}  // namespace cya
