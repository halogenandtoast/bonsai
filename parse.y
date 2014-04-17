%{
  #include <stdio.h>
  int yylex(void);
  void yyerror(const char *error_message) { fprintf(stderr, "%s\n", error_message); }
%}

%token NUMBER PLUS MINUS

%start program

%%

program: NUMBER PLUS NUMBER { printf("%d\n", $1 + $3) }
       | NUMBER MINUS NUMBER { printf("%d\n", $1 - $3) }
