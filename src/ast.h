#ifndef AST_H
#define AST_H

#include <vector>
using namespace std;


enum type {
    Int
};

enum opr {
    add,
    sub,
    mul,
    quot
};


namespace ast {

    struct node;
        /* Base struct */
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
    struct println;
    struct typed_ids;

    struct node {
        /* Base struct */
    };

    struct program : public node {
        declarations* decl;
        code* block;
        program(declarations *d, code* c): decl(d), block(c){}
    };

    /* declarations */

    struct declarations : public node {
        vector<typed_ids*> *ds;
        declarations(vector<typed_ids*> *v): ds(v) {}
    };

    /* Auxiliary types for declations and onward */
    struct id : public node {
        string name;
        id (string s): name(s) {}
    };
    
    struct id_ : public id {
        string name;
        expr* subscript;
        id_(string s, expr *e): id(s), subscript(e){}
    };
    
    struct typed_ids : public node {
        type dtype;
        vector<id*> *t_ids;
        typed_ids(type d, vector<id*> *v): 
            dtype(d), t_ids(v) {}
    };



    struct expr: public node{
    
    };

    struct Int: public node {
        int value;
        Int(int v): value(v){}
    };

    struct binOp: public expr {
        opr op;
        expr *left;
        expr *right;

        binOp(opr op, expr *l, expr *r): 
            op(op), left(l), right(r) {}
    };



    /* statements */
    struct code : public node {
        vector<statement*> statements;
        code(vector<statement*> s):statements(s) {}
    };

    struct statement: public node {
    
    };

    struct assign: public statement {
    
    };

    struct cblock: public statement{
        expr *cond;
        code *block;
        cblock(expr *c, code *b): cond(c), block(b){}
    };

    struct while_: public cblock{
        while_(expr *c, code *b): cblock(c, b){}
    };

    struct if_: public cblock {
        if_(expr *c, code *b): cblock(c, b){}
    };

    struct for_: public statement {
        statement* init;
        expr* cond;
        expr* step;
        code* block;

        for_(statement *i, expr *c, expr *s, code *b): 
            init(i), cond(c), step(s), block(b){}
    };

    struct print: public statement {
    
    };

    struct println: public statement {
    
    };

}

#endif
