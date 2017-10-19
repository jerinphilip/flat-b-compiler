#include "visitor.h"


void visitor::pprinter::visit(ast::node *node){
    cout << "Declarations" << endl;
}

void visitor::pprinter::visit(ast::program *program){
    cout << "Program" << endl;
    program->decl->accept(this);
    program->block->accept(this);
}

void visitor::pprinter::visit(ast::declarations *declarations){
    cout << "Declarations" << endl;
}

void visitor::pprinter::visit(ast::code *code){
    cout << "Code" << endl;
}

void visitor::pprinter::visit(ast::id *id){
    cout << "Code" << endl;
}

void visitor::pprinter::visit(ast::id_ *id_){
    cout << "Code" << endl;
}

void visitor::pprinter::visit(ast::expr *expr){
    cout << "Code" << endl;
}

void visitor::pprinter::visit(ast::statement *statement){
    cout << "Code" << endl;
}

void visitor::pprinter::visit(ast::assign *assign){
    cout << "Code" << endl;
}

void visitor::pprinter::visit(ast::while_ *while_){
    cout << "Code" << endl;
}

void visitor::pprinter::visit(ast::if_ *if_){
    cout << "Code" << endl;
}

void visitor::pprinter::visit(ast::for_ *for_){
    cout << "Code" << endl;
}

void visitor::pprinter::visit(ast::print *print){
    cout << "Code" << endl;
}
