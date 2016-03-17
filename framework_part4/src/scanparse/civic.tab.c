/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "src/scanparse/civic.y" /* yacc.c:339  */



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


#line 88 "y.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "y.tab.h".  */
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
#line 23 "src/scanparse/civic.y" /* yacc.c:355  */

 nodetype            nodetype;
 char               *id;
 int                 cint;
 float               cflt;
 type                ctype;
 node               *node;

#line 225 "y.tab.c" /* yacc.c:355  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 240 "y.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  18
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   684

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  45
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  33
/* YYNRULES -- Number of rules.  */
#define YYNRULES  109
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  249

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   299

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    68,    68,    74,    78,    84,    88,    92,    98,   102,
     108,   112,   116,   120,   124,   130,   135,   141,   145,   149,
     153,   157,   161,   165,   171,   177,   183,   189,   194,   199,
     204,   209,   215,   219,   225,   229,   235,   241,   245,   249,
     253,   257,   261,   265,   271,   276,   282,   286,   290,   294,
     298,   302,   306,   310,   314,   320,   324,   329,   334,   340,
     345,   354,   358,   362,   366,   370,   374,   378,   382,   388,
     392,   398,   402,   408,   412,   416,   420,   424,   428,   432,
     436,   437,   438,   439,   440,   441,   442,   443,   444,   445,
     446,   447,   448,   450,   454,   460,   466,   471,   477,   483,
     489,   493,   497,   503,   509,   515,   519,   527,   528,   529
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "BRACKET_L", "BRACKET_R",
  "CURLY_BRACKET_L", "CURLY_BRACKET_R", "STRAIGHT_BRACKET_L",
  "STRAIGHT_BRACKET_R", "COMMA", "SEMICOLON", "MINUS", "PLUS", "STAR",
  "SLASH", "PERCENT", "LE", "LT", "GE", "GT", "EQ", "NE", "OR", "AND",
  "TRUEVAL", "FALSEVAL", "LET", "NOT", "IF", "ELSE", "WHILE", "DO", "FOR",
  "RETURN", "EXTERN", "EXPORT", "VOID", "INT", "FLT", "BOOL", "NUM",
  "FLOAT", "ID", "UNARY", "IFX", "$accept", "program", "declarations",
  "decl", "globaldec", "globaldef", "stmts", "stmt", "assign", "while",
  "dowhile", "if", "for", "return", "exprstmt", "funbody", "fundefs",
  "fundef", "param", "ids", "vardec", "varlet", "exprs", "expr", "cast",
  "funcall", "arrexpr", "var", "constant", "floatval", "intval", "boolval",
  "type", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299
};
# endif

