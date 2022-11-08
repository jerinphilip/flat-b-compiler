#include "ast.h"
#include "visitor.h"

/* PPRINTER */
void ast::Program::accept(visitor::PrettyPrinter *p) { p->visit(this); }
void ast::Declarations::accept(visitor::PrettyPrinter *p) { p->visit(this); }
void ast::Id::accept(visitor::PrettyPrinter *p) { p->visit(this); }
void ast::IdArrayAccess::accept(visitor::PrettyPrinter *p) { p->visit(this); }
void ast::Expr::accept(visitor::PrettyPrinter *p) { p->visit(this); }
void ast::Code::accept(visitor::PrettyPrinter *p) { p->visit(this); }
void ast::Statement::accept(visitor::PrettyPrinter *p) { p->visit(this); }
void ast::Assign::accept(visitor::PrettyPrinter *p) { p->visit(this); }
void ast::CodeBlock::accept(visitor::PrettyPrinter *p) { p->visit(this); }
void ast::While::accept(visitor::PrettyPrinter *p) { p->visit(this); }
void ast::If::accept(visitor::PrettyPrinter *p) { p->visit(this); }
void ast::For::accept(visitor::PrettyPrinter *p) { p->visit(this); }
void ast::Print::accept(visitor::PrettyPrinter *p) { p->visit(this); }
void ast::TypedIds::accept(visitor::PrettyPrinter *p) { p->visit(this); }
void ast::Integer::accept(visitor::PrettyPrinter *p) { p->visit(this); }
void ast::BinOp::accept(visitor::PrettyPrinter *p) { p->visit(this); }
void ast::NoOp::accept(visitor::PrettyPrinter *p) { p->visit(this); }
void ast::Goto::accept(visitor::PrettyPrinter *p) { p->visit(this); }
void ast::IdDef::accept(visitor::PrettyPrinter *p) { p->visit(this); }
void ast::IdRef::accept(visitor::PrettyPrinter *p) { p->visit(this); }
void ast::IdArrayDef::accept(visitor::PrettyPrinter *p) { p->visit(this); }
void ast::IdArrayRef::accept(visitor::PrettyPrinter *p) { p->visit(this); }
void ast::Literal::accept(visitor::PrettyPrinter *p) { p->visit(this); }
void ast::Read::accept(visitor::PrettyPrinter *p) { p->visit(this); }
void ast::Labelled::accept(visitor::PrettyPrinter *p) { p->visit(this); }

/* INTERPRETER */
void ast::Program::accept(visitor::Interpreter *p) { p->visit(this); }
void ast::Declarations::accept(visitor::Interpreter *p) { p->visit(this); }
void ast::Id::accept(visitor::Interpreter *p) { p->visit(this); }
void ast::IdArrayAccess::accept(visitor::Interpreter *p) { p->visit(this); }
void ast::Expr::accept(visitor::Interpreter *p) { p->visit(this); }
void ast::Code::accept(visitor::Interpreter *p) { p->visit(this); }
void ast::Statement::accept(visitor::Interpreter *p) { p->visit(this); }
void ast::Assign::accept(visitor::Interpreter *p) { p->visit(this); }
void ast::CodeBlock::accept(visitor::Interpreter *p) { p->visit(this); }
void ast::While::accept(visitor::Interpreter *p) { p->visit(this); }
void ast::If::accept(visitor::Interpreter *p) { p->visit(this); }
void ast::For::accept(visitor::Interpreter *p) { p->visit(this); }
void ast::Print::accept(visitor::Interpreter *p) { p->visit(this); }
void ast::TypedIds::accept(visitor::Interpreter *p) { p->visit(this); }
void ast::Integer::accept(visitor::Interpreter *p) { p->visit(this); }
void ast::BinOp::accept(visitor::Interpreter *p) { p->visit(this); }
void ast::NoOp::accept(visitor::Interpreter *p) { p->visit(this); }
void ast::Goto::accept(visitor::Interpreter *p) { p->visit(this); }
void ast::IdDef::accept(visitor::Interpreter *p) { p->visit(this); }
void ast::IdRef::accept(visitor::Interpreter *p) { p->visit(this); }
void ast::IdArrayDef::accept(visitor::Interpreter *p) { p->visit(this); }
void ast::IdArrayRef::accept(visitor::Interpreter *p) { p->visit(this); }
void ast::Literal::accept(visitor::Interpreter *p) { p->visit(this); }
void ast::Read::accept(visitor::Interpreter *p) { p->visit(this); }
void ast::Labelled::accept(visitor::Interpreter *p) { p->visit(this); }

/* COMPILER */
void ast::Program::accept(visitor::Compiler *p) { p->visit(this); }
void ast::Declarations::accept(visitor::Compiler *p) { p->visit(this); }
void ast::Id::accept(visitor::Compiler *p) { p->visit(this); }
void ast::IdArrayAccess::accept(visitor::Compiler *p) { p->visit(this); }
void ast::Expr::accept(visitor::Compiler *p) { p->visit(this); }
void ast::Code::accept(visitor::Compiler *p) { p->visit(this); }
void ast::Statement::accept(visitor::Compiler *p) { p->visit(this); }
void ast::Assign::accept(visitor::Compiler *p) { p->visit(this); }
void ast::CodeBlock::accept(visitor::Compiler *p) { p->visit(this); }
void ast::While::accept(visitor::Compiler *p) { p->visit(this); }
void ast::If::accept(visitor::Compiler *p) { p->visit(this); }
void ast::For::accept(visitor::Compiler *p) { p->visit(this); }
void ast::Print::accept(visitor::Compiler *p) { p->visit(this); }
void ast::TypedIds::accept(visitor::Compiler *p) { p->visit(this); }
void ast::Integer::accept(visitor::Compiler *p) { p->visit(this); }
void ast::BinOp::accept(visitor::Compiler *p) { p->visit(this); }
void ast::NoOp::accept(visitor::Compiler *p) { p->visit(this); }
void ast::Goto::accept(visitor::Compiler *p) { p->visit(this); }
void ast::IdDef::accept(visitor::Compiler *p) { p->visit(this); }
void ast::IdRef::accept(visitor::Compiler *p) { p->visit(this); }
void ast::IdArrayDef::accept(visitor::Compiler *p) { p->visit(this); }
void ast::IdArrayRef::accept(visitor::Compiler *p) { p->visit(this); }
void ast::Literal::accept(visitor::Compiler *p) { p->visit(this); }
void ast::Read::accept(visitor::Compiler *p) { p->visit(this); }
void ast::Labelled::accept(visitor::Compiler *p) { p->visit(this); }
