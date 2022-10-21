
#ifndef CYA_TOKEN_H_
#define CYA_TOKEN_H_

#include <map>
#include <string>

class Token {
 public:
  Token(const int line, const int position, const std::map<std::string, std::string>& values) : 
    line_(line), position_(position), values_(values) {}
 private:
  int line_;
  int position_;
  std::map<std::string, std::string> values_;
};

#endif // !CYA_TOKEN_H_
