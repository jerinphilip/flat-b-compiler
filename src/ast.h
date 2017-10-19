#ifndef AST_H
#define AST_H

#include <vector>
#include <string>
using namespace std;

enum type {
    Int
};

enum opr {
    add,
    sub,
    mul,
    quot,
    lt,
    gt,
    le,
    ge,
    eq
};

namespace visitor {
    struct pprinter;
    struct interpreter;
}

namespace ast {

    struct node;
    struct program;
    struct declarations;
    struct id;
    struct id_;
    struct expr;
    struct code;
    struct statement;
    struct assign;
    struct cblock;
    struct while_;
    struct if_;
    struct for_;
    struct print;
    struct typed_ids;


    struct node {
        /* Base struct */

        virtual void accept(visitor::pprinter *) = 0;
        virtual void accept(visitor::interpreter *) = 0;
    };

    struct program : public node {
        declarations* decl;
        code* block;
        program(declarations *d, code* c): decl(d), block(c){}
        void accept(visitor::pprinter *p);
        void accept(visitor::interpreter *p);
    };

    /* declarations */

    struct declarations : public node {
        vector<typed_ids*> *ds;
        declarations(vector<typed_ids*> *v): ds(v) {}

        void accept(visitor::pprinter *p);
        void accept(visitor::interpreter *p);
    };

    /* Auxiliary types for declations and onward */
    struct expr: public node{
        void accept(visitor::pprinter *p);
        void accept(visitor::interpreter *p);
    };

    struct id : public expr {
        string name;
        id (string s): name(s) {}
        void accept(visitor::pprinter *p);
        void accept(visitor::interpreter *p);
    };
    
    struct id_ : public id {
        string name;
        expr* subscript;
        id_(string s, expr *e): id(s), subscript(e){}
        void accept(visitor::pprinter *p);
        void accept(visitor::interpreter *p);
    };
    
    struct typed_ids : public node {
        type dtype;
        vector<id*> *t_ids;
        typed_ids(type d, vector<id*> *v): 
            dtype(d), t_ids(v) {}
        void accept(visitor::pprinter *p);
        void accept(visitor::interpreter *p);
    };




    struct integer: public expr {
        int value;
        integer(int v): value(v){}
        void accept(visitor::pprinter *p);
        void accept(visitor::interpreter *p);
    };

    struct binOp: public expr {
        opr op;
        expr *left;
        expr *right;

        binOp(opr op, expr *l, expr *r): 
            op(op), left(l), right(r) {}
        void accept(visitor::pprinter *p);
        void accept(visitor::interpreter *p);
    };



    /* statements */
    struct code : public node {
        vector<statement*> *statements;
        code(vector<statement*> *s):statements(s) {}
        void accept(visitor::pprinter *p);
        void accept(visitor::interpreter *p);
    };

    struct statement: public node {
    
        void accept(visitor::pprinter *p);
        void accept(visitor::interpreter *p);
    };

    struct assign: public statement {
        id *ref;
        expr *value;

        assign(id *ref, expr *value): ref(ref), value(value) {}
    
        void accept(visitor::pprinter *p);
        void accept(visitor::interpreter *p);
    };

    struct cblock: public statement{
        expr *cond;
        code *block;
        cblock(expr *c, code *b): cond(c), block(b){}
        void accept(visitor::pprinter *p);
        void accept(visitor::interpreter *p);
    };

    struct while_: public cblock{
        while_(expr *c, code *b): cblock(c, b){}
        void accept(visitor::pprinter *p);
        void accept(visitor::interpreter *p);
    };

    struct if_: public cblock {
        code *otherwise;
        if_(expr *c, code *b, code *o = NULL): 
            cblock(c, b), otherwise(o) { }
        void accept(visitor::pprinter *p);
        void accept(visitor::interpreter *p);
    };

    struct for_: public statement {
        id *var;
        expr *start;
        expr *step;
        expr *end;
        code* block;

        for_(id *i, expr *init, expr *delta, expr *end, code *b): 
            var(i), start(init), step(delta), end(end), block(b){}
        void accept(visitor::pprinter *p);
        void accept(visitor::interpreter *p);
    };

    struct goto_: public id, statement {
        expr *cond;
        goto_ (string label, expr* e=NULL): id(label), cond(e) {}
        void accept(visitor::pprinter *p);
        void accept(visitor::interpreter *p);
    };

    struct print: public statement {
    
        void accept(visitor::pprinter *p);
        void accept(visitor::interpreter *p);
    };


    struct no_op: public statement {
        no_op(){}
        void accept(visitor::pprinter *p);
        void accept(visitor::interpreter *p);
    };


}



#endif
