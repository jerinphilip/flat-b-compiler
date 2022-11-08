#include "dtype.h"
#include "visitor.h"

namespace visitor {

Compiler::Compiler() {
  module = new Module("main", context);
  module->setTargetTriple("x86_64-pc-linux-gnu");
  main_fn = Function::Create(FunctionType::get(Type::getVoidTy(context), false),
                             GlobalValue::ExternalLinkage, "main", module);
  printf = Function::Create(FunctionType::get(Type::getInt64Ty(context), true),
                            GlobalValue::ExternalLinkage, "printf", module);
  scanf = Function::Create(FunctionType::get(Type::getInt64Ty(context), true),
                           GlobalValue::ExternalLinkage, "scanf", module);
}

Value *Compiler::string_to_Value(std::string s) {
  GlobalVariable *var = new GlobalVariable(
      *module, ArrayType::get(IntegerType::get(context, 8), (s.size() + 1)),
      true, GlobalVariable::InternalLinkage, NULL, "literal");

  var->setInitializer(ConstantDataArray::getString(context, s, true));
  return var;
}

Value *Compiler::int_to_Value(int x) {
  GlobalVariable *var =
      new GlobalVariable(*module, Type::getInt64Ty(context), false,
                         GlobalValue::CommonLinkage, NULL, "integer");
  var->setInitializer(ConstantInt::get(context, APInt(64, x, true)));
  return var;
}

bool Compiler::declared_before(const std::string &s) {
  return v_table.find(s) != v_table.end();
}

void Compiler::label(std::map<std::string, ast::Code *> m) { table = m; }

void Compiler::visit(ast::Node *node) {}

void Compiler::visit(ast::Program *program) {
  main_block = BasicBlock::Create(context, "main_fn", main_fn);
  entry.push(main_block);

  program->decl->accept(this);
  program->block->accept(this);

  // TODO: New
  ReturnInst::Create(context, entry.top());
  entry.pop();
  module->print(outs(), nullptr);
}

void Compiler::visit(ast::Declarations *declarations) {
  for (auto &p : *(declarations->ds)) {
    p->accept(this);
  }
}

void Compiler::visit(ast::Code *code) {
  for (auto &p : *(code->statements)) {
    p->accept(this);
  }
}

void Compiler::visit(ast::Id *id) {
  if (not declared_before(id->name)) {
    std::cerr << "Undefined variable " << id->name << std::endl;
    // exit(-1);
  }
  Value *location = v_table[id->name];
  // Value *r = new LoadInst(location, "vr", entry.top());
  Value *r = nullptr;
  eval.push((void *)r);
  format.place("%d", r);
}

void Compiler::visit(ast::IdArrayAccess *id_) {
  if (not declared_before(id_->name)) {
    std::cerr << "Undefined variable " << id_->name << std::endl;
    // exit(-1);
  }

  id_->subscript->accept(this);
  auto start = ConstantInt::get(context, APInt(64, StringRef("0"), 10));
  auto offset = (Value *)eval.top();
  eval.pop();

  std::vector<Value *> index_params = {start, offset};
  // Value *location = GetElementPtrInst::CreateInBounds(
  //     v_table[id_->name], index_params, "vr", entry.top());
  // Value *r = new LoadInst(location, "vr", entry.top());
  Value *location = nullptr;
  Value *r = nullptr;
  eval.push((void *)r);
  format.place("%d", r);
}

void Compiler::visit(ast::IdRef *id_ref) {
  if (not declared_before(id_ref->name)) {
    std::cerr << "Undefined variable " << id_ref->name << std::endl;
    // exit(-1);
  }

  Value *ret_val = (Value *)eval.top();
  eval.pop();
  StoreInst *r =
      new StoreInst(ret_val, v_table[id_ref->name], false, entry.top());
  eval.push((void *)r);
}

void Compiler::visit(ast::IdArrayRef *idA_ref) {
  if (not declared_before(idA_ref->name)) {
    std::cerr << "Undefined variable " << idA_ref->name << std::endl;
    // exit(-1);
  }

  Value *ret_val = (Value *)eval.top();
  eval.pop();

  idA_ref->subscript->accept(this);
  auto start = ConstantInt::get(context, APInt(64, StringRef("0"), 10));
  auto offset = (Value *)eval.top();
  eval.pop();
  std::vector<Value *> index_params = {start, offset};
  // Value *location = GetElementPtrInst::CreateInBounds(
  //     v_table[idA_ref->name], index_params, "vr", entry.top());
  Value *location = nullptr;

  Value *instruction = new StoreInst(ret_val, location, false, entry.top());
  eval.push((void *)instruction);
}

void Compiler::visit(ast::Expr *expr) {}

void Compiler::visit(ast::Statement *statement) {}

void Compiler::visit(ast::Assign *assign) {
  assign->tree->accept(this);
  assign->ref->accept(this);
}

void Compiler::visit(ast::While *while_) {
  BasicBlock *parent, *pre, *body, *post;
  parent = entry.top();

  pre = body = post = NULL;

  pre = BasicBlock::Create(context, "pre", parent->getParent(), 0);
  body = BasicBlock::Create(context, "body", parent->getParent(), 0);
  post = BasicBlock::Create(context, "post", parent->getParent(), 0);

  entry.push(pre);
  while_->cond->accept(this);
  ZExtInst *condition = (ZExtInst *)eval.top();
  eval.pop();
  // Value *comparison = condition;
  ConstantInt *zero = ConstantInt::get(Type::getInt64Ty(context), 0, true);
  ICmpInst *comparison =
      new ICmpInst(*pre, ICmpInst::ICMP_NE, condition, zero, "vr");
  entry.pop();

  BranchInst::Create(body, post, comparison, pre);
  BranchInst::Create(pre, parent);

  entry.push(body);
  while_->block->accept(this);
  body = entry.top();
  entry.pop();

  if (not body->getTerminator()) {
    BranchInst::Create(pre, body);
  }

  entry.push(post);
}

void Compiler::visit(ast::If *if_) {
  BasicBlock *if_block, *merge_block, *else_block;
  if_block = merge_block = else_block = NULL;

  BasicBlock *ret_block = NULL;
  BasicBlock *parent = entry.top();
  assert(parent != NULL);

  if_->cond->accept(this);
  ZExtInst *condition = (ZExtInst *)eval.top();
  eval.pop();
  // Value *comparison = condition;
  ConstantInt *zero = ConstantInt::get(Type::getInt64Ty(context), 0, true);
  ICmpInst *comparison =
      new ICmpInst(*parent, ICmpInst::ICMP_NE, condition, zero, "vr");

  if_block = BasicBlock::Create(context, "if_block", parent->getParent());
  merge_block = BasicBlock::Create(context, "merge_block", parent->getParent());

  entry.push(if_block);
  if_->block->accept(this);
  ret_block = entry.top();
  entry.pop();

  if (not ret_block->getTerminator()) {
    BranchInst::Create(merge_block, ret_block);
  }

  if (if_->otherwise != NULL) {

    else_block = BasicBlock::Create(context, "else_block", parent->getParent());
    entry.push(else_block);
    if_->otherwise->accept(this);
    ret_block = entry.top();
    entry.pop();

    if (not ret_block->getTerminator()) {
      // cerr << "terminator Happening! " << endl;
      BranchInst::Create(merge_block, ret_block);
    }
    // BranchInst::Create(if_block, else_block, condition, parent);
    BranchInst::Create(if_block, else_block, comparison, parent);
  } else {
    // BranchInst::Create(if_block, merge_block, condition, parent);
    BranchInst::Create(if_block, merge_block, comparison, parent);
  }

  entry.push(merge_block);
}

void Compiler::visit(ast::For *for_) {
  BasicBlock *parent = entry.top();
  BasicBlock *pre, *body, *post;

  pre = body = post = NULL;

  pre = BasicBlock::Create(context, "for_pre", parent->getParent(), 0);
  body = BasicBlock::Create(context, "for_body", parent->getParent(), 0);
  post = BasicBlock::Create(context, "for_post", parent->getParent(), 0);

  /* Initialize before entering loop, hopefully in parent */
  for_->init->accept(this);
  void *location;
  void **var = &location;
  for_->init->ref->vnode(var);
  ast::Id *ivar = (ast::Id *)location;

  ast::BinOp *rhs = new ast::BinOp(Op::add, ivar, for_->step);
  ast::Assign *step = new ast::Assign(for_->init->ref, rhs);
  ast::BinOp *check = new ast::BinOp(Op::le, ivar, for_->end);

  entry.push(pre);
  check->accept(this);
  ZExtInst *condition = (ZExtInst *)eval.top();
  eval.pop();
  // Value *comparison = condition;
  ConstantInt *zero = ConstantInt::get(Type::getInt64Ty(context), 0, true);
  ICmpInst *comparison =
      new ICmpInst(*pre, ICmpInst::ICMP_NE, condition, zero, "vr");
  BranchInst::Create(body, post, comparison, pre);
  BranchInst::Create(pre, parent);
  entry.pop();

  entry.push(body);

  for_->block->accept(this);
  step->accept(this);

  body = entry.top();
  entry.pop();

  if (not body->getTerminator()) {
    BranchInst::Create(pre, body);
  }

  entry.push(post);
}

void Compiler::visit(ast::Print *print) {
  /* Reset */
  format.init();

  bool first = true;
  auto ts = *print->args;
  reverse(ts.begin(), ts.end());
  for (auto &p : ts) {
    if (not first) {
      format.str += " ";
    }
    first = false;
    p->accept(this);
    Value *r = (Value *)eval.top();
    eval.pop();
    format.update();
  }

  if (print->newline) {
    format.str += "\n";
  }

  std::vector<Value *> new_args;
  Value *fvar = string_to_Value(format.str);
  new_args.push_back(fvar);
  new_args.insert(new_args.end(), format.args.begin(), format.args.end());
  CallInst::Create(printf, makeArrayRef(new_args), std::string("printf"),
                   entry.top());

  format.finish();
}

void Compiler::visit(ast::TypedIds *twrap) {
  currentType = twrap->dtype;
  auto *ps = twrap->t_ids;
  for (auto &p : *ps) {
    p->accept(this);
  }
}

void Compiler::visit(ast::NoOp *no_op) {}

void Compiler::visit(ast::Goto *goto_) {
  if (l_table.find(goto_->label) != l_table.end()) {
    BasicBlock *parent, *follow, *non_follow;
    parent = entry.top();
    follow = l_table[goto_->label];
    if (goto_->cond) {
      goto_->cond->accept(this);
      ZExtInst *condition = (ZExtInst *)eval.top();
      eval.pop();
      // Value *comparison = condition;
      ConstantInt *zero = ConstantInt::get(Type::getInt64Ty(context), 0, true);
      ICmpInst *comparison =
          new ICmpInst(*parent, ICmpInst::ICMP_NE, condition, zero, "vr");

      non_follow =
          BasicBlock::Create(context, "post-target", parent->getParent(), 0);
      BranchInst::Create(follow, non_follow, comparison, parent);
      entry.push(non_follow);

    } else {
      BranchInst::Create(follow, parent);
    }
  }
  /*
     if(goto_->cond == NULL){
     ast::code *code = table[goto_->label];
     code->accept(this);
     exit(0);
     }
     else{
     dataType dt;
     goto_->cond->accept(this);
     dt = evalStack.top(); evalStack.pop();
     if (dt.T.i){
     ast::code *code = table[goto_->label];
     code->accept(this);
     exit(0);
     }
     }
     */
}

void Compiler::visit(ast::Integer *integer) {
  Constant *r = ConstantInt::get(Type::getInt64Ty(context), integer->value);
  eval.push((void *)r);
  format.place("%d", r);
}

void Compiler::visit(ast::BinOp *binOp) {

  binOp->left->accept(this);
  Value *left = (Value *)eval.top();
  eval.pop();
  binOp->right->accept(this);
  Value *right = (Value *)eval.top();
  eval.pop();

  auto parent = entry.top();
  auto binary_operator = [&left, &right, &parent,
                          this](Instruction::BinaryOps Op) {
    auto *b = BinaryOperator::Create(Op, left, right, "vr", parent);
    eval.push((void *)b);
  };

  auto cmp_operator = [&left, &right, &parent, this](CmpInst::Predicate pred) {
    auto *z = new ZExtInst(
        CmpInst::Create(Instruction::ICmp, pred, left, right, "vr", parent),
        Type::getInt64Ty(context), "zext", parent);
    eval.push((void *)z);
  };

  switch (binOp->op) {
  case Op::add:
    binary_operator(Instruction::Add);
    break;
  case Op::sub:
    binary_operator(Instruction::Sub);
    break;
  case Op::mul:
    binary_operator(Instruction::Mul);
    break;
  case Op::quot:
    binary_operator(Instruction::SDiv);
    break;
  case Op::lt:
    cmp_operator(ICmpInst::ICMP_SLT);
    break;
  case Op::gt:
    cmp_operator(ICmpInst::ICMP_SGT);
    break;
  case Op::le:
    cmp_operator(ICmpInst::ICMP_SLE);
    break;
  case Op::ge:
    cmp_operator(ICmpInst::ICMP_SGE);
    break;
  case Op::eq:
    cmp_operator(ICmpInst::ICMP_EQ);
    break;
  default:
    break;
  }
}

void Compiler::visit(ast::IdDef *id_def) {

  if (declared_before(id_def->name)) {
    std::cerr << "Redeclaration of variable " << id_def->name << std::endl;
    // exit(-1);
  } else {

    GlobalVariable *var =
        new GlobalVariable(*module, Type::getInt64Ty(context), false,
                           GlobalValue::CommonLinkage, NULL, id_def->name);
    var->setInitializer(
        ConstantInt::get(context, APInt(64, StringRef("0"), 10)));

    v_table[id_def->name] = var;
    // cerr << "Declaration of variable " << id_def->name << endl;
  }
}

void Compiler::visit(ast::IdArrayDef *idA_def) {
  if (declared_before(idA_def->name)) {
    std::cerr << "Redeclaration of variable " << idA_def->name << std::endl;
    // exit(-1);
  } else {
    GlobalVariable *var = new GlobalVariable(
        *module, ArrayType::get(Type::getInt64Ty(context), idA_def->size),
        false, GlobalValue::CommonLinkage, NULL, idA_def->name);
    var->setInitializer(ConstantAggregateZero::get(
        ArrayType::get(Type::getInt64Ty(context), idA_def->size)));

    v_table[idA_def->name] = var;
    // cerr << "Declaration of variable " << idA_def->name << endl;
  }
}

void Compiler::visit(ast::Literal *literal) {
  auto var = string_to_Value(literal->value);
  eval.push(var);
  format.place("%s", var);
}

void Compiler::visit(ast::Read *read) {
  format.init();
  /*
  Value *location = GetElementPtrInst::Create(
      PointerType::getInt64Ty(context),
      var,
      index_params,
      "invar_ref",
      entry.top());


  std::vector<Value*> new_args = {string_to_Value("%d"), location};
  CallInst::Create(scanf, makeArrayRef(new_args), string("scanf"),
  entry.top()); auto *r = new LoadInst(location, "invar", entry.top());
  eval.push(r);
  read->var->accept(this);
  */
  format.finish();
}

void Compiler::visit(ast::Labelled *labelled) {
  BasicBlock *parent, *follow;
  parent = entry.top();
  follow = BasicBlock::Create(context, "target", parent->getParent(), 0);
  BranchInst::Create(follow, parent);

  l_table[labelled->label] = follow;
  entry.push(follow);
  labelled->block->accept(this);
}
} // namespace visitor
