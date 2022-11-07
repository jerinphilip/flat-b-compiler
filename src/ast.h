#ifndef AST_H
#define AST_H

#include <iostream>
#include <string>
#include <vector>
using namespace std;

enum FlatBType {
  Int,
  Bool,
  Char,
  CharArray,
  IntArray,
  Pointer,
};

enum class Op { add, sub, mul, quot, lt, gt, le, ge, eq };

namespace visitor {
struct pprinter;
struct interpreter;
struct compiler;
} // namespace visitor

namespace ast {

struct Node;
struct Program;
struct Declarations;
struct Id;
struct IdArrayAccess;
struct Expr;
struct Code;
struct Labelled;
struct Statement;
struct Assign;
struct Cblock;
struct While;
struct If;
struct For;
struct Print;
struct TypedIds;

struct Node {

  virtual void accept(visitor::pprinter *) = 0;
  virtual void accept(visitor::interpreter *) = 0;
  virtual void accept(visitor::compiler *) = 0;

  virtual ~Node() = default;
};

struct Program : public Node {
  Declarations *decl;
  Code *block;
  Program(Declarations *d, Code *c) : decl(d), block(c) {}
  void accept(visitor::pprinter *p);
  void accept(visitor::interpreter *p);
  void accept(visitor::compiler *p);
};

/* declarations */

struct Declarations : public Node {
  vector<TypedIds *> *ds;
  Declarations(vector<TypedIds *> *v) : ds(v) {}

  void accept(visitor::pprinter *p);
  void accept(visitor::interpreter *p);
  void accept(visitor::compiler *p);
};

/* Auxiliary types for declations and onward */
struct Expr : public Node {
  virtual void accept(visitor::pprinter *p);
  virtual void accept(visitor::interpreter *p);
  virtual void accept(visitor::compiler *p);
  virtual ~Expr() = default;
};

struct Id : public Expr {
  string name;
  Id(string s) : name(s) {
    // cerr << "Initializing: " << name << endl;
  }

  virtual void accept(visitor::pprinter *p);
  virtual void accept(visitor::interpreter *p);
  virtual void accept(visitor::compiler *p);

  virtual ~Id() = default;
};

struct IdArrayAccess : public Id {
  Expr *subscript;
  IdArrayAccess(string s, Expr *e) : Id(s), subscript(e) {
    // cerr << "Initializing: " << s << endl;
    // cerr << "Other: "<< name << endl;
  }
  void accept(visitor::pprinter *p);
  void accept(visitor::interpreter *p);
  void accept(visitor::compiler *p);
};

struct IdBase : public Node {
  virtual void vnode(void **) = 0;
  virtual ~IdBase() = default;
};

struct IdRef : public IdBase {
  string name;
  IdRef(string s) : name(s) {
    // cerr << "Initializing: " << name << endl;
  }
  virtual void accept(visitor::pprinter *p);
  virtual void accept(visitor::interpreter *p);
  virtual void accept(visitor::compiler *p);
  virtual void vnode(void **p) { *p = new Id(name); }
  virtual ~IdRef() = default;
};

struct IdArrayRef : public IdRef {
  Expr *subscript;
  IdArrayRef(string s, Expr *e) : IdRef(s), subscript(e) {}
  void accept(visitor::pprinter *p);
  void accept(visitor::interpreter *p);
  void accept(visitor::compiler *p);
  void vnode(void **p) { *p = new IdArrayAccess(name, subscript); }
};

struct IdDef : public Node {
  string name;
  IdDef(string s) : name(s) {}
  virtual void accept(visitor::pprinter *p);
  virtual void accept(visitor::interpreter *p);
  virtual void accept(visitor::compiler *p);
  virtual ~IdDef() = default;
};

struct IdArrayDef : public IdDef {
  int size;
  IdArrayDef(string s, int sz) : IdDef(s), size(sz) {}
  void accept(visitor::pprinter *p);
  void accept(visitor::interpreter *p);
  void accept(visitor::compiler *p);
};

struct TypedIds : public Node {
  FlatBType dtype;
  vector<IdDef *> *t_ids;
  TypedIds(FlatBType d, vector<IdDef *> *v) : dtype(d), t_ids(v) {}
  void accept(visitor::pprinter *p);
  void accept(visitor::interpreter *p);
  void accept(visitor::compiler *p);
};

struct Integer : public Expr {
  int value;
  Integer(int v) : value(v) {}
  void accept(visitor::pprinter *p);
  void accept(visitor::interpreter *p);
  void accept(visitor::compiler *p);
};

struct BinOp : public Expr {
  Op op;
  Expr *left;
  Expr *right;

