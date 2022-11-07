#include "iparser.h"

int main(int argc, char *argv[]) {
  if (argc == 1) {
    fprintf(stderr, "Correct usage: %s filename\n", argv[0]);
    exit(1);
  }

  if (argc > 2) {
    fprintf(stderr, "Passing more arguments than necessary.\n");
    fprintf(stderr, "Correct usage: %s filename\n", argv[0]);
  }

  yyin = fopen(argv[1], "r");

  // visitor::pprinter V;
  visitor::interpreter V;
  // visitor::compiler V;

  if (yyparse() == 0) {
    V.label(labels);
    V.visit(pgm);
  }
}
