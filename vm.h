#ifndef _BONSAI_H_
#define _BONSAI_H_

#include <stdlib.h>

#define FIXNUM_FLAG 0x01
#define INT2FIX(i) ((VALUE)(i << 1 | FIXNUM_FLAG))
#define STACK_SIZE 10000

typedef unsigned long VALUE;

enum op_code {
  NOOP,
  PUSH_LITERAL,
#define PUSH_LITERAL PUSH_LITERAL
  PLUS,
#define PLUS PLUS
  SEND,
#define SEND SEND
  LEAVE
#define LEAVE LEAVE
};

typedef struct Instruction {
  enum op_code op;
  char *label;
  VALUE value;
} Instruction;

typedef struct VM {
  VALUE *stack;
  int stack_pointer;
  Instruction *instructions;
  int instruction_pointer;
} VM;

VM *vm_init();
void vm_eval(VM *vm, Instruction *instructions);
void vm_destroy(VM *vm);
VALUE bonsai_func_call(const char *, size_t, ...);


#endif