  BinOp(Op op, Expr *l, Expr *r) : op(op), left(l), right(r) {}
  void accept(visitor::pprinter *p);
  void accept(visitor::interpreter *p);
  void accept(visitor::compiler *p);
};

struct Statement : public Node {
  virtual void accept(visitor::pprinter *p);
  virtual void accept(visitor::interpreter *p);
  virtual void accept(visitor::compiler *p);
  virtual ~Statement() = default;
};

/* Statements */
struct Code : public Statement {
  vector<Statement *> *statements;
  Code(vector<Statement *> *s) : statements(s) {}
  void accept(visitor::pprinter *p);
  void accept(visitor::interpreter *p);
  void accept(visitor::compiler *p);
};

struct Labelled : public Statement {
  string label;
  Code *block;
  Labelled(string label, Code *s) : label(label), block(s) {}
  void accept(visitor::pprinter *p);
  void accept(visitor::interpreter *p);
  void accept(visitor::compiler *p);
};

struct Assign : public Statement {
  IdRef *ref;
  Expr *tree;

  Assign(IdRef *ref, Expr *e) : ref(ref), tree(e) {}

  void accept(visitor::pprinter *p);
  void accept(visitor::interpreter *p);
  void accept(visitor::compiler *p);
};

struct CodeBlock : public Statement {
  Expr *cond;
  Code *block;
  CodeBlock(Expr *c, Code *b) : cond(c), block(b) {}
  virtual void accept(visitor::pprinter *p);
  virtual void accept(visitor::interpreter *p);
  virtual void accept(visitor::compiler *p);
  virtual ~CodeBlock() = default;
};

struct While : public CodeBlock {
  While(Expr *c, Code *b) : CodeBlock(c, b) {}
  void accept(visitor::pprinter *p);
  void accept(visitor::interpreter *p);
  void accept(visitor::compiler *p);
};

struct If : public CodeBlock {
  Code *otherwise;
  If(Expr *c, Code *b, Code *o = NULL) : CodeBlock(c, b), otherwise(o) {}
  void accept(visitor::pprinter *p) final;
  void accept(visitor::interpreter *p) final;
  void accept(visitor::compiler *p) final;
};

struct For : public Statement {
  Assign *init;
  /*
  id_ref *var;
  Expr *start;
  */
  Expr *step;
  Expr *end;
  Code *block;

  For(Assign *init,
      /*id_ref *i, Expr *init,*/
      Expr *delta, Expr *end, Code *b)
      : /*var(i), start(init), */
        init(init), step(delta), end(end), block(b) {}
  void accept(visitor::pprinter *p) final;
  void accept(visitor::interpreter *p) final;
  void accept(visitor::compiler *p) final;
};

struct Goto : public Statement {
  Expr *cond;
  string label;
  Goto(string label, Expr *e = NULL) : label(label), cond(e) {}
  void accept(visitor::pprinter *p);
  void accept(visitor::interpreter *p);
  void accept(visitor::compiler *p);
};

struct Print : public Statement {
  vector<ast::Expr *> *args;
  bool newline;

  Print(vector<ast::Expr *> *args, bool newline)
      : args(args), newline(newline) {}

  void accept(visitor::pprinter *p);
  void accept(visitor::interpreter *p);
  void accept(visitor::compiler *p);
};

struct NoOp : public Statement {
  NoOp() {}
  void accept(visitor::pprinter *p);
  void accept(visitor::interpreter *p);
  void accept(visitor::compiler *p);
};

struct Literal : public Expr {
  string value;
  Literal(string s) { value = s.substr(1, s.size() - 2); }
  void accept(visitor::pprinter *p);
  void accept(visitor::interpreter *p);
  void accept(visitor::compiler *p);
};

struct Read : public Statement {
  IdRef *var;

  Read(IdRef *var) : var(var) {}
  void accept(visitor::pprinter *p) final;
  void accept(visitor::interpreter *p) final;
  void accept(visitor::compiler *p) final;
};
} // namespace ast

#endif
