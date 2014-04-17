#include "vm.h"
#include <stdio.h>
#include <string.h>

VALUE bonsai_func_call(const char * method, VALUE value) {
  if (strcmp(method, "puts") == 0) {
    printf("%d\n", (int)(value >> 1));
  }
  return value;
}

