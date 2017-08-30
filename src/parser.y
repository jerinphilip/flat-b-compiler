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
%token k_goto
%token NUMBER
%token IDENTIFIER
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
         | IDENTIFIER ':' statement
declaration: dtype id_list EOS
id_list: var | var ',' id_list
var: IDENTIFIER | id_array
id_array: IDENTIFIER '[' NUMBER ']'
dtype: k_integer
arithExpr: arithExpr '+' arithExpr
         | arithExpr '*' arithExpr 
         | arithExpr '/' arithExpr
         | arithExpr '-' arithExpr
         | '(' arithExpr ')'
         | NUMBER
         | IDENTIFIER
         | id_array

boolExpr:  arithExpr boolOp arithExpr | '(' boolExpr ')';
lval: IDENTIFIER | id_array
boolOp: '<' | '>' | GE | LE | EQ
while: k_while boolExpr block
 

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
