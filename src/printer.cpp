#include "ast.h"
#include "visitor.h"


void visitor::pprinter::visit(ast::node *node){
}

void visitor::pprinter::visit(ast::program *program){
    program->decl->accept(this);
    program->block->accept(this);
}

void visitor::pprinter::visit(ast::declarations *declarations){
    cout << "decl {" << endl;
    for (auto &p : *(declarations->ds)){
        p->accept(this);
    }
    cout << "}\n";
}

void visitor::pprinter::visit(ast::code *code){
    //cout << "Code" << endl;
}

void visitor::pprinter::visit(ast::id *id){
    //cout << "Code" << endl;
    cout << id->name;
}

void visitor::pprinter::visit(ast::id_ *id_){
    //cout << "Code" << endl;
    cout << id_->name << "[" ;
    id_->subscript->accept(this);
    cout << "]";
}

void visitor::pprinter::visit(ast::expr *expr){
    //cout << "Code" << endl;
}

void visitor::pprinter::visit(ast::statement *statement){
    //cout << "Code" << endl;
}

void visitor::pprinter::visit(ast::assign *assign){
    //cout << "Code" << endl;
}

void visitor::pprinter::visit(ast::while_ *while_){
    //cout << "Code" << endl;
}

void visitor::pprinter::visit(ast::if_ *if_){
    //cout << "Code" << endl;
}

void visitor::pprinter::visit(ast::for_ *for_){
    //cout << "Code" << endl;
}

void visitor::pprinter::visit(ast::print *print){
    //cout << "Code" << endl;
}

void visitor::pprinter::visit(ast::typed_ids *tIdWrapper){
    //cout << "Typed ids" << endl;
    string dtype;
    switch(tIdWrapper->dtype){
        case type::Int : dtype = "int"; break;
        case type::Bool: dtype = "bool"; break;
        case type::Char: dtype = "char"; break;
        default: break;
    }
    cout << dtype << " ";
    bool first = true;
    auto *ps = tIdWrapper->t_ids;
    reverse(ps->begin(), ps->end());
    for (auto &p: *ps){
        if (not first)
            cout << ", ";
        first = false;
        p->accept(this);

    }
    cout << ";\n";

}

void visitor::pprinter::visit(ast::no_op *no_op){
    cout << "No-Op" << endl;
}

void visitor::pprinter::visit(ast::goto_ *goto_){
    cout << "Go-To" << endl;
}

void visitor::pprinter::visit(ast::integer *integer){
    cout << integer->value;
}

void visitor::pprinter::visit(ast::id_def *id_def){
}

void visitor::pprinter::visit(ast::idA_def *idA_def){
}

void visitor::pprinter::visit(ast::binOp *binOp){
}

void visitor::pprinter::visit(ast::id_ref *id_ref){
}

void visitor::pprinter::visit(ast::idA_ref *idA_ref){
}
