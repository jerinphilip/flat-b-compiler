#include "visitor.h"
#include "dtype.h"


void visitor::compiler::visit(ast::node *node){

}

void visitor::compiler::visit(ast::program *program){
	main_block = BasicBlock::Create(context, "main_fn", main_fn);
	entry.push(main_block);

	program->decl->accept(this);
	program->block->accept(this);

	// TODO: New
	ReturnInst::Create(context, entry.top());
	entry.pop();
	module->print(outs(), nullptr);

}

void visitor::compiler::visit(ast::declarations *declarations){
	for (auto &p : *(declarations->ds)){
		p->accept(this);
	}
}

void visitor::compiler::visit(ast::code *code){
	for(auto &p: *(code->statements)){
		p->accept(this);
	}
}

void visitor::compiler::visit(ast::id *id){
	if ( not declared_before(id->name)){
		cerr << "Undefined variable " << id->name << endl;
		//exit(-1);
	}
    Value *location = v_table[id->name];
    auto *r = new LoadInst(location, "vr", entry.top());
    eval.push((void*)r);
}

void visitor::compiler::visit(ast::id_ *id_){
	if ( not declared_before(id_->name)){
		cerr << "Undefined variable " << id_->name << endl;
		//exit(-1);
	}

	id_->subscript->accept(this);
	auto start = ConstantInt::get(context, APInt(64, StringRef("0"), 10));
	auto offset = (Value*) eval.top(); eval.pop();

	vector<Value*> index_params = {start, offset};
	Value *location =  GetElementPtrInst::CreateInBounds(
			v_table[id_->name], 
			index_params,
			"vr",
			entry.top());
    auto *r = new LoadInst(location, "vr", entry.top());
    eval.push((void*)r);
}

void visitor::compiler::visit(ast::id_ref *id_ref){
	if ( not declared_before(id_ref->name)){
		cerr << "Undefined variable " << id_ref->name << endl;
		//exit(-1);
	}

	Value *ret_val = (Value*) eval.top(); eval.pop();
	StoreInst *r = new StoreInst(ret_val, v_table[id_ref->name], false, entry.top());
	eval.push((void*)r);
}

void visitor::compiler::visit(ast::idA_ref *idA_ref){
	if ( not declared_before(idA_ref->name)){
		cerr << "Undefined variable " << idA_ref->name << endl;
		//exit(-1);
	}

	Value *ret_val = (Value*)eval.top(); eval.pop();

	idA_ref->subscript->accept(this);
	auto start = ConstantInt::get(context, APInt(64, StringRef("0"), 10));
	auto offset = (Value*) eval.top(); eval.pop();
	vector<Value*> index_params = {start, offset};
	Value *location =  GetElementPtrInst::CreateInBounds(
			v_table[idA_ref->name], 
			index_params,
			"vr",
			entry.top());

	Value *instruction = new StoreInst(ret_val, location, false, entry.top());
	eval.push((void*)instruction);
	/*
	   dataType dt;
	   dt.dtype = type::Pointer;
	   bool declared = env.find(idA_ref->name) != env.end();
	   if(not declared)

	   idA_ref->subscript->accept(this);
	   dataType sc = evalStack.top(); evalStack.pop();
	   int sub = sc.T.i;
	   dt.T.p = &(env[idA_ref->name].T.A[sub]);
	   evalStack.push(dt);
	   */
}

void visitor::compiler::visit(ast::expr *expr){
}

void visitor::compiler::visit(ast::statement *statement){
}

void visitor::compiler::visit(ast::assign *assign){
	assign->tree->accept(this);
	assign->ref->accept(this);
}

