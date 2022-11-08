#pragma once

#include "ast.h"
#include "dtype.h"
#include "llvm/IR/Instructions.h"
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
using namespace llvm;

namespace visitor {

struct Visitor {
  virtual void visit(ast::Node *node) = 0;
  virtual void visit(ast::Program *program) = 0;
  virtual void visit(ast::Declarations *declarations) = 0;
  virtual void visit(ast::Id *id) = 0;
  virtual void visit(ast::IdArrayAccess *id_arry_access) = 0;
  virtual void visit(ast::Expr *expr) = 0;
  virtual void visit(ast::Code *code) = 0;
  virtual void visit(ast::Statement *statement) = 0;
  virtual void visit(ast::Assign *assign) = 0;
  virtual void visit(ast::While *while_block) = 0;
  virtual void visit(ast::If *if_block) = 0;
  virtual void visit(ast::For *for_block) = 0;
  virtual void visit(ast::Print *print) = 0;
  virtual void visit(ast::TypedIds *type_ids) = 0;
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

  virtual void label(std::map<std::string, ast::Code *> m) = 0;

  virtual ~Visitor() = default;
};

struct PrettyPrinter : public Visitor {
  void visit(ast::Node *node_) final;
  void visit(ast::Program *program) final;
  void visit(ast::Declarations *declarations) final;
  void visit(ast::Id *id) final;
  void visit(ast::IdArrayAccess *id_array_access) final;
  void visit(ast::Expr *expr) final;
  void visit(ast::Code *code) final;
  void visit(ast::Statement *statement) final;
  void visit(ast::Assign *assign) final;
  void visit(ast::While *while_block) final;
  void visit(ast::If *if_block) final;
  void visit(ast::For *for_block) final;
  void visit(ast::Print *print) final;
  void visit(ast::TypedIds *type_ids) final;
  void visit(ast::NoOp *no_op) final;
  void visit(ast::Goto *goto_) final;
  void visit(ast::Integer *integer) final;
  void visit(ast::IdDef *id_def) final;
  void visit(ast::IdArrayDef *id_array_def) final;
  void visit(ast::BinOp *bin_op) final;
  void visit(ast::IdRef *id_ref) final;
  void visit(ast::IdArrayRef *id_array_ref) final;
  void visit(ast::Literal *literal) final;
  void visit(ast::Read *read) final;
  void visit(ast::Labelled *labelled) final;

  void label(std::map<std::string, ast::Code *> m) final;
};

struct Interpreter : public Visitor {
private:
  std::stack<DataType> stack_;

  DataType pop_stack() {
    DataType data_type = stack_.top();
    stack_.pop();
    return data_type;
  }

public:
  std::map<std::string, DataType> env;
  ast::Program *root;
  FlatBType currentType;
  std::map<std::string, ast::Code *> table;

  void label(std::map<std::string, ast::Code *> m) final;

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
  std::map<std::string, DataType> env;
  std::stack<DataType> evalStack;
  ast::Program *root;
  FlatBType currentType;
  std::map<std::string, ast::Code *> table;

  struct {
    struct {
      std::string s;
      Value *v;
    } var;

    std::string str;
    std::vector<Value *> args;
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

    void place(std::string s_, Value *v_) {
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
  std::stack<BasicBlock *> entry;
  std::stack<BasicBlock *> exit;

  std::stack<void *> eval;

  /* Variable and Label Tables */
  std::map<std::string, Value *> v_table;
  std::map<std::string, BasicBlock *> l_table;

  Compiler();
  Value *string_to_Value(std::string s);
  Value *int_to_Value(int x);
  bool declared_before(const std::string &s);

  void label(std::map<std::string, ast::Code *> m) final;
  void visit(ast::Node *node) final;
  void visit(ast::Program *program) final;
  void visit(ast::Declarations *declarations) final;
  void visit(ast::Id *id) final;
  void visit(ast::IdArrayAccess *id_array_access) final;
  void visit(ast::Expr *expr) final;
  void visit(ast::Code *code) final;
  void visit(ast::Statement *s) final;
  void visit(ast::Assign *a) final;
  void visit(ast::While *w) final;
  void visit(ast::If *if_block) final;
  void visit(ast::For *for_block) final;
  void visit(ast::Print *print) final;
  void visit(ast::TypedIds *type_ids) final;
  void visit(ast::NoOp *no_op) final;
  void visit(ast::Goto *goto_) final;
  void visit(ast::Integer *integer) final;
  void visit(ast::IdDef *id_def) final;
  void visit(ast::IdArrayDef *id_array_def) final;
  void visit(ast::BinOp *bin_op) final;
  void visit(ast::IdRef *id_ref) final;
  void visit(ast::IdArrayRef *id_array_ref) final;
  void visit(ast::Literal *literal) final;
  void visit(ast::Read *read) final;
  void visit(ast::Labelled *labelled) final;
};

inline std::unique_ptr<Visitor> make_visitor(std::string type) {
  if (type == "-i") {
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
