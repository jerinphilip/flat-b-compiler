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

struct Compiler : public Visitor {
  ast::Program *root;
  FlatBType currentType;
  std::map<std::string, ast::Block *> table;

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

  EvalStack eval;

  /* Variable and Label Tables */
  std::map<std::string, Value *> value_table;
  std::map<std::string, size_t> sizes_table;
  std::map<std::string, BasicBlock *> label_table;

  Compiler();
  Value *string_to_Value(const std::string &s);
  Value *int_to_Value(int x);
  bool declared_before(const std::string &s);

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
};
}  // namespace visitor