void visitor::compiler::visit(ast::while_ *while_){
    BasicBlock *parent, *pre, *body, *post;
    parent = entry.top();

    pre = body = post = NULL;

    pre = BasicBlock::Create(context, "pre", parent->getParent(), 0);
    body = BasicBlock::Create(context, "body", parent->getParent(), 0);
    post = BasicBlock::Create(context, "post", parent->getParent(), 0);

    entry.push(pre);
	while_->cond->accept(this);
	ZExtInst *condition = (ZExtInst*)eval.top(); eval.pop();
    // Value *comparison = condition;
    ConstantInt *zero = ConstantInt::get(Type::getInt64Ty(context), 0, true);
    ICmpInst *comparison = new ICmpInst(*pre, 
            ICmpInst::ICMP_NE, 
            condition, 
            zero,
            "vr");
    entry.pop();

    BranchInst::Create(body, post, comparison, pre);
    BranchInst::Create(pre, parent);

    entry.push(body);
    while_->block->accept(this);
    body = entry.top(); entry.pop();

    if ( not body->getTerminator()){
        BranchInst::Create(pre, body); 
    }

    entry.push(post);
}

void visitor::compiler::visit(ast::if_ *if_){
    BasicBlock *if_block, *merge_block, *else_block;
    if_block = merge_block = else_block = NULL;

	BasicBlock *ret_block = NULL;
	BasicBlock *parent = entry.top();
    assert ( parent != NULL );

	if_->cond->accept(this);
	ZExtInst *condition = (ZExtInst*)eval.top(); eval.pop();
    // Value *comparison = condition;
    ConstantInt *zero = ConstantInt::get(Type::getInt64Ty(context), 0, true);
    ICmpInst *comparison = new ICmpInst(*parent, 
            ICmpInst::ICMP_NE, 
            condition, 
            zero,
            "vr");



	if_block = BasicBlock::Create(context, "if_block", parent->getParent());
	merge_block = BasicBlock::Create(context, "merge_block", parent->getParent());

	entry.push(if_block);
	if_->block->accept(this);
	ret_block = entry.top(); entry.pop();

	
	if ( not ret_block->getTerminator()){
		BranchInst::Create(merge_block, ret_block);
	}


	if ( if_->otherwise!= NULL ){

		else_block = BasicBlock::Create(context, "else_block", parent->getParent());
		entry.push(else_block);
		if_->otherwise->accept(this);
		ret_block = entry.top(); entry.pop();

		if (not ret_block->getTerminator()){
            cerr << "terminator Happening! " << endl;
			BranchInst::Create(merge_block, ret_block);
		}
		//BranchInst::Create(if_block, else_block, condition, parent);
		BranchInst::Create(if_block, else_block, comparison, parent);
	}
	else{
		//BranchInst::Create(if_block, merge_block, condition, parent);
		BranchInst::Create(if_block, merge_block, comparison, parent);
	}

	entry.push(merge_block);
}

void visitor::compiler::visit(ast::for_ *for_){
	/*
	   for_->init->accept(this);

	   void *location;k
	   void **var = &location; 
	   for_->init->ref->vnode(var);
	   ast::id* ivar = (ast::id*)location;

	   ast::binOp *rhs = new ast::binOp(opr::add, ivar, for_->step);
	   ast::assign *step = new ast::assign(for_->init->ref, rhs);
	   ast::binOp *check = new ast::binOp(opr::le, ivar, for_->end);

	   dataType cond;
	   cond.dtype = type::Int;
	   cond.T.i = 1;
	   do {
	   check->accept(this);
	//evalStack.push(cond);
	cond = evalStack.top(); evalStack.pop();
	if (cond.T.i){
	for_->block->accept(this); 
	*/

	/* Evaluate body */
	/*
	   step->accept(this);
	   }
	   }while (cond.T.i);
	   */
}

void visitor::compiler::visit(ast::print *print){
	/* Reset */
	format.str = "";
	format.args.clear();

	bool first = true;
	auto ts = *print->args;
	reverse(ts.begin(), ts.end());
	for (auto &p: ts){
		if (not first){
			format.str += " ";
		}
		first = false;
		p->accept(this);
	}

	if (print->newline){
		format.str += "\n";
	}

	vector<Value*> args;
	vector<Value*> fargs = format.args;
	Value *fvar = string_to_Value(format.str);
	args.push_back(fvar);
	args.insert(args.end(), fargs.begin(), fargs.end());
	CallInst::Create(printf, makeArrayRef(args), string("printf"), entry.top());

}

void visitor::compiler::visit(ast::typed_ids *twrap){
	currentType = twrap->dtype;
	auto *ps = twrap->t_ids;
	for (auto &p : *ps ) {
		p->accept(this);
	}
}

