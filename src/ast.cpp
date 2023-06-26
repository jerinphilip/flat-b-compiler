#include "ast.h"

#include "compiler.h"
#include "formatter.h"
#include "interpreter.h"
#include "visitor.h"

/* PPRINTER */
void ast::Program::accept(visitor::Visitor *p) { p->visit(this); }
void ast::Declarations::accept(visitor::Visitor *p) { p->visit(this); }
void ast::Id::accept(visitor::Visitor *p) { p->visit(this); }
void ast::IdArrayAccess::accept(visitor::Visitor *p) { p->visit(this); }
void ast::Expr::accept(visitor::Visitor *p) { p->visit(this); }
void ast::Block::accept(visitor::Visitor *p) { p->visit(this); }
void ast::Statement::accept(visitor::Visitor *p) { p->visit(this); }
void ast::Assign::accept(visitor::Visitor *p) { p->visit(this); }
void ast::While::accept(visitor::Visitor *p) { p->visit(this); }
void ast::If::accept(visitor::Visitor *p) { p->visit(this); }
void ast::For::accept(visitor::Visitor *p) { p->visit(this); }
void ast::Print::accept(visitor::Visitor *p) { p->visit(this); }
void ast::TypedIds::accept(visitor::Visitor *p) { p->visit(this); }
void ast::Integer::accept(visitor::Visitor *p) { p->visit(this); }
void ast::BinOp::accept(visitor::Visitor *p) { p->visit(this); }
void ast::NoOp::accept(visitor::Visitor *p) { p->visit(this); }
void ast::Goto::accept(visitor::Visitor *p) { p->visit(this); }
void ast::IdDef::accept(visitor::Visitor *p) { p->visit(this); }
void ast::IdRef::accept(visitor::Visitor *p) { p->visit(this); }
void ast::IdArrayDef::accept(visitor::Visitor *p) { p->visit(this); }
void ast::IdArrayRef::accept(visitor::Visitor *p) { p->visit(this); }
void ast::Literal::accept(visitor::Visitor *p) { p->visit(this); }
void ast::Read::accept(visitor::Visitor *p) { p->visit(this); }
void ast::Labelled::accept(visitor::Visitor *p) { p->visit(this); }
