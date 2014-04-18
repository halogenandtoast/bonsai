#include "node.h"
#include "vm.h"
#include <stdarg.h>
#include <string.h>
#include <stdio.h>

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
      free(node);
      break;
  }
}

struct Node *run_node(struct Node *node) {
  struct Node *return_value;
  struct Node *left;
  struct Node *right;
  int value;

  switch(node->type) {
    case FUNCTION_CALL_NODE:
      left = run_node(node->u2.n);
      return_value = new_node(LITERAL_NODE, 1, bonsai_func_call(node->u1.s, 1, left->u1.v));
      break;
    case BINARY_NODE:
      left = run_node(node->u2.n);
      right = run_node(node->u3.n);
      return_value = new_node(LITERAL_NODE, 1, bonsai_func_call(node->u1.s, 2, left->u1.v, right->u1.v));
      break;
    case EXPRESSION_NODE:
      return_value = run_node(node->u1.n);
      if (node->u2.n != NULL) {
        return_value = run_node(node->u2.n);
      }
      break;
    case LITERAL_NODE:
      return_value = node;
      break;
  }

  if(left != NULL) free_node(left);
  if(right != NULL) free_node(right);
  return return_value;
}

struct Node *append_node(struct Node *parent, struct Node *child) {
  struct Node *head = parent;
  while(head->u2.n != NULL) head = head->u2.n;
  head->u2.n = child;
  return parent;
}

int bonsai_run(struct Node *node) {
  vm_init();
  run_node(node);
  free_node(node);
  vm_destroy();
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
  }

  va_end(arguments);

  return node;
}
