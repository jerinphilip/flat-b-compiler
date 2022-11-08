#include "ast.h"
#include "dtype.h"
#include "visitor.h"

namespace visitor {
void pprinter::label(map<string, ast::Code *> m) {}

void pprinter::visit(ast::Node *node) {}

void pprinter::visit(ast::Program *program) {
  program->decl->accept(this);
  program->block->accept(this);
}

void pprinter::visit(ast::Declarations *declarations) {
  cout << "decl {" << endl;
  for (auto &p : *(declarations->ds)) {
    p->accept(this);
  }
  cout << "}\n";
}

void pprinter::visit(ast::Code *code) {
  // cout << "Code" << endl;
}

void pprinter::visit(ast::Id *id) {
  // cout << "Code" << endl;
  cout << id->name;
}

void pprinter::visit(ast::IdArrayAccess *id_) {
  // cout << "Code" << endl;
  cout << id_->name << "[";
  id_->subscript->accept(this);
  cout << "]";
}

void pprinter::visit(ast::Expr *expr) {
  // cout << "Code" << endl;
}

void pprinter::visit(ast::Statement *statement) {
  // cout << "Code" << endl;
}

void pprinter::visit(ast::Assign *assign) {
  // cout << "Code" << endl;
}

void pprinter::visit(ast::While *while_) {
  // cout << "Code" << endl;
}

void pprinter::visit(ast::If *if_) {
  // cout << "Code" << endl;
}

void pprinter::visit(ast::For *for_) {
  // cout << "Code" << endl;
}

void pprinter::visit(ast::Print *print) {
  // cout << "Code" << endl;
}

void pprinter::visit(ast::TypedIds *tIdWrapper) {
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

void pprinter::visit(ast::NoOp *no_op) { cout << "No-Op" << endl; }

void pprinter::visit(ast::Goto *goto_) { cout << "Go-To" << endl; }

void pprinter::visit(ast::Integer *integer) { cout << integer->value; }

void pprinter::visit(ast::IdDef *id_def) {}

void pprinter::visit(ast::IdArrayDef *idA_def) {}

void pprinter::visit(ast::BinOp *binOp) {}

void pprinter::visit(ast::IdRef *id_ref) {}

void pprinter::visit(ast::IdArrayRef *idA_ref) {}
void pprinter::visit(ast::Literal *literal) {}
void pprinter::visit(ast::Read *read) {}
void pprinter::visit(ast::Labelled *labelled) {}
} // namespace visitor
