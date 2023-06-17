#include "formatter.h"

#include "ast.h"
#include "visitor.h"

namespace visitor {

void Formatter::label(std::map<std::string, ast::Block *> m) {}

void Formatter::visit(ast::Node *node) {}

void Formatter::visit(ast::Program *program) {
  program->declarations->accept(this);
  program->block->accept(this);
}

void Formatter::visit(ast::Declarations *declarations) {
  std::cout << "declarations {" << std::endl;
  for (auto &typed_ids : *(declarations->typed_ids)) {
    typed_ids->accept(this);
  }
  std::cout << "}\n";
}

void Formatter::visit(ast::Block *code) {
  // std::cout << "Code" << std::endl;
}

void Formatter::visit(ast::Id *id) {
  // std::cout << "Code" << std::endl;
  std::cout << id->name;
}

void Formatter::visit(ast::IdArrayAccess *id_) {
  // std::cout << "Code" << std::endl;
  std::cout << id_->name << "[";
  id_->subscript->accept(this);
  std::cout << "]";
}

void Formatter::visit(ast::Expr *expr) {
  // std::cout << "Code" << std::endl;
}

void Formatter::visit(ast::Statement *statement) {
  // std::cout << "Code" << std::endl;
}

void Formatter::visit(ast::Assign *assign) {
  // std::cout << "Code" << std::endl;
}

void Formatter::visit(ast::While *while_) {
  // std::cout << "Code" << std::endl;
}

void Formatter::visit(ast::If *if_) {
  // std::cout << "Code" << std::endl;
}

void Formatter::visit(ast::For *for_) {
  // std::cout << "Code" << std::endl;
}

void Formatter::visit(ast::Print *print) {
  // std::cout << "Code" << std::endl;
}

void Formatter::visit(ast::TypedIds *typed_ids) {
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

void Formatter::visit(ast::NoOp * /*no_op*/) {
  std::cout << "No-Op" << std::endl;
}

void Formatter::visit(ast::Goto * /*goto_*/) {
  std::cout << "Go-To" << std::endl;
}

void Formatter::visit(ast::Integer *integer) {
  std::cout << integer->value;
}

void Formatter::visit(ast::IdDef *id_def) {}

void Formatter::visit(ast::IdArrayDef *idA_def) {}

void Formatter::visit(ast::BinOp *binOp) {}

void Formatter::visit(ast::IdRef *id_ref) {}

void Formatter::visit(ast::IdArrayRef *idA_ref) {}
void Formatter::visit(ast::Literal *literal) {}
void Formatter::visit(ast::Read *read) {}
void Formatter::visit(ast::Labelled *labelled) {}
}  // namespace visitor
