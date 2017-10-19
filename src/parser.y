%{
  #include <stdio.h>
  #include <stdlib.h>   
  #include <iostream>
  #include <vector>
  extern "C" FILE *yyin;
  extern "C" int yylex (void);
  extern "C" int yyparse (void);
  void yyerror (char const *s);
  #include "ast.h"
  #include "visitor.h"
  #include "lex.yy.c"
  using namespace std;

  ast::program *pgm = NULL;

%}


%union {
    int Int;
    char* String;
    ast::program *program;
    ast::declarations *declarations;
    vector<ast::typed_ids*> *tIds;
    ast::typed_ids *tId;
    ast::statement *statement;
    vector<ast::statement*> *statements;
    ast::id *id;
    vector<ast::id*> *ids;
    ast::expr *expr;
    ast::code *code;
    type dtype;
    opr op;
    ast::while_ *while_;
    ast::for_ *for_;
    ast::if_ *if_;
}

%type <Int> NUMBER;
%type <String> IDENTIFIER;
%type <program> program;
%type <declarations> decl_block;
%type <code> code_block;
%type <code> block;
%type <tId> declaration;
%type <ids> id_list;
%type <statements> statement_list;
%type <statement> statement;
%type <dtype> dtype;
%type <id> var;
%type <id> id_loc;
%type <id> lval;
%type <tIds> declaration_list;
%type <op> boolOp;
%type <expr> boolExpr;
%type <expr> arithExpr;
%type <while_> while;
%type <for_> for;
%type <if_> if;

/*%token declaration_list*/
/*%token statement_list*/
%token k_declaration
%token k_statement
%token k_integer
%token k_if
%token k_else
%token k_for
%token k_while
%token k_print
%token k_println
%token k_read
%token k_cond_goto
%token k_uncond_goto
%token NUMBER
%token IDENTIFIER
%token STRING
%token ETOK
%token EOS;
%left '-'
%left '+'
%left '*'
%left '/'

%left '<'
%left '>'
%left GE
%left LE
%left EQ

%%

program            :  decl_block code_block { $$ = new ast::program($1, $2); pgm = $$;}
                   ;
decl_block         :  k_declaration '{' declaration_list '}' { $$ = new ast::declarations($3); }
                   ;
code_block         :  k_statement block { $$ = $2; }
                   ;
block              : '{' statement_list '}' { $$ =  new ast::code($2); }
                   ;

declaration_list   : declaration_list declaration { $1->push_back($2); $$ = $1;}
                   | %empty {$$ = new vector<ast::typed_ids*>;}
                   ;
statement_list     : statement_list statement { $1->push_back($2); $$ = $1;}
                   | %empty {$$ = new vector<ast::statement*>;} 
                   ;

statement          : lval '=' arithExpr EOS { $$ = new ast::assign($1, $3); }  
                   | while                  { $$ = $1; }   
                   | IDENTIFIER ':'         { string sId = string($1); $$ = new ast::goto_(sId); } 
                   | if                     { $$ = $1; } 
                   | for                    { $$ = $1; }  
                   | goto EOS               {}    
                   | print EOS             /* { $$ = $1; }               */    
                   | println EOS           /* { $$ = $1; }               */      
                   | read EOS              /* { $$ = $1; }               */   
                   | EOS                   /* { $$ = new ast::no_op(); } */
                   ;
declaration        : dtype id_list EOS { $$ = new ast::typed_ids($1, $2); }
                   /*| EOS {$$ */
                   ;
id_list            : var { $$ = new vector<ast::id*>; $$->push_back($1); }
                   | var ',' id_list { $3->push_back($1); $$ = $3; }
                   ;

var                : IDENTIFIER { $$ = new ast::id($1); }
                   | IDENTIFIER '[' NUMBER ']' { string sId = string($1); $$ = new ast::id_(sId, new ast::integer($3)); }
                   ;

id_loc             : IDENTIFIER '[' arithExpr ']' { string sId = string($1); $$ = new ast::id_(sId, $3); }
                   ;
dtype              : k_integer { $$ = type::Int; }
                   ;
arithExpr          : arithExpr '+' arithExpr  { $$ = new ast::binOp(opr::add, $1, $3);  }
                   | arithExpr '*' arithExpr  { $$ = new ast::binOp(opr::mul, $1, $3);  }  
                   | arithExpr '/' arithExpr  { $$ = new ast::binOp(opr::quot, $1, $3);  }
                   | arithExpr '-' arithExpr  { $$ = new ast::binOp(opr::sub, $1, $3);  }
                   | '(' arithExpr ')'        { $$ = $2; }
                   | NUMBER                   { $$ = new ast::integer($1); }
                   | IDENTIFIER               { $$ = new ast::id($1); }
                   | id_loc                   { $$ = $1; }
                   ;


boolExpr           :  arithExpr boolOp arithExpr  { $$ = new ast::binOp($2, $1, $3); }
                   | '(' boolExpr ')'       { $$ = $2; }
                   ;

lval               : IDENTIFIER              { $$ = new ast::id($1); } 
                   | id_loc                  { $$ = $1; }
                   ;

boolOp             : '<'  { $$ = opr::lt; }
                   | '>'  { $$ = opr::gt; }
                   | GE   { $$ = opr::ge; }
                   | LE   { $$ = opr::le; }
                   | EQ   { $$ = opr::eq; }
                   ;

while              : k_while boolExpr block     { $$ = new ast::while_($2, $3); }
                   ;

if                 : k_if boolExpr block        { $$ = new ast::if_($2, $3); }
                   | k_if boolExpr block k_else block { $$ = new ast::if_($2, $3, $5); }
                   ;

for                : k_for lval '=' arithExpr ',' arithExpr block
                   | k_for lval '=' arithExpr ',' arithExpr ',' arithExpr block
                   ;

goto               : k_cond_goto IDENTIFIER k_if boolExpr 
                   | k_uncond_goto IDENTIFIER
                   ;

print              : k_print printables
                   ;
println            : k_println printables
                   ;
printables         : printable | printable ',' printables
                   ;
printable          : lval | STRING
                   ;

read               : k_read lval
                   ;
     
%%

void yyerror (char const *s)
{
       fprintf (stderr, "%s\n", s);
}

int main(int argc, char *argv[])
{
	if (argc == 1 ) {
		fprintf(stderr, "Correct usage: bcc filename\n");
		exit(1);
	}

	if (argc > 2) {
		fprintf(stderr, "Passing more arguments than necessary.\n");
		fprintf(stderr, "Correct usage: bcc filename\n");
	}

	yyin = fopen(argv[1], "r");

    //visitor::pprinter print;
	yyparse();
    //print.visit(pgm);
}
