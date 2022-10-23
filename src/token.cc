
#include "cya/token.h"

namespace cya {

std::ostream& operator<<(std::ostream& out, const Token& input_token) {
  out << input_token.to_string_func_(input_token);
  return out;
}

}
