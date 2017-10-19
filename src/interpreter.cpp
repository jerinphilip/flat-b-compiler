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

    cout << "Code, Done" << endl;
}

void visitor::interpreter::visit(ast::id *id){
    cout << "Evaluating id" << endl;
    cout << "id, done" << endl;
    
}

void visitor::interpreter::visit(ast::id_ *id_){
    cout << "Evaluating id_" << endl;
    cout << "id_, done" << endl;
}

void visitor::interpreter::visit(ast::expr *expr){
    cout << "Code" << endl;
}

void visitor::interpreter::visit(ast::statement *statement){
    cout << "Code" << endl;
}

void visitor::interpreter::visit(ast::assign *assign){
    cout << "Code" << endl;
}

void visitor::interpreter::visit(ast::while_ *while_){
    cout << "Code" << endl;
}

void visitor::interpreter::visit(ast::if_ *if_){
    cout << "Code" << endl;
}

void visitor::interpreter::visit(ast::for_ *for_){
    cout << "Code" << endl;
}

void visitor::interpreter::visit(ast::print *print){
    cout << "Code" << endl;
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
