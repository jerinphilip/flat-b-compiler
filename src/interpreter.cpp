#include "visitor.h"


void visitor::interpreter::visit(ast::node *node){
}

void visitor::interpreter::visit(ast::program *program){
    program->decl->accept(this);
    //program->block->accept(this);
}

void visitor::interpreter::visit(ast::declarations *declarations){
    cout << "Declarations" << endl;
    for (auto &p : *(declarations->ds)){
        p->accept(this);
    }
}

void visitor::interpreter::visit(ast::code *code){
    cout << "Code" << endl;
}

void visitor::interpreter::visit(ast::id *id){
    cout << "Code" << endl;
}

void visitor::interpreter::visit(ast::id_ *id_){
    cout << "Code" << endl;
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

void visitor::interpreter::visit(ast::typed_ids *t_ids){
    cout << "Typed ids" << endl;
}

void visitor::interpreter::visit(ast::no_op *no_op){
    cout << "No-Op" << endl;
}

void visitor::interpreter::visit(ast::goto_ *no_op){
    cout << "goto_" << endl;
}
