%{
  #include <stdio.h>
  #include "node.h"
  #include "vm.h"
  int yylex(void);
  void yyerror(const char *error_message) { fprintf(stderr, "%s\n", error_message); }
%}

%token <ival> TNUMBER
%token <sval> TID
%token TPLUS TMINUS TDOT TLPAREN TRPAREN

%left TPLUS TMINUS
%left TDOT

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

program: expressions { $$ = bonsai_run(append_node($1, new_node(DONE_NODE, 0))); }

expressions: expressions expression { $$ = append_node($1, new_node(EXPRESSION_NODE, 1, $2, NULL)); }
           | expression { $$ = new_node(EXPRESSION_NODE, 1, $1, NULL); }

expression: expression TPLUS expression { $$ = new_node(BINARY_NODE, 3, "+", $1, $3); }
          | expression TMINUS expression { $$ = new_node(BINARY_NODE, 3, "-", $1, $3); }
          | expression TDOT TID TLPAREN TRPAREN { $$ = new_node(FUNCTION_CALL_NODE, 2, $3, $1); free($3); }
          | TLPAREN expression TRPAREN { $$ = $2; }
          | TNUMBER { $$ = new_node(LITERAL_NODE, 1, INT2FIX($1)); }
