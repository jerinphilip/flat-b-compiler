#include "ast.h"
#include "dtype.h"
#include "visitor.h"

namespace visitor {
void PrettyPrinter::label(std::map<std::string, ast::Code *> m) {}

void PrettyPrinter::visit(ast::Node *node) {}

void PrettyPrinter::visit(ast::Program *program) {
  program->decl->accept(this);
  program->block->accept(this);
}

void PrettyPrinter::visit(ast::Declarations *declarations) {
  std::cout << "decl {" << std::endl;
  for (auto &p : *(declarations->ds)) {
    p->accept(this);
  }
  std::cout << "}\n";
}

void PrettyPrinter::visit(ast::Code *code) {
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

void PrettyPrinter::visit(ast::TypedIds *tIdWrapper) {
  // std::cout << "Typed ids" << std::endl;
  std::string dtype;
  switch (tIdWrapper->dtype) {
  case FlatBType::Int:
    dtype = "int";
    break;
  case FlatBType::Bool:
    dtype = "bool";
    break;
  case FlatBType::Char:
    dtype = "char";
    break;
  default:
    break;
  }
  std::cout << dtype << " ";
  bool first = true;
  auto *ps = tIdWrapper->t_ids;
  reverse(ps->begin(), ps->end());
  for (auto &p : *ps) {
    if (not first)
      std::cout << ", ";
    first = false;
    p->accept(this);
  }
  std::cout << ";\n";
}

void PrettyPrinter::visit(ast::NoOp *no_op) {
  std::cout << "No-Op" << std::endl;
}

void PrettyPrinter::visit(ast::Goto *goto_) {
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
} // namespace visitor
