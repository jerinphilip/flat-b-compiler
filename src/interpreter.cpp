#include "dtype.h"
#include "visitor.h"

void visitor::interpreter::visit(ast::node *node) {}

void visitor::interpreter::visit(ast::program *program) {
  root = program;
  program->decl->accept(this);
  program->block->accept(this);
}

void visitor::interpreter::visit(ast::declarations *declarations) {
  for (auto &p : *(declarations->ds)) {
    p->accept(this);
  }
}

void visitor::interpreter::visit(ast::code *code) {
  for (auto &p : *(code->statements)) {
    p->accept(this);
  }
}

void visitor::interpreter::visit(ast::id *id) {
  dataType dt;
  bool declared = env.find(id->name) != env.end();
  if (not declared)
    cerr << "Undefined variable" << endl;

  /* TODO, Ascertain dtype from pointer type */
  dt.dtype = type::Int;
  dt.T.i = env[id->name].T.i;
  evalStack.push(dt);
}

void visitor::interpreter::visit(ast::id_ *id_) {
  dataType dt;
  dt.dtype = type::Int;
  bool declared = env.find(id_->name) != env.end();
  if (not declared)
    cerr << "Undefined variable" << endl;

  id_->subscript->accept(this);

  dataType sc = evalStack.top();
  evalStack.pop();
  int sub = sc.T.i;
  dataType d = env[id_->name];
  dt.T.i = env[id_->name].T.A[sub];
  /*
   */
  evalStack.push(dt);
}

void visitor::interpreter::visit(ast::id_ref *id_ref) {
  dataType dt;
  dt.dtype = type::Pointer;
  bool declared = env.find(id_ref->name) != env.end();
  if (not declared)
    cerr << "Undefined variable" << endl;

  dt.T.p = &(env[id_ref->name].T.i);
  evalStack.push(dt);
}

void visitor::interpreter::visit(ast::idA_ref *idA_ref) {
  dataType dt;
  dt.dtype = type::Pointer;
  bool declared = env.find(idA_ref->name) != env.end();
  if (not declared)
    cerr << "Undefined variable" << endl;

  idA_ref->subscript->accept(this);
  dataType sc = evalStack.top();
  evalStack.pop();
  int sub = sc.T.i;
  dt.T.p = &(env[idA_ref->name].T.A[sub]);
  evalStack.push(dt);
}

void visitor::interpreter::visit(ast::expr *expr) {}

void visitor::interpreter::visit(ast::statement *statement) {}

void visitor::interpreter::visit(ast::assign *assign) {
  assign->ref->accept(this);
  dataType ref = evalStack.top();
  evalStack.pop();
  assign->tree->accept(this);
  dataType value = evalStack.top();
  evalStack.pop();
  *(ref.T.p) = value.T.i;
}

void visitor::interpreter::visit(ast::while_ *while_) {
  dataType cond;
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

void visitor::interpreter::visit(ast::if_ *if_) {
  dataType cond;
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

void visitor::interpreter::visit(ast::for_ *for_) {
  for_->init->accept(this);

  void *location;
  void **var = &location;
  for_->init->ref->vnode(var);
  ast::id *ivar = (ast::id *)location;

  ast::binOp *rhs = new ast::binOp(opr::add, ivar, for_->step);
  ast::assign *step = new ast::assign(for_->init->ref, rhs);
  ast::binOp *check = new ast::binOp(opr::le, ivar, for_->end);

  dataType cond;
  cond.dtype = type::Int;
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

void visitor::interpreter::visit(ast::print *print) {
  bool first = true;
  auto ts = *print->args;
  reverse(ts.begin(), ts.end());
  for (auto &p : ts) {
    if (not first) {
      cout << " ";
    }
    first = false;
    p->accept(this);
    dataType dt = evalStack.top();
    evalStack.pop();
    switch (dt.dtype) {
    case type::Int:
      cout << dt.T.i;
      break;
    case type::CharArray:
      cout << dt.T.s;
      break;
    case type::Bool:
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

void visitor::interpreter::visit(ast::typed_ids *twrap) {
  currentType = twrap->dtype;
  auto *ps = twrap->t_ids;
  for (auto &p : *ps) {
    p->accept(this);
  }
}

void visitor::interpreter::visit(ast::no_op *no_op) {}

void visitor::interpreter::visit(ast::goto_ *goto_) {
  if (goto_->cond == NULL) {
    ast::code *code = table[goto_->label];
    code->accept(this);
    exit(0);
  } else {
    dataType dt;
    goto_->cond->accept(this);
    dt = evalStack.top();
    evalStack.pop();
    if (dt.T.i) {
      ast::code *code = table[goto_->label];
      code->accept(this);
      exit(0);
    }
  }
}

void visitor::interpreter::visit(ast::integer *integer) {
  dataType dt;
  dt.dtype = type::Int;
  dt.T.i = integer->value;
  evalStack.push(dt);
}

void visitor::interpreter::visit(ast::binOp *binOp) {

  /* Evaluate and put on stack */
  binOp->left->accept(this);
  dataType left = evalStack.top();
  evalStack.pop();
  binOp->right->accept(this);
  dataType right = evalStack.top();
  evalStack.pop();

  /* TODO Generalize for types */

  if (left.dtype != right.dtype) {
  } else {
    switch (binOp->op) {
    case opr::add:
      evalStack.push(left + right);
      break;
    case opr::sub:
      evalStack.push(left - right);
      break;
    case opr::mul:
      evalStack.push(left * right);
      break;
    case opr::quot:
      evalStack.push(left / right);
      break;
    case opr::lt:
      evalStack.push(left < right);
      break;
    case opr::gt:
      evalStack.push(left > right);
      break;
    case opr::le:
      evalStack.push(left <= right);
      break;
    case opr::ge:
      evalStack.push(left >= right);
      break;
    case opr::eq:
      evalStack.push(left == right);
      break;
    default:
      break;
    }
  }
}

void visitor::interpreter::visit(ast::id_def *id_def) {
  dataType dt;
  dt.dtype = currentType;
  switch (dt.dtype) {
  case type::Int:
    dt.T.i = 0;
    break;
  default:
    break;
  }

  string name = id_def->name;
  env[name] = dt;
}

void visitor::interpreter::visit(ast::idA_def *idA_def) {
  string name = idA_def->name;
  int size = idA_def->size;
  dataType dt;
  dt.dtype = currentType;
  switch (dt.dtype) {
  case type::Int:
    dt.T.A = new int[size];
    dt.dtype = IntArray;
    break;
  default:
    break;
  }

  env[name] = dt;
}

void visitor::interpreter::visit(ast::literal *literal) {
  dataType dt;
  dt.dtype = type::CharArray;
  dt.T.s = (char *)literal->value.c_str();
  evalStack.push(dt);
}

void visitor::interpreter::visit(ast::read *read) {
  read->var->accept(this);
  dataType ref = evalStack.top();
  evalStack.pop();
  int value;
  cin >> value;
  *(ref.T.p) = value;
}

void visitor::interpreter::visit(ast::labelled *labelled) {
  labelled->block->accept(this);
}
