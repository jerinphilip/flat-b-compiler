#pragma once
#include "visitor.h"

namespace visitor {

class EvalStack : public std::stack<Value *> {
 public:
  Value *consume() {
    Value *tmp = top();
    pop();
    return tmp;
  }
};

// Represents printf/scanf format-args.
struct FormatArgs {
  struct {
    std::string specifier;
    Value *value;
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

  void append(std::string specifier, Value *value) {
    if (flag) {
      var.specifier = specifier;
      var.value = value;
    }
  }

  void update() {
    str += var.specifier;
    args.push_back(var.value);
  }
};

struct Compiler : public Visitor {
 public:
  Compiler();

  void label(std::map<std::string, ast::Block *> m) final;
  void visit(ast::Node *node) final;
  void visit(ast::Program *program) final;
  void visit(ast::Declarations *declarations) final;
  void visit(ast::Id *id) final;
  void visit(ast::IdArrayAccess *id_array_access) final;
  void visit(ast::Expr *expr) final;
  void visit(ast::Block *code) final;
  void visit(ast::Statement *statement) final;
  void visit(ast::Assign *assign) final;
  void visit(ast::While *while_block) final;
  void visit(ast::If *if_block) final;
  void visit(ast::For *for_block) final;
  void visit(ast::Print *print) final;
  void visit(ast::TypedIds *typed_ids) final;
  void visit(ast::NoOp *no_op) final;
  void visit(ast::Goto *goto_) final;
  void visit(ast::Integer *integer) final;
  void visit(ast::IdDef *id_def) final;
  void visit(ast::IdArrayDef *id_array_def) final;
  void visit(ast::BinOp *binOp) final;
  void visit(ast::IdRef *id_ref) final;
  void visit(ast::IdArrayRef *id_array_ref) final;
  void visit(ast::Literal *literal) final;
  void visit(ast::Read *read) final;
  void visit(ast::Labelled *labelled) final;

 private:
  FormatArgs format_;
  LLVMContext context_;
  Module module_;

  ast::Program *root;
  std::map<std::string, ast::Block *> table;
  std::map<std::string, BasicBlock *> label_table;
  std::map<std::string, Value *> value_table;
  std::map<std::string, size_t> sizes_table;
  std::stack<BasicBlock *> entry;
  std::stack<BasicBlock *> exit;
  BasicBlock *main_block;
  EvalStack eval_;

  Function *main_fn;
  Function *printf, *scanf;

  /* Variable and Label Tables */

  Value *string_to_Value(const std::string &s);
  Value *int_to_Value(int x);
  bool declared_before(const std::string &identifier);
};
}  // namespace visitor
