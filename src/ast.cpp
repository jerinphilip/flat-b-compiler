#include "ast.h"
#include "visitor.h"

void ast::program::accept(visitor::pprinter *p){
    p->visit(this);
}
void ast::declarations::accept(visitor::pprinter *p){ 
    p->visit(this);
}
void ast::id::accept(visitor::pprinter *p){ 
    p->visit(this);
}

void ast::id_::accept(visitor::pprinter *p){
    p->visit(this);
}
//void ast::expr::accept(visitor::pprinter *p){ }
void ast::code::accept(visitor::pprinter *p){
    p->visit(this);
}
void ast::statement::accept(visitor::pprinter *p){
    p->visit(this);
}
void ast::assign::accept(visitor::pprinter *p){
    p->visit(this);
}
void ast::cblock::accept(visitor::pprinter *p){
    p->visit(this);
}
void ast::while_::accept(visitor::pprinter *p){
    p->visit(this);
}
void ast::if_::accept(visitor::pprinter *p){
    p->visit(this);
}
void ast::for_::accept(visitor::pprinter *p){
    p->visit(this);
}
void ast::print::accept(visitor::pprinter *p){
    p->visit(this);
}
void ast::println::accept(visitor::pprinter *p){
    p->visit(this);
}
void ast::typed_ids::accept(visitor::pprinter *p){
    p->visit(this);
}
void ast::integer::accept(visitor::pprinter *p){
    p->visit(this);
}
void ast::binOp::accept(visitor::pprinter *p){
    p->visit(this);
}
