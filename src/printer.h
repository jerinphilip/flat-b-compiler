#ifndef PRINTER_H
#define PRINTER_H

#include <bits/stdc++.h>
#include "ast.h"
using namespace std;

class pprinter {
    void visit(ast::node node_);
    void visit(ast::program program_);
    void visit(ast::declarations declarations_);
    void visit(ast::id id_);
    void visit(ast::idA idA_);
    void visit(ast::expr *e);
    void visit(ast::code *c);
    void visit(ast::statement *s);
    void visit(ast::assign *a);
    void visit(ast::while_ w);
    void visit(ast::if_ *ib);
    void visit(ast::for_ *fb);
    void visit(ast::print *print;
    void visit(ast::println;

};

#endif
