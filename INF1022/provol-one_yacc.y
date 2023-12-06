%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int yylex();
void yyerror(const char* s);

%}

%union {
    char* strval;
    int numval;
}

%token <strval> ID
%token <numval> NUM
%token ENTRADA SAIDA ENQUANTO FACA FIMP FIML INC ZERA SE ENTAO SENAO VEZES VIRGULA IGUAL ABRE_PAREN FECHA_PAREN NEWLINE

%left '+' '-'
%left '*' '/'

%start program

%%
program : ENTRADA varlist NEWLINE SAIDA varlist NEWLINE cmds FIMP NEWLINE{ printf("Programa aceito!\n"); exit(EXIT_SUCCESS); }
        

varlist : ID { printf("Variável: %s\n", $1); }
        | ID VIRGULA varlist { printf("Variável: %s\n", $1); }
        ;

cmds : cmd NEWLINE cmds
     | cmd NEWLINE
     ;

cmd : ID IGUAL ID { printf("%s = %s\n", $1, $3); }
    | ID IGUAL NUM { printf("%s = %d\n", $1, $3); }
    | INC ABRE_PAREN ID FECHA_PAREN { printf("INC(%s)\n", $3); }
    | ZERA ABRE_PAREN ID FECHA_PAREN { printf("ZERA(%s)\n", $3); }
    | ENQUANTO ID FACA NEWLINE cmds FIML { printf("ENQUANTO %s FACA ... FIML\n", $2); }
    | SE ID ENTAO NEWLINE cmds SENAO NEWLINE cmds FIML{ printf("SE %s ENTAO ... SENAO ... FIML\n", $2); }
    | SE ID ENTAO cmds FIML { printf("SE %s ENTAO ...FIM\n", $2); }
    | FACA cmds VEZES ID FIML { printf("FACA ... VEZES %s FIML\n", $4); }
    ;

%%

void yyerror(const char* s) {
    printf("Prov-a-lone found a: %s\n", s);
    exit(EXIT_FAILURE);
}

int main() {
    yyparse();
    return 0;
}
