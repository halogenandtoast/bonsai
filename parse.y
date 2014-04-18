%{
  #include <stdio.h>
  #include "node.h"
  #include "vm.h"
  int yylex(void);
  void yyerror(const char *error_message) { fprintf(stderr, "%s\n", error_message); }
%}

%token <ival> NUMBER
%token <sval> ID
%token PLUS MINUS DOT LPAREN RPAREN

%left PLUS MINUS
%left DOT

%union {
  struct Node *node;
  int ival;
  char *sval;
  VALUE v;
}

%type <ival> program
%type <node> expressions expression

%start program

%%

program: expressions { $$ = bonsai_run($1); }

expressions: expressions expression { $$ = append_node($1, new_node(EXPRESSION_NODE, 1, $2, NULL)); }
           | expression { $$ = new_node(EXPRESSION_NODE, 1, $1, NULL); }

expression: expression PLUS expression { $$ = new_node(BINARY_NODE, 3, "+", $1, $3); }
          | expression MINUS expression { $$ = new_node(BINARY_NODE, 3, "-", $1, $3); }
          | expression DOT ID LPAREN RPAREN { $$ = new_node(FUNCTION_CALL_NODE, 2, $3, $1); free($3); }
          | LPAREN expression RPAREN { $$ = $2; }
          | NUMBER { $$ = new_node(LITERAL_NODE, 1, INT2FIX($1)); }
