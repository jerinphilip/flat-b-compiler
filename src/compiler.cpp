#include "dtype.h"
#include "visitor.h"

void visitor::compiler::visit(ast::Node *node) {}

void visitor::compiler::visit(ast::Program *program) {
  main_block = BasicBlock::Create(context, "main_fn", main_fn);
  entry.push(main_block);

  program->decl->accept(this);
  program->block->accept(this);

  // TODO: New
  ReturnInst::Create(context, entry.top());
  entry.pop();
  module->print(outs(), nullptr);
}

void visitor::compiler::visit(ast::Declarations *declarations) {
  for (auto &p : *(declarations->ds)) {
    p->accept(this);
  }
}

void visitor::compiler::visit(ast::Code *code) {
  for (auto &p : *(code->statements)) {
    p->accept(this);
  }
}

void visitor::compiler::visit(ast::Id *id) {
  if (not declared_before(id->name)) {
    cerr << "Undefined variable " << id->name << endl;
    // exit(-1);
  }
  Value *location = v_table[id->name];
  // Value *r = new LoadInst(location, "vr", entry.top());
  Value *r = nullptr;
  eval.push((void *)r);
  format.place("%d", r);
}

void visitor::compiler::visit(ast::IdArrayAccess *id_) {
  if (not declared_before(id_->name)) {
    cerr << "Undefined variable " << id_->name << endl;
    // exit(-1);
  }

  id_->subscript->accept(this);
  auto start = ConstantInt::get(context, APInt(64, StringRef("0"), 10));
  auto offset = (Value *)eval.top();
  eval.pop();

  vector<Value *> index_params = {start, offset};
  // Value *location = GetElementPtrInst::CreateInBounds(
  //     v_table[id_->name], index_params, "vr", entry.top());
  // Value *r = new LoadInst(location, "vr", entry.top());
  Value *location = nullptr;
  Value *r = nullptr;
  eval.push((void *)r);
  format.place("%d", r);
}

void visitor::compiler::visit(ast::IdRef *id_ref) {
  if (not declared_before(id_ref->name)) {
    cerr << "Undefined variable " << id_ref->name << endl;
    // exit(-1);
  }

  Value *ret_val = (Value *)eval.top();
  eval.pop();
  StoreInst *r =
      new StoreInst(ret_val, v_table[id_ref->name], false, entry.top());
  eval.push((void *)r);
}

void visitor::compiler::visit(ast::IdArrayRef *idA_ref) {
  if (not declared_before(idA_ref->name)) {
    cerr << "Undefined variable " << idA_ref->name << endl;
    // exit(-1);
  }

  Value *ret_val = (Value *)eval.top();
  eval.pop();

  idA_ref->subscript->accept(this);
  auto start = ConstantInt::get(context, APInt(64, StringRef("0"), 10));
  auto offset = (Value *)eval.top();
  eval.pop();
  vector<Value *> index_params = {start, offset};
  // Value *location = GetElementPtrInst::CreateInBounds(
  //     v_table[idA_ref->name], index_params, "vr", entry.top());
  Value *location = nullptr;

  Value *instruction = new StoreInst(ret_val, location, false, entry.top());
  eval.push((void *)instruction);
}

void visitor::compiler::visit(ast::Expr *expr) {}

void visitor::compiler::visit(ast::Statement *statement) {}

void visitor::compiler::visit(ast::Assign *assign) {
  assign->tree->accept(this);
  assign->ref->accept(this);
}

void visitor::compiler::visit(ast::While *while_) {
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

void visitor::compiler::visit(ast::If *if_) {
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

void visitor::compiler::visit(ast::For *for_) {
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

void visitor::compiler::visit(ast::Print *print) {
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

  vector<Value *> new_args;
  Value *fvar = string_to_Value(format.str);
  new_args.push_back(fvar);
  new_args.insert(new_args.end(), format.args.begin(), format.args.end());
  CallInst::Create(printf, makeArrayRef(new_args), string("printf"),
                   entry.top());

  format.finish();
}

void visitor::compiler::visit(ast::TypedIds *twrap) {
  currentType = twrap->dtype;
  auto *ps = twrap->t_ids;
  for (auto &p : *ps) {
    p->accept(this);
  }
}

void visitor::compiler::visit(ast::NoOp *no_op) {}

void visitor::compiler::visit(ast::Goto *goto_) {
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

void visitor::compiler::visit(ast::Integer *integer) {
  Constant *r = ConstantInt::get(Type::getInt64Ty(context), integer->value);
  eval.push((void *)r);
  format.place("%d", r);
}

void visitor::compiler::visit(ast::BinOp *binOp) {

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

void visitor::compiler::visit(ast::IdDef *id_def) {

  if (declared_before(id_def->name)) {
    cerr << "Redeclaration of variable " << id_def->name << endl;
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

void visitor::compiler::visit(ast::IdArrayDef *idA_def) {
  if (declared_before(idA_def->name)) {
    cerr << "Redeclaration of variable " << idA_def->name << endl;
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

void visitor::compiler::visit(ast::Literal *literal) {
  auto var = string_to_Value(literal->value);
  eval.push(var);
  format.place("%s", var);
}

void visitor::compiler::visit(ast::Read *read) {
  format.init();
  /*
  Value *location = GetElementPtrInst::Create(
      PointerType::getInt64Ty(context),
      var,
      index_params,
      "invar_ref",
      entry.top());


  vector<Value*> new_args = {string_to_Value("%d"), location};
  CallInst::Create(scanf, makeArrayRef(new_args), string("scanf"), entry.top());
  auto *r = new LoadInst(location, "invar", entry.top());
  eval.push(r);
  read->var->accept(this);
  */
  format.finish();
}

void visitor::compiler::visit(ast::Labelled *labelled) {
  BasicBlock *parent, *follow;
  parent = entry.top();
  follow = BasicBlock::Create(context, "target", parent->getParent(), 0);
  BranchInst::Create(follow, parent);

  l_table[labelled->label] = follow;
  entry.push(follow);
  labelled->block->accept(this);
}