void visitor::compiler::visit(ast::no_op *no_op){
}

void visitor::compiler::visit(ast::goto_ *goto_){
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

void visitor::compiler::visit(ast::integer *integer){
	Constant *r = ConstantInt::get(Type::getInt64Ty(context), integer->value);
	eval.push((void*)r);
}


void visitor::compiler::visit(ast::binOp *binOp){

	binOp->left->accept(this);
	Value* left = (Value*)eval.top(); eval.pop();
	binOp->right->accept(this);
	Value* right = (Value*)eval.top(); eval.pop();

	auto parent = entry.top();
	auto binary_operator = [&left, &right, &parent, this](Instruction::BinaryOps Op){
		auto *b = BinaryOperator::Create(Op, left, right, "vr", parent);
        eval.push((void*)b);
	};

	auto cmp_operator = [&left, &right, &parent, this](CmpInst::Predicate pred){
		auto *z =  new ZExtInst(
				CmpInst::Create(
					Instruction::ICmp,
					pred,
					left, 
					right,
					"vr",
					parent),
				Type::getInt64Ty(context),
				"zext",
				parent);
        eval.push((void*)z);
	};



	switch (binOp->op){
		case opr::add:  
			binary_operator(Instruction::Add);
			break;
		case opr::sub:  
			binary_operator(Instruction::Sub);
			break;
		case opr::mul:  
			binary_operator(Instruction::Mul);
			break;
		case opr::quot: 
			binary_operator(Instruction::SDiv);
			break;
		case opr::lt: 
			cmp_operator(ICmpInst::ICMP_SLT);
			break;
		case opr::gt: 
			cmp_operator(ICmpInst::ICMP_SGT);
			break;
		case opr::le: 
			cmp_operator(ICmpInst::ICMP_SLE);
			break;
		case opr::ge: 
			cmp_operator(ICmpInst::ICMP_SGE);
			break;
		case opr::eq: 
			cmp_operator(ICmpInst::ICMP_EQ);
			break;
		default:
			break;
	}
}

void visitor::compiler::visit(ast::id_def *id_def){

	if (declared_before(id_def->name)){
		cerr << "Redeclaration of variable " << id_def->name << endl;
		//exit(-1);
	}
	else{

		GlobalVariable *var = new GlobalVariable(*module, 
				Type::getInt64Ty(context),
				false,
				GlobalValue::CommonLinkage,
				NULL,
				id_def->name);
		var->setInitializer(ConstantInt::get(context, 
					APInt(64, StringRef("0"), 10)));

		v_table[id_def->name] = var;
		cerr << "Declaration of variable " << id_def->name << endl;
	}

}

void visitor::compiler::visit(ast::idA_def *idA_def){
	if (declared_before(idA_def->name)){
		cerr << "Redeclaration of variable " << idA_def->name << endl;
		//exit(-1);
	}
	else{
		GlobalVariable *var = new GlobalVariable(*module,
				ArrayType::get(Type::getInt64Ty(context), idA_def->size),
				false,
				GlobalValue::CommonLinkage,
				NULL,
				idA_def->name);
		var->setInitializer(
				ConstantAggregateZero::get(
					ArrayType::get(
						Type::getInt64Ty(context), idA_def->size)));

		v_table[idA_def->name] = var;
		cerr << "Declaration of variable " << idA_def->name << endl;
	}
}

void visitor::compiler::visit(ast::literal *literal){
	/*
	   dataType dt;
	   dt.dtype = type::CharArray;
	   dt.T.s = (char*)literal->value.c_str();
	   evalStack.push(dt);
	   */
	format.str += "%s";
	auto var =  string_to_Value(literal->value);
	format.args.push_back(var);
}

void visitor::compiler::visit(ast::read *read){
	/*
	   read->var->accept(this);
	   dataType ref = evalStack.top(); evalStack.pop();
	   int value;
	   cin >> value;
	 *(ref.T.p) = value;
	 */
}

void visitor::compiler::visit(ast::labelled *labelled){
	labelled->block->accept(this);
}

