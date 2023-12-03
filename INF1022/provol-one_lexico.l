%{
#include "provol-one_yacc.tab.h"
%}

ID      [a-zA-Z][a-zA-Z0-9]*
NUM     [0-9]+

%%

ENTRADA    { return ENTRADA; }
SAIDA      { return SAIDA; }
FIM        { return FIM; }
ENQUANTO   { return ENQUANTO; }
SE         { return SE; }
SENAO      { return SENAO; }
FAZAXVEZES { return FAZAXVEZES; }
INC        { return INC; }
ZERA       { return ZERA; }
=          { return IGUAL; }
+         { return MAIS; }
-          { return MENOS; }
*         { return VEZES; }
/          { return DIVIDIDO; }
<=         { return MENORIGUAL; }
>=         { return MAIORIGUAL; }
<          { return MENOR; }
>          { return MAIOR; }
==         { return IGUALIGUAL; }
E          { return E; }
OU         { return OU; }
NÃO        { return NAO; }
(         { return ABREPAR; }
)         { return FECHAPAR; }
,          { return VIRGULA; }
XVEZES     { return XVEZES; }
{ID}       { yylval.strval = strdup(yytext); return ID; }
{NUM}      { yylval.numval = atoi(yytext); return NUM; }
[ \t\n]    ; // ignorar espaços em branco
.          { fprintf(stderr, "Caractere inesperado: %s\n", yytext); }
