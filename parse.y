%{
  #include <stdio.h>
  int yylex(void);
  void yyerror(const char *error_message) { fprintf(stderr, "%s\n", error_message); }
%}

%token NUMBER PLUS MINUS

%left PLUS MINUS

%start program

%%

program: expressions

expressions: expressions expression
           | expression { printf("%d\n", $1); }

expression: expression PLUS expression { $$ = $1 + $3; }
          | expression MINUS expression { $$ = $1 - $3; }
          | NUMBER { $$ = $1; }
