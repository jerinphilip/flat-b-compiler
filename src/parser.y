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
  #include "lexer.h"
  using namespace std;

  ast::Program *pgm = NULL;
  ast::Code *code = NULL;

  map<string, ast::Code*> labels;

%}


%union {
    int Int;
    char* String;
    ast::Program *program;
    ast::Declarations *declarations;
    vector<ast::TypedIds*> *tIds;
    ast::TypedIds *tId;
    ast::Statement *statement;
    vector<ast::Statement*> *statements;
    ast::Id *id;
    vector<ast::Id*> *ids;
    vector<ast::IdDef*> *defs; 
    ast::IdDef *def;
    ast::IdRef *ref;
    ast::Expr *expr;
    ast::Code *code;
    FlatBType dtype;
    Op op;
    ast::While *while_;
    ast::For *for_;
    ast::If *if_;
    ast::NoOp *no_op;
    ast::Goto *goto_;
    vector<ast::Expr*> *exprs;
    ast::Print *print;
    ast::Read *read;
    ast::Labelled *labelled;
}

%type <Int> NUMBER;
%type <String> IDENTIFIER;
%type <String> STRING;
%type <program> program;
%type <declarations> decl_block;
%type <code> code_block;
%type <code> block;
%type <tId> declaration;
%type <defs> id_list;
%type <statements> statement_list;
%type <statement> statement;
%type <dtype> dtype;
%type <def> var;
%type <tIds> declaration_list;
%type <op> boolOp;
%type <expr> boolExpr;
%type <expr> arithExpr;
%type <while_> while;
%type <for_> for;
%type <if_> if;
%type <goto_> goto;
%type <ref> lval;
%type <exprs> printables;
%type <expr> printable;
%type <print> print;
%type <read> read;
%type <print> println;
%type <labelled> labelled_block;

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

program            :  decl_block code_block                                     { $$ = new ast::Program($1, $2); pgm = $$;}
                   ;
decl_block         :  k_declaration '{' declaration_list '}'                    { $$ = new ast::Declarations($3); }
                   ;
code_block         :  k_statement block                                         { $$ = $2; }
                   ;
block              : '{' statement_list '}'                                     { $$ =  new ast::Code($2); }
                   ;
declaration_list   : declaration_list declaration                               { $1->push_back($2); $$ = $1; }
                   | %empty                                                     { $$ = new vector<ast::TypedIds*>(); }
                   ;

labelled_block     : IDENTIFIER ':' statement_list                              { code = new ast::Code($3); $$ = new ast::Labelled($1, code); labels[($1)] = code;}
statement_list     : statement_list statement                                   { $1->push_back($2); $$ = $1; }
                   | statement_list labelled_block                              { $1->push_back($2); $$ = $1; }
                   | %empty                                                     { $$ = new vector<ast::Statement*>(); } 
                   ;
statement          : lval '=' arithExpr EOS                                     { $$ = new ast::Assign($1, $3); }  
                   | lval '=' boolExpr EOS                                      { $$ = new ast::Assign($1, $3); }  
                   | while                                                      { $$ = $1; }   
                   /*| IDENTIFIER ':'                                             { string sId = string($1); $$ = new ast::goto_(sId); } */
                   | if                                                         { $$ = $1; } 
                   | for                                                        { $$ = $1; }  
                   | goto EOS                                                   { $$ = $1; }    
                   | print EOS                                                  { $$ = $1; }                   
                   | println EOS                                                { $$ = $1; }                     
                   | read EOS                                                   { $$ = $1; }                  
                   | EOS                                                        { $$ = new ast::NoOp(); } 
                   ;
declaration        : dtype id_list EOS                                          { $$ = new ast::TypedIds($1, $2); }
                   /*| EOS {$$ */
                   ;
id_list            : var                                                        { $$ = new vector<ast::IdDef*>(); $$->push_back($1); }
                   | var ',' id_list                                            { $3->push_back($1); $$ = $3; }
                   ;
var                : IDENTIFIER                                                 { $$ = new ast::IdDef(string($1)); }
                   | IDENTIFIER '[' NUMBER ']'                                  { string sId = string($1); $$ = new ast::IdArrayDef(sId, $3); }
                   ;
