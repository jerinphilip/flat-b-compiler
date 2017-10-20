%{
    #include <vector>
    #include "ast.h"
    #include "parser.tab.h"
%}

%%
"declblock"             return k_declaration;
"codeblock"             return k_statement;
"int"                   return k_integer;
"for"                   return k_for;
"while"                 return k_while;
"if"                    return k_if;
"else"                  return k_else;
"print"                 return k_print;
"println"               return k_println;
"read"                  return k_read;
"goto"                  return k_cond_goto;
"got"                   return k_uncond_goto;
[0-9][0-9]*	            {  
                            //printf("Token type: Number, Lexeme/Token Value: %s\n", yytext);  
                            yylval.Int = atoi(yytext);
                            return NUMBER; 
                        }
[a-zA-Z][a-zA-Z0-9]*    {  
                            //printf("Token type: Identifier, Lexeme/Token Value: %s\n", yytext);  
                            yylval.String = strdup(yytext);
                            return IDENTIFIER; 
                        } 
"+"		                return '+';
"-"		                return '-';
"*"		                return '*';
"/"		                return '/';
"{"		                return '{';
"}"		                return '}';
"["		                return '[';
"]"		                return ']';
";"                     return EOS;
":"                     return ':';
"="                     return '=';
"<"                     return '<';
">"                     return '>';
">="                    return GE;
"<="                    return LE;
"=="                    return EQ;
"("                     return '(';
")"                     return ')';
[ \t\n]		            { /* Do nothing */ }
","                     return ',';
\"(\\.|[^"])*\"         {
                            //printf("Token type: String, Lexeme/Token Value: %s\n", yytext);
                            yylval.String = strdup(yytext);
                            return STRING;
                        }
.		                { 
                            printf("Unexpected token encountered: %s\n", yytext); 
                            return ETOK;
                        }
