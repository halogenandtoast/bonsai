#include "vm.h"
#include "class.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

VALUE cInteger;

VALUE bs_integer_puts(VALUE self) {
  printf("%d\n", (int)(self >> 1));
  return self;
}

void vm_init() {
  cInteger = bs_class_create("Integer");
  bs_add_method(cInteger, "puts", bs_integer_puts);
}

VALUE bonsai_func_call(const char *method, VALUE value) {
  struct Method *current_method = ((struct Class *)cInteger)->method;
  while (current_method && strcmp(current_method->name, method) != 0) {
    current_method = current_method->method;
  }
  if(current_method) {
    return current_method->c_method(value);
  } else {
    fprintf(stderr, "Undefined method %s\n", method);
    exit(1);
    return 0;
  }
}
