#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "types.h"

enum class Op { add, sub, mul, quot, lt, gt, le, ge, eq };

// Forward declarations.
namespace visitor {
struct Visitor;
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
  virtual void accept(visitor::Visitor *) = 0;

  virtual ~Node() = default;
};

struct Program : public Node {
  Declarations *declarations;
  Block *block;
  Program(Declarations *d, Block *c) : declarations(d), block(c) {}
  void accept(visitor::Visitor *p);
};

/* declarations */

struct Declarations : public Node {
  std::vector<TypedIds *> *typed_ids;
  Declarations(std::vector<TypedIds *> *v) : typed_ids(v) {}

  void accept(visitor::Visitor *p);
};

/* Auxiliary types for declations and onward */
struct Expr : public Node {
  virtual void accept(visitor::Visitor *p);
  virtual ~Expr() = default;
};

struct Id : public Expr {
  std::string name;
  Id(std::string name) : name(name) {}

  virtual void accept(visitor::Visitor *p);

  virtual ~Id() = default;
};

struct IdArrayAccess : public Id {
  Expr *subscript;

  IdArrayAccess(std::string name, Expr *subscript)
      : Id(name), subscript(subscript) {}
  void accept(visitor::Visitor *p);
};

struct IdRef : public Node {
  std::string name;
  IdRef(std::string s) : name(s) {
    // cerr << "Initializing: " << name << endl;
  }
  virtual void accept(visitor::Visitor *p);
  Id *id() { return new Id(name); }
  virtual ~IdRef() = default;
};

struct IdArrayRef : public IdRef {
  Expr *subscript;
  IdArrayRef(std::string s, Expr *e) : IdRef(s), subscript(e) {}
  void accept(visitor::Visitor *p);
};

struct IdDef : public Node {
  std::string name;
  IdDef(std::string s) : name(s) {}
  virtual void accept(visitor::Visitor *p);
  virtual ~IdDef() = default;
};

struct IdArrayDef : public IdDef {
  int size;
  IdArrayDef(std::string s, int sz) : IdDef(s), size(sz) {}
  void accept(visitor::Visitor *p);
};

struct TypedIds : public Node {
  FlatBType type;
  std::vector<IdDef *> *id_defs;
  TypedIds(FlatBType d, std::vector<IdDef *> *v) : type(d), id_defs(v) {}
  void accept(visitor::Visitor *p);
};

struct Integer : public Expr {
  int value;
  Integer(int v) : value(v) {}
  void accept(visitor::Visitor *p);
};

struct BinOp : public Expr {
  Op op;
  Expr *left;
  Expr *right;

  BinOp(Op op, Expr *l, Expr *r) : op(op), left(l), right(r) {}
  void accept(visitor::Visitor *p);
};

struct Statement : public Node {
  virtual void accept(visitor::Visitor *p);
  virtual ~Statement() = default;
};

/* Statements */
struct Block : public Node {
  std::vector<Statement *> *statements;
  Block(std::vector<Statement *> *s) : statements(s) {}
  void accept(visitor::Visitor *p);
};

struct Labelled : public Statement {
  std::string label;
  Block *block;
  Labelled(std::string label, Block *s) : label(label), block(s) {}
  void accept(visitor::Visitor *p);
};

struct Assign : public Statement {
  IdRef *ref;
  Expr *tree;

  Assign(IdRef *ref, Expr *e) : ref(ref), tree(e) {}

  void accept(visitor::Visitor *p);
};

struct While : public Statement {
  Expr *condition;
  Block *block;
  While(Expr *c, Block *b) : condition(c), block(b) {}
  void accept(visitor::Visitor *p);
};

struct If : public Statement {
  Expr *condition;
  Block *block;
  Block *otherwise;
  If(Expr *c, Block *b, Block *o = NULL)
      : condition(c), block(b), otherwise(o) {}
  void accept(visitor::Visitor *p) final;
};

struct For : public Statement {
  Assign *init;
  Expr *step;
  Expr *end;
  Block *body;

  For(Assign *init, Expr *delta, Expr *end, Block *b)
      : init(init), step(delta), end(end), body(b) {}
  void accept(visitor::Visitor *p) final;
};

struct Goto : public Statement {
  Expr *condition;
  std::string label;
  Goto(std::string label, Expr *e = NULL) : label(label), condition(e) {}
  void accept(visitor::Visitor *p);
};

struct Print : public Statement {
  std::vector<ast::Expr *> *args;
  bool newline;

  Print(std::vector<ast::Expr *> *args, bool newline)
      : args(args), newline(newline) {}

  void accept(visitor::Visitor *p);
};

struct NoOp : public Statement {
  NoOp() {}
  void accept(visitor::Visitor *p);
};

struct Literal : public Expr {
  std::string value;
  Literal(std::string s) { value = s.substr(1, s.size() - 2); }
  void accept(visitor::Visitor *p);
};

struct Read : public Statement {
  IdRef *var;

  Read(IdRef *var) : var(var) {}
  void accept(visitor::Visitor *p) final;
};
}  // namespace ast
