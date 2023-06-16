#include "visitor.h"

#include "compiler.h"
#include "interpreter.h"
#include "printer.h"

namespace visitor {

std::unique_ptr<Visitor> make_visitor(std::string type) {
  if (type == "-i") {
    return std::make_unique<visitor::Interpreter>();
  }
  if (type == "-c") {
    return std::make_unique<visitor::Compiler>();
  }

  if (type == "-f") {
    return std::make_unique<visitor::PrettyPrinter>();
  }

  std::abort();
  return nullptr;
}
}  // namespace visitor
