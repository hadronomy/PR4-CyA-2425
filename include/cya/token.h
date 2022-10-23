
#ifndef CYA_TOKEN_H_
#define CYA_TOKEN_H_

#include <map>
#include <ostream>
#include <string>
#include <functional>

namespace cya {

class Token {
 public:
  Token(const int line,
        const int position,
        const std::map<std::string, std::string>& values,
        std::function<std::string(const Token&)> to_string_func) :
    line_(line), position_(position), values_(values), to_string_func_(to_string_func) { }

    inline int GetLine() const { return line_; }
    inline int GetPosition() const { return position_; }
    inline std::string GetValue(const std::string& value_name) const { return values_.at(value_name); }
    inline std::map<std::string, std::string> GetValues() const { return values_; }
    inline std::function<std::string(const Token&)> GetToString() const { return to_string_func_; }

    inline std::string ToString() const { return to_string_func_(*this); }

    friend std::ostream& operator <<(std::ostream& out, const Token& input_token);
 private:
  int line_;
  int position_;
  std::map<std::string, std::string> values_;
  std::function<std::string(const Token&)> to_string_func_;
};

}

#endif // !CYA_TOKEN_H_
