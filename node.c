#include "node.h"
#include <stdarg.h>
#include <string.h>
#include <stdio.h>

struct Node *run_node(struct Node *node) {
  struct Node *return_value;
  struct Node *left;
  struct Node *right;
  int value;

  switch(node->type) {
    case BINARY_NODE:
      left = run_node(node->u2.n);
      right = run_node(node->u3.n);

      if (strcmp("+", node->u1.s) == 0) {
        value = left->u1.i + right->u1.i;
        printf("%d\n", value);
        return_value = new_node(LITERAL_NODE, 1, value);
      } else if (strcmp("-", node->u1.s) == 0) {
        value = left->u1.i - right->u1.i;
        printf("%d\n", value);
        return_value = new_node(LITERAL_NODE, 1, value);
      } else {
        printf("Failed with %s", node->u1.s);
      }
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
  return return_value;
}

struct Node *append_node(struct Node *parent, struct Node *child) {
  struct Node *head = parent;
  while(head->u2.n != NULL) head = head->u2.n;
  head->u2.n = child;
  return parent;
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
      node->u1.s = va_arg(arguments, const char *);
      node->u2.n = va_arg(arguments, struct Node *);
      node->u3.n = va_arg(arguments, struct Node *);
      break;
    case LITERAL_NODE:
      node->u1.i = va_arg(arguments, int);
      break;
  }

  va_end(arguments);

  return node;
}
