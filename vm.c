#include "vm.h"
#include "class.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

VALUE cInteger;

VALUE bs_integer_puts(VALUE self) {
  printf("%d\n", (int)(self >> 1));
  return self;
}

VALUE bs_integer_plus(VALUE self, VALUE other) {
  int left = (int)(self >> 1);
  int right = (int)(other >> 1);
  int result = left + right;
  return INT2FIX(result);
}

void vm_init() {
  cInteger = bs_class_create("Integer");
  bs_add_method(cInteger, "puts", bs_integer_puts);
  bs_add_method(cInteger, "+", bs_integer_plus);
}

void vm_destroy() {
  bs_class_free(cInteger);
}

VALUE bonsai_func_call(const char *method, size_t size, ...) {
  struct Method *current_method = ((struct Class *)cInteger)->method;
  va_list args;
  while (current_method && strcmp(current_method->name, method) != 0) {
    current_method = current_method->method;
  }
  if(current_method) {
    va_start(args, size);
    if(size == 1) {
      VALUE value = va_arg(args, VALUE);
      va_end(args);
      return current_method->c_method(value);
    } else {
      VALUE left = va_arg(args, VALUE);
      VALUE right = va_arg(args, VALUE);
      va_end(args);
      return current_method->c_method(left, right);
    }
  } else {
    fprintf(stderr, "Undefined method %s\n", method);
    exit(1);
    return 0;
  }
}
