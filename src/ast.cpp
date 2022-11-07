#include "ast.h"
#include "visitor.h"

/* PPRINTER */
void ast::Program::accept(visitor::pprinter *p) { p->visit(this); }
void ast::Declarations::accept(visitor::pprinter *p) { p->visit(this); }
void ast::Id::accept(visitor::pprinter *p) { p->visit(this); }
void ast::IdArrayAccess::accept(visitor::pprinter *p) { p->visit(this); }
void ast::Expr::accept(visitor::pprinter *p) { p->visit(this); }
void ast::Code::accept(visitor::pprinter *p) { p->visit(this); }
void ast::Statement::accept(visitor::pprinter *p) { p->visit(this); }
void ast::Assign::accept(visitor::pprinter *p) { p->visit(this); }
void ast::CodeBlock::accept(visitor::pprinter *p) { p->visit(this); }
void ast::While::accept(visitor::pprinter *p) { p->visit(this); }
void ast::If::accept(visitor::pprinter *p) { p->visit(this); }
void ast::For::accept(visitor::pprinter *p) { p->visit(this); }
void ast::Print::accept(visitor::pprinter *p) { p->visit(this); }
void ast::TypedIds::accept(visitor::pprinter *p) { p->visit(this); }
void ast::Integer::accept(visitor::pprinter *p) { p->visit(this); }
void ast::BinOp::accept(visitor::pprinter *p) { p->visit(this); }
void ast::NoOp::accept(visitor::pprinter *p) { p->visit(this); }
void ast::Goto::accept(visitor::pprinter *p) { p->visit(this); }
void ast::IdDef::accept(visitor::pprinter *p) { p->visit(this); }
void ast::IdRef::accept(visitor::pprinter *p) { p->visit(this); }
void ast::IdArrayDef::accept(visitor::pprinter *p) { p->visit(this); }
void ast::IdArrayRef::accept(visitor::pprinter *p) { p->visit(this); }
void ast::Literal::accept(visitor::pprinter *p) { p->visit(this); }
void ast::Read::accept(visitor::pprinter *p) { p->visit(this); }
void ast::Labelled::accept(visitor::pprinter *p) { p->visit(this); }

/* INTERPRETER */
void ast::Program::accept(visitor::interpreter *p) { p->visit(this); }
void ast::Declarations::accept(visitor::interpreter *p) { p->visit(this); }
void ast::Id::accept(visitor::interpreter *p) { p->visit(this); }
void ast::IdArrayAccess::accept(visitor::interpreter *p) { p->visit(this); }
void ast::Expr::accept(visitor::interpreter *p) { p->visit(this); }
void ast::Code::accept(visitor::interpreter *p) { p->visit(this); }
void ast::Statement::accept(visitor::interpreter *p) { p->visit(this); }
void ast::Assign::accept(visitor::interpreter *p) { p->visit(this); }
void ast::CodeBlock::accept(visitor::interpreter *p) { p->visit(this); }
void ast::While::accept(visitor::interpreter *p) { p->visit(this); }
void ast::If::accept(visitor::interpreter *p) { p->visit(this); }
void ast::For::accept(visitor::interpreter *p) { p->visit(this); }
void ast::Print::accept(visitor::interpreter *p) { p->visit(this); }
void ast::TypedIds::accept(visitor::interpreter *p) { p->visit(this); }
void ast::Integer::accept(visitor::interpreter *p) { p->visit(this); }
void ast::BinOp::accept(visitor::interpreter *p) { p->visit(this); }
void ast::NoOp::accept(visitor::interpreter *p) { p->visit(this); }
void ast::Goto::accept(visitor::interpreter *p) { p->visit(this); }
void ast::IdDef::accept(visitor::interpreter *p) { p->visit(this); }
void ast::IdRef::accept(visitor::interpreter *p) { p->visit(this); }
void ast::IdArrayDef::accept(visitor::interpreter *p) { p->visit(this); }
void ast::IdArrayRef::accept(visitor::interpreter *p) { p->visit(this); }
void ast::Literal::accept(visitor::interpreter *p) { p->visit(this); }
void ast::Read::accept(visitor::interpreter *p) { p->visit(this); }
void ast::Labelled::accept(visitor::interpreter *p) { p->visit(this); }

/* COMPILER */
void ast::Program::accept(visitor::compiler *p) { p->visit(this); }
void ast::Declarations::accept(visitor::compiler *p) { p->visit(this); }
void ast::Id::accept(visitor::compiler *p) { p->visit(this); }
void ast::IdArrayAccess::accept(visitor::compiler *p) { p->visit(this); }
void ast::Expr::accept(visitor::compiler *p) { p->visit(this); }
void ast::Code::accept(visitor::compiler *p) { p->visit(this); }
void ast::Statement::accept(visitor::compiler *p) { p->visit(this); }
void ast::Assign::accept(visitor::compiler *p) { p->visit(this); }
void ast::CodeBlock::accept(visitor::compiler *p) { p->visit(this); }
void ast::While::accept(visitor::compiler *p) { p->visit(this); }
void ast::If::accept(visitor::compiler *p) { p->visit(this); }
void ast::For::accept(visitor::compiler *p) { p->visit(this); }
void ast::Print::accept(visitor::compiler *p) { p->visit(this); }
void ast::TypedIds::accept(visitor::compiler *p) { p->visit(this); }
void ast::Integer::accept(visitor::compiler *p) { p->visit(this); }
void ast::BinOp::accept(visitor::compiler *p) { p->visit(this); }
void ast::NoOp::accept(visitor::compiler *p) { p->visit(this); }
void ast::Goto::accept(visitor::compiler *p) { p->visit(this); }
void ast::IdDef::accept(visitor::compiler *p) { p->visit(this); }
void ast::IdRef::accept(visitor::compiler *p) { p->visit(this); }
void ast::IdArrayDef::accept(visitor::compiler *p) { p->visit(this); }
void ast::IdArrayRef::accept(visitor::compiler *p) { p->visit(this); }
void ast::Literal::accept(visitor::compiler *p) { p->visit(this); }
void ast::Read::accept(visitor::compiler *p) { p->visit(this); }
void ast::Labelled::accept(visitor::compiler *p) { p->visit(this); }
