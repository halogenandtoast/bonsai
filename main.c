#include <stdio.h>
#include <stdlib.h>
#include "y.tab.h"

int yyparse();

int main(int argc, char *argv[]) {
  yyparse();
  return EXIT_SUCCESS;
}
