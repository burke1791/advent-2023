%option case-insensitive noyywrap nodefault
%option bison-bridge

%{

#include <string.h>

#include "gram.tab.h"

%}

%%

GAME  { return GAME; }

RED   |
GREEN |
BLUE    { yylval->str = strdup(yytext); return COLOR; }

[0-9]+    { yylval->i = atoi(yytext); return NUMBER; }

[;:,]     { return yytext[0]; }

[ \t\n]   /* whitespace */
.   /* everything else */

%%