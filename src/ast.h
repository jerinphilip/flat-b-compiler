#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "types.h"

enum class Op { add, sub, mul, quot, lt, gt, le, ge, eq };

// Forward declarations.
namespace visitor {
struct PrettyPrinter;
struct Interpreter;
struct Compiler;
}  // namespace visitor

namespace ast {

struct Node;
struct Program;
struct Declarations;
struct Id;
struct IdArrayAccess;
struct Expr;
struct Block;
struct Labelled;
struct Statement;
struct Assign;
struct While;
struct If;
struct For;
struct Print;
struct TypedIds;

struct Node {
  virtual void accept(visitor::PrettyPrinter *) = 0;
  virtual void accept(visitor::Interpreter *) = 0;
  virtual void accept(visitor::Compiler *) = 0;

  virtual ~Node() = default;
};

struct Program : public Node {
  Declarations *declarations;
  Block *block;
  Program(Declarations *d, Block *c) : declarations(d), block(c) {}
  void accept(visitor::PrettyPrinter *p);
  void accept(visitor::Interpreter *p);
  void accept(visitor::Compiler *p);
};

/* declarations */

struct Declarations : public Node {
  std::vector<TypedIds *> *typed_ids;
  Declarations(std::vector<TypedIds *> *v) : typed_ids(v) {}

  void accept(visitor::PrettyPrinter *p);
  void accept(visitor::Interpreter *p);
  void accept(visitor::Compiler *p);
};

/* Auxiliary types for declations and onward */
struct Expr : public Node {
  virtual void accept(visitor::PrettyPrinter *p);
  virtual void accept(visitor::Interpreter *p);
  virtual void accept(visitor::Compiler *p);
  virtual ~Expr() = default;
};

struct Id : public Expr {
  std::string name;
  Id(std::string name) : name(name) {}

  virtual void accept(visitor::PrettyPrinter *p);
  virtual void accept(visitor::Interpreter *p);
  virtual void accept(visitor::Compiler *p);

  virtual ~Id() = default;
};

struct IdArrayAccess : public Id {
  Expr *subscript;

  IdArrayAccess(std::string name, Expr *subscript)
      : Id(name), subscript(subscript) {}
  void accept(visitor::PrettyPrinter *p);
  void accept(visitor::Interpreter *p);
  void accept(visitor::Compiler *p);
};

struct IdBase : public Node {
  virtual void vnode(void **) = 0;
  virtual ~IdBase() = default;
};

struct IdRef : public IdBase {
  std::string name;
  IdRef(std::string s) : name(s) {
    // cerr << "Initializing: " << name << endl;
  }
  virtual void accept(visitor::PrettyPrinter *p);
  virtual void accept(visitor::Interpreter *p);
  virtual void accept(visitor::Compiler *p);
  virtual void vnode(void **p) { *p = new Id(name); }
  virtual ~IdRef() = default;
};

struct IdArrayRef : public IdRef {
  Expr *subscript;
  IdArrayRef(std::string s, Expr *e) : IdRef(s), subscript(e) {}
  void accept(visitor::PrettyPrinter *p);
  void accept(visitor::Interpreter *p);
  void accept(visitor::Compiler *p);
  void vnode(void **p) { *p = new IdArrayAccess(name, subscript); }
};

struct IdDef : public Node {
  std::string name;
  IdDef(std::string s) : name(s) {}
  virtual void accept(visitor::PrettyPrinter *p);
  virtual void accept(visitor::Interpreter *p);
  virtual void accept(visitor::Compiler *p);
  virtual ~IdDef() = default;
};

struct IdArrayDef : public IdDef {
  int size;
  IdArrayDef(std::string s, int sz) : IdDef(s), size(sz) {}
  void accept(visitor::PrettyPrinter *p);
  void accept(visitor::Interpreter *p);
  void accept(visitor::Compiler *p);
};

struct TypedIds : public Node {
  FlatBType type;
  std::vector<IdDef *> *id_defs;
  TypedIds(FlatBType d, std::vector<IdDef *> *v) : type(d), id_defs(v) {}
  void accept(visitor::PrettyPrinter *p);
  void accept(visitor::Interpreter *p);
  void accept(visitor::Compiler *p);
};

struct Integer : public Expr {
  int value;
  Integer(int v) : value(v) {}
  void accept(visitor::PrettyPrinter *p);
  void accept(visitor::Interpreter *p);
  void accept(visitor::Compiler *p);
};

struct BinOp : public Expr {
  Op op;
  Expr *left;
  Expr *right;

