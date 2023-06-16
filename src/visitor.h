#pragma once

#include <llvm/ADT/APFloat.h>
#include <llvm/ADT/STLExtras.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>
#include <llvm/IR/Verifier.h>

#include <map>
#include <memory>
#include <stack>

#include "ast.h"
#include "llvm/IR/Instructions.h"
#include "types.h"
using namespace llvm;

namespace visitor {

struct Visitor {
  virtual void visit(ast::Node *node) = 0;
  virtual void visit(ast::Program *program) = 0;
  virtual void visit(ast::Declarations *declarations) = 0;
  virtual void visit(ast::Id *id) = 0;
  virtual void visit(ast::IdArrayAccess *id_arry_access) = 0;
  virtual void visit(ast::Expr *expr) = 0;
  virtual void visit(ast::Block *code) = 0;
  virtual void visit(ast::Statement *statement) = 0;
  virtual void visit(ast::Assign *assign) = 0;
  virtual void visit(ast::While *while_block) = 0;
  virtual void visit(ast::If *if_block) = 0;
  virtual void visit(ast::For *for_block) = 0;
  virtual void visit(ast::Print *print) = 0;
  virtual void visit(ast::TypedIds *typed_ids) = 0;
  virtual void visit(ast::NoOp *no_op) = 0;
  virtual void visit(ast::Goto *goto_) = 0;
  virtual void visit(ast::Integer *integer) = 0;
  virtual void visit(ast::IdDef *id_def) = 0;
  virtual void visit(ast::IdArrayDef *id_array_def) = 0;
  virtual void visit(ast::BinOp *bin_op) = 0;
  virtual void visit(ast::IdRef *id_ref) = 0;
  virtual void visit(ast::IdArrayRef *id_array_ref) = 0;
  virtual void visit(ast::Literal *literal) = 0;
  virtual void visit(ast::Read *read) = 0;
  virtual void visit(ast::Labelled *labelled) = 0;

  virtual void label(std::map<std::string, ast::Block *> m) = 0;

  virtual ~Visitor() = default;
};

std::unique_ptr<Visitor> make_visitor(std::string type);

}  // namespace visitor
