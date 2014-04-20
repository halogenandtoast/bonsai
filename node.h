#ifndef _NODE_H_
#define _NODE_H_

#include <stdlib.h>
#include "vm.h"

enum node_type {
  EXPRESSION_NODE,
#define EXPRESSION_NODE EXPRESSION_NODE
  BINARY_NODE,
#define BINARY_NODE BINARY_NODE
  LITERAL_NODE,
#define LITERAL_NODE LITERAL_NODE
  FUNCTION_CALL_NODE,
#define FUNCTION_CALL_NODE FUNCTION_CALL_NODE
  DONE_NODE,
#define DONE_NODE DONE_NODE
};

struct Node {
  enum node_type type;
  union {
    struct Node *n;
    int i;
    char *s;
    VALUE v;
  } u1;
  union {
    struct Node *n;
    int i;
    char *s;
    VALUE v;
  } u2;
  union {
    struct Node *n;
    int i;
    char *s;
    VALUE v;
  } u3;
};

struct Node *new_node(enum node_type type, size_t size, ...);
struct Node *append_node(struct Node *parent, struct Node *child);
void run_node(Instruction **instructions, struct Node *node);
void free_node(struct Node *node);
int bonsai_run(struct Node *node);

#endif
