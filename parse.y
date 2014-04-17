%{
  #include <stdio.h>
  #include "node.h"
  int yylex(void);
  void yyerror(const char *error_message) { fprintf(stderr, "%s\n", error_message); }
%}

%token <ival> NUMBER
%token PLUS MINUS

%left PLUS MINUS

%union {
  struct Node *node;
  int ival;
}

%type <node> program expressions expression

%start program

%%

program: expressions { $$ = new_node(PROGRAM_NODE, 1, $1); }

expressions: expressions expression { $$ = append_node($1, $2); }
           | expression { $$ = new_node(EXPRESSION_NODE, 1, $1); }

expression: expression PLUS expression { $$ = new_node(BINARY_NODE, 3, "+", $1, $3); }
          | expression MINUS expression { $$ = new_node(BINARY_NODE, 3, "-", $1, $3); }
          | NUMBER { $$ = new_node(LITERAL_NODE, 1, $1); }
