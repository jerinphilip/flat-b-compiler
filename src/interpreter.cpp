#include "interpreter.h"

#include "types.h"
#include "visitor.h"

namespace visitor {

void Interpreter::label(std::map<std::string, ast::Block *> m) {
  table_ = m;
  /*
  std::cerr << "labels: ";
  for(auto p: table_){
      std::cerr << p.first << " ";
  }
  std::cerr << std::endl;
  */
}

void Interpreter::visit(ast::Node *node) {}

void Interpreter::visit(ast::Program *program) {
  root_ = program;
  program->declarations->accept(this);
  program->block->accept(this);
}

void Interpreter::visit(ast::Declarations *declarations) {
  for (auto &typed_ids : *(declarations->typed_ids)) {
    typed_ids->accept(this);
  }
}

void Interpreter::visit(ast::Block *code) {
  for (auto &statement : *(code->statements)) {
    statement->accept(this);
  }
}

void Interpreter::visit(ast::Id *id) {
  FlatBValue value;
  bool declared = env_.find(id->name) != env_.end();
  if (not declared) std::cerr << "Undefined variable" << std::endl;

  /* TODO, Ascertain type from pointer type */
  value.type = FlatBType::Int;
  value.underlying.Int = env_[id->name].underlying.Int;
  stack_.push(value);
}

void Interpreter::visit(ast::IdArrayAccess *id_array_access) {
  FlatBValue value;
  value.type = FlatBType::Int;
  bool declared = env_.find(id_array_access->name) != env_.end();
  if (not declared) std::cerr << "Undefined variable" << std::endl;

  id_array_access->subscript->accept(this);

  FlatBValue sc = pop_stack();
  int sub = sc.underlying.Int;
  FlatBValue d = env_[id_array_access->name];
  value.underlying.Int = env_[id_array_access->name].underlying.IntArray[sub];
  /*
   */
  stack_.push(value);
}

void Interpreter::visit(ast::IdRef *id_ref) {
  FlatBValue value;
  value.type = FlatBType::Pointer;
  bool declared = env_.find(id_ref->name) != env_.end();
  if (not declared) std::cerr << "Undefined variable" << std::endl;

  value.underlying.Pointer = &(env_[id_ref->name].underlying.Int);
  stack_.push(value);
}

void Interpreter::visit(ast::IdArrayRef *id_array_ref) {
  FlatBValue value;
  value.type = FlatBType::Pointer;
  bool declared = env_.find(id_array_ref->name) != env_.end();
  if (not declared) std::cerr << "Undefined variable" << std::endl;

  id_array_ref->subscript->accept(this);
  FlatBValue sc = pop_stack();
  int sub = sc.underlying.Int;
  value.underlying.Pointer =
      &(env_[id_array_ref->name].underlying.IntArray[sub]);
  stack_.push(value);
}

void Interpreter::visit(ast::Expr *expr) {}

void Interpreter::visit(ast::Statement *statement) {}

void Interpreter::visit(ast::Assign *assign) {
  assign->ref->accept(this);
  FlatBValue ref = pop_stack();
  assign->tree->accept(this);
  FlatBValue value = pop_stack();
  *(ref.underlying.Pointer) = value.underlying.Int;
}

void Interpreter::visit(ast::While *while_block) {
  FlatBValue condition;
  while_block->condition->accept(this);
  condition = pop_stack();
  while (condition.underlying.Int) {
    while_block->block->accept(this);

    /* Step */
    while_block->condition->accept(this);
    condition = pop_stack();
  }
}

void Interpreter::visit(ast::If *if_) {
  FlatBValue condition;
  if_->condition->accept(this);
  condition = pop_stack();
  if (condition.underlying.Int) {
    if_->block->accept(this);
  } else {
    if (if_->otherwise != nullptr) {
      if_->otherwise->accept(this);
    }
  }
}

void Interpreter::visit(ast::For *for_block) {
  for_block->init->accept(this);

  auto *ivar = for_block->init->ref->id();
  auto *rhs = new ast::BinOp(Op::add, ivar, for_block->step);
  auto *step = new ast::Assign(for_block->init->ref, rhs);
  auto *check = new ast::BinOp(Op::le, ivar, for_block->end);

  FlatBValue condition;
  condition.type = FlatBType::Int;
  condition.underlying.Int = 1;
  do {
    check->accept(this);
    // evalStack.push(condition);
    condition = pop_stack();
    if (condition.underlying.Int) {
      for_block->body->accept(this); /* Evaluate body */
      step->accept(this);
    }
  } while (condition.underlying.Int != 0);
}

void Interpreter::visit(ast::Print *print) {
  bool first = true;
  auto ts = *print->args;
  reverse(ts.begin(), ts.end());
  for (auto &p : ts) {
    if (not first) {
      std::cout << " ";
    }
    first = false;
    p->accept(this);
    FlatBValue value = pop_stack();
    switch (value.type) {
      case FlatBType::Int:
        std::cout << value.underlying.Int;
        break;
      case FlatBType::CharArray:
        std::cout << value.underlying.CharArray;
        break;
      case FlatBType::Bool:
        std::cout << value.underlying.Bool;
        break;
      default:
        break;
    }
  }

  if (print->newline) {
    std::cout << "\n";
  }
}

void Interpreter::visit(ast::TypedIds *typed_ids) {
  current_type_ = typed_ids->type;
  auto *id_defs = typed_ids->id_defs;
  for (auto &id_def : *id_defs) {
    id_def->accept(this);
  }
}

void Interpreter::visit(ast::NoOp *no_op) {}

void Interpreter::visit(ast::Goto *goto_) {
  if (goto_->condition == nullptr) {
    ast::Block *code = table_[goto_->label];
    code->accept(this);
    exit(0);
  } else {
    FlatBValue value;
    goto_->condition->accept(this);
    value = pop_stack();
    if (value.underlying.Int) {
      ast::Block *code = table_[goto_->label];
      code->accept(this);
      exit(0);
    }
  }
}

void Interpreter::visit(ast::Integer *integer) {
  FlatBValue value;
  value.type = FlatBType::Int;
  value.underlying.Int = integer->value;
  stack_.push(value);
}

void Interpreter::visit(ast::BinOp *bin_op) {
  /* Evaluate and put on stack */
  bin_op->left->accept(this);
  FlatBValue left = pop_stack();
  bin_op->right->accept(this);
  FlatBValue right = pop_stack();

  /* TODO Generalize for types */

  if (left.type != right.type) {
  } else {
    switch (bin_op->op) {
      case Op::add:
        stack_.push(left + right);
        break;
      case Op::sub:
        stack_.push(left - right);
        break;
      case Op::mul:
        stack_.push(left * right);
        break;
      case Op::quot:
        stack_.push(left / right);
        break;
      case Op::lt:
        stack_.push(left < right);
        break;
      case Op::gt:
        stack_.push(left > right);
        break;
      case Op::le:
        stack_.push(left <= right);
        break;
      case Op::ge:
        stack_.push(left >= right);
        break;
      case Op::eq:
        stack_.push(left == right);
        break;
      default:
        break;
    }
  }
}

void Interpreter::visit(ast::IdDef *id_def) {
  FlatBValue value;
  value.type = current_type_;
  switch (value.type) {
    case FlatBType::Int:
      value.underlying.Int = 0;
      break;
    default:
      break;
  }

  std::string name = id_def->name;
  env_[name] = value;
}

void Interpreter::visit(ast::IdArrayDef *id_array_def) {
  std::string name = id_array_def->name;
  int size = id_array_def->size;
  FlatBValue value;
  value.type = current_type_;
  switch (value.type) {
    case FlatBType::Int:
      value.underlying.IntArray = new int[size];
      value.type = FlatBType::IntArray;
      break;
    default:
      break;
  }

  env_[name] = value;
}

void Interpreter::visit(ast::Literal *literal) {
  FlatBValue value;
  value.type = FlatBType::CharArray;
  value.underlying.CharArray = const_cast<char *>(literal->value.c_str());
  stack_.push(value);
}

void Interpreter::visit(ast::Read *read) {
  read->var->accept(this);
  FlatBValue ref = pop_stack();
  int value;
  std::cin >> value;
  *(ref.underlying.Pointer) = value;
}

void Interpreter::visit(ast::Labelled *labelled) {
  labelled->block->accept(this);
}
}  // namespace visitor
