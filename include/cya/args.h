
#ifndef CYA_ARGS_H_
#define CYA_ARGS_H_

#include <map>
#include <string>

class Args {
 public:
  Args() { }
 private:
  std::map<std::string, bool> bool_args_;
  std::map<std::string, std::string> literal_args_;
  std::map<std::string, std::string> int_args_;
};

#endif // CYA_ARGS_H_
