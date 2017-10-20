#include "ast.h"
#include "visitor.h"

/* PPRINTER */
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
void ast::expr::accept(visitor::pprinter *p){
    p->visit(this);
}
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
void ast::typed_ids::accept(visitor::pprinter *p){
    p->visit(this);
}
void ast::integer::accept(visitor::pprinter *p){
    p->visit(this);
}
void ast::binOp::accept(visitor::pprinter *p){
    p->visit(this);
}
void ast::no_op::accept(visitor::pprinter *p){
    p->visit(this);
}
void ast::goto_::accept(visitor::pprinter *p){
    p->visit(this);
}
void ast::id_def::accept(visitor::pprinter *p){
    p->visit(this);
}
void ast::id_ref::accept(visitor::pprinter *p){
    p->visit(this);
}
void ast::idA_def::accept(visitor::pprinter *p){
    p->visit(this);
}
void ast::idA_ref::accept(visitor::pprinter *p){
    p->visit(this);
}
void ast::literal::accept(visitor::pprinter *p){
    p->visit(this);
}
void ast::read::accept(visitor::pprinter *p){
    p->visit(this);
}
void ast::labelled::accept(visitor::pprinter *p){
    p->visit(this);
}

/* INTERPRETER */
void ast::program::accept(visitor::interpreter *p){
    p->visit(this);
}
void ast::declarations::accept(visitor::interpreter *p){ 
    p->visit(this);
}
void ast::id::accept(visitor::interpreter *p){ 
    p->visit(this);
}
void ast::id_::accept(visitor::interpreter *p){
    p->visit(this);
}
void ast::expr::accept(visitor::interpreter *p){
    p->visit(this);
}
void ast::code::accept(visitor::interpreter *p){
    p->visit(this);
}
void ast::statement::accept(visitor::interpreter *p){
    p->visit(this);
}
void ast::assign::accept(visitor::interpreter *p){
    p->visit(this);
}
void ast::cblock::accept(visitor::interpreter *p){
    p->visit(this);
}
void ast::while_::accept(visitor::interpreter *p){
    p->visit(this);
}
void ast::if_::accept(visitor::interpreter *p){
    p->visit(this);
}
void ast::for_::accept(visitor::interpreter *p){
    p->visit(this);
}
void ast::print::accept(visitor::interpreter *p){
    p->visit(this);
}
void ast::typed_ids::accept(visitor::interpreter *p){
    p->visit(this);
}
void ast::integer::accept(visitor::interpreter *p){
    p->visit(this);
}
void ast::binOp::accept(visitor::interpreter *p){
    p->visit(this);
}
void ast::no_op::accept(visitor::interpreter *p){
    p->visit(this);
}
void ast::goto_::accept(visitor::interpreter *p){
    p->visit(this);
}
void ast::id_def::accept(visitor::interpreter *p){
    p->visit(this);
}
void ast::id_ref::accept(visitor::interpreter *p){
    p->visit(this);
}
void ast::idA_def::accept(visitor::interpreter *p){
    p->visit(this);
}
void ast::idA_ref::accept(visitor::interpreter *p){
    p->visit(this);
}
void ast::literal::accept(visitor::interpreter *p){
    p->visit(this);
}
void ast::read::accept(visitor::interpreter *p){
    p->visit(this);
}
void ast::labelled::accept(visitor::interpreter *p){
    p->visit(this);
}


