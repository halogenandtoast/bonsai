#include <stdio.h>
#include <stdlib.h>
#include "vm.h"
#include "y.tab.h"

extern FILE *yyin;
int yyparse();

int main(int argc, char *argv[]) {
  if(argc > 1) {
    yyin = fopen(argv[1], "r");
  }
  yyparse();
  return EXIT_SUCCESS;
}
