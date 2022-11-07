#ifndef PRINTER_H
#define PRINTER_H

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

struct Visitor {};

struct pprinter : public Visitor {
  void visit(ast::Node *node_);
  void visit(ast::Program *program);
  void visit(ast::Declarations *declarations);
  void visit(ast::Id *id);
  void visit(ast::IdArrayAccess *id_);
  void visit(ast::Expr *expr);
  void visit(ast::Code *code);
  void visit(ast::Statement *statement);
  void visit(ast::Assign *a);
  void visit(ast::While *w);
  void visit(ast::If *ib);
  void visit(ast::For *fb);
  void visit(ast::Print *print);
  void visit(ast::TypedIds *t_ids);
  void visit(ast::NoOp *no_op);
  void visit(ast::Goto *goto_);
  void visit(ast::Integer *integer);
  void visit(ast::IdDef *id_def);
  void visit(ast::IdArrayDef *idA_def);
  void visit(ast::BinOp *binOp);
  void visit(ast::IdRef *id_ref);
  void visit(ast::IdArrayRef *idA_ref);
  void visit(ast::Literal *literal);
  void visit(ast::Read *read);
  void visit(ast::Labelled *labelled);
};

struct interpreter : public Visitor {
  map<string, dataType> env;
  stack<dataType> evalStack;
  ast::Program *root;
  type currentType;
  map<string, ast::Code *> table;

  void label(map<string, ast::Code *> m) {
    table = m;
    /*
    cerr << "labels: ";
    for(auto p: table){
        cerr << p.first << " ";
    }
    cerr << endl;
    */
  }

  void visit(ast::Node *node_);
  void visit(ast::Program *program);
  void visit(ast::Declarations *declarations);
  void visit(ast::Id *id);
  void visit(ast::IdArrayAccess *id_);
  void visit(ast::Expr *e);
  void visit(ast::Code *c);
  void visit(ast::Statement *s);
  void visit(ast::Assign *a);
  void visit(ast::While *w);
  void visit(ast::If *ib);
  void visit(ast::For *fb);
  void visit(ast::Print *print);
  void visit(ast::TypedIds *t_ids);
  void visit(ast::NoOp *no_op);
  void visit(ast::Goto *goto_);
  void visit(ast::Integer *integer);
  void visit(ast::IdDef *id_def);
  void visit(ast::IdArrayDef *idA_def);
  void visit(ast::BinOp *binOp);
  void visit(ast::IdRef *id_ref);
  void visit(ast::IdArrayRef *idA_ref);
  void visit(ast::Literal *literal);
  void visit(ast::Read *read);
  void visit(ast::Labelled *labelled);
};

struct compiler : public Visitor {
  map<string, dataType> env;
  stack<dataType> evalStack;
  ast::Program *root;
  type currentType;
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

  void label(map<string, ast::Code *> m) { table = m; }

  compiler() {
    module = new Module("main", context);
    module->setTargetTriple("x86_64-pc-linux-gnu");
    main_fn =
        Function::Create(FunctionType::get(Type::getVoidTy(context), false),
                         GlobalValue::ExternalLinkage, "main", module);
    printf =
        Function::Create(FunctionType::get(Type::getInt64Ty(context), true),
                         GlobalValue::ExternalLinkage, "printf", module);
    scanf = Function::Create(FunctionType::get(Type::getInt64Ty(context), true),
                             GlobalValue::ExternalLinkage, "scanf", module);
  }

  Value *string_to_Value(string s) {
    GlobalVariable *var = new GlobalVariable(
        *module, ArrayType::get(IntegerType::get(context, 8), (s.size() + 1)),
        true, GlobalVariable::InternalLinkage, NULL, "literal");

    var->setInitializer(ConstantDataArray::getString(context, s, true));
    return var;
  }

  Value *int_to_Value(int x) {
    GlobalVariable *var =
        new GlobalVariable(*module, Type::getInt64Ty(context), false,
                           GlobalValue::CommonLinkage, NULL, "integer");
    var->setInitializer(ConstantInt::get(context, APInt(64, x, true)));
    return var;
  }

  bool declared_before(const string &s) {
    return v_table.find(s) != v_table.end();
  }

  void visit(ast::Node *node_);
  void visit(ast::Program *program);
  void visit(ast::Declarations *declarations);
  void visit(ast::Id *id);
  void visit(ast::IdArrayAccess *id_);
  void visit(ast::Expr *e);
  void visit(ast::Code *c);
  void visit(ast::Statement *s);
  void visit(ast::Assign *a);
  void visit(ast::While *w);
  void visit(ast::If *ib);
  void visit(ast::For *fb);
  void visit(ast::Print *print);
  void visit(ast::TypedIds *t_ids);
  void visit(ast::NoOp *no_op);
  void visit(ast::Goto *goto_);
  void visit(ast::Integer *integer);
  void visit(ast::IdDef *id_def);
  void visit(ast::IdArrayDef *idA_def);
  void visit(ast::BinOp *binOp);
  void visit(ast::IdRef *id_ref);
  void visit(ast::IdArrayRef *idA_ref);
  void visit(ast::Literal *literal);
  void visit(ast::Read *read);
  void visit(ast::Labelled *labelled);
};

inline std::unique_ptr<Visitor> make_visitor(std::string type) {
  if (type == "interpreter") {
    return std::make_unique<visitor::interpreter>();
  }
  if (type == "compiler") {
    return std::make_unique<visitor::compiler>();
  }
  std::abort();
  return nullptr;
}

} // namespace visitor
  //

#endif
