%{


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <memory.h>

#include "types.h"
#include "tree_basic.h"
#include "str.h"
#include "dbug.h"
#include "ctinfo.h"
#include "free.h"
#include "globals.h"

static node *parseresult = NULL;
extern int yylex();
static int yyerror( char *errname);

%}

%union {
 nodetype            nodetype;
 char               *id;
 int                 cint;
 float               cflt;
 type                ctype;
 node               *node;
}

%token BRACKET_L BRACKET_R CURLY_BRACKET_L CURLY_BRACKET_R
%token STRAIGHT_BRACKET_L STRAIGHT_BRACKET_R COMMA SEMICOLON
%token MINUS PLUS STAR SLASH PERCENT LE LT GE GT EQ NE OR AND
%token TRUEVAL FALSEVAL LET NOT IF ELSE WHILE DO FOR
%token RETURN EXTERN EXPORT VOID INT FLT BOOL

%token <cint> NUM
%token <cflt> FLOAT
%token <id> ID

%type <node> intval floatval boolval constant
%type <node> stmts stmt assign varlet program
%type <node> declarations decl fundefs fundef
%type <node> param funbody globaldef exprs expr
%type <node> globaldec ids vardec cast 
%type <node> if while dowhile for return 
%type <node> exprstmt var funcall error
%type <ctype> type

%right LET
%left OR
%left AND
%left EQ NE
%left LE LT GE GT
%left MINUS PLUS
%left STAR SLASH PERCENT
%left BRACKET_L BRACKET_R
%left UNARY

%nonassoc IFX
%nonassoc ELSE

%start program

%%

program: declarations
         {
           parseresult = TBmakeProgram($1, NULL, NULL);
         }
         ;

declarations: decl declarations
        {
           $$ = TBmakeDeclarations($1, $2);
        }
         | decl
         {
           $$ = TBmakeDeclarations( $1, NULL);
         }
         ;

decl:    globaldec
         {
           $$ = $1;
         }
         | globaldef
         {
           $$ = $1;
         }
         | fundef
         {
           $$ = $1;
         }
         ;

globaldec: EXTERN type ID SEMICOLON
         {
            $$ = TBmakeGlobaldec( $2, $3, NULL);
         }
         | EXTERN type ID STRAIGHT_BRACKET_L ids STRAIGHT_BRACKET_R SEMICOLON
         {
            $$ = TBmakeGlobaldec( $2, $3, $5);
         }
         ;

globaldef: EXPORT type ID SEMICOLON 
         {
            $$ = TBmakeGlobaldef( $2, $3, TRUE, NULL, NULL);
         }
         | EXPORT type ID LET expr SEMICOLON
         {
            $$ = TBmakeGlobaldef( $2, $3, TRUE, NULL, $5);
         }
         | EXPORT type ID exprs SEMICOLON
         {
            $$ = TBmakeGlobaldef( $2, $3, TRUE, $4, NULL);
         }
         | EXPORT type ID exprs LET expr SEMICOLON
         {
            $$ = TBmakeGlobaldef( $2, $3, TRUE, $4, $6);
         }
         | type ID SEMICOLON
         {
            $$ = TBmakeGlobaldef( $1, $2, FALSE, NULL, NULL);
         }
         | type ID LET expr SEMICOLON
         {
            $$ = TBmakeGlobaldef( $1, $2, FALSE, NULL, $4);
         }
         | type ID exprs SEMICOLON
         {
            $$ = TBmakeGlobaldef( $1, $2, FALSE, $3, NULL);
         }
         | type ID exprs LET expr SEMICOLON
         {
            $$ = TBmakeGlobaldef( $1, $2, FALSE, $3, $5);
         }
         ;

stmts: stmt stmts
        {
          $$ = TBmakeStmts( $1, $2);
        }
        | 
        stmt
        {
          $$ = TBmakeStmts( $1, NULL);
        }
        ;

stmt: 	assign
       {
         $$ = $1;
       }
       | while
       {
         $$ = $1;
       }
       | dowhile
       {
         $$ = $1;
       }
       | for
       {
         $$ = $1;
       }
       | if
       {
         $$ = $1;
       }
       | return
       {
         $$ = $1;
       }
       | exprstmt
       {
         $$ = $1;
       }
       ;

assign: varlet LET expr SEMICOLON
        {
          $$ = TBmakeAssign( $1, $3);
        }
        ;

while: WHILE BRACKET_L expr BRACKET_R CURLY_BRACKET_L stmts CURLY_BRACKET_R
        {
          $$ = TBmakeWhile( $3, $6);
        }
        ;

dowhile: DO CURLY_BRACKET_L stmts CURLY_BRACKET_R WHILE BRACKET_L expr BRACKET_R SEMICOLON
        {
          $$ = TBmakeDowhile( $7, $3);
        }
        | DO stmt WHILE BRACKET_L expr BRACKET_R SEMICOLON
        {
          $$ = TBmakeDowhile( $5, $2);
        }
        ;

