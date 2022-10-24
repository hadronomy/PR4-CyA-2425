
#ifndef CYA_TOKEN_DEFINITIONS_H_
#define CYA_TOKEN_DEFINITIONS_H_

#include "token_definition.h"
#include "token.h"
#include "utils.h"

namespace cya {

TokenDefinition kStatementDefinition("STATEMENTS", std::regex(R"((while|for) \(.*\))"),[](const std::smatch& match) {
  std::map<std::string, std::string> values;
  values.emplace("type", match[1]);
  return values;
}, [](const Token& token) {
  std::stringstream result;
  result << "[Line " << token.GetLine() << "] LOOP: " << token.GetValues().at("type");
  return result.str();
});

TokenDefinition kVariableDefinition("VARIABLES", std::regex(R"(^ *(int|double) +(\S*) *(= *(\S*))?;)"), [](const std::smatch& match) {
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
  result << token.GetValues().at("name");
  if (token.GetValues().count("value")) {
    result << " = " << token.GetValues().at("value");
  }
  return result.str();
});

const TokenDefinition kCommentDefinition("COMMENTS", std::regex(R"((/\*\*( |.)*)|(^ *\*( |.)*)|(( |.)*\*/)|(//( |.)*))"), [](const std::smatch& match) {
  std::map<std::string, std::string> values;
  values.emplace("value", match[0]);
  return values;
}, [](const Token& token) {
  std::stringstream result;
  result << token.GetValue("value");
  return result.str();
}, true);

const std::vector<TokenDefinition> kTokenDefinitions{
  kStatementDefinition,
  kVariableDefinition,
  kCommentDefinition
};

}

#endif //CYA_TOKEN_DEFINITIONS_H_
