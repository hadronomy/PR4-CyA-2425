
#include <regex>
#include <map>
#include <iostream>

#include "cya/code_analyzer.h"

namespace cya {

void CodeAnalyzer::Analyze(const std::vector<std::string>& lines) {
  for (int i = 0; i < lines.size(); ++i) {
    const auto& line = lines[i];
    for (const auto& definition : token_definitions_) {
      std::smatch match;
      if (std::regex_search(line, match, definition.GetRegex())) {
        std::map<std::string, std::string> values = definition.GetSerializer()(match);
        Token token(i + 1, 0, values, definition.GetToString());
        AddToken(definition.GetName(), token);
      }
    }
  }
}

}