dtype              : k_integer                                                  { $$ = FlatBType::Int; }
                   ;
arithExpr          : arithExpr '+' arithExpr                                    { $$ = new ast::BinOp(Op::add, $1, $3);  }
                   | arithExpr '*' arithExpr                                    { $$ = new ast::BinOp(Op::mul, $1, $3);  }  
                   | arithExpr '/' arithExpr                                    { $$ = new ast::BinOp(Op::quot, $1, $3);  }
                   | arithExpr '-' arithExpr                                    { $$ = new ast::BinOp(Op::sub, $1, $3);  }
                   | '(' arithExpr ')'                                          { $$ = $2; }
                   | NUMBER                                                     { $$ = new ast::Integer($1); }
                   | IDENTIFIER                                                 { $$ = new ast::Id($1); }
                   | IDENTIFIER '[' arithExpr ']'                               { string sId = string($1); $$ = new ast::IdArrayAccess(sId, $3); }
                   ;
boolExpr           :  arithExpr boolOp arithExpr                                { $$ = new ast::BinOp($2, $1, $3); }
                   | '(' boolExpr ')'                                           { $$ = $2; }
                   ;
lval               : IDENTIFIER                                                 { $$ = new ast::IdRef($1); } 
                   | IDENTIFIER '[' arithExpr ']'                               { string sId = string($1); $$ = new ast::IdArrayRef(sId, $3); }
                   ;
boolOp             : '<'                                                        { $$ = Op::lt; }
                   | '>'                                                        { $$ = Op::gt; }
                   | GE                                                         { $$ = Op::ge; }
                   | LE                                                         { $$ = Op::le; }
                   | EQ                                                         { $$ = Op::eq; }
                   ;
while              : k_while boolExpr block                                     { $$ = new ast::While($2, $3); }
                   ;
if                 : k_if boolExpr block                                        { $$ = new ast::If($2, $3); }
                   | k_if boolExpr block k_else block                           { $$ = new ast::If($2, $3, $5); }
                   ;
for                : k_for lval '=' arithExpr ',' arithExpr block               { $$ = new ast::For(new ast::Assign($2, $4), (new ast::Integer(1)), $6, $7); }
                   | k_for lval '=' arithExpr ',' arithExpr ',' arithExpr block { $$ = new ast::For(new ast::Assign($2, $4), $8, $6, $9); }
                   ;
goto               : k_cond_goto IDENTIFIER k_if boolExpr                       { string sId = string($2); $$ = new ast::Goto(sId, $4); }
                   | k_uncond_goto IDENTIFIER                                   { string sId = string($2); $$ = new ast::Goto(sId); }
                   ;                                                            
print              : k_print printables                                         { $$ = new ast::Print($2, false); } 
                   ;                                                            
println            : k_println printables                                       { $$ = new ast::Print($2, true); }
                   ;                                                            
printables         : printable                                                  { $$ = new vector<ast::Expr*>(); $$->push_back($1); }
                   | printable ',' printables                                   { $3->push_back($1);  $$ = $3;}
                   ;                                                            
printable          : arithExpr                                                  { $$ = $1 ;}
                   | STRING                                                     { $$ = new ast::Literal($1); }
                   ;                                                            
read               : k_read lval                                                { $$ = new ast::Read($2);}
                   ;                                            
     
%%

void yyerror (char const *s)
{
       fprintf (stderr, "%s\n", s);
}

int main(int argc, char *argv[]) {
  if (argc == 1) {
    fprintf(stderr, "Correct usage: %s filename\n", argv[0]);
    exit(1);
  }

  if (argc > 2) {
    fprintf(stderr, "Passing more arguments than necessary.\n");
    fprintf(stderr, "Correct usage: %s filename\n", argv[0]);
  }

  std::unique_ptr<visitor::Visitor> visitor = visitor::make_visitor(argv[1]);

  yyin = fopen(argv[2], "r");
  if (yyparse() == 0) {
    visitor->label(labels);
    visitor->visit(pgm);
  }

  return 0;
}


