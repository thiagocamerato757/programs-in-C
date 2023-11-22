%{
#include "ProvolOne.tab.h"
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
NAO        { return NAO; }
(         { return ABREPAR; }
)         { return FECHAPAR; }
,          { return VIRGULA; }
XVEZES     { return XVEZES; }
[a-zA-Z][a-zA-Z0-9]* { yylval.strval = strdup(yytext); return ID; }
[0-9]+   { yylval.numval = atoi(yytext); return NUM; }
[ \t\n]  ; // ignorar espaços em branco
.        { fprintf(stderr, "Caractere inesperado: %s\n", yytext); }
%%

int yywrap() {
    return 1;
}

