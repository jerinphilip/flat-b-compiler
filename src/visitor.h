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
struct pprinter {
  void visit(ast::node *node_);
  void visit(ast::program *program);
  void visit(ast::declarations *declarations);
  void visit(ast::id *id);
  void visit(ast::id_ *id_);
  void visit(ast::expr *e);
  void visit(ast::code *c);
  void visit(ast::statement *s);
  void visit(ast::assign *a);
  void visit(ast::while_ *w);
  void visit(ast::if_ *ib);
  void visit(ast::for_ *fb);
  void visit(ast::print *print);
  void visit(ast::typed_ids *t_ids);
  void visit(ast::no_op *no_op);
  void visit(ast::goto_ *goto_);
  void visit(ast::integer *integer);
  void visit(ast::id_def *id_def);
  void visit(ast::idA_def *idA_def);
  void visit(ast::binOp *binOp);
  void visit(ast::id_ref *id_ref);
  void visit(ast::idA_ref *idA_ref);
  void visit(ast::literal *literal);
  void visit(ast::read *read);
  void visit(ast::labelled *labelled);
};

struct interpreter {
  map<string, dataType> env;
  stack<dataType> evalStack;
  ast::program *root;
  type currentType;
  map<string, ast::code *> table;

  void label(map<string, ast::code *> m) {
    table = m;
    /*
    cerr << "labels: ";
    for(auto p: table){
        cerr << p.first << " ";
    }
    cerr << endl;
    */
  }

  void visit(ast::node *node_);
  void visit(ast::program *program);
  void visit(ast::declarations *declarations);
  void visit(ast::id *id);
  void visit(ast::id_ *id_);
  void visit(ast::expr *e);
  void visit(ast::code *c);
  void visit(ast::statement *s);
  void visit(ast::assign *a);
  void visit(ast::while_ *w);
  void visit(ast::if_ *ib);
  void visit(ast::for_ *fb);
  void visit(ast::print *print);
  void visit(ast::typed_ids *t_ids);
  void visit(ast::no_op *no_op);
  void visit(ast::goto_ *goto_);
  void visit(ast::integer *integer);
  void visit(ast::id_def *id_def);
  void visit(ast::idA_def *idA_def);
  void visit(ast::binOp *binOp);
  void visit(ast::id_ref *id_ref);
  void visit(ast::idA_ref *idA_ref);
  void visit(ast::literal *literal);
  void visit(ast::read *read);
  void visit(ast::labelled *labelled);
};

struct compiler {
  map<string, dataType> env;
  stack<dataType> evalStack;
  ast::program *root;
  type currentType;
  map<string, ast::code *> table;

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

  void label(map<string, ast::code *> m) { table = m; }

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

  void visit(ast::node *node_);
  void visit(ast::program *program);
  void visit(ast::declarations *declarations);
  void visit(ast::id *id);
  void visit(ast::id_ *id_);
  void visit(ast::expr *e);
  void visit(ast::code *c);
  void visit(ast::statement *s);
  void visit(ast::assign *a);
  void visit(ast::while_ *w);
  void visit(ast::if_ *ib);
  void visit(ast::for_ *fb);
  void visit(ast::print *print);
  void visit(ast::typed_ids *t_ids);
  void visit(ast::no_op *no_op);
  void visit(ast::goto_ *goto_);
  void visit(ast::integer *integer);
  void visit(ast::id_def *id_def);
  void visit(ast::idA_def *idA_def);
  void visit(ast::binOp *binOp);
  void visit(ast::id_ref *id_ref);
  void visit(ast::idA_ref *idA_ref);
  void visit(ast::literal *literal);
  void visit(ast::read *read);
  void visit(ast::labelled *labelled);
};
} // namespace visitor

#endif
