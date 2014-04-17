#include <stdlib.h>

#ifndef _NODE_H_
#define _NODE_H_

enum node_type {
  PROGRAM_NODE,
#define PROGRAM_NODE PROGRAM_NODE
  EXPRESSION_NODE,
#define EXPRESSION_NODE EXPRESSION_NODE
  BINARY_NODE,
#define BINARY_NODE BINARY_NODE
  LITERAL_NODE
#define LITERAL_NODE LITERAL_NODE
};

struct Node {
  enum node_type type;
  union {
    struct Node *n;
    int i;
    const char *s;
  } u1;
  union {
    struct Node *n;
    int i;
    const char *s;
  } u2;
  union {
    struct Node *n;
    int i;
    const char *s;
  } u3;
};

struct Node *new_node(enum node_type type, size_t size, ...);
struct Node *append_node(struct Node *parent, struct Node *child);

#endif
