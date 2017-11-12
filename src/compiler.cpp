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
    module->print(errs(), nullptr);

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

    Value *ret_val = (Value*) eval.top(); eval.pop();

    StoreInst *r = new StoreInst(ret_val, v_table[id->name], false, entry.top());
    eval.push((void*)r);

    
}

void visitor::compiler::visit(ast::id_ *id_){
    if ( not declared_before(id_->name)){
        cerr << "Undefined variable " << id_->name << endl;
        //exit(-1);
    }

    Value *ret_val = (Value*)eval.top(); eval.pop();

    id_->subscript->accept(this);
    auto start = ConstantInt::get(context, APInt(64, StringRef("0"), 10));
    auto offset = (Value*) eval.top(); eval.pop();
    vector<Value*> index_params = {start, offset};
    Value *location =  GetElementPtrInst::CreateInBounds(
            v_table[id_->name], 
            index_params,
            "vr",
            entry.top());

    Value *instruction = new StoreInst(ret_val, location, false, entry.top());
    eval.push((void*)instruction);
}

void visitor::compiler::visit(ast::id_ref *id_ref){
    /*
    dataType dt;
    dt.dtype = type::Pointer;
    bool declared = env.find(id_ref->name) != env.end();
    if(not declared)

    dt.T.p = &(env[id_ref->name].T.i);
    evalStack.push(dt);
    */
}

void visitor::compiler::visit(ast::idA_ref *idA_ref){
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
    /*
    dataType cond;
    while_->cond->accept(this);
    cond = evalStack.top(); evalStack.pop();
    while (cond.T.i){
        while_->block->accept(this);
    */

        /* Step */
    /*
        while_->cond->accept(this);
        cond = evalStack.top(); evalStack.pop();
    }
    */
}

void visitor::compiler::visit(ast::if_ *if_){
    /*
    dataType cond;
    if_->cond->accept(this);
    cond = evalStack.top(); evalStack.pop();
    if (cond.T.i){
        if_->block->accept(this);
    }
    else{
        if(if_->otherwise != NULL){
            if_->otherwise->accept(this);
        }
    }
    */
}

void visitor::compiler::visit(ast::for_ *for_){
    /*
    for_->init->accept(this);

    void *location;
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
    /*
    dataType dt;
    dt.dtype = type::Int;
    dt.T.i = integer->value;
    evalStack.push(dt);
    */
}


void visitor::compiler::visit(ast::binOp *binOp){

    /* Evaluate and put on stack */
    /*
    binOp->left->accept(this);
    dataType left = evalStack.top(); evalStack.pop();
    binOp->right->accept(this);
    dataType right = evalStack.top(); evalStack.pop();
    */


    /* TODO Generalize for types */

    /*
    if ( left.dtype != right.dtype ){
    }
    else{
        switch (binOp->op){
            case opr::add:  evalStack.push(left + right); break;
            case opr::sub:  evalStack.push(left - right); break;
            case opr::mul:  evalStack.push(left * right); break;
            case opr::quot: evalStack.push(left / right); break;
            case opr::lt: evalStack.push(left < right); break;
            case opr::gt: evalStack.push(left > right); break;
            case opr::le: evalStack.push(left <= right); break;
            case opr::ge: evalStack.push(left >= right); break;
            case opr::eq: evalStack.push(left == right); break;
            default:
                break;
        }
    }
    */
}

void visitor::compiler::visit(ast::id_def *id_def){
    /*
    dataType dt;
    dt.dtype = currentType;
    switch (dt.dtype){
        case type::Int:
            dt.T.i = 0;
            break;
        default:
            break;
    }

    string name = id_def->name;
    env[name] = dt;
    */

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
    /*
    string name = idA_def->name;
    int size = idA_def->size;
    dataType dt;
    dt.dtype = currentType;
    switch (dt.dtype){
        case type::Int:
            dt.T.A = new int[size];
            dt.dtype = IntArray;
            break;
        default:
            break;
    }

    env[name] = dt;
    */
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

