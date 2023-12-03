/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    ENTRADA = 258,
    SAIDA = 259,
    FIM = 260,
    ENQUANTO = 261,
    SE = 262,
    SENAO = 263,
    FAZAXVEZES = 264,
    INC = 265,
    ZERA = 266,
    IGUAL = 267,
    MAIS = 268,
    MENOS = 269,
    DIVIDIDO = 270,
    MENORIGUAL = 271,
    MAIORIGUAL = 272,
    MENOR = 273,
    MAIOR = 274,
    IGUALIGUAL = 275,
    E = 276,
    OU = 277,
    NAO = 278,
    ABREPAR = 279,
    FECHAPAR = 280,
    VIRGULA = 281,
    ID = 282,
    NUM = 283,
    VEZES = 284,
    UMINUS = 285
  };
#endif
/* Tokens.  */
#define ENTRADA 258
#define SAIDA 259
#define FIM 260
#define ENQUANTO 261
#define SE 262
#define SENAO 263
#define FAZAXVEZES 264
#define INC 265
#define ZERA 266
#define IGUAL 267
#define MAIS 268
#define MENOS 269
#define DIVIDIDO 270
#define MENORIGUAL 271
#define MAIORIGUAL 272
#define MENOR 273
#define MAIOR 274
#define IGUALIGUAL 275
#define E 276
#define OU 277
#define NAO 278
#define ABREPAR 279
#define FECHAPAR 280
#define VIRGULA 281
#define ID 282
#define NUM 283
#define VEZES 284
#define UMINUS 285

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
