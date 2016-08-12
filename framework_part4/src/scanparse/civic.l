%{

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <limits.h>
#include <errno.h>


#include "types.h"
#include "node_basic.h"
#include "str.h"
#include "free.h"
#include "civic.tab.h"
#include "globals.h"
#include "ctinfo.h"


#define FILTER(token) \
  global.col += yyleng;  \
  return( token);

#define LINEBUF_SIZE 256
#define YY_NO_UNPUT
#define YY_NO_INPUT

static int yyerror( char *errname);
static int rangeCheck( char *integer);



%}

%p 6000 /* set positions to 6000 */
%e 2000 /* set nodes to 1100 */
%option noyywrap
%option nounput





%%

"("                        { FILTER( BRACKET_L); }
")"                        { FILTER( BRACKET_R); }
"{"                        { FILTER( CURLY_BRACKET_L);}
"}"                        { FILTER( CURLY_BRACKET_R);}
"["                        { FILTER( STRAIGHT_BRACKET_L);}
"]"                        { FILTER( STRAIGHT_BRACKET_R);}
","                        { FILTER( COMMA); }
";"                        { FILTER( SEMICOLON); }

"-"                        { FILTER( MINUS); }
"+"                        { FILTER( PLUS);  }
"*"                        { FILTER( STAR);  } 
"/"                        { FILTER( SLASH);  } 
"%"                        { FILTER( PERCENT);  } 

"<="                       { FILTER( LE);    }
"<"                        { FILTER( LT);    } 
">="                       { FILTER( GE);    }
">"                        { FILTER( GT);    }
"=="                       { FILTER( EQ);    }
"!="                       { FILTER( NE);    }
"&&"                       { FILTER( AND);    }
"||"                       { FILTER( OR);    }

"="                        { FILTER( LET);    }
"!"                        { FILTER( NOT);    }
"true"                     { FILTER( TRUEVAL); }
"false"                    { FILTER( FALSEVAL); }
"if"                       { FILTER( IF);     }
"else"                     { FILTER( ELSE);   }
"while"                    { FILTER( WHILE);  }
"do"                       { FILTER( DO);     }
"for"                      { FILTER( FOR);    }
"return"                   { FILTER( RETURN); }
"extern"                   { FILTER( EXTERN); }
"export"                   { FILTER( EXPORT); }
"void"                     { FILTER( VOID);   }
"int"                      { FILTER( INT);    }
"float"                    { FILTER( FLT);    }
"bool"                     { FILTER( BOOL);   }

[A-Za-z][A-Za-z0-9_]*      { yylval.id = STRcpy(yytext);
                             FILTER( ID);
                           }

[0-9]+                     { yylval.cint=atoi(yytext);
                              rangeCheck(yytext);
                             FILTER( NUM);
                           }

[0-9]+\.[0-9]+              { yylval.cflt=atof(yytext);
                             FILTER( FLOAT);
                            }

\n.*                       { global.line += 1;
                             global.col = 0;
                             yyless(1);
                           }

[ \t]                      { global.col += yyleng;
                           }
\/\/.*                      {/* single comment */}
\/\*([^*]|\*+[^*/])*\*\/   {/* multi comment */}
%%

static int yyerror( char *error)
{
  CTIabort( "Error parsing source code: %s\n", 
            error);

  return( 0);
}

static int rangeCheck( char *integer)
{
  errno = 0;
  long output;

  output = strtol(integer, NULL, 10);

  printf("Test %ld\n", output);

  if(errno || output >= INT_MAX || output <= INT_MIN){
    yyerror("Integer out of range");
  }

  return( 0);
}