if:     IF BRACKET_L expr BRACKET_R stmt %prec IFX 
        {
            $$ = TBmakeIf($3, $5, NULL);
        }
        |
        IF BRACKET_L expr BRACKET_R CURLY_BRACKET_L stmts %prec IFX CURLY_BRACKET_R
        {
            $$ = TBmakeIf($3, $6, NULL);
        }
        |
        IF BRACKET_L expr BRACKET_R stmt ELSE stmt
        {
            $$ = TBmakeIf($3, $5, $7);
        }
        |
        IF BRACKET_L expr BRACKET_R CURLY_BRACKET_L stmts CURLY_BRACKET_R ELSE CURLY_BRACKET_L stmts CURLY_BRACKET_R
        {
          $$ = TBmakeIf($3, $6, $10);
        }
        |
        IF BRACKET_L expr BRACKET_R stmt ELSE CURLY_BRACKET_L stmts CURLY_BRACKET_R
        {
          $$ = TBmakeIf( $3, $5, $8);
        }
        |
        IF BRACKET_L expr BRACKET_R CURLY_BRACKET_L stmts CURLY_BRACKET_R ELSE stmt
        {
          $$ = TBmakeIf( $3, $6, $9);
        }        
        ;

for:    FOR BRACKET_L INT ID LET expr COMMA expr COMMA expr BRACKET_R CURLY_BRACKET_L stmts CURLY_BRACKET_R
        {
          $$ = TBmakeFor($4, $6, $8, $10, $13, NULL);
        }
        | FOR BRACKET_L INT ID LET expr COMMA expr BRACKET_R CURLY_BRACKET_L stmts CURLY_BRACKET_R
        {
          $$ = TBmakeFor( $4, $6, $8, NULL, $11, NULL);
        }
        | FOR BRACKET_L INT ID LET expr COMMA expr COMMA expr BRACKET_R stmt
        {
          $$ = TBmakeFor( $4, $6, $8, $10, NULL, $12);
        }
        | FOR BRACKET_L INT ID LET expr COMMA expr BRACKET_R stmt
        {
          $$ = TBmakeFor( $4, $6, $8, NULL, NULL, $10);
        }
        ;

return:   RETURN expr SEMICOLON
        {
          $$ = TBmakeReturn($2);
        }
        | RETURN SEMICOLON
        {
          $$ = TBmakeReturn(NULL);
        }
        ;

exprstmt: funcall SEMICOLON
        {
          $$ = TBmakeExprstmt($1);
        }
        ;

funbody:vardec
        {
          $$ = TBmakeFunbody($1, NULL, NULL);
        }
        | vardec fundefs
        {
          $$ = TBmakeFunbody($1, $2, NULL);
        }
        | vardec stmts
        {
          $$ = TBmakeFunbody($1, NULL, $2);
        }               
        | fundefs stmts
        {
          $$ = TBmakeFunbody(NULL, $1, $2);
        } 
        | stmts
        {
          $$ = TBmakeFunbody(NULL, NULL, $1); 
        }
        |fundefs
        {
          $$ = TBmakeFunbody(NULL, $1, NULL);
        }
        | vardec fundefs stmts
        {
          $$ = TBmakeFunbody($1, $2, $3);
        }
        ;

fundefs:  fundef
        {
          $$ = TBmakeFundefs($1, NULL);
        }
        |
          fundef fundefs
        {
          $$ = TBmakeFundefs($1, $2);
        }
        ; 

