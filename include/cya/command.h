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
 * Archivo command.h: Command definition
 * Referencias:
 */

#ifndef COMMAND_CLI_H_
#define COMMAND_CLI_H_

#include <map>
#include <string>
#include <memory>
#include <vector>

namespace cya {

class Command {
 public:
  explicit Command(
          const std::string& usage,
          const std::string& description = "",
          const std::string& short_desc = "",
          const std::string& long_desc = ""
  ) : usage_(usage),
      description_(description),
      short_(short_desc),
      long_(long_desc),
      min_positional_(0),
      max_positional_(0),
      positional_args_() { }

  inline std::string GetUsage() const { return usage_; }
  inline std::string GetDescription() const { return description_; }
  inline std::string GetShort() const { return short_; }
  inline std::string GetLong() const { return long_; }
  inline std::map<std::string, std::shared_ptr<Command>> GetSubcommands() const { return subcommands_; }
  inline std::vector<std::string> GetPositionalArgs() const { return positional_args_; }
  inline std::string GetPositionalArg(const int index) const { return positional_args_.at(index); }

  inline Command& AddSubcommand(const Command& subcommand) {
    if (!subcommands_.count(subcommand.GetUsage())) {
      subcommands_.emplace(subcommand.GetUsage(), std::make_shared<Command>(subcommand));
      return static_cast<Command&>(*this);
    }
    throw "Trying to add a subcommand with a name in use";
  }
  inline Command& SetPositionalArgumentsRange(const int min, const int max) {
    min_positional_ = min;
    max_positional_ = max;
    return static_cast<Command&>(*this);
  }

  Command& Parse(const int argc, const char *argv[]);
  Command& Parse(const std::vector<std::string>& arguments);

 private:
  std::string usage_;
  std::string description_;
  std::string short_;
  std::string long_;
  std::map<std::string, std::shared_ptr<Command>> subcommands_;
  int min_positional_;
  int max_positional_;
  std::vector<std::string> positional_args_;
};

}

#endif //COMMAND_CLI_H_
