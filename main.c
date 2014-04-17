#include <stdio.h>
#include <stdlib.h>
#include "vm.h"
#include "y.tab.h"

#define YYDEBUG

extern FILE *yyin;
extern int yydebug;
int yyparse();

int main(int argc, char *argv[]) {
  yydebug = 0;
  vm_init();
  if(argc > 1) {
    yyin = fopen(argv[1], "r");
  }
  yyparse();
  return EXIT_SUCCESS;
}