#define YYPACT_NINF -171

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-171)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     342,    76,   361,   -16,  -171,  -171,  -171,    18,  -171,   342,
    -171,  -171,  -171,    -5,    25,  -171,  -171,    79,  -171,  -171,
     173,    10,    21,   117,   228,  -171,   228,  -171,  -171,   228,
     228,  -171,  -171,    71,    -3,   486,  -171,  -171,  -171,  -171,
    -171,  -171,  -171,  -171,    41,  -171,    83,    90,    20,    62,
      91,    94,   371,    15,   109,  -171,   530,  -171,   183,  -171,
    -171,   228,   228,   228,   228,   228,   228,   228,   228,   228,
     228,   228,   228,   228,   228,   228,   110,   119,   272,   120,
      41,   121,   132,   287,   140,  -171,   228,  -171,  -171,  -171,
     133,   544,  -171,   118,   118,  -171,  -171,  -171,   405,   405,
     405,   405,   665,   665,   641,   654,    41,   137,  -171,   143,
     146,   145,   157,   223,   401,   233,  -171,   136,  -171,  -171,
    -171,  -171,  -171,  -171,  -171,   159,   136,   401,   497,   144,
      29,   300,   164,    76,  -171,   168,   315,  -171,  -171,  -171,
    -171,  -171,   228,   228,   136,   138,  -171,   558,   135,    62,
    -171,  -171,  -171,  -171,  -171,  -171,   136,    33,   228,   228,
      82,  -171,   175,   147,  -171,  -171,  -171,   182,   391,   411,
     186,   151,  -171,   176,   431,  -171,   228,   108,   572,   187,
      68,  -171,   228,  -171,    76,  -171,     0,   196,   179,   177,
     195,   198,  -171,   228,  -171,   169,   586,  -171,   136,   189,
     136,   209,   228,  -171,   178,   600,    -2,  -171,   213,   249,
     215,   228,   501,    54,  -171,  -171,   228,   199,   136,  -171,
    -171,   451,   228,  -171,   228,   614,   256,   221,   219,   351,
     628,  -171,   136,  -171,  -171,  -171,   226,   228,  -171,   231,
     228,   471,  -171,   232,   236,  -171,   228,   237,  -171
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,   107,   108,   109,     0,     2,     4,
       5,     6,     7,     0,     0,    10,    46,     0,     1,     3,
       0,     0,     0,     0,     0,    11,     0,   105,   106,     0,
       0,   104,   103,    99,     0,    72,    79,    76,    94,    75,
      73,   100,   101,   102,     0,     8,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    78,     0,    77,     0,    93,
      13,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    59,     0,     0,     0,
       0,    56,     0,     0,     0,    74,     0,    98,    12,    97,
       0,     0,    71,    81,    80,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,     0,     0,    52,     0,
       0,     0,     0,     0,     0,    70,    41,    16,    17,    18,
      19,    21,    20,    22,    23,     0,    42,    44,    37,     0,
       0,     0,     0,     0,    51,     0,     0,    95,    96,    14,
      60,     9,     0,     0,     0,     0,    35,     0,     0,     0,
      69,    15,    48,    40,    45,    39,    38,     0,     0,     0,
       0,    54,     0,     0,    55,    47,    53,     0,     0,     0,
       0,     0,    34,     0,     0,    43,     0,     0,     0,     0,
       0,    65,     0,    50,    57,    49,     0,     0,     0,     0,
      74,     0,    61,     0,    24,     0,     0,    58,     0,    27,
       0,     0,     0,    36,     0,     0,     0,    66,     0,     0,
       0,     0,     0,     0,    62,    67,     0,     0,     0,    28,
      25,     0,     0,    63,     0,     0,     0,     0,     0,     0,
       0,    68,     0,    31,    30,    26,     0,     0,    64,     0,
       0,     0,    29,     0,     0,    33,     0,     0,    32
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -171,  -171,   240,  -171,  -171,   243,   -47,  -170,  -171,  -171,
    -171,  -171,  -171,  -171,  -171,   -68,   -51,     2,   -21,     4,
    -171,  -171,   -24,   -20,  -171,  -171,   218,  -171,  -171,  -171,
    -171,  -171,    12
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     7,     8,     9,    10,    11,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,    51,    77,
     128,   129,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    48
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      54,    47,    12,    52,    16,   198,    55,    60,   215,    56,
      57,    12,    13,    14,    13,   135,   199,    44,    18,    86,
      45,    13,    80,    61,   216,    46,    17,    80,   109,    52,
     110,   111,   112,   113,    90,    53,   159,    20,    92,   219,
     176,    91,   115,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   233,    81,     4,     5,
       6,    82,    81,   162,   223,    49,   137,    21,   167,    24,
     151,   160,    50,    26,    58,   177,   154,   156,    24,   153,
     224,   155,    22,    76,   132,   180,    27,    28,    78,    30,
     130,   150,   181,   147,    79,   130,    83,   170,    84,     4,
       5,     6,    31,    32,    33,     4,     5,     6,   182,   175,
     140,   180,   164,     4,     5,     6,    16,    87,   192,   106,
      49,    50,   168,   169,    24,   131,   148,   107,    26,   174,
     133,    65,    66,    67,   193,   179,    86,   138,   178,   148,
     157,    27,    28,   130,    30,   136,   142,   141,   130,   143,
     144,   208,   191,   210,     4,     5,     6,    31,    32,    33,
     145,    82,   196,   197,   109,   152,   110,   111,   112,   113,
     158,   227,   163,   205,   165,   171,    23,   173,   115,   180,
      24,   183,   212,    25,    26,   239,    49,    89,   185,   184,
      24,   221,   188,   189,    26,   195,   225,    27,    28,    29,
      30,   200,   229,   202,   230,   203,   204,    27,    28,   201,
      30,   206,   211,    31,    32,    33,   243,   241,   209,   217,
     213,   220,   247,    31,    32,    33,    49,   234,   226,   235,
      24,    49,   240,   146,    26,    24,   149,   242,   245,    26,
      24,   246,     0,   248,    26,    15,     0,    27,    28,    19,
      30,    59,    27,    28,   218,    30,     0,    27,    28,     0,
      30,   232,     0,    31,    32,    33,     0,     0,    31,    32,
      33,     0,     0,    31,    32,    33,     0,   109,   108,   110,
     111,   112,   113,     0,   109,     0,   110,   111,   112,   113,
       0,   115,     0,   134,     0,     0,     0,     0,   115,     0,
     109,     0,   110,   111,   112,   113,   161,   114,     3,     4,
       5,     6,     0,     0,   115,   109,     0,   110,   111,   112,
     113,   166,   114,     3,     4,     5,     6,     0,   109,   115,
     110,   111,   112,   113,     0,   114,     3,     4,     5,     6,
       0,     0,   115,   109,     0,   110,   111,   112,   113,     0,
     114,     3,     4,     5,     6,   236,     0,   115,     0,     0,
     237,     0,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    85,     1,     2,     3,     4,
       5,     6,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,   186,     2,     3,     4,     5,
       6,     0,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,   187,    63,    64,    65,    66,
      67,     0,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,   190,   114,     3,     4,     5,
       6,     0,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,   228,     0,     0,     0,     0,
       0,     0,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,   244,     0,     0,     0,     0,
       0,     0,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    62,     0,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
     222,     0,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,   109,     0,   110,   111,   112,
     113,     0,   114,     3,     4,     5,     6,     0,     0,   115,
      88,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,   139,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,   172,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,   194,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,   207,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
     214,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,   231,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,   238,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,     0,    75,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    63,    64,    65,    66,
      67,    68,    69,    70,    71
};

