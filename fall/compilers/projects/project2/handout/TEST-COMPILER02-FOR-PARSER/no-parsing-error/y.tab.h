/* A Bison parser, made by GNU Bison 3.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2019 Free Software Foundation,
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
    PROGRAM = 258,
    ID = 259,
    LPAR = 260,
    RPAR = 261,
    SEMICOLON = 262,
    PERIOD = 263,
    COMMA = 264,
    VAR = 265,
    COLON = 266,
    ARRAY = 267,
    LBRACKET = 268,
    RBRACKET = 269,
    NUM = 270,
    STRINGCONST = 271,
    OF = 272,
    INTEGER = 273,
    REAL = 274,
    FUNCTION = 275,
    PROCEDURE = 276,
    PBEGIN = 277,
    AND = 278,
    OR = 279,
    END = 280,
    ASSIGNOP = 281,
    IF = 282,
    THEN = 283,
    ELSE = 284,
    WHILE = 285,
    DO = 286,
    LESSTHAN = 287,
    GREATERTHAN = 288,
    LEQ = 289,
    GEQ = 290,
    EQUAL = 291,
    NOTEQUAL = 292,
    PLUS = 293,
    MINUS = 294,
    MULTIPLY = 295,
    DIVIDE = 296,
    NOT = 297,
    RANGE = 298,
    BLANK = 299,
    COMMENT = 300,
    IDENTIFIER = 301
  };
#endif
/* Tokens.  */
#define PROGRAM 258
#define ID 259
#define LPAR 260
#define RPAR 261
#define SEMICOLON 262
#define PERIOD 263
#define COMMA 264
#define VAR 265
#define COLON 266
#define ARRAY 267
#define LBRACKET 268
#define RBRACKET 269
#define NUM 270
#define STRINGCONST 271
#define OF 272
#define INTEGER 273
#define REAL 274
#define FUNCTION 275
#define PROCEDURE 276
#define PBEGIN 277
#define AND 278
#define OR 279
#define END 280
#define ASSIGNOP 281
#define IF 282
#define THEN 283
#define ELSE 284
#define WHILE 285
#define DO 286
#define LESSTHAN 287
#define GREATERTHAN 288
#define LEQ 289
#define GEQ 290
#define EQUAL 291
#define NOTEQUAL 292
#define PLUS 293
#define MINUS 294
#define MULTIPLY 295
#define DIVIDE 296
#define NOT 297
#define RANGE 298
#define BLANK 299
#define COMMENT 300
#define IDENTIFIER 301

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
