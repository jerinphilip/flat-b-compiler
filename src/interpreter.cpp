#include "visitor.h"

void visitor::interpreter::visit(ast::node *node){

}

void visitor::interpreter::visit(ast::program *program){
    cerr << "Evaluating program" << endl;
    program->decl->accept(this);
    program->block->accept(this);
}

void visitor::interpreter::visit(ast::declarations *declarations){
    cerr << "Evaluation declarations" << endl;
    for (auto &p : *(declarations->ds)){
        p->accept(this);
    }
    cerr << "Declarations, done." << endl;
}

void visitor::interpreter::visit(ast::code *code){
    cerr << "Evaluating Code" << endl;
    for(auto &p: *(code->statements)){
        p->accept(this);
    }
    cerr << "Code, Done" << endl;
}

void visitor::interpreter::visit(ast::id *id){
    cerr << "Evaluating id" << endl;
    dataType dt;
    bool declared = env.find(id->name) != env.end();
    if(not declared)
        cerr << "Undefined variable" << endl;

    /* TODO, Ascertain dtype from pointer type */
    dt.dtype = type::Int;
    dt.T.i = env[id->name].T.i;
    evalStack.push(dt);
    cerr << "id, done" << endl;
    
}

void visitor::interpreter::visit(ast::id_ *id_){
    cerr << "Evaluating id_" << endl;
    dataType dt;
    dt.dtype = type::Pointer;
    bool declared = env.find(id_->name) != env.end();
    if(not declared)
        cerr << "Undefined variable" << endl;

    id_->subscript->accept(this);
    dataType sc = evalStack.top(); evalStack.pop();
    int sub = sc.T.i;
    dt.T.i = env[id_->name].T.A[sub];
    evalStack.push(dt);
    cerr << "id_, done" << endl;
}

void visitor::interpreter::visit(ast::id_ref *id_ref){
    cerr << "Evaluating id_ref" << endl;
    dataType dt;
    dt.dtype = type::Pointer;
    bool declared = env.find(id_ref->name) != env.end();
    if(not declared)
        cerr << "Undefined variable" << endl;

    dt.T.p = &(env[id_ref->name].T.i);
    evalStack.push(dt);
    cerr << "id_ref, done" << endl;
    
}

void visitor::interpreter::visit(ast::idA_ref *idA_ref){
    cerr << "Evaluating idA_ref" << endl;
    dataType dt;
    dt.dtype = type::Pointer;
    bool declared = env.find(idA_ref->name) != env.end();
    if(not declared)
        cerr << "Undefined variable" << endl;

    idA_ref->subscript->accept(this);
    dataType sc = evalStack.top(); evalStack.pop();
    int sub = sc.T.i;
    dt.T.p = &(env[idA_ref->name].T.A[sub]);
    evalStack.push(dt);
    cerr << "idA_ref, done" << endl;
}

void visitor::interpreter::visit(ast::expr *expr){
    cerr << "Code" << endl;
}

void visitor::interpreter::visit(ast::statement *statement){
    cerr << "Evaluating Statement" << endl; 
    cerr << "Statement, Done" << endl;
}

void visitor::interpreter::visit(ast::assign *assign){
    cerr << "[ assign -------- " << endl;
    assign->ref->accept(this);
    dataType ref = evalStack.top(); evalStack.pop();
    assign->tree->accept(this);
    dataType value = evalStack.top(); evalStack.pop();
    cerr << "Temp pointer: " << (long)ref.T.p << endl;
    *(ref.T.p) = value.T.i;
    cerr << assign->ref->name << " = " << value.T.i << " ; "<< endl;
    cerr << " -------- assign ]" << endl;
}

void visitor::interpreter::visit(ast::while_ *while_){
    cerr << "Evaluating While" << endl;
    cerr << "While, Done" << endl;
}

void visitor::interpreter::visit(ast::if_ *if_){
    cerr << "Evaluating If" << endl;
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
    cerr << "If, Done" << endl;
}

void visitor::interpreter::visit(ast::for_ *for_){
    cerr << "[ for ---" << endl;
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
        cerr << "Check: " << cond.T.i << endl;
        if (cond.T.i){
            for_->block->accept(this); /* Evaluate body */
            step->accept(this);
        }
    }while (cond.T.i);
    cerr << "---- for ]" << endl;
}

void visitor::interpreter::visit(ast::print *print){
    cerr << "[ print ---" << endl;
    bool first = true;
    cerr << "[size] " << print->args->size() << endl;
    auto ts = *print->args;
    reverse(ts.begin(), ts.end());
    for (auto &p: ts){
        if (not first){
            cout << " ";
        }
        first = false;
        p->accept(this);
        dataType dt = evalStack.top(); evalStack.pop();
        switch(dt.dtype){
            case type::Int: 
                cout << dt.T.i;
                break;
            case type::CharArray:
                cout << dt.T.s ;
                break;
            case type::Bool:
                cout << dt.T.b ;
                break;
            default:
                break;
        }
    }

    if (print->newline){
        cout << "\n";
    }

    cerr << "--- print ]" << endl;
}

void visitor::interpreter::visit(ast::typed_ids *twrap){
    cerr << "Evaluating typed_ids" << endl;
    auto *ps = twrap->t_ids;
    for (auto &p : *ps ) {
        p->accept(this);
    }
    cerr << "Typed Ids, Done" << endl;
}

void visitor::interpreter::visit(ast::no_op *no_op){
    cerr << "No-Op" << endl;
}

void visitor::interpreter::visit(ast::goto_ *no_op){
    cerr << "goto_" << endl;
}

void visitor::interpreter::visit(ast::integer *integer){
    cerr << "[ integer ---- ]" << endl;
    dataType dt;
    dt.dtype = type::Int;
    dt.T.i = integer->value;
    evalStack.push(dt);
    cerr << integer->value << endl;
    cerr << " ----- integer ]" << endl;

}


void visitor::interpreter::visit(ast::binOp *binOp){
    cerr << "[ binary op ----- " << endl;

    /* Evaluate and put on stack */
    binOp->left->accept(this);
    dataType left = evalStack.top(); evalStack.pop();
    binOp->right->accept(this);
    dataType right = evalStack.top(); evalStack.pop();


    /* TODO Generalize for types */
    cerr << "Left, right: " << left.dtype << ", " << right.dtype << endl; 

    if ( left.dtype != right.dtype ){
        cerr << "Type mismatch!" << endl;
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


    cerr << " ----- binary op ]" <<endl;

}

void visitor::interpreter::visit(ast::id_def *id_def){
    cerr << "Defining " << id_def->name << endl;
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
}

void visitor::interpreter::visit(ast::idA_def *idA_def){
    cerr << "Defining array ";
    string name = idA_def->name;
    int size = idA_def->size;
    cerr << name << "["<< size << "]" << endl;
    dataType dt;
    dt.dtype = currentType;
    switch (dt.dtype){
        case type::Int:
            dt.T.A = new int[size];
            break;
        default:
            break;
    }

    env[name] = dt;
}

void visitor::interpreter::visit(ast::literal *literal){
    dataType dt;
    dt.dtype = type::CharArray;
    dt.T.s = (char*)literal->value.c_str();
    cerr << "Literal: " << literal->value << endl;
    evalStack.push(dt);
}