  BinOp(Op op, Expr *l, Expr *r) : op(op), left(l), right(r) {}
  void accept(visitor::PrettyPrinter *p);
  void accept(visitor::Interpreter *p);
  void accept(visitor::Compiler *p);
};

struct Statement : public Node {
  virtual void accept(visitor::PrettyPrinter *p);
  virtual void accept(visitor::Interpreter *p);
  virtual void accept(visitor::Compiler *p);
  virtual ~Statement() = default;
};

/* Statements */
struct Block : public Node {
  std::vector<Statement *> *statements;
  Block(std::vector<Statement *> *s) : statements(s) {}
  void accept(visitor::PrettyPrinter *p);
  void accept(visitor::Interpreter *p);
  void accept(visitor::Compiler *p);
};

struct Labelled : public Statement {
  std::string label;
  Block *block;
  Labelled(std::string label, Block *s) : label(label), block(s) {}
  void accept(visitor::PrettyPrinter *p);
  void accept(visitor::Interpreter *p);
  void accept(visitor::Compiler *p);
};

struct Assign : public Statement {
  IdRef *ref;
  Expr *tree;

  Assign(IdRef *ref, Expr *e) : ref(ref), tree(e) {}

  void accept(visitor::PrettyPrinter *p);
  void accept(visitor::Interpreter *p);
  void accept(visitor::Compiler *p);
};

struct While : public Statement {
  Expr *condition;
  Block *block;
  While(Expr *c, Block *b) : condition(c), block(b) {}
  void accept(visitor::PrettyPrinter *p);
  void accept(visitor::Interpreter *p);
  void accept(visitor::Compiler *p);
};

struct If : public Statement {
  Expr *condition;
  Block *block;
  Block *otherwise;
  If(Expr *c, Block *b, Block *o = NULL)
      : condition(c), block(b), otherwise(o) {}
  void accept(visitor::PrettyPrinter *p) final;
  void accept(visitor::Interpreter *p) final;
  void accept(visitor::Compiler *p) final;
};

struct For : public Statement {
  Assign *init;
  Expr *step;
  Expr *end;
  Block *body;

  For(Assign *init, Expr *delta, Expr *end, Block *b)
      : init(init), step(delta), end(end), body(b) {}
  void accept(visitor::PrettyPrinter *p) final;
  void accept(visitor::Interpreter *p) final;
  void accept(visitor::Compiler *p) final;
};

struct Goto : public Statement {
  Expr *condition;
  std::string label;
  Goto(std::string label, Expr *e = NULL) : label(label), condition(e) {}
  void accept(visitor::PrettyPrinter *p);
  void accept(visitor::Interpreter *p);
  void accept(visitor::Compiler *p);
};

struct Print : public Statement {
  std::vector<ast::Expr *> *args;
  bool newline;

  Print(std::vector<ast::Expr *> *args, bool newline)
      : args(args), newline(newline) {}

  void accept(visitor::PrettyPrinter *p);
  void accept(visitor::Interpreter *p);
  void accept(visitor::Compiler *p);
};

struct NoOp : public Statement {
  NoOp() {}
  void accept(visitor::PrettyPrinter *p);
  void accept(visitor::Interpreter *p);
  void accept(visitor::Compiler *p);
};

struct Literal : public Expr {
  std::string value;
  Literal(std::string s) { value = s.substr(1, s.size() - 2); }
  void accept(visitor::PrettyPrinter *p);
  void accept(visitor::Interpreter *p);
  void accept(visitor::Compiler *p);
};

struct Read : public Statement {
  IdRef *var;

  Read(IdRef *var) : var(var) {}
  void accept(visitor::PrettyPrinter *p) final;
  void accept(visitor::Interpreter *p) final;
  void accept(visitor::Compiler *p) final;
};
}  // namespace ast
