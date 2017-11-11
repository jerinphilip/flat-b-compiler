#ifndef PRINTER_H
#define PRINTER_H

#include <bits/stdc++.h>
#include "ast.h"
#include "dtype.h"
#include <llvm/ADT/APFloat.h>
#include <llvm/ADT/STLExtras.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Verifier.h>
#include <llvm/IR/Value.h>
using namespace llvm;
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

    struct compiler{
        map<string, dataType> env;
        stack <dataType> evalStack;
        ast::program *root;
        type currentType;
        map <string, ast::code*> table;

        LLVMContext context;
        Module* module;
        BasicBlock main_block;


        /* To circumvent void return type, stupid Visitor Pattern */
        stack <BasicBlock*> entry;
        stack <BasicBlock*> exit;

        void label(map<string, ast::code*> m){
            table = m;
        }

        compiler(){
            /* Initializing, for LLVM stuff */
            module = new Module("main", context);
            module->setTargetTriple("x86_64-pc-linux-gnu");

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
