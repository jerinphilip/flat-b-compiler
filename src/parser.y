%{
  #include <stdio.h>
  #include <stdlib.h>
  FILE *yyin;
  int yylex (void);
  void yyerror (char const *s);
%}

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

program:	decl_block code_block
decl_block:  k_declaration'{' declaration_list '}'
code_block:  k_statement block
block: '{' statement_list '}'

declaration_list: declaration | declaration declaration_list
statement_list: statement | statement statement_list
statement: lval '=' arithExpr EOS
         | while
         | IDENTIFIER ':' 
         | if
         | for
         | goto EOS
         | print EOS
         | println EOS
         | read EOS
declaration: dtype id_list EOS
id_list: var | var ',' id_list
var: IDENTIFIER | IDENTIFIER '[' NUMBER ']'
id_loc : IDENTIFIER '[' arithExpr ']' 
dtype: k_integer
arithExpr: arithExpr '+' arithExpr
         | arithExpr '*' arithExpr 
         | arithExpr '/' arithExpr
         | arithExpr '-' arithExpr
         | '(' arithExpr ')'
         | NUMBER
         | IDENTIFIER
         | id_loc


boolExpr:  arithExpr boolOp arithExpr | '(' boolExpr ')';
lval: IDENTIFIER | id_loc
boolOp: '<' | '>' | GE | LE | EQ
while: k_while boolExpr block
if: k_if boolExpr block | k_if boolExpr block k_else block
for: k_for lval '=' arithExpr ',' arithExpr block
   | k_for lval '=' arithExpr ',' arithExpr ',' arithExpr block
goto: k_cond_goto IDENTIFIER k_if boolExpr | k_uncond_goto IDENTIFIER
print: k_print printables
println: k_println printables
printables: printable | printable ',' printables
printable: lval | STRING
read: k_read lval
     
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

	yyparse();
}
