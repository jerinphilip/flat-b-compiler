#include "ast.h"
#include "dtype.h"
#include "visitor.h"

void visitor::pprinter::visit(ast::Node *node) {}

void visitor::pprinter::visit(ast::Program *program) {
  program->decl->accept(this);
  program->block->accept(this);
}

void visitor::pprinter::visit(ast::Declarations *declarations) {
  cout << "decl {" << endl;
  for (auto &p : *(declarations->ds)) {
    p->accept(this);
  }
  cout << "}\n";
}

void visitor::pprinter::visit(ast::Code *code) {
  // cout << "Code" << endl;
}

void visitor::pprinter::visit(ast::Id *id) {
  // cout << "Code" << endl;
  cout << id->name;
}

void visitor::pprinter::visit(ast::IdArrayAccess *id_) {
  // cout << "Code" << endl;
  cout << id_->name << "[";
  id_->subscript->accept(this);
  cout << "]";
}

void visitor::pprinter::visit(ast::Expr *expr) {
  // cout << "Code" << endl;
}

void visitor::pprinter::visit(ast::Statement *statement) {
  // cout << "Code" << endl;
}

void visitor::pprinter::visit(ast::Assign *assign) {
  // cout << "Code" << endl;
}

void visitor::pprinter::visit(ast::While *while_) {
  // cout << "Code" << endl;
}

void visitor::pprinter::visit(ast::If *if_) {
  // cout << "Code" << endl;
}

void visitor::pprinter::visit(ast::For *for_) {
  // cout << "Code" << endl;
}

void visitor::pprinter::visit(ast::Print *print) {
  // cout << "Code" << endl;
}

void visitor::pprinter::visit(ast::TypedIds *tIdWrapper) {
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

void visitor::pprinter::visit(ast::NoOp *no_op) { cout << "No-Op" << endl; }

void visitor::pprinter::visit(ast::Goto *goto_) { cout << "Go-To" << endl; }

void visitor::pprinter::visit(ast::Integer *integer) { cout << integer->value; }

void visitor::pprinter::visit(ast::IdDef *id_def) {}

void visitor::pprinter::visit(ast::IdArrayDef *idA_def) {}

void visitor::pprinter::visit(ast::BinOp *binOp) {}

void visitor::pprinter::visit(ast::IdRef *id_ref) {}

void visitor::pprinter::visit(ast::IdArrayRef *idA_ref) {}
void visitor::pprinter::visit(ast::Literal *literal) {}
void visitor::pprinter::visit(ast::Read *read) {}
void visitor::pprinter::visit(ast::Labelled *labelled) {}
