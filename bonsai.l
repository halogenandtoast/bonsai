%{
  #include <stdio.h>
  #include "vm.h"
  #include "y.tab.h"
%}

%option noyywrap

%%

[0-9]+ { yylval.ival = atoi(yytext); return NUMBER; }
"+" { return PLUS; }
"-" { return MINUS; }
"." { return DOT; }
[a-z_]+ { yylval.sval = strdup(yytext); return ID; }
"(" { return LPAREN; }
")" { return RPAREN; }
[ \t\n] {}
. { fprintf(stderr, "Invalid token: %s\n", yytext); }
