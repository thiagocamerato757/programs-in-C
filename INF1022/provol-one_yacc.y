%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int yylex();
void yyerror(const char *s);

%}

%token ENTRADA SAIDA FIM ENQUANTO SE SENAO FAZAXVEZES INC ZERA
%token IGUAL MAIS MENOS VEZES DIVIDIDO MENORIGUAL MAIORIGUAL MENOR MAIOR IGUALIGUAL E OU NAO
%token ABREPAR FECHAPAR VIRGULA ID NUM

%%
program : ENTRADA varlist SAIDA varlist cmds FIM
        ;

varlist : ID VIRGULA varlist
        | ID
        ;

cmds : cmd cmds
     | cmd
     ;

cmd : ENQUANTO ID FAZAXVEZES exp FIM
    | SE exp FAZAXVEZES cmds FIM
    | SE exp FAZAXVEZES cmds SENAO cmds FIM
    | ID IGUAL exp
    | INC ABREPAR ID FECHAPAR
    | ZERA ABREPAR ID FECHAPAR
    | FAZAXVEZES cmds XVEZES exp FIM
    ;

exp : exp OU exp
    | exp E exp
    | NAO exp
    | exp MENOR exp
    | exp MAIOR exp
    | exp MENORIGUAL exp
    | exp MAIORIGUAL exp
    | exp IGUALIGUAL exp
    | exp MAIS exp
    | exp MENOS exp
    | exp VEZES exp
    | exp DIVIDIDO exp
    | ABREPAR exp FECHAPAR
    | ID
    | NUM
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Erro: %s\n", s);
    exit(EXIT_FAILURE);
}

int main() {
    yyparse();
    return 0;
}

