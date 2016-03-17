/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

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
    BRACKET_L = 258,
    BRACKET_R = 259,
    CURLY_BRACKET_L = 260,
    CURLY_BRACKET_R = 261,
    STRAIGHT_BRACKET_L = 262,
    STRAIGHT_BRACKET_R = 263,
    COMMA = 264,
    SEMICOLON = 265,
    MINUS = 266,
    PLUS = 267,
    STAR = 268,
    SLASH = 269,
    PERCENT = 270,
    LE = 271,
    LT = 272,
    GE = 273,
    GT = 274,
    EQ = 275,
    NE = 276,
    OR = 277,
    AND = 278,
    TRUEVAL = 279,
    FALSEVAL = 280,
    LET = 281,
    NOT = 282,
    IF = 283,
    ELSE = 284,
    WHILE = 285,
    DO = 286,
    FOR = 287,
    RETURN = 288,
    EXTERN = 289,
    EXPORT = 290,
    VOID = 291,
    INT = 292,
    FLT = 293,
    BOOL = 294,
    NUM = 295,
    FLOAT = 296,
    ID = 297,
    UNARY = 298,
    IFX = 299
  };
#endif
/* Tokens.  */
#define BRACKET_L 258
#define BRACKET_R 259
#define CURLY_BRACKET_L 260
#define CURLY_BRACKET_R 261
#define STRAIGHT_BRACKET_L 262
#define STRAIGHT_BRACKET_R 263
#define COMMA 264
#define SEMICOLON 265
#define MINUS 266
#define PLUS 267
#define STAR 268
#define SLASH 269
#define PERCENT 270
#define LE 271
#define LT 272
#define GE 273
#define GT 274
#define EQ 275
#define NE 276
#define OR 277
#define AND 278
#define TRUEVAL 279
#define FALSEVAL 280
#define LET 281
#define NOT 282
#define IF 283
#define ELSE 284
#define WHILE 285
#define DO 286
#define FOR 287
#define RETURN 288
#define EXTERN 289
#define EXPORT 290
#define VOID 291
#define INT 292
#define FLT 293
#define BOOL 294
#define NUM 295
#define FLOAT 296
#define ID 297
#define UNARY 298
#define IFX 299

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 23 "src/scanparse/civic.y" /* yacc.c:1909  */

 nodetype            nodetype;
 char               *id;
 int                 cint;
 float               cflt;
 type                ctype;
 node               *node;

#line 151 "y.tab.h" /* yacc.c:1909  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
