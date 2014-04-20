#include "node.h"
#include "vm.h"
#include <stdarg.h>
#include <string.h>
#include <stdio.h>

void *create_instruction(Instruction *instruction, enum op_code code) {
  instruction->op = code;
}

void *create_send(Instruction *instruction, enum op_code code, char *method) {
  create_instruction(instruction, code);
  instruction->label = strdup(method); // TODO: free this
}

void *create_push_instruction(Instruction *instruction, enum op_code code, VALUE value) {
  create_instruction(instruction, code);
  instruction->value = value;
}

void free_node(struct Node *node) {
  switch(node->type) {
    case FUNCTION_CALL_NODE:
      free(node->u1.s);
      free_node(node->u2.n);
      free(node);
      break;
    case BINARY_NODE:
      free(node->u1.s);
      free_node(node->u2.n);
      free_node(node->u3.n);
      free(node);
      break;
    case EXPRESSION_NODE:
      if (node->u2.n != NULL) {
        free_node(node->u2.n);
      }
      free_node(node->u1.n);
      free(node);
      break;
    case LITERAL_NODE:
    case DONE_NODE:
      free(node);
      break;
  }
}

void run_node(Instruction **instructions, struct Node *node) {
  switch(node->type) {
    case FUNCTION_CALL_NODE:
      run_node(instructions, node->u2.n);
      create_send(*instructions, SEND, node->u1.s);
      *instructions = *instructions + 1;
      break;
    case BINARY_NODE:
      run_node(instructions, node->u2.n);
      run_node(instructions, node->u3.n);
      create_instruction(*instructions, PLUS);
      *instructions = *instructions + 1;
      break;
    case EXPRESSION_NODE:
      run_node(instructions, node->u1.n);
      if (node->u2.n != NULL) {
        run_node(instructions, node->u2.n);
      }
      break;
    case DONE_NODE:
      create_instruction(*instructions, LEAVE);
      break;
    case LITERAL_NODE:
      create_push_instruction(*instructions, PUSH_LITERAL, node->u1.v);
      *instructions = *instructions + 1;
      break;
  }
}

struct Node *append_node(struct Node *parent, struct Node *child) {
  struct Node *head = parent;
  while(head->u2.n != NULL) head = head->u2.n;
  head->u2.n = child;
  return parent;
}

int bonsai_run(struct Node *node) {
  VM *vm = vm_init();
  Instruction *instructions = (Instruction *)malloc(sizeof(Instruction) * 5000);
  Instruction *head = instructions;
  run_node(&head, node);
  free_node(node);
  vm_eval(vm, instructions);
  vm_destroy(vm);
  return 0;
}

struct Node *new_node(enum node_type type, size_t size, ...) {
  va_list arguments;
  struct Node *node = (struct Node *) malloc(sizeof(struct Node));
  node->type = type;

  va_start(arguments, size);

  switch (type) {
    case EXPRESSION_NODE:
      node->u1.n = va_arg(arguments, struct Node *);
      node->u2.n = va_arg(arguments, struct Node *);
      break;
    case BINARY_NODE:
      node->u1.s = strdup(va_arg(arguments, char *));
      node->u2.n = va_arg(arguments, struct Node *);
      node->u3.n = va_arg(arguments, struct Node *);
      break;
    case LITERAL_NODE:
      node->u1.v = va_arg(arguments, int);
      break;
    case FUNCTION_CALL_NODE:
      node->u1.s = strdup(va_arg(arguments, char *));
      node->u2.n = va_arg(arguments, struct Node *);
      break;
    case DONE_NODE:
      break;
  }

  va_end(arguments);

  return node;
}
