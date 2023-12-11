%option case-insensitive nodefault noyywrap
%option bison-bridge

%{

#include "gram.tab.h"

%}

%%

SEEDS   { return SEEDS; }

"SEED-TO-SOIL MAP:"             { return SEED_SOIL; }
"SOIL-TO-FERTILIZER MAP:"       { return SOIL_FERTILIZER; }
"FERTILIZER-TO-WATER MAP:"      { return FERTILIZER_WATER; }
"WATER-TO-LIGHT MAP:"           { return WATER_LIGHT; }
"LIGHT-TO-TEMPERATURE MAP:"     { return LIGHT_TEMP; }
"TEMPERATURE-TO-HUMIDITY MAP:"  { return TEMP_HUMIDITY; }
"HUMIDITY-TO-LOCATION MAP:"     { return HUMIDITY_LOCATION; }

[0-9]+    { yylval->i = atoi(yytext); return NUMBER; }


[\r\n]  /*  newline  */
.   /* everything else */

%%