/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingenierıa Informática
 * Asignatura: Computabilidad y Algoritmia
 * Curso: 2º
 * Práctica 4: Code Analyzer Curso 2022-2023
 * Grado en Ingeniería Informática Computabilidad y Algoritmia
 * Autor: Pablo Hernández Jiménez
 * Correo: alu0101495934@ull.edu.es
 * Fecha: 24/10/2022
 * Archivo token.h: cya::Token definition
 * Referencias:
 */

#ifndef CYA_TOKEN_H_
#define CYA_TOKEN_H_

#include <map>
#include <set>
#include <ostream>
#include <string>
#include <functional>

namespace cya {

/**
 * @brief Stores information about a token found within a text
 */
class Token {
 public:
  Token(const int line,
        const int position,
        const std::map<std::string, std::string>& values,
        const std::function<std::string(const Token&)>& to_string_func) :
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
