%{
  #include <stdio.h>
  #include "y.tab.h"
%}

%option noyywrap

%%

[0-9]+ { yylval.ival = atoi(yytext); return NUMBER; }
"+" { return PLUS; }
"-" { return MINUS; }
[ \t\n] {}
. { fprintf(stderr, "Invalid token %s", yytext); }