static const yytype_int16 yycheck[] =
{
      24,    22,     0,    23,     2,     5,    26,    10,    10,    29,
      30,     9,     0,     1,     2,    83,   186,     7,     0,     4,
      10,     9,     7,    26,    26,     4,    42,     7,    28,    49,
      30,    31,    32,    33,    58,    23,     7,    42,    62,   209,
       7,    61,    42,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,   226,    42,    37,    38,
      39,    49,    42,   131,    10,     3,    86,    42,   136,     7,
     117,    42,     4,    11,     3,    42,   127,   128,     7,   126,
      26,   128,     3,    42,    80,     3,    24,    25,     5,    27,
      78,   115,    10,   113,     4,    83,     5,   144,     4,    37,
      38,    39,    40,    41,    42,    37,    38,    39,    26,   156,
     106,     3,   133,    37,    38,    39,   114,     8,    10,     9,
       3,     4,   142,   143,     7,     5,   114,     8,    11,   149,
       9,    13,    14,    15,    26,   159,     4,     4,   158,   127,
     128,    24,    25,   131,    27,     5,     3,    10,   136,     3,
       5,   198,   176,   200,    37,    38,    39,    40,    41,    42,
       3,   149,   182,   184,    28,     6,    30,    31,    32,    33,
      26,   218,     8,   193,     6,    37,     3,    42,    42,     3,
       7,     6,   202,    10,    11,   232,     3,     4,     6,    42,
       7,   211,     6,    42,    11,     8,   216,    24,    25,    26,
      27,     5,   222,    26,   224,    10,     8,    24,    25,    30,
      27,    42,     3,    40,    41,    42,   240,   237,    29,     6,
      42,     6,   246,    40,    41,    42,     3,     6,    29,    10,
       7,     3,     6,    10,    11,     7,     3,     6,     6,    11,
       7,     5,    -1,     6,    11,     2,    -1,    24,    25,     9,
      27,    33,    24,    25,     5,    27,    -1,    24,    25,    -1,
      27,     5,    -1,    40,    41,    42,    -1,    -1,    40,    41,
      42,    -1,    -1,    40,    41,    42,    -1,    28,     6,    30,
      31,    32,    33,    -1,    28,    -1,    30,    31,    32,    33,
      -1,    42,    -1,     6,    -1,    -1,    -1,    -1,    42,    -1,
      28,    -1,    30,    31,    32,    33,     6,    35,    36,    37,
      38,    39,    -1,    -1,    42,    28,    -1,    30,    31,    32,
      33,     6,    35,    36,    37,    38,    39,    -1,    28,    42,
      30,    31,    32,    33,    -1,    35,    36,    37,    38,    39,
      -1,    -1,    42,    28,    -1,    30,    31,    32,    33,    -1,
      35,    36,    37,    38,    39,     4,    -1,    42,    -1,    -1,
       9,    -1,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,     4,    34,    35,    36,    37,
      38,    39,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,     4,    35,    36,    37,    38,
      39,    -1,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,     4,    11,    12,    13,    14,
      15,    -1,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,     4,    35,    36,    37,    38,
      39,    -1,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,     4,    -1,    -1,    -1,    -1,
      -1,    -1,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,     4,    -1,    -1,    -1,    -1,
      -1,    -1,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,     9,    -1,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
       9,    -1,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    28,    -1,    30,    31,    32,
      33,    -1,    35,    36,    37,    38,    39,    -1,    -1,    42,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    -1,    23,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    11,    12,    13,    14,
      15,    16,    17,    18,    19
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    34,    35,    36,    37,    38,    39,    46,    47,    48,
      49,    50,    62,    77,    77,    50,    62,    42,     0,    47,
      42,    42,     3,     3,     7,    10,    11,    24,    25,    26,
      27,    40,    41,    42,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,     7,    10,     4,    63,    77,     3,
       4,    63,    68,    77,    67,    68,    68,    68,     3,    71,
      10,    26,     9,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    42,    64,     5,     4,
       7,    42,    77,     5,     4,     4,     4,     8,    10,     4,
      67,    68,    67,    68,    68,    68,    68,    68,    68,    68,
      68,    68,    68,    68,    68,    68,     9,     8,     6,    28,
      30,    31,    32,    33,    35,    42,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    65,    66,
      77,     5,    64,     9,     6,    60,     5,    68,     4,    10,
      64,    10,     3,     3,     5,     3,    10,    68,    77,     3,
      67,    51,     6,    51,    61,    51,    61,    77,    26,     7,
      42,     6,    60,     8,    63,     6,     6,    60,    68,    68,
      51,    37,    10,    42,    68,    51,     7,    42,    68,    67,
       3,    10,    26,     6,    42,     6,     4,     4,     6,    42,
       4,    67,    10,    26,    10,     8,    68,    63,     5,    52,
       5,    30,    26,    10,     8,    68,    42,    10,    51,    29,
      51,     3,    68,    42,    10,    10,    26,     6,     5,    52,
       6,    68,     9,    10,    26,    68,    29,    51,     4,    68,
      68,    10,     5,    52,     6,    10,     4,     9,    10,    51,
       6,    68,     6,    67,     4,     6,     5,    67,     6
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    45,    46,    47,    47,    48,    48,    48,    49,    49,
      50,    50,    50,    50,    50,    51,    51,    52,    52,    52,
      52,    52,    52,    52,    53,    54,    55,    56,    56,    56,
      56,    56,    57,    57,    58,    58,    59,    60,    60,    60,
      60,    60,    60,    60,    61,    61,    62,    62,    62,    62,
      62,    62,    62,    62,    62,    63,    63,    63,    63,    64,
      64,    65,    65,    65,    65,    65,    65,    65,    65,    66,
      66,    67,    67,    68,    68,    68,    68,    68,    68,    68,
      68,    68,    68,    68,    68,    68,    68,    68,    68,    68,
      68,    68,    68,    68,    68,    69,    70,    70,    71,    72,
      73,    73,    73,    74,    75,    76,    76,    77,    77,    77
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     4,     7,
       2,     3,     5,     4,     6,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     4,     7,     9,     5,     7,    11,
       9,     9,    14,    12,     3,     2,     5,     1,     2,     2,
       2,     1,     1,     3,     1,     2,     2,     7,     7,     8,
       8,     6,     6,     7,     7,     4,     2,     5,     6,     1,
       3,     4,     6,     7,     9,     3,     5,     6,     8,     2,
       1,     3,     1,     1,     3,     1,     1,     2,     2,     1,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     2,     1,     4,     4,     3,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 69 "src/scanparse/civic.y" /* yacc.c:1646  */
    {
           parseresult = TBmakeProgram((yyvsp[0].node), NULL);
         }
#line 1569 "y.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 75 "src/scanparse/civic.y" /* yacc.c:1646  */
    {
           (yyval.node) = TBmakeDeclarations((yyvsp[-1].node), (yyvsp[0].node));
        }
#line 1577 "y.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 79 "src/scanparse/civic.y" /* yacc.c:1646  */
    {
           (yyval.node) = TBmakeDeclarations( (yyvsp[0].node), NULL);
         }
#line 1585 "y.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 85 "src/scanparse/civic.y" /* yacc.c:1646  */
    {
           (yyval.node) = (yyvsp[0].node);
         }
#line 1593 "y.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 89 "src/scanparse/civic.y" /* yacc.c:1646  */
    {
           (yyval.node) = (yyvsp[0].node);
         }
#line 1601 "y.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 93 "src/scanparse/civic.y" /* yacc.c:1646  */
    {
           (yyval.node) = (yyvsp[0].node);
         }
#line 1609 "y.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 99 "src/scanparse/civic.y" /* yacc.c:1646  */
    {
            (yyval.node) = TBmakeGlobaldec( (yyvsp[-2].ctype), (yyvsp[-1].id), NULL);
         }
#line 1617 "y.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 103 "src/scanparse/civic.y" /* yacc.c:1646  */
    {
            (yyval.node) = TBmakeGlobaldec( (yyvsp[-5].ctype), (yyvsp[-4].id), (yyvsp[-2].node));
         }
#line 1625 "y.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 109 "src/scanparse/civic.y" /* yacc.c:1646  */
    {
            (yyval.node) = (yyvsp[0].node);
         }
#line 1633 "y.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 113 "src/scanparse/civic.y" /* yacc.c:1646  */
    {
            (yyval.node) = TBmakeGlobaldef( (yyvsp[-2].ctype), (yyvsp[-1].id), NULL, NULL);
         }
#line 1641 "y.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 117 "src/scanparse/civic.y" /* yacc.c:1646  */
    {
            (yyval.node) = TBmakeGlobaldef( (yyvsp[-4].ctype), (yyvsp[-3].id), NULL, (yyvsp[-1].node));
         }
#line 1649 "y.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 121 "src/scanparse/civic.y" /* yacc.c:1646  */
    {
            (yyval.node) = TBmakeGlobaldef( (yyvsp[-3].ctype), (yyvsp[-2].id), (yyvsp[-1].node), NULL);
         }
#line 1657 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 125 "src/scanparse/civic.y" /* yacc.c:1646  */
    {
            (yyval.node) = TBmakeGlobaldef( (yyvsp[-5].ctype), (yyvsp[-4].id), (yyvsp[-3].node), (yyvsp[-1].node));
         }
#line 1665 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 131 "src/scanparse/civic.y" /* yacc.c:1646  */
    {
          (yyval.node) = TBmakeStmts( (yyvsp[-1].node), (yyvsp[0].node));
        }
#line 1673 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 136 "src/scanparse/civic.y" /* yacc.c:1646  */
    {
          (yyval.node) = TBmakeStmts( (yyvsp[0].node), NULL);
        }
#line 1681 "y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 142 "src/scanparse/civic.y" /* yacc.c:1646  */
    {
         (yyval.node) = (yyvsp[0].node);
       }
#line 1689 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 146 "src/scanparse/civic.y" /* yacc.c:1646  */
    {
         (yyval.node) = (yyvsp[0].node);
       }
#line 1697 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 150 "src/scanparse/civic.y" /* yacc.c:1646  */
    {
         (yyval.node) = (yyvsp[0].node);
       }
#line 1705 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 154 "src/scanparse/civic.y" /* yacc.c:1646  */
    {
         (yyval.node) = (yyvsp[0].node);
       }
#line 1713 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 158 "src/scanparse/civic.y" /* yacc.c:1646  */
    {
         (yyval.node) = (yyvsp[0].node);
       }
#line 1721 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 162 "src/scanparse/civic.y" /* yacc.c:1646  */
    {
         (yyval.node) = (yyvsp[0].node);
       }
#line 1729 "y.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 166 "src/scanparse/civic.y" /* yacc.c:1646  */
    {
         (yyval.node) = (yyvsp[0].node);
       }
#line 1737 "y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 172 "src/scanparse/civic.y" /* yacc.c:1646  */
    {
          (yyval.node) = TBmakeAssign( (yyvsp[-3].node), (yyvsp[-1].node));
        }
#line 1745 "y.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 178 "src/scanparse/civic.y" /* yacc.c:1646  */
    {
          (yyval.node) = TBmakeWhile( (yyvsp[-4].node), (yyvsp[-1].node));
        }
#line 1753 "y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 184 "src/scanparse/civic.y" /* yacc.c:1646  */
    {
          (yyval.node) = TBmakeDowhile( (yyvsp[-2].node), (yyvsp[-6].node));
        }
#line 1761 "y.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 190 "src/scanparse/civic.y" /* yacc.c:1646  */
    {
            (yyval.node) = TBmakeIf((yyvsp[-2].node), (yyvsp[0].node), NULL);
        }
#line 1769 "y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 195 "src/scanparse/civic.y" /* yacc.c:1646  */
    {
            (yyval.node) = TBmakeIf((yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node));
        }
#line 1777 "y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 200 "src/scanparse/civic.y" /* yacc.c:1646  */
    {
          (yyval.node) = TBmakeIf((yyvsp[-8].node), (yyvsp[-5].node), (yyvsp[-1].node));
        }
#line 1785 "y.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 205 "src/scanparse/civic.y" /* yacc.c:1646  */
    {
          (yyval.node) = TBmakeIf( (yyvsp[-6].node), (yyvsp[-4].node), (yyvsp[-1].node));
        }
#line 1793 "y.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 210 "src/scanparse/civic.y" /* yacc.c:1646  */
    {
          (yyval.node) = TBmakeIf( (yyvsp[-6].node), (yyvsp[-3].node), (yyvsp[0].node));
        }
#line 1801 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 216 "src/scanparse/civic.y" /* yacc.c:1646  */
    {
          (yyval.node) = TBmakeFor((yyvsp[-10].id), (yyvsp[-8].node), (yyvsp[-6].node), (yyvsp[-4].node), (yyvsp[-1].node), NULL);
        }
#line 1809 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 220 "src/scanparse/civic.y" /* yacc.c:1646  */
    {
          (yyval.node) = TBmakeFor( (yyvsp[-8].id), (yyvsp[-6].node), (yyvsp[-4].node), NULL, (yyvsp[-1].node), NULL);
        }
#line 1817 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 226 "src/scanparse/civic.y" /* yacc.c:1646  */
    {
          (yyval.node) = TBmakeReturn((yyvsp[-1].node));
        }
#line 1825 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 230 "src/scanparse/civic.y" /* yacc.c:1646  */
    {
          (yyval.node) = TBmakeReturn(NULL);
        }
#line 1833 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 236 "src/scanparse/civic.y" /* yacc.c:1646  */
    {
          TBmakeExprstmt((yyvsp[-2].node));
        }
#line 1841 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 242 "src/scanparse/civic.y" /* yacc.c:1646  */
    {
          (yyval.node) = TBmakeFunbody((yyvsp[0].node), NULL, NULL);
        }
#line 1849 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 246 "src/scanparse/civic.y" /* yacc.c:1646  */
    {
          (yyval.node) = TBmakeFunbody((yyvsp[-1].node), (yyvsp[0].node), NULL);
        }
#line 1857 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 250 "src/scanparse/civic.y" /* yacc.c:1646  */
    {
          (yyval.node) = TBmakeFunbody((yyvsp[-1].node), NULL, (yyvsp[0].node));
        }
#line 1865 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 254 "src/scanparse/civic.y" /* yacc.c:1646  */
    {
          (yyval.node) = TBmakeFunbody(NULL, (yyvsp[-1].node), (yyvsp[0].node));
        }
#line 1873 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 258 "src/scanparse/civic.y" /* yacc.c:1646  */
    {
          (yyval.node) = TBmakeFunbody(NULL, NULL, (yyvsp[0].node)); 
        }
#line 1881 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 262 "src/scanparse/civic.y" /* yacc.c:1646  */
    {
          (yyval.node) = TBmakeFunbody(NULL, (yyvsp[0].node), NULL);
        }
#line 1889 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 266 "src/scanparse/civic.y" /* yacc.c:1646  */
    {
          (yyval.node) = TBmakeFunbody((yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));
        }
#line 1897 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 272 "src/scanparse/civic.y" /* yacc.c:1646  */
    {
          (yyval.node) = TBmakeFundefs((yyvsp[0].node), NULL);
        }
#line 1905 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 277 "src/scanparse/civic.y" /* yacc.c:1646  */
    {
          (yyval.node) = TBmakeFundefs((yyvsp[-1].node), (yyvsp[0].node));
        }
#line 1913 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 283 "src/scanparse/civic.y" /* yacc.c:1646  */
    {
          (yyval.node) = (yyvsp[0].node);
        }
#line 1921 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 287 "src/scanparse/civic.y" /* yacc.c:1646  */
    {
          (yyval.node) = TBmakeFundef((yyvsp[-6].ctype), (yyvsp[-5].id), NULL, (yyvsp[-1].node), NULL);
        }
#line 1929 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 291 "src/scanparse/civic.y" /* yacc.c:1646  */
    {
          (yyval.node) = TBmakeFundef(T_unknown, (yyvsp[-5].id), NULL, (yyvsp[-1].node), NULL);
        }
#line 1937 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 295 "src/scanparse/civic.y" /* yacc.c:1646  */
    {
          (yyval.node) = TBmakeFundef((yyvsp[-7].ctype), (yyvsp[-6].id), (yyvsp[-4].node), (yyvsp[-1].node), NULL);
        }
#line 1945 "y.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 299 "src/scanparse/civic.y" /* yacc.c:1646  */
    {
          (yyval.node) = TBmakeFundef(T_unknown, (yyvsp[-6].id), (yyvsp[-4].node), (yyvsp[-1].node), NULL);
        }
#line 1953 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 303 "src/scanparse/civic.y" /* yacc.c:1646  */
    {
          (yyval.node) = TBmakeFundef( (yyvsp[-5].ctype), (yyvsp[-4].id), NULL, NULL, NULL);
        }
#line 1961 "y.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 307 "src/scanparse/civic.y" /* yacc.c:1646  */
    {
          (yyval.node) = TBmakeFundef( T_unknown, (yyvsp[-4].id), NULL, NULL, NULL);
        }
#line 1969 "y.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 311 "src/scanparse/civic.y" /* yacc.c:1646  */
    {
          (yyval.node) = TBmakeFundef( (yyvsp[-6].ctype), (yyvsp[-5].id), (yyvsp[-3].node), NULL, NULL);
        }
#line 1977 "y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 315 "src/scanparse/civic.y" /* yacc.c:1646  */
    {
          (yyval.node) = TBmakeFundef( T_unknown, (yyvsp[-5].id), (yyvsp[-3].node), NULL, NULL);
        }
#line 1985 "y.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 321 "src/scanparse/civic.y" /* yacc.c:1646  */
    {
          (yyval.node) = TBmakeParam((yyvsp[-3].ctype), (yyvsp[-2].id), NULL, (yyvsp[0].node));
        }
#line 1993 "y.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 325 "src/scanparse/civic.y" /* yacc.c:1646  */
    {
          (yyval.node) = TBmakeParam((yyvsp[-1].ctype), (yyvsp[0].id), NULL, NULL);
        }
#line 2001 "y.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 330 "src/scanparse/civic.y" /* yacc.c:1646  */
    {
          (yyval.node) = TBmakeParam((yyvsp[-4].ctype), (yyvsp[0].id), (yyvsp[-2].node), NULL);
        }
#line 2009 "y.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 335 "src/scanparse/civic.y" /* yacc.c:1646  */
    {
          (yyval.node) = TBmakeParam((yyvsp[-5].ctype), (yyvsp[-1].id), (yyvsp[-3].node), (yyvsp[0].node));
        }
#line 2017 "y.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 341 "src/scanparse/civic.y" /* yacc.c:1646  */
    {
          (yyval.node) = TBmakeIds((yyvsp[0].id), NULL);
        }
#line 2025 "y.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 346 "src/scanparse/civic.y" /* yacc.c:1646  */
    {
          (yyval.node) = TBmakeIds((yyvsp[-2].id), (yyvsp[0].node));
        }
#line 2033 "y.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 355 "src/scanparse/civic.y" /* yacc.c:1646  */
    {
          (yyval.node) = TBmakeVardec( (yyvsp[-2].ctype), (yyvsp[-1].id), NULL, NULL, (yyvsp[-3].node));
        }
#line 2041 "y.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 359 "src/scanparse/civic.y" /* yacc.c:1646  */
    {
          (yyval.node) = TBmakeVardec((yyvsp[-4].ctype), (yyvsp[-3].id), NULL, (yyvsp[-1].node), (yyvsp[-5].node));
        }
#line 2049 "y.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 363 "src/scanparse/civic.y" /* yacc.c:1646  */
    {
          (yyval.node) = TBmakeVardec( (yyvsp[-5].ctype), (yyvsp[-1].id), (yyvsp[-3].node), NULL, (yyvsp[-6].node));
        }
#line 2057 "y.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 367 "src/scanparse/civic.y" /* yacc.c:1646  */
    {
          (yyval.node) = TBmakeVardec( (yyvsp[-7].ctype), (yyvsp[-3].id), (yyvsp[-5].node), (yyvsp[-1].node), (yyvsp[-8].node));
        }
#line 2065 "y.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 371 "src/scanparse/civic.y" /* yacc.c:1646  */
    {
          (yyval.node) = TBmakeVardec( (yyvsp[-2].ctype), (yyvsp[-1].id), NULL, NULL, NULL);
        }
#line 2073 "y.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 375 "src/scanparse/civic.y" /* yacc.c:1646  */
    {
          (yyval.node) = TBmakeVardec((yyvsp[-4].ctype), (yyvsp[-3].id), NULL, (yyvsp[-1].node), NULL);
        }
#line 2081 "y.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 379 "src/scanparse/civic.y" /* yacc.c:1646  */
    {
          (yyval.node) = TBmakeVardec( (yyvsp[-5].ctype), (yyvsp[-1].id), (yyvsp[-3].node), NULL, NULL);
        }
#line 2089 "y.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 383 "src/scanparse/civic.y" /* yacc.c:1646  */
    {
          (yyval.node) = TBmakeVardec( (yyvsp[-7].ctype), (yyvsp[-3].id), (yyvsp[-5].node), (yyvsp[-1].node), NULL);
        }
#line 2097 "y.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 389 "src/scanparse/civic.y" /* yacc.c:1646  */
    {
          (yyval.node) = TBmakeVarlet( STRcpy( (yyvsp[-1].id)), (yyvsp[0].node));
        }
#line 2105 "y.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 393 "src/scanparse/civic.y" /* yacc.c:1646  */
    {
          (yyval.node) = TBmakeVarlet( STRcpy( (yyvsp[0].id)), NULL);
        }
#line 2113 "y.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 399 "src/scanparse/civic.y" /* yacc.c:1646  */
    {
          (yyval.node) = TBmakeExprs( (yyvsp[-2].node), (yyvsp[0].node));
        }
#line 2121 "y.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 403 "src/scanparse/civic.y" /* yacc.c:1646  */
    {
          (yyval.node) = TBmakeExprs( (yyvsp[0].node), NULL);
        }
#line 2129 "y.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 409 "src/scanparse/civic.y" /* yacc.c:1646  */
    {
        (yyval.node) = (yyvsp[0].node);
      }
#line 2137 "y.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 413 "src/scanparse/civic.y" /* yacc.c:1646  */
    {
        (yyval.node) = (yyvsp[-1].node);
    }
#line 2145 "y.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 417 "src/scanparse/civic.y" /* yacc.c:1646  */
    {
      (yyval.node) = (yyvsp[0].node);
    }
#line 2153 "y.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 421 "src/scanparse/civic.y" /* yacc.c:1646  */
    {
      (yyval.node) = (yyvsp[0].node);
    }
#line 2161 "y.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 425 "src/scanparse/civic.y" /* yacc.c:1646  */
    {
        (yyval.node) = TBmakeMonop(MO_not, (yyvsp[0].node));
      }
#line 2169 "y.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 429 "src/scanparse/civic.y" /* yacc.c:1646  */
    {
        (yyval.node) = TBmakeMonop(MO_neg, (yyvsp[0].node));
      }
#line 2177 "y.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 433 "src/scanparse/civic.y" /* yacc.c:1646  */
    {
        (yyval.node) = (yyvsp[0].node);
      }
#line 2185 "y.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 436 "src/scanparse/civic.y" /* yacc.c:1646  */
    { (yyval.node) = TBmakeBinop(BO_add, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2191 "y.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 437 "src/scanparse/civic.y" /* yacc.c:1646  */
    { (yyval.node) = TBmakeBinop(BO_sub, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2197 "y.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 438 "src/scanparse/civic.y" /* yacc.c:1646  */
    { (yyval.node) = TBmakeBinop(BO_mul, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2203 "y.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 439 "src/scanparse/civic.y" /* yacc.c:1646  */
    { (yyval.node) = TBmakeBinop(BO_div, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2209 "y.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 440 "src/scanparse/civic.y" /* yacc.c:1646  */
    { (yyval.node) = TBmakeBinop(BO_mod, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2215 "y.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 441 "src/scanparse/civic.y" /* yacc.c:1646  */
    { (yyval.node) = TBmakeBinop(BO_le, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2221 "y.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 442 "src/scanparse/civic.y" /* yacc.c:1646  */
    { (yyval.node) = TBmakeBinop(BO_lt, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2227 "y.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 443 "src/scanparse/civic.y" /* yacc.c:1646  */
    { (yyval.node) = TBmakeBinop(BO_ge, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2233 "y.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 444 "src/scanparse/civic.y" /* yacc.c:1646  */
    { (yyval.node) = TBmakeBinop(BO_gt, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2239 "y.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 445 "src/scanparse/civic.y" /* yacc.c:1646  */
    { (yyval.node) = TBmakeBinop(BO_eq, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2245 "y.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 446 "src/scanparse/civic.y" /* yacc.c:1646  */
    { (yyval.node) = TBmakeBinop(BO_ne, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2251 "y.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 447 "src/scanparse/civic.y" /* yacc.c:1646  */
    { (yyval.node) = TBmakeBinop(BO_or, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2257 "y.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 448 "src/scanparse/civic.y" /* yacc.c:1646  */
    { (yyval.node) = TBmakeBinop(BO_and, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2263 "y.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 451 "src/scanparse/civic.y" /* yacc.c:1646  */
    {
        (yyval.node) = (yyvsp[0].node);
      }
#line 2271 "y.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 455 "src/scanparse/civic.y" /* yacc.c:1646  */
    {
        (yyval.node) = (yyvsp[0].node);
      }
#line 2279 "y.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 461 "src/scanparse/civic.y" /* yacc.c:1646  */
    {
        (yyval.node) = TBmakeCast((yyvsp[-2].ctype), (yyvsp[0].node));
      }
#line 2287 "y.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 467 "src/scanparse/civic.y" /* yacc.c:1646  */
    {
      (yyval.node) = TBmakeFuncall( STRcpy( (yyvsp[-3].id)), (yyvsp[-1].node));
    }
#line 2295 "y.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 472 "src/scanparse/civic.y" /* yacc.c:1646  */
    {
      (yyval.node) = TBmakeFuncall( STRcpy((yyvsp[-2].id)), NULL);
    }
#line 2303 "y.tab.c" /* yacc.c:1646  */
    break;

  case 98:
#line 478 "src/scanparse/civic.y" /* yacc.c:1646  */
    {
        (yyval.node) = TBmakeArrexpr((yyvsp[-1].node));
      }
#line 2311 "y.tab.c" /* yacc.c:1646  */
    break;

  case 99:
#line 484 "src/scanparse/civic.y" /* yacc.c:1646  */
    {
        (yyval.node) = TBmakeVar( (yyvsp[0].id), NULL);
      }
#line 2319 "y.tab.c" /* yacc.c:1646  */
    break;

  case 100:
#line 490 "src/scanparse/civic.y" /* yacc.c:1646  */
    {
            (yyval.node) = (yyvsp[0].node);
          }
#line 2327 "y.tab.c" /* yacc.c:1646  */
    break;

  case 101:
#line 494 "src/scanparse/civic.y" /* yacc.c:1646  */
    {
            (yyval.node) = (yyvsp[0].node);
          }
#line 2335 "y.tab.c" /* yacc.c:1646  */
    break;

  case 102:
#line 498 "src/scanparse/civic.y" /* yacc.c:1646  */
    {
            (yyval.node) = (yyvsp[0].node);
          }
#line 2343 "y.tab.c" /* yacc.c:1646  */
    break;

  case 103:
#line 504 "src/scanparse/civic.y" /* yacc.c:1646  */
    {
             (yyval.node) = TBmakeFloat( (yyvsp[0].cflt));
           }
#line 2351 "y.tab.c" /* yacc.c:1646  */
    break;

  case 104:
#line 510 "src/scanparse/civic.y" /* yacc.c:1646  */
    {
          (yyval.node) = TBmakeNum( (yyvsp[0].cint));
        }
#line 2359 "y.tab.c" /* yacc.c:1646  */
    break;

  case 105:
#line 516 "src/scanparse/civic.y" /* yacc.c:1646  */
    {
           (yyval.node) = TBmakeBool( TRUE);
         }
#line 2367 "y.tab.c" /* yacc.c:1646  */
    break;

  case 106:
#line 520 "src/scanparse/civic.y" /* yacc.c:1646  */
    {
           (yyval.node) = TBmakeBool( FALSE);
         }
#line 2375 "y.tab.c" /* yacc.c:1646  */
    break;

  case 107:
#line 527 "src/scanparse/civic.y" /* yacc.c:1646  */
    { (yyval.ctype) = T_int;  }
#line 2381 "y.tab.c" /* yacc.c:1646  */
    break;

  case 108:
#line 528 "src/scanparse/civic.y" /* yacc.c:1646  */
    { (yyval.ctype) = T_float;}
#line 2387 "y.tab.c" /* yacc.c:1646  */
    break;

  case 109:
#line 529 "src/scanparse/civic.y" /* yacc.c:1646  */
    { (yyval.ctype) = T_boolean;}
#line 2393 "y.tab.c" /* yacc.c:1646  */
    break;


#line 2397 "y.tab.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 531 "src/scanparse/civic.y" /* yacc.c:1906  */


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