fundef: EXTERN type ID BRACKET_L BRACKET_R SEMICOLON
        {
         $$ = TBmakeFundef($2, $3, FALSE, TRUE, NULL, NULL, NULL, NULL);
        }  
        | EXTERN VOID ID BRACKET_L BRACKET_R SEMICOLON
        {
         $$ = TBmakeFundef(T_unknown, $3, FALSE, TRUE, NULL, NULL, NULL, NULL);
        } 
        | EXTERN type ID BRACKET_L param BRACKET_R SEMICOLON
        {
         $$ = TBmakeFundef($2, $3, FALSE, TRUE, $5, NULL, NULL, NULL);
        } 
        | EXTERN VOID ID BRACKET_L param BRACKET_R SEMICOLON
        {
         $$ = TBmakeFundef(T_unknown, $3, FALSE, TRUE, $5, NULL, NULL, NULL);
        }
        |EXPORT type ID BRACKET_L BRACKET_R CURLY_BRACKET_L funbody CURLY_BRACKET_R
        {
          $$ = TBmakeFundef($2, $3, TRUE, FALSE, NULL, $7, NULL, NULL);
        }
        | EXPORT VOID ID BRACKET_L BRACKET_R CURLY_BRACKET_L funbody CURLY_BRACKET_R
        {
          $$ = TBmakeFundef(T_unknown, $3, TRUE, FALSE, NULL, $7, NULL, NULL);
        }
        | EXPORT type ID BRACKET_L param BRACKET_R CURLY_BRACKET_L funbody CURLY_BRACKET_R
        {
          $$ = TBmakeFundef($2, $3, TRUE, FALSE, $5, $8, NULL, NULL);
        }
        | EXPORT VOID ID BRACKET_L param BRACKET_R CURLY_BRACKET_L funbody CURLY_BRACKET_R
        {
          $$ = TBmakeFundef(T_unknown, $3, TRUE, FALSE, $5, $8, NULL, NULL);
        }
        | EXPORT type ID BRACKET_L BRACKET_R CURLY_BRACKET_L CURLY_BRACKET_R
        {
          $$ = TBmakeFundef( $2, $3, TRUE, FALSE, NULL, NULL, NULL, NULL);
        }
        | EXPORT VOID ID BRACKET_L BRACKET_R CURLY_BRACKET_L CURLY_BRACKET_R
        {
          $$ = TBmakeFundef( T_unknown, $3, TRUE, FALSE, NULL, NULL, NULL, NULL);
        }
        | EXPORT type ID BRACKET_L param BRACKET_R CURLY_BRACKET_L CURLY_BRACKET_R
        {
          $$ = TBmakeFundef( $2, $3, TRUE, FALSE, $5, NULL, NULL, NULL);
        }
        | EXPORT VOID ID BRACKET_L param BRACKET_R CURLY_BRACKET_L CURLY_BRACKET_R
        {
          $$ = TBmakeFundef( T_unknown, $3, TRUE, FALSE, $5, NULL, NULL, NULL);
        }  
        |type ID BRACKET_L BRACKET_R CURLY_BRACKET_L funbody CURLY_BRACKET_R
        {
          $$ = TBmakeFundef($1, $2, FALSE, FALSE, NULL, $6, NULL, NULL);
        }
        | VOID ID BRACKET_L BRACKET_R CURLY_BRACKET_L funbody CURLY_BRACKET_R
        {
          $$ = TBmakeFundef(T_unknown, $2, FALSE, FALSE, NULL, $6, NULL, NULL);
        }
        | type ID BRACKET_L param BRACKET_R CURLY_BRACKET_L funbody CURLY_BRACKET_R
        {
          $$ = TBmakeFundef($1, $2, FALSE, FALSE, $4, $7, NULL, NULL);
        }
        | VOID ID BRACKET_L param BRACKET_R CURLY_BRACKET_L funbody CURLY_BRACKET_R
        {
          $$ = TBmakeFundef(T_unknown, $2, FALSE, FALSE, $4, $7, NULL, NULL);
        }
        | type ID BRACKET_L BRACKET_R CURLY_BRACKET_L CURLY_BRACKET_R
        {
          $$ = TBmakeFundef( $1, $2, FALSE, FALSE, NULL, NULL, NULL, NULL);
        }
        | VOID ID BRACKET_L BRACKET_R CURLY_BRACKET_L CURLY_BRACKET_R
        {
          $$ = TBmakeFundef( T_unknown, $2, FALSE, FALSE, NULL, NULL, NULL, NULL);
        }
        | type ID BRACKET_L param BRACKET_R CURLY_BRACKET_L CURLY_BRACKET_R
        {
          $$ = TBmakeFundef( $1, $2, FALSE, FALSE, $4, NULL, NULL, NULL);
        }
        | VOID ID BRACKET_L param BRACKET_R CURLY_BRACKET_L CURLY_BRACKET_R
        {
          $$ = TBmakeFundef( T_unknown, $2, FALSE, FALSE, $4, NULL, NULL, NULL);
        }
        ;

param:  type ID COMMA param 
        {
          $$ = TBmakeParam($1, $2, NULL, $4);
        }
        |type ID      
        {
          $$ = TBmakeParam($1, $2, NULL, NULL);
        }   
        |
        type STRAIGHT_BRACKET_L ids STRAIGHT_BRACKET_R ID
        {
          $$ = TBmakeParam($1, $5, $3, NULL);
        }
        |
        type STRAIGHT_BRACKET_L ids STRAIGHT_BRACKET_R ID param
        {
          $$ = TBmakeParam($1, $5, $3, $6);
        }
        ;

ids:    ID 
        {
          $$ = TBmakeIds($1, NULL);
        }
        |
        ID COMMA ids
        {
          $$ = TBmakeIds($1, $3);
        }
        ;

      


