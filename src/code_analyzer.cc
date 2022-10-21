
#include <regex>
#include <map>
#include <iostream>

#include "cya/code_analyzer.h"

namespace cya {

void CodeAnalyzer::Analyze(const std::vector<std::string>& lines) {
  for (int i = 0; i < lines.size(); ++i) {
    const auto line = lines[i];
    for (const auto& definition : token_definitions_) {
      if (std::regex_match(line, definition.GetRegex())) {
        std::map<std::string, std::string> values;
        values.emplace("line", line);
        Token token(i, 0, values);
        if (!tokens_.count(definition.GetName())) {
          tokens_.emplace(definition.GetName(), std::vector<Token>());
        }
        tokens_.at(definition.GetName()).emplace_back(token);
      }
    }
  }
}

}
