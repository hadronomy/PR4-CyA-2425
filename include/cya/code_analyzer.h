
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
  explicit CodeAnalyzer(const std::vector<TokenDefinition>& definitions) : token_definitions_(definitions), tokens_() {}
  template<class... TType>
  explicit CodeAnalyzer(TType... definition) : CodeAnalyzer(std::vector<TokenDefinition>{definition...}) {}

  inline std::vector<Token> GetTokens(const std::string& token_name) const { 
    if (!tokens_.count(token_name))
      return std::vector<Token>();
    return tokens_.at(token_name);
  }
  inline std::map<std::string, std::vector<Token>> GetAllTokens() const { return tokens_; }

  inline void AddToken(const std::string& token_name, const Token& token) {
    if (!tokens_.count(token_name)) {
      tokens_.emplace(token_name, std::vector<Token>());
    }
    tokens_.at(token_name).emplace_back(token);
  }

  void Analyze(const std::vector<std::string>& lines);

 private:
  std::vector<TokenDefinition> token_definitions_;
  std::map<std::string, std::vector<Token>> tokens_;
};

}

#endif
