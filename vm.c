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

VM *vm_init() {
  VM *vm = (VM *) malloc(sizeof(VM));
  vm->stack = (VALUE *) malloc(sizeof(VALUE) * STACK_SIZE);
  vm->stack_pointer = 0;

  cInteger = bs_class_create("Integer");
  bs_add_method(cInteger, "puts", bs_integer_puts);

  return vm;
}

void vm_eval(VM *vm, Instruction *instructions) {
  VALUE right, left, self, result;
  Instruction instruction;
  vm->instructions = instructions;
  vm->instruction_pointer = 0;


  while(vm->instructions[vm->instruction_pointer].op != LEAVE) {
    instruction = vm->instructions[vm->instruction_pointer];
    switch(instruction.op) {
      case PUSH_LITERAL:
        vm->stack[vm->stack_pointer++] = instruction.value;
        break;
      case PLUS:
        right = vm->stack[--vm->stack_pointer];
        left = vm->stack[--vm->stack_pointer];
        result = (left >> 1) + (right >> 1);
        vm->stack[vm->stack_pointer++] = INT2FIX(result);
        break;
      case SEND:
        self = vm->stack[--vm->stack_pointer];
        bonsai_func_call(instruction.label, 1, self);
        break;
    }
    vm->instruction_pointer++;
  }
}

void vm_destroy(VM *vm) {
  free(vm->instructions);
  free(vm->stack);
  free(vm);
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
