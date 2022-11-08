#include "dtype.h"
#include "visitor.h"

namespace visitor {

void interpreter::label(map<string, ast::Code *> m) {
  table = m;
  /*
  cerr << "labels: ";
  for(auto p: table){
      cerr << p.first << " ";
  }
  cerr << endl;
  */
}

void interpreter::visit(ast::Node *node) {}

void interpreter::visit(ast::Program *program) {
  root = program;
  program->decl->accept(this);
  program->block->accept(this);
}

void interpreter::visit(ast::Declarations *declarations) {
  for (auto &p : *(declarations->ds)) {
    p->accept(this);
  }
}

void interpreter::visit(ast::Code *code) {
  for (auto &p : *(code->statements)) {
    p->accept(this);
  }
}

void interpreter::visit(ast::Id *id) {
  DataType dt;
  bool declared = env.find(id->name) != env.end();
  if (not declared)
    cerr << "Undefined variable" << endl;

  /* TODO, Ascertain dtype from pointer type */
  dt.dtype = FlatBType::Int;
  dt.T.i = env[id->name].T.i;
  evalStack.push(dt);
}

void interpreter::visit(ast::IdArrayAccess *id_) {
  DataType dt;
  dt.dtype = FlatBType::Int;
  bool declared = env.find(id_->name) != env.end();
  if (not declared)
    cerr << "Undefined variable" << endl;

  id_->subscript->accept(this);

  DataType sc = evalStack.top();
  evalStack.pop();
  int sub = sc.T.i;
  DataType d = env[id_->name];
  dt.T.i = env[id_->name].T.A[sub];
  /*
   */
  evalStack.push(dt);
}

void interpreter::visit(ast::IdRef *id_ref) {
  DataType dt;
  dt.dtype = FlatBType::Pointer;
  bool declared = env.find(id_ref->name) != env.end();
  if (not declared)
    cerr << "Undefined variable" << endl;

  dt.T.p = &(env[id_ref->name].T.i);
  evalStack.push(dt);
}

void interpreter::visit(ast::IdArrayRef *idA_ref) {
  DataType dt;
  dt.dtype = FlatBType::Pointer;
  bool declared = env.find(idA_ref->name) != env.end();
  if (not declared)
    cerr << "Undefined variable" << endl;

  idA_ref->subscript->accept(this);
  DataType sc = evalStack.top();
  evalStack.pop();
  int sub = sc.T.i;
  dt.T.p = &(env[idA_ref->name].T.A[sub]);
  evalStack.push(dt);
}

void interpreter::visit(ast::Expr *expr) {}

void interpreter::visit(ast::Statement *statement) {}

void interpreter::visit(ast::Assign *assign) {
  assign->ref->accept(this);
  DataType ref = evalStack.top();
  evalStack.pop();
  assign->tree->accept(this);
  DataType value = evalStack.top();
  evalStack.pop();
  *(ref.T.p) = value.T.i;
}

void interpreter::visit(ast::While *while_) {
  DataType cond;
  while_->cond->accept(this);
  cond = evalStack.top();
  evalStack.pop();
  while (cond.T.i) {
    while_->block->accept(this);

    /* Step */
    while_->cond->accept(this);
    cond = evalStack.top();
    evalStack.pop();
  }
}

void interpreter::visit(ast::If *if_) {
  DataType cond;
  if_->cond->accept(this);
  cond = evalStack.top();
  evalStack.pop();
  if (cond.T.i) {
    if_->block->accept(this);
  } else {
    if (if_->otherwise != NULL) {
      if_->otherwise->accept(this);
    }
  }
}

void interpreter::visit(ast::For *for_) {
  for_->init->accept(this);

  void *location;
  void **var = &location;
  for_->init->ref->vnode(var);
  ast::Id *ivar = (ast::Id *)location;

  ast::BinOp *rhs = new ast::BinOp(Op::add, ivar, for_->step);
  ast::Assign *step = new ast::Assign(for_->init->ref, rhs);
  ast::BinOp *check = new ast::BinOp(Op::le, ivar, for_->end);

  DataType cond;
  cond.dtype = FlatBType::Int;
  cond.T.i = 1;
  do {
    check->accept(this);
    // evalStack.push(cond);
    cond = evalStack.top();
    evalStack.pop();
    if (cond.T.i) {
      for_->block->accept(this); /* Evaluate body */
      step->accept(this);
    }
  } while (cond.T.i);
}

void interpreter::visit(ast::Print *print) {
  bool first = true;
  auto ts = *print->args;
  reverse(ts.begin(), ts.end());
  for (auto &p : ts) {
    if (not first) {
      cout << " ";
    }
    first = false;
    p->accept(this);
    DataType dt = evalStack.top();
    evalStack.pop();
    switch (dt.dtype) {
    case FlatBType::Int:
      cout << dt.T.i;
      break;
    case FlatBType::CharArray:
      cout << dt.T.s;
      break;
    case FlatBType::Bool:
      cout << dt.T.b;
      break;
    default:
      break;
    }
  }

  if (print->newline) {
    cout << "\n";
  }
}

void interpreter::visit(ast::TypedIds *twrap) {
  currentType = twrap->dtype;
  auto *ps = twrap->t_ids;
  for (auto &p : *ps) {
    p->accept(this);
  }
}

void interpreter::visit(ast::NoOp *no_op) {}

void interpreter::visit(ast::Goto *goto_) {
  if (goto_->cond == NULL) {
    ast::Code *code = table[goto_->label];
    code->accept(this);
    exit(0);
  } else {
    DataType dt;
    goto_->cond->accept(this);
    dt = evalStack.top();
    evalStack.pop();
    if (dt.T.i) {
      ast::Code *code = table[goto_->label];
      code->accept(this);
      exit(0);
    }
  }
}

void interpreter::visit(ast::Integer *integer) {
  DataType dt;
  dt.dtype = FlatBType::Int;
  dt.T.i = integer->value;
  evalStack.push(dt);
}

void interpreter::visit(ast::BinOp *binOp) {

  /* Evaluate and put on stack */
  binOp->left->accept(this);
  DataType left = evalStack.top();
  evalStack.pop();
  binOp->right->accept(this);
  DataType right = evalStack.top();
  evalStack.pop();

  /* TODO Generalize for types */

  if (left.dtype != right.dtype) {
  } else {
    switch (binOp->op) {
    case Op::add:
      evalStack.push(left + right);
      break;
    case Op::sub:
      evalStack.push(left - right);
      break;
    case Op::mul:
      evalStack.push(left * right);
      break;
    case Op::quot:
      evalStack.push(left / right);
      break;
    case Op::lt:
      evalStack.push(left < right);
      break;
    case Op::gt:
      evalStack.push(left > right);
      break;
    case Op::le:
      evalStack.push(left <= right);
      break;
    case Op::ge:
      evalStack.push(left >= right);
      break;
    case Op::eq:
      evalStack.push(left == right);
      break;
    default:
      break;
    }
  }
}

void interpreter::visit(ast::IdDef *id_def) {
  DataType dt;
  dt.dtype = currentType;
  switch (dt.dtype) {
  case FlatBType::Int:
    dt.T.i = 0;
    break;
  default:
    break;
  }

  string name = id_def->name;
  env[name] = dt;
}

void interpreter::visit(ast::IdArrayDef *idA_def) {
  string name = idA_def->name;
  int size = idA_def->size;
  DataType dt;
  dt.dtype = currentType;
  switch (dt.dtype) {
  case FlatBType::Int:
    dt.T.A = new int[size];
    dt.dtype = IntArray;
    break;
  default:
    break;
  }

  env[name] = dt;
}

void interpreter::visit(ast::Literal *literal) {
  DataType dt;
  dt.dtype = FlatBType::CharArray;
  dt.T.s = (char *)literal->value.c_str();
  evalStack.push(dt);
}

void interpreter::visit(ast::Read *read) {
  read->var->accept(this);
  DataType ref = evalStack.top();
  evalStack.pop();
  int value;
  cin >> value;
  *(ref.T.p) = value;
}

void interpreter::visit(ast::Labelled *labelled) {
  labelled->block->accept(this);
}
} // namespace visitor
