#ifndef PRINTER_H
#define PRINTER_H

#include <bits/stdc++.h>
#include "ast.h"
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


    struct interpreter{
        map<string, dataType> env;
        stack <dataType> evalStack;
        ast::program *root;

        type currentType;
        int currentStatus;
        map <string, ast::code*> table;

        void label(map<string, ast::code*> m){
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
}

#endif
