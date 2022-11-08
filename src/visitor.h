#pragma once

#include "ast.h"
#include "dtype.h"
#include "llvm/IR/Instructions.h"
#include <bits/stdc++.h>
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
using namespace llvm;
using namespace std;

namespace visitor {

struct Visitor {
  virtual void visit(ast::Node *node_) = 0;
  virtual void visit(ast::Program *program) = 0;
  virtual void visit(ast::Declarations *declarations) = 0;
  virtual void visit(ast::Id *id) = 0;
  virtual void visit(ast::IdArrayAccess *id_) = 0;
  virtual void visit(ast::Expr *expr) = 0;
  virtual void visit(ast::Code *code) = 0;
  virtual void visit(ast::Statement *statement) = 0;
  virtual void visit(ast::Assign *a) = 0;
  virtual void visit(ast::While *w) = 0;
  virtual void visit(ast::If *ib) = 0;
  virtual void visit(ast::For *fb) = 0;
  virtual void visit(ast::Print *print) = 0;
  virtual void visit(ast::TypedIds *t_ids) = 0;
  virtual void visit(ast::NoOp *no_op) = 0;
  virtual void visit(ast::Goto *goto_) = 0;
  virtual void visit(ast::Integer *integer) = 0;
  virtual void visit(ast::IdDef *id_def) = 0;
  virtual void visit(ast::IdArrayDef *idA_def) = 0;
  virtual void visit(ast::BinOp *binOp) = 0;
  virtual void visit(ast::IdRef *id_ref) = 0;
  virtual void visit(ast::IdArrayRef *idA_ref) = 0;
  virtual void visit(ast::Literal *literal) = 0;
  virtual void visit(ast::Read *read) = 0;
  virtual void visit(ast::Labelled *labelled) = 0;

  virtual void label(map<string, ast::Code *> m) = 0;

  virtual ~Visitor() = default;
};

struct PrettyPrinter : public Visitor {
  void visit(ast::Node *node_) final;
  void visit(ast::Program *program) final;
  void visit(ast::Declarations *declarations) final;
  void visit(ast::Id *id) final;
  void visit(ast::IdArrayAccess *id_) final;
  void visit(ast::Expr *expr) final;
  void visit(ast::Code *code) final;
  void visit(ast::Statement *statement) final;
  void visit(ast::Assign *a) final;
  void visit(ast::While *w) final;
  void visit(ast::If *ib) final;
  void visit(ast::For *fb) final;
  void visit(ast::Print *print) final;
  void visit(ast::TypedIds *t_ids) final;
  void visit(ast::NoOp *no_op) final;
  void visit(ast::Goto *goto_) final;
  void visit(ast::Integer *integer) final;
  void visit(ast::IdDef *id_def) final;
  void visit(ast::IdArrayDef *idA_def) final;
  void visit(ast::BinOp *binOp) final;
  void visit(ast::IdRef *id_ref) final;
  void visit(ast::IdArrayRef *idA_ref) final;
  void visit(ast::Literal *literal) final;
  void visit(ast::Read *read) final;
  void visit(ast::Labelled *labelled) final;

  void label(map<string, ast::Code *> m) final;
};

struct Interpreter : public Visitor {
  map<string, DataType> env;
  stack<DataType> evalStack;
  ast::Program *root;
  FlatBType currentType;
  map<string, ast::Code *> table;

  void label(map<string, ast::Code *> m) final;

  void visit(ast::Node *node_) final;
  void visit(ast::Program *program) final;
  void visit(ast::Declarations *declarations) final;
  void visit(ast::Id *id) final;
  void visit(ast::IdArrayAccess *id_) final;
  void visit(ast::Expr *e) final;
  void visit(ast::Code *c) final;
  void visit(ast::Statement *s) final;
  void visit(ast::Assign *a) final;
  void visit(ast::While *w) final;
  void visit(ast::If *ib) final;
  void visit(ast::For *fb) final;
  void visit(ast::Print *print) final;
  void visit(ast::TypedIds *t_ids) final;
  void visit(ast::NoOp *no_op) final;
  void visit(ast::Goto *goto_) final;
  void visit(ast::Integer *integer) final;
  void visit(ast::IdDef *id_def) final;
  void visit(ast::IdArrayDef *idA_def) final;
  void visit(ast::BinOp *binOp) final;
  void visit(ast::IdRef *id_ref) final;
  void visit(ast::IdArrayRef *idA_ref) final;
  void visit(ast::Literal *literal) final;
  void visit(ast::Read *read) final;
  void visit(ast::Labelled *labelled) final;
};

struct Compiler : public Visitor {
  map<string, DataType> env;
  stack<DataType> evalStack;
  ast::Program *root;
  FlatBType currentType;
  map<string, ast::Code *> table;

  struct {
    struct {
      string s;
      Value *v;
    } var;

    string str;
    vector<Value *> args;
    bool flag;

    void init() {
      flag = true;
      str = "";
      args.clear();
    }

    void finish() {
      flag = false;
      str = "";
      args.clear();
    }

    void place(string s_, Value *v_) {
      if (flag) {
        var.s = s_;
        var.v = v_;
      }
    }

    void update() {
      str += var.s;
      args.push_back(var.v);
    }

  } format;

  LLVMContext context;
  Module *module;
  BasicBlock *main_block;

  Function *main_fn;
  Function *printf, *scanf;

  /* To circumvent void return type, stupid Visitor Pattern */
  stack<BasicBlock *> entry;
  stack<BasicBlock *> exit;

  stack<void *> eval;

  /* Variable and Label Tables */
  map<string, Value *> v_table;
  map<string, BasicBlock *> l_table;
  void label(map<string, ast::Code *> m) final;
  Compiler();
  Value *string_to_Value(string s);

  Value *int_to_Value(int x);

  bool declared_before(const string &s);

  void visit(ast::Node *node_) final;
  void visit(ast::Program *program) final;
  void visit(ast::Declarations *declarations) final;
  void visit(ast::Id *id) final;
  void visit(ast::IdArrayAccess *id_) final;
  void visit(ast::Expr *e) final;
  void visit(ast::Code *c) final;
  void visit(ast::Statement *s) final;
  void visit(ast::Assign *a) final;
  void visit(ast::While *w) final;
  void visit(ast::If *ib) final;
  void visit(ast::For *fb) final;
  void visit(ast::Print *print) final;
  void visit(ast::TypedIds *t_ids) final;
  void visit(ast::NoOp *no_op) final;
  void visit(ast::Goto *goto_) final;
  void visit(ast::Integer *integer) final;
  void visit(ast::IdDef *id_def) final;
  void visit(ast::IdArrayDef *idA_def) final;
  void visit(ast::BinOp *binOp) final;
  void visit(ast::IdRef *id_ref) final;
  void visit(ast::IdArrayRef *idA_ref) final;
  void visit(ast::Literal *literal) final;
  void visit(ast::Read *read) final;
  void visit(ast::Labelled *labelled) final;
};

inline std::unique_ptr<Visitor> make_visitor(std::string type) {
  if (type == "-r") {
    return std::make_unique<visitor::Interpreter>();
  }
  if (type == "-c") {
    return std::make_unique<visitor::Compiler>();
  }

  if (type == "-f") {
    return std::make_unique<visitor::PrettyPrinter>();
  }

  std::abort();
  return nullptr;
}

} // namespace visitor
