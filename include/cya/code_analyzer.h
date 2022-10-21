
#ifndef CYA_CODE_ANALYZER_H_
#define CYA_CODE_ANALYZER_H_

#include <string>
#include <vector>
#include <map>

#include "token_definition.h"
#include "token.h"

namespace cya {

class CodeAnalyzer {
 public:
  CodeAnalyzer(const std::vector<TokenDefinition>& definitions) : token_definitions_(definitions), tokens_() {}
  template<class... TType>
  CodeAnalyzer(TType... definition) : CodeAnalyzer(std::vector<TokenDefinition>{definition...}) {}

  inline std::vector<Token> GetTokens(const std::string& token_name) const { 
    if (!tokens_.count(token_name))
      return std::vector<Token>();
    return tokens_.at(token_name);
  }

  void Analyze(const std::vector<std::string>& lines);

 private:
  std::vector<TokenDefinition> token_definitions_;
  std::map<std::string, std::vector<Token>> tokens_;
};

}

#endif
