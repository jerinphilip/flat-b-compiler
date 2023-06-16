#include "printer.h"

#include "ast.h"
#include "visitor.h"

namespace visitor {

void PrettyPrinter::label(std::map<std::string, ast::Block *> m) {}

void PrettyPrinter::visit(ast::Node *node) {}

void PrettyPrinter::visit(ast::Program *program) {
  program->declarations->accept(this);
  program->block->accept(this);
}

void PrettyPrinter::visit(ast::Declarations *declarations) {
  std::cout << "declarations {" << std::endl;
  for (auto &typed_ids : *(declarations->typed_ids)) {
    typed_ids->accept(this);
  }
  std::cout << "}\n";
}

void PrettyPrinter::visit(ast::Block *code) {
  // std::cout << "Code" << std::endl;
}

void PrettyPrinter::visit(ast::Id *id) {
  // std::cout << "Code" << std::endl;
  std::cout << id->name;
}

void PrettyPrinter::visit(ast::IdArrayAccess *id_) {
  // std::cout << "Code" << std::endl;
  std::cout << id_->name << "[";
  id_->subscript->accept(this);
  std::cout << "]";
}

void PrettyPrinter::visit(ast::Expr *expr) {
  // std::cout << "Code" << std::endl;
}

void PrettyPrinter::visit(ast::Statement *statement) {
  // std::cout << "Code" << std::endl;
}

void PrettyPrinter::visit(ast::Assign *assign) {
  // std::cout << "Code" << std::endl;
}

void PrettyPrinter::visit(ast::While *while_) {
  // std::cout << "Code" << std::endl;
}

void PrettyPrinter::visit(ast::If *if_) {
  // std::cout << "Code" << std::endl;
}

void PrettyPrinter::visit(ast::For *for_) {
  // std::cout << "Code" << std::endl;
}

void PrettyPrinter::visit(ast::Print *print) {
  // std::cout << "Code" << std::endl;
}

void PrettyPrinter::visit(ast::TypedIds *typed_ids) {
  // std::cout << "Typed ids" << std::endl;
  std::string type;
  switch (typed_ids->type) {
    case FlatBType::Int:
      type = "int";
      break;
    case FlatBType::Bool:
      type = "bool";
      break;
    case FlatBType::Char:
      type = "char";
      break;
    default:
      break;
  }
  std::cout << type << " ";
  bool first = true;
  auto *id_defs = typed_ids->id_defs;
  reverse(id_defs->begin(), id_defs->end());
  for (auto &id_def : *id_defs) {
    if (not first) std::cout << ", ";
    first = false;
    id_def->accept(this);
  }
  std::cout << ";\n";
}

void PrettyPrinter::visit(ast::NoOp * /*no_op*/) {
  std::cout << "No-Op" << std::endl;
}

void PrettyPrinter::visit(ast::Goto * /*goto_*/) {
  std::cout << "Go-To" << std::endl;
}

void PrettyPrinter::visit(ast::Integer *integer) {
  std::cout << integer->value;
}

void PrettyPrinter::visit(ast::IdDef *id_def) {}

void PrettyPrinter::visit(ast::IdArrayDef *idA_def) {}

void PrettyPrinter::visit(ast::BinOp *binOp) {}

void PrettyPrinter::visit(ast::IdRef *id_ref) {}

void PrettyPrinter::visit(ast::IdArrayRef *idA_ref) {}
void PrettyPrinter::visit(ast::Literal *literal) {}
void PrettyPrinter::visit(ast::Read *read) {}
void PrettyPrinter::visit(ast::Labelled *labelled) {}
}  // namespace visitor
