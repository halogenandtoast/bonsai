#include "node.h"
#include <stdarg.h>

struct Node *append_node(struct Node *parent, struct Node *child) {
  struct Node *head = parent;
  while(head->u2.n != NULL) head = head->u2.n;
  head->u2.n = child;
  return parent;
}

struct Node *new_node(enum node_type type, size_t size, ...) {
  va_list arguments;
  struct Node *node = (struct Node *) malloc(sizeof(struct Node));

  va_start(arguments, size);

  switch (type) {
    case PROGRAM_NODE:
      node->u1.n = va_arg(arguments, struct Node *);
      break;
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
