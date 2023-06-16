#pragma once
#include <stack>

#include "visitor.h"

namespace visitor {

struct Interpreter : public Visitor {
 private:
  std::stack<FlatBValue> stack_;
  std::map<std::string, FlatBValue> env_;
  ast::Program *root_;
  FlatBType current_type_;
  std::map<std::string, ast::Code *> table_;

  FlatBValue pop_stack() {
    FlatBValue data_type = stack_.top();
    stack_.pop();
    return data_type;
  }

 public:
  void label(std::map<std::string, ast::Code *> m) final;

  void visit(ast::Node *node) final;
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
  void visit(ast::TypedIds *typed_ids) final;
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
}