%{
#include "provol-one_yacc.tab.h"
%}

ID [a-zA-Z_][a-zA-Z_0-9]*
NUM [0-9]+

%%

"ENTRADA"    { return ENTRADA; }
"SAIDA"      { return SAIDA; }
"ENQUANTO"   { return ENQUANTO; }
"FACA"       { return FACA; }
"FIMP"       { return FIMP; }
"FIML"       { return FIML;}
"INC"        { return INC; }
"ZERA"       { return ZERA; }
"SE"         { return SE; }
"ENTAO"      { return ENTAO; }
"SENAO"      { return SENAO; }
"VEZES"      { return VEZES; }
","          { return VIRGULA; }
"="          { return IGUAL; }
"("          { return ABRE_PAREN; }
")"          { return FECHA_PAREN; }
\n           { return NEWLINE; }
[ \t]        ; // Ignorar espaços e tabs
{ID}         { yylval.strval = strdup(yytext); return ID; }
{NUM}        { yylval.numval = atoi(yytext); return NUM; }
.            { printf("Caracter desconhecido: %s\n", yytext); }

%%
