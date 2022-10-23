
#include <vector>
#include <iostream>

#include "cya/command.h"

namespace cya {

Command& Command::Parse(const int argc, const char *argv[]) {
  std::vector<std::string> arguments(argv + 1, argv + argc);
  return Parse(arguments);
}

Command& Command::Parse(const std::vector<std::string>& arguments) {
  for (const auto& argument : arguments) {
    std::cout << argument << " ";
  }
  std::cout << std::endl;
  return static_cast<Command&>(*this);
}

}
