
#ifndef CYA_TOKEN_DEFINITION_H_
#define CYA_TOKEN_DEFINITION_H_

#include <string>
#include <regex>
#include <functional>

class TokenDefinition {
 public:
  TokenDefinition(
    const std::string& name, 
    const std::regex& regex, 
    std::function<void(std::map<std::string, std::string>&)> serializer) : 
    name_(name), regex_(regex), serializer_() { }

  std::string GetName() const { return name_; }
  std::regex GetRegex() const { return regex_; }
  std::function<void(std::map<std::string, std::string>&)> GetSerializer() const { return serializer_; }

 private:
  std::string name_;
  std::regex regex_;
  std::function<void(std::map<std::string, std::string>&)> serializer_;
};

#endif