vardec: vardec type ID SEMICOLON
        {
          $$ = TBmakeVardec( $2, $3, NULL, NULL, $1);
        }
        | vardec type ID LET expr SEMICOLON
        {
          $$ = TBmakeVardec($2, $3, NULL, $5, $1);
        }
        | vardec type STRAIGHT_BRACKET_L exprs STRAIGHT_BRACKET_R ID SEMICOLON
        {
          $$ = TBmakeVardec( $2, $6, $4, NULL, $1);
        }
        | vardec type STRAIGHT_BRACKET_L exprs STRAIGHT_BRACKET_R ID LET expr SEMICOLON
        {
          $$ = TBmakeVardec( $2, $6, $4, $8, $1);
        }
        | type ID SEMICOLON
        {
          $$ = TBmakeVardec( $1, $2, NULL, NULL, NULL);
        }
        | type ID LET expr SEMICOLON
        {
          $$ = TBmakeVardec($1, $2, NULL, $4, NULL);
        }
        | type STRAIGHT_BRACKET_L exprs STRAIGHT_BRACKET_R ID SEMICOLON
        {
          $$ = TBmakeVardec( $1, $5, $3, NULL, NULL);
        }
        | type STRAIGHT_BRACKET_L exprs STRAIGHT_BRACKET_R ID LET expr SEMICOLON
        {
          $$ = TBmakeVardec( $1, $5, $3, $7, NULL);
        }
        ;

varlet: ID
        {
          $$ = TBmakeVarlet( STRcpy( $1), NULL);
        }
        ;

exprs: expr COMMA exprs
        {
          $$ = TBmakeExprs( $1, $3);
        }
      | expr
        {
          $$ = TBmakeExprs( $1, NULL);
        }
        ;

expr: constant
      {
        $$ = $1;
      }
    | BRACKET_L expr BRACKET_R 
    {
        $$ = $2;
    }   
    | var
    {
      $$ = $1;
    }
    | funcall
    {
      $$ = $1;
    }    
    | NOT expr %prec UNARY
      {
        $$ = TBmakeMonop(MO_not, $2);
      }
    | MINUS expr %prec UNARY
      {
        $$ = TBmakeMonop(MO_neg, $2);
      }
      | cast
      {
        $$ = $1;
      }
      |expr PLUS expr     { $$ = TBmakeBinop(BO_add, $1, $3); }
      | expr MINUS expr    { $$ = TBmakeBinop(BO_sub, $1, $3); }
      | expr STAR expr      { $$ = TBmakeBinop(BO_mul, $1, $3); }
     | expr SLASH expr    { $$ = TBmakeBinop(BO_div, $1, $3); }
     | expr PERCENT expr  { $$ = TBmakeBinop(BO_mod, $1, $3); }
     | expr LE expr        { $$ = TBmakeBinop(BO_le, $1, $3); }
     | expr LT expr       { $$ = TBmakeBinop(BO_lt, $1, $3); }
     | expr GE expr        { $$ = TBmakeBinop(BO_ge, $1, $3); }
     | expr GT expr        { $$ = TBmakeBinop(BO_gt, $1, $3); }
     | expr EQ expr        { $$ = TBmakeBinop(BO_eq, $1, $3); }
     | expr NE expr        { $$ = TBmakeBinop(BO_ne, $1, $3); }
     | expr OR expr        { $$ = TBmakeBinop(BO_or, $1, $3); }
     | expr AND expr      { $$ = TBmakeBinop(BO_and, $1, $3); }
    ;

cast: BRACKET_L type BRACKET_R expr
      {
        $$ = TBmakeCast($2, $4);
      }
      ;

funcall: ID BRACKET_L exprs BRACKET_R
    {
      $$ = TBmakeFuncall( STRcpy( $1), $3);
    }
    |
    ID BRACKET_L BRACKET_R
    {
      $$ = TBmakeFuncall( STRcpy($1), NULL);
    }
    ;

var : ID
      {
        $$ = TBmakeVar( $1, NULL);
      }
      ;

constant: floatval
          {
            $$ = $1;
          }
        | intval
          {
            $$ = $1;
          }
        | boolval
          {
            $$ = $1;
          }
        ;

floatval: FLOAT
           {
             $$ = TBmakeFloat( $1);
           }
         ;

intval: NUM
        {
          $$ = TBmakeNum( $1);
        }
      ;

boolval: TRUEVAL
         {
           $$ = TBmakeBool( TRUE);
         }
       | FALSEVAL
         {
           $$ = TBmakeBool( FALSE);
         }
       ;



type: INT        { $$ = T_int;  }
    | FLT        { $$ = T_float;}
    | BOOL       { $$ = T_boolean;}
    ;
%%

static int yyerror( char *error)
{
  CTIabort( "line %d, col %d\nError parsing source code: %s\n", 
            global.line, global.col, error);

  return( 0);
}

node *YYparseTree( void)
{
  DBUG_ENTER("YYparseTree");

  yyparse();

  DBUG_RETURN( parseresult);
}

