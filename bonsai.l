%{
  #include <stdio.h>
  #include "vm.h"
  #include "y.tab.h"
%}

%option noyywrap

%%

[0-9]+ { yylval.ival = atoi(yytext); return TNUMBER; }
"+" { return TPLUS; }
"-" { return TMINUS; }
"." { return TDOT; }
[a-z_]+ { yylval.sval = strdup(yytext); return TID; }
"(" { return TLPAREN; }
")" { return TRPAREN; }
[ \t\n] {}
. { fprintf(stderr, "Invalid token: %s\n", yytext); }
