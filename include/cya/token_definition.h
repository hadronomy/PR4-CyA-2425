
#ifndef CYA_TOKEN_DEFINITION_H_
#define CYA_TOKEN_DEFINITION_H_

#include <string>
#include <regex>
#include <functional>

namespace cya {

class Token;

class TokenDefinition {
 public:
  TokenDefinition(
          const std::string& name,
          const std::regex& regex,
          std::function<std::map<std::string, std::string>(const std::smatch&)> serializer,
          std::function<std::string(const Token&)> to_string,
          const bool is_multiple = false) :
          name_(name), regex_(regex), serializer_(serializer), to_string_func_(to_string), is_multiline_(is_multiple) { }

  inline std::string GetName() const { return name_; }
  inline std::regex GetRegex() const { return regex_; }
  inline std::function<std::map<std::string, std::string>(const std::smatch&)> GetSerializer() const { return serializer_; }
  inline std::function<std::string(const Token&)> GetToString() const { return to_string_func_; }

 private:
  std::string name_;
  std::regex regex_;
  std::function<std::map<std::string, std::string>(const std::smatch&)> serializer_;
  std::function<std::string(const Token&)> to_string_func_;
  bool is_multiline_;
};

}

#endif
