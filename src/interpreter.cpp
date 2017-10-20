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
    cout << "Evaluating Code" << endl;
    for(auto &p: *(code->statements)){
        p->accept(this);
    }
    cout << "Code, Done" << endl;
}

void visitor::interpreter::visit(ast::id *id){
    cout << "Evaluating id" << endl;
    dataType dt;
    bool declared = env.find(id->name) != env.end();
    if(not declared)
        cerr << "Undefined variable" << endl;

    evalStack.push(env[id->name]);
    cout << "id, done" << endl;
    
}

void visitor::interpreter::visit(ast::id_ *id_){
    cout << "Evaluating id_" << endl;
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
    cout << "id_, done" << endl;
}

void visitor::interpreter::visit(ast::id_ref *id_ref){
    cout << "Evaluating id_ref" << endl;
    dataType dt;
    dt.dtype = type::Pointer;
    bool declared = env.find(id_ref->name) != env.end();
    if(not declared)
        cerr << "Undefined variable" << endl;

    dt.T.p = &(env[id_ref->name].T.i);
    evalStack.push(dt);
    cout << "id_ref, done" << endl;
    
}

void visitor::interpreter::visit(ast::idA_ref *idA_ref){
    cout << "Evaluating idA_ref" << endl;
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
    cout << "idA_ref, done" << endl;
}

void visitor::interpreter::visit(ast::expr *expr){
    cout << "Code" << endl;
}

void visitor::interpreter::visit(ast::statement *statement){
    cout << "Evaluating Statement" << endl; 
    cout << "Statement, Done" << endl;
}

void visitor::interpreter::visit(ast::assign *assign){
    cout << "[ assign -------- " << endl;
    assign->ref->accept(this);
    dataType ref = evalStack.top(); evalStack.pop();
    assign->tree->accept(this);
    dataType value = evalStack.top(); evalStack.pop();
    *(ref.T.p) = value.T.i;
    cout << assign->ref->name << " = " << value.T.i << " ; "<< endl;
    cout << " -------- assign ]" << endl;
}

void visitor::interpreter::visit(ast::while_ *while_){
    cout << "Evaluating While" << endl;
    cout << "While, Done" << endl;
}

void visitor::interpreter::visit(ast::if_ *if_){
    cout << "Evaluating If" << endl;
    cout << "If, Done" << endl;
}

void visitor::interpreter::visit(ast::for_ *for_){
    cout << "[ for ---" << endl;
    cout << "---- for ]" << endl;
}

void visitor::interpreter::visit(ast::print *print){
    cout << "[ print ---" << endl;
    cout << "--- print ]" << endl;
}

void visitor::interpreter::visit(ast::typed_ids *twrap){
    cout << "Evaluating typed_ids" << endl;
    auto *ps = twrap->t_ids;
    for (auto &p : *ps ) {
        p->accept(this);
    }
    cout << "Typed Ids, Done" << endl;
}

void visitor::interpreter::visit(ast::no_op *no_op){
    cout << "No-Op" << endl;
}

void visitor::interpreter::visit(ast::goto_ *no_op){
    cout << "goto_" << endl;
}

void visitor::interpreter::visit(ast::integer *integer){
    cout << "[ integer ---- ]" << endl;
    dataType dt;
    dt.dtype = type::Int;
    dt.T.i = integer->value;
    evalStack.push(dt);
    cout << integer->value << endl;
    cout << " ----- integer ]" << endl;

}


void visitor::interpreter::visit(ast::binOp *binOp){
    cout << "[ binary op ----- " << endl;

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
            default:
                break;
        }
    }


    cout << " ----- binary op ]" <<endl;

}

void visitor::interpreter::visit(ast::id_def *id_def){
    cout << "Defining " << id_def->name << endl;
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
    cout << "Defining array ";
    string name = idA_def->name;
    int size = idA_def->size;
    cout << name << "["<< size << "]" << endl;
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
