%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int yylex();
void yyerror(const char *s);

%}

%union {
    char *strval;
    int numval;
}

%type <strval> program varlist cmd cmds exp
%token <strval> ID
%token <numval> NUM
%token <strval> ENTRADA
%token <strval> SAIDA
%token <strval> ENQUANTO
%token <strval> FACA
%token <strval> FIMP
%token <strval> FIML
%token <numval> INC
%token <numval> ZERA
%token <strval> SE
%token <strval> ENTAO
%token <strval> SENAO
%token <strval> VEZES
%token <strval> VIRGULA
%token <numval> IGUAL
%token <strval> ABRE_PAREN
%token <strval> FECHA_PAREN
%token <numval> NEWLINE
%token <numval> MAIS
%token <numval> MENOS
%token <numval> MULT
%token <numval> DIVID
%token <numval> IQUALL
%token <numval> NIQUAL
%token <numval> MAIOR
%token <numval> MENOR
%token <numval> MAIORI
%token <numval> MENORI

%start program

%left MAIS MENOS
%left MULT DIVID
%nonassoc MENOR MAIOR MENORI MAIORI IQUALL NIQUAL
%left IGUAL INC ZERA

%%

program : ENTRADA varlist NEWLINE SAIDA varlist NEWLINE cmds FIMP NEWLINE {
    printf("Código Fonte Resultante:\n%s\n", $7);
    exit(EXIT_SUCCESS);
}

varlist : ID {
    $$ = $1;
}
        | ID VIRGULA varlist {
            char *result = malloc(strlen($1) + strlen($3) + 3);
            strcpy(result, $1);
            strcat(result, ",");
            strcat(result, $3);
            $$ = result;
        }
        ;

cmds : cmd NEWLINE cmds {
    char *result = malloc(strlen($1) + strlen($3) + 3);
    strcpy(result, $1);
    strcat(result, "\n");
    strcat(result, $3);
    $$ = result;
}
     | cmd NEWLINE {
         $$ = $1;
     }
     ;

cmd : ID IGUAL exp {
         char *result = malloc(strlen($1) + strlen($3) + 2);
         strcpy(result, $1);
         strcat(result, "=");
         strcat(result, $3);
         $$ = result;
     }
    | INC ABRE_PAREN ID FECHA_PAREN {
        char *result = malloc(strlen($3) + 6);
        strcpy(result, $3);
        strcat(result, "+=1");
        $$ = result;
    }
    | ZERA ABRE_PAREN ID FECHA_PAREN {
        char *result = malloc(strlen($3) + 6);
        strcpy(result, $3);
        strcat(result, "=");
        strcat(result, "0");
        $$ = result;
    }
    | ENQUANTO exp FACA NEWLINE cmds FIML {
        char *result = malloc(strlen($2) + strlen($5) + 14);
        strcpy(result, "while ");
        strcat(result, $2);
        strcat(result, ":\n");
        strcat(result, $5);
        $$ = result;
    }
    | SE exp ENTAO NEWLINE cmds SENAO NEWLINE cmds FIML {
        char *result = malloc(strlen($2) + strlen($5) + strlen($8) + 18);
        strcpy(result, "if ");
        strcat(result, $2);
        strcat(result, ":\n");
        strcat(result, $5);
        strcat(result, "\nelse:\n");
        strcat(result, $8);
        strcat(result, ":\n");
        $$ = result;
    }
    | SE exp ENTAO NEWLINE cmds FIML {
        char *result = malloc(strlen($2) + strlen($5) + 10);
        strcpy(result, "if ");
        strcat(result, $2);
        strcat(result, ":\n");
        strcat(result, $5);
        $$ = result;
    }
    | FACA cmds VEZES ID FIML {
        char *result = malloc(strlen($4) + strlen($2) + 12);
        strcpy(result, "for ");
        strcat(result, $4);
        strcat(result, " in range(");
        strcat(result, $4);
        strcat(result, "):\n");
        strcat(result, $2);
        $$ = result;
    }
    ;

exp : exp MAIS exp {
        char *result = malloc(strlen($1) + strlen($3) + 4);
        strcpy(result, $1);
        strcat(result, "+");
        strcat(result, $3);
        $$ = result;
    }
    | exp MENOS exp {
        char *result = malloc(strlen($1) + strlen($3) + 4);
        strcpy(result, $1);
        strcat(result, "-");
        strcat(result, $3);
        $$ = result;
    }
    | exp MULT exp {
        char *result = malloc(strlen($1) + strlen($3) + 4);
        strcpy(result, $1);
        strcat(result, "*");
        strcat(result, $3);
        $$ = result;
    }
    | exp DIVID exp {
        char *result = malloc(strlen($1) + strlen($3) + 4);
        strcpy(result, $1);
        strcat(result, "/");
        strcat(result, $3);
        $$ = result;
    }
    | exp IQUALL exp {
        char *result = malloc(strlen($1) + strlen($3) + 4);
        strcpy(result, $1);
        strcat(result, "==");
        strcat(result, $3);
        $$ = result;
    }
    | exp NIQUAL exp {
        char *result = malloc(strlen($1) + strlen($3) + 4);
        strcpy(result, $1);
        strcat(result, "!=");
        strcat(result, $3);
        $$ = result;
    }
    | exp MAIOR exp {
        char *result = malloc(strlen($1) + strlen($3) + 4);
        strcpy(result, $1);
        strcat(result, ">");
        strcat(result, $3);
        $$ = result;
    }
    | exp MENOR exp {
        char *result = malloc(strlen($1) + strlen($3) + 4);
        strcpy(result, $1);
        strcat(result, "<");
        strcat(result, $3);
        $$ = result;
    }
    | exp MAIORI exp {
        char *result = malloc(strlen($1) + strlen($3) + 5);
        strcpy(result, $1);
        strcat(result, ">=");
        strcat(result, $3);
        $$ = result;
    }
    | exp MENORI exp {
        char *result = malloc(strlen($1) + strlen($3) + 5);
        strcpy(result, $1);
        strcat(result, "<=");
        strcat(result, $3);
        $$ = result;
    }
    | NUM {
        char *result = malloc(12);  // Ajuste este tamanho conforme necessário
        sprintf(result, "%d", $1);
        $$ = result;
    }
    | ID {
        char *result = malloc(strlen($1) + 1);
        strcpy(result, $1);
        $$ = result;
    }
    | ABRE_PAREN exp FECHA_PAREN {
        char *result = malloc(strlen($1) + strlen($2) + 2);
        strcpy(result, "(");
        strcat(result, $2);
        strcat(result, ")");
        $$ = result;
    }
    ;

%%

void yyerror(const char *s) {
    printf("Provol-One encontrou um erro: %s\n", s);
    exit(EXIT_FAILURE);
}

int main() {
    yyparse();
    return 0;
}
