#include "ast.h"
#include "dtype.h"
#include "visitor.h"

namespace visitor {
void PrettyPrinter::label(map<string, ast::Code *> m) {}

void PrettyPrinter::visit(ast::Node *node) {}

void PrettyPrinter::visit(ast::Program *program) {
  program->decl->accept(this);
  program->block->accept(this);
}

void PrettyPrinter::visit(ast::Declarations *declarations) {
  cout << "decl {" << endl;
  for (auto &p : *(declarations->ds)) {
    p->accept(this);
  }
  cout << "}\n";
}

void PrettyPrinter::visit(ast::Code *code) {
  // cout << "Code" << endl;
}

void PrettyPrinter::visit(ast::Id *id) {
  // cout << "Code" << endl;
  cout << id->name;
}

void PrettyPrinter::visit(ast::IdArrayAccess *id_) {
  // cout << "Code" << endl;
  cout << id_->name << "[";
  id_->subscript->accept(this);
  cout << "]";
}

void PrettyPrinter::visit(ast::Expr *expr) {
  // cout << "Code" << endl;
}

void PrettyPrinter::visit(ast::Statement *statement) {
  // cout << "Code" << endl;
}

void PrettyPrinter::visit(ast::Assign *assign) {
  // cout << "Code" << endl;
}

void PrettyPrinter::visit(ast::While *while_) {
  // cout << "Code" << endl;
}

void PrettyPrinter::visit(ast::If *if_) {
  // cout << "Code" << endl;
}

void PrettyPrinter::visit(ast::For *for_) {
  // cout << "Code" << endl;
}

void PrettyPrinter::visit(ast::Print *print) {
  // cout << "Code" << endl;
}

void PrettyPrinter::visit(ast::TypedIds *tIdWrapper) {
  // cout << "Typed ids" << endl;
  string dtype;
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
  cout << dtype << " ";
  bool first = true;
  auto *ps = tIdWrapper->t_ids;
  reverse(ps->begin(), ps->end());
  for (auto &p : *ps) {
    if (not first)
      cout << ", ";
    first = false;
    p->accept(this);
  }
  cout << ";\n";
}

void PrettyPrinter::visit(ast::NoOp *no_op) { cout << "No-Op" << endl; }

void PrettyPrinter::visit(ast::Goto *goto_) { cout << "Go-To" << endl; }

void PrettyPrinter::visit(ast::Integer *integer) { cout << integer->value; }

void PrettyPrinter::visit(ast::IdDef *id_def) {}

void PrettyPrinter::visit(ast::IdArrayDef *idA_def) {}

void PrettyPrinter::visit(ast::BinOp *binOp) {}

void PrettyPrinter::visit(ast::IdRef *id_ref) {}

void PrettyPrinter::visit(ast::IdArrayRef *idA_ref) {}
void PrettyPrinter::visit(ast::Literal *literal) {}
void PrettyPrinter::visit(ast::Read *read) {}
void PrettyPrinter::visit(ast::Labelled *labelled) {}
} // namespace visitor
