
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
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
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 1 "parser.y"

    #include <stdio.h>
    #include <stdlib.h>
    #include <ctype.h>
    #include <string.h>
    #include <stdbool.h>
    #include "symbol_table.h"
    #include "stack.h"

    #define TYPE_LEN 4
    #define LABEL_LEN 100
    #define TOKEN_LEN 100000
    #define YYINITDEPTH 10000
    #define dbg
    #ifdef dbg
    #define YYDEBUG 1
    #define YYERROR_VERBOSE
    int yydebug = 1;
    #endif

    extern int yylex();
    void error(char* s);
    void yyerror(char (*type)[TYPE_LEN], char* s);
    TokenType assert_var_status(char var_name[TOKEN_LEN], bool required);
    void combine_numbers();
    void gen_empty_arr();
    void gen_const_arr();
    void begin_program();
    void begin_block();
    void end_block();
    void end_program();
    void codegen_declare(char (*type)[TYPE_LEN], char var_name[TOKEN_LEN]);
    void codegen_assign();
    void codegen_expList();
    void codegen_print();
    void codegen_arithmetic();
    void codegen_dotproduct();
    void codegen_const_arr();
    void codegen_index();
    void codegen_if();
    void codegen_while();
    void codegen_free();
    void tab_print(int a);
    
    extern char *yytext;

    int expListCount = 0;
    int lts = 0;
    char ls_last[TOKEN_LEN];
    FILE *fp;


/* Line 189 of yacc.c  */
#line 126 "parser.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     BEGIN_KWD = 258,
     END = 259,
     TYPE = 260,
     IF_COND = 261,
     IF_BLOCK = 262,
     LOOP_COND = 263,
     LOOP_BLOCK = 264,
     PRINT = 265,
     SEMICOLON = 266,
     INDEX = 267,
     COMMA = 268,
     PAR_BEGIN = 269,
     PAR_END = 270,
     CONST_ARR_BEGIN = 271,
     CONST_ARR_END = 272,
     INT_VAL = 273,
     IDENTIFIER = 274,
     REL_OP = 275,
     DOT_OP = 276,
     OP = 277,
     ASSIGN = 278
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 191 "parser.tab.c"

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
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
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
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   79

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  24
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  29
/* YYNRULES -- Number of rules.  */
#define YYNRULES  45
/* YYNRULES -- Number of states.  */
#define YYNSTATES  84

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   278

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
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
      15,    16,    17,    18,    19,    20,    21,    22,    23
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     4,     9,    10,    15,    17,    20,    23,
      26,    29,    31,    33,    34,    38,    42,    46,    47,    55,
      56,    64,    67,    69,    73,    75,    76,    81,    83,    85,
      86,    91,    95,    96,   101,   103,   105,   107,   109,   115,
     116,   121,   123,   125,   129,   132
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      25,     0,    -1,    -1,     3,    26,    29,     4,    -1,    -1,
       3,    28,    29,     4,    -1,    30,    -1,    30,    29,    -1,
      31,    11,    -1,    33,    11,    -1,    38,    11,    -1,    34,
      -1,    36,    -1,    -1,     5,    32,    39,    -1,    43,    23,
      44,    -1,    47,    23,    44,    -1,    -1,     6,    14,    48,
      15,     7,    35,    27,    -1,    -1,     8,    14,    48,    15,
       9,    37,    27,    -1,    10,    40,    -1,    42,    -1,    42,
      13,    39,    -1,    44,    -1,    -1,    44,    13,    41,    40,
      -1,    19,    -1,    19,    -1,    -1,    44,    22,    45,    44,
      -1,    44,    21,    44,    -1,    -1,    14,    46,    44,    15,
      -1,    43,    -1,    47,    -1,    52,    -1,    50,    -1,    43,
      12,    14,    44,    15,    -1,    -1,    44,    20,    49,    44,
      -1,    18,    -1,    50,    -1,    50,    13,    51,    -1,    16,
      17,    -1,    16,    51,    17,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    69,    69,    69,    72,    72,    75,    76,    79,    80,
      81,    82,    83,    86,    86,    89,    90,    93,    93,    96,
      96,    99,   102,   103,   106,   107,   107,   110,   113,   116,
     116,   117,   118,   118,   119,   120,   121,   122,   125,   128,
     128,   131,   133,   134,   137,   138
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "BEGIN_KWD", "END", "TYPE", "IF_COND",
  "IF_BLOCK", "LOOP_COND", "LOOP_BLOCK", "PRINT", "SEMICOLON", "INDEX",
  "COMMA", "PAR_BEGIN", "PAR_END", "CONST_ARR_BEGIN", "CONST_ARR_END",
  "INT_VAL", "IDENTIFIER", "REL_OP", "DOT_OP", "OP", "ASSIGN", "$accept",
  "program", "$@1", "block", "$@2", "statement_list", "statement",
  "declarator", "$@3", "assignment", "conditional", "$@4", "loop", "$@5",
  "print", "variable_list", "expression_list", "$@6", "variable_declare",
  "variable_declared", "expression", "$@7", "$@8", "index", "cond", "$@9",
  "number", "numbers", "const_arr", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    24,    26,    25,    28,    27,    29,    29,    30,    30,
      30,    30,    30,    32,    31,    33,    33,    35,    34,    37,
      36,    38,    39,    39,    40,    41,    40,    42,    43,    45,
      44,    44,    46,    44,    44,    44,    44,    44,    47,    49,
      48,    50,    51,    51,    52,    52
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     4,     0,     4,     1,     2,     2,     2,
       2,     1,     1,     0,     3,     3,     3,     0,     7,     0,
       7,     2,     1,     3,     1,     0,     4,     1,     1,     0,
       4,     3,     0,     4,     1,     1,     1,     1,     5,     0,
       4,     1,     1,     3,     2,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     2,     0,     0,     1,    13,     0,     0,     0,    28,
       0,     6,     0,     0,    11,    12,     0,     0,     0,     0,
       0,     0,    32,     0,    41,    21,    34,    24,    35,    37,
      36,     3,     7,     8,     9,    10,     0,     0,     0,    27,
      14,    22,     0,     0,     0,     0,    44,    42,     0,    25,
       0,    29,     0,    15,    16,     0,    39,     0,     0,     0,
       0,    45,     0,    31,     0,     0,    23,     0,    17,    19,
      33,    43,    26,    30,    38,    40,     0,     0,     4,    18,
      20,     0,     0,     5
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     2,     3,    79,    81,    10,    11,    12,    19,    13,
      14,    76,    15,    77,    16,    40,    25,    62,    41,    26,
      27,    64,    45,    28,    43,    67,    29,    48,    30
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -19
static const yytype_int8 yypact[] =
{
       9,   -19,     7,     5,   -19,   -19,     2,    20,    13,   -19,
      14,     5,    30,    37,   -19,   -19,    38,    -6,    28,    33,
      13,    13,   -19,    26,   -19,   -19,    41,     1,   -19,   -19,
     -19,   -19,   -19,   -19,   -19,   -19,    40,    13,    13,   -19,
     -19,    42,    18,    43,    44,    13,   -19,    47,    39,   -19,
      13,   -19,    13,    24,    24,    33,   -19,    50,    52,     4,
      45,   -19,    13,   -19,    13,    15,   -19,    13,   -19,   -19,
     -19,   -19,   -19,   -19,   -19,    24,    59,    59,   -19,   -19,
     -19,     5,    60,   -19
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -19,   -19,   -19,   -12,   -19,    -9,   -19,   -19,   -19,   -19,
     -19,   -19,   -19,   -19,   -19,    11,     6,   -19,   -19,    -3,
     -17,   -19,   -19,    -2,    46,   -19,   -18,    10,   -19
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      17,    18,    32,    42,    42,    47,    36,     4,    17,    18,
       5,     6,     1,     7,    49,     8,    20,    37,    31,    70,
      53,    54,    50,    51,     9,    50,    51,    22,    59,    23,
      74,    24,     9,    63,    21,    65,    50,    51,    56,    50,
      51,    33,    47,    46,    24,    50,    51,    73,    34,    35,
      75,    38,    39,    36,    52,    55,    61,    68,    57,    58,
      60,    69,    78,    24,    83,    80,    66,    44,    72,     0,
      71,     0,    82,     0,     0,     0,     0,     0,    17,    18
};

static const yytype_int8 yycheck[] =
{
       3,     3,    11,    20,    21,    23,    12,     0,    11,    11,
       5,     6,     3,     8,    13,    10,    14,    23,     4,    15,
      37,    38,    21,    22,    19,    21,    22,    14,    45,    16,
      15,    18,    19,    50,    14,    52,    21,    22,    20,    21,
      22,    11,    60,    17,    18,    21,    22,    64,    11,    11,
      67,    23,    19,    12,    14,    13,    17,     7,    15,    15,
      13,     9,     3,    18,     4,    77,    55,    21,    62,    -1,
      60,    -1,    81,    -1,    -1,    -1,    -1,    -1,    81,    81
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,    25,    26,     0,     5,     6,     8,    10,    19,
      29,    30,    31,    33,    34,    36,    38,    43,    47,    32,
      14,    14,    14,    16,    18,    40,    43,    44,    47,    50,
      52,     4,    29,    11,    11,    11,    12,    23,    23,    19,
      39,    42,    44,    48,    48,    46,    17,    50,    51,    13,
      21,    22,    14,    44,    44,    13,    20,    15,    15,    44,
      13,    17,    41,    44,    45,    44,    39,    49,     7,     9,
      15,    51,    40,    44,    15,    44,    35,    37,     3,    27,
      27,    28,    29,     4
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (type, YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value, type); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, char (*type)[4])
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, type)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    char (*type)[4];
#endif
{
  if (!yyvaluep)
    return;
  YYUSE (type);
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, char (*type)[4])
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, type)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    char (*type)[4];
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep, type);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule, char (*type)[4])
#else
static void
yy_reduce_print (yyvsp, yyrule, type)
    YYSTYPE *yyvsp;
    int yyrule;
    char (*type)[4];
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       , type);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule, type); \
} while (YYID (0))

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
#ifndef	YYINITDEPTH
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
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

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, char (*type)[4])
#else
static void
yydestruct (yymsg, yytype, yyvaluep, type)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    char (*type)[4];
#endif
{
  YYUSE (yyvaluep);
  YYUSE (type);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (char (*type)[4]);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (char (*type)[4])
#else
int
yyparse (type)
    char (*type)[4];
#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
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
  int yytoken;
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

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

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
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
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
  *++yyvsp = yylval;

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
     `$$ = $1'.

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

/* Line 1455 of yacc.c  */
#line 69 "parser.y"
    { begin_program(); ;}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 69 "parser.y"
    { end_program(); return 0; ;}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 72 "parser.y"
    { begin_block(); ;}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 72 "parser.y"
    { end_block(); ;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 86 "parser.y"
    { strcpy(*type,yytext); ;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 89 "parser.y"
    { codegen_assign(); ;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 90 "parser.y"
    { codegen_assign(); ;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 93 "parser.y"
    { codegen_if(); ;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 96 "parser.y"
    { codegen_while(); ;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 99 "parser.y"
    { codegen_print(); ;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 106 "parser.y"
    { codegen_expList(); ;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 107 "parser.y"
    { codegen_expList(); ;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 110 "parser.y"
    { codegen_declare(type, yytext); ;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 113 "parser.y"
    { push(NULL, yytext, assert_var_status(yytext, true)); ;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 116 "parser.y"
    { push(NULL, yytext, OPERATOR); ;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 116 "parser.y"
    { codegen_arithmetic(); ;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 117 "parser.y"
    { codegen_dotproduct(); ;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 118 "parser.y"
    { push(NULL, yytext, OPERATOR); ;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 118 "parser.y"
    { push(NULL, yytext, OPERATOR); codegen_arithmetic(); ;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 121 "parser.y"
    { codegen_const_arr(); ;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 125 "parser.y"
    { codegen_index(); ;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 128 "parser.y"
    { push(NULL, yytext, REL_OPERATOR); ;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 128 "parser.y"
    { codegen_arithmetic(); ;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 131 "parser.y"
    { push(NULL, yytext, INT); ;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 134 "parser.y"
    { combine_numbers(); ;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 137 "parser.y"
    { gen_empty_arr(); ;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 138 "parser.y"
    { gen_const_arr(); ;}
    break;



/* Line 1455 of yacc.c  */
#line 1645 "parser.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (type, YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (type, yymsg);
	  }
	else
	  {
	    yyerror (type, YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
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
		      yytoken, &yylval, type);
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

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
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
		  yystos[yystate], yyvsp, type);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


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

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (type, YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval, type);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp, type);
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
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1675 of yacc.c  */
#line 140 "parser.y"


int main(void) {
    Table table;
    Stack stack;
    char type[TYPE_LEN];

    fp = fopen("output.c", "w");

    char zero[TOKEN_LEN];
    sprintf(zero, "%d", 0);

    table.size = 0;
    insert(&table, (Variable){0});
    get(&table, NULL, NULL, 0);
    update(&table, NULL, zero);
    find(&table, NULL);
    size(&table);

    stack.top = -1;
    push(&stack, NULL, EXP_LIST);
    pop(&stack, NULL);
    yyparse(&type);
    fclose(fp);
    return 0;
}

void yyerror(char (*type)[TYPE_LEN], char* s) {
	fprintf(stderr, "error: %s\n", s);
}

void error(char* s) {
    yyerror(NULL, s);
}

bool isInteger(char token[TOKEN_LEN]) {
    for(int i = (token[0] == '-'); i < TOKEN_LEN && token[i] != '\0'; i++) {
        if (!isdigit(token[i])) {
            return false;
        }
    }
    return true;
}

bool isConstArray(char token[TOKEN_LEN]) {
    return (token[0] == '[' && token[strnlen_s(token, TOKEN_LEN) - 1] == ']');
}

int getConstArrSize(char array[TOKEN_LEN]) {
    int elementCount = 0;
    bool began = false;
    while(strtok(((!began) ? array : NULL), ", []{}")) {
        began = true;
        elementCount++;
    }
    return elementCount;
}

TokenType assert_var_status(char var_name[TOKEN_LEN], bool required) {
    if((find(NULL, var_name) >= 0) != required) {
        char errorMsg[TOKEN_LEN];
        sprintf(errorMsg, "Variable %s %s.\n", var_name, (required ? " not declared" : " already declared."));
        error(errorMsg);
        exit(1);
    } else if(!required) {
        return 0;
    }
    Variable var;
    get(NULL, &var, var_name, 0);
    return var.type;
}

void combine_numbers() {
    char expVal[TOKEN_LEN];
    StackMember m1, m2;
    pop(NULL, &m2);
    pop(NULL, &m1);
    sprintf(expVal, "%s, %s", m1.token, m2.token);
    push(NULL, expVal, INT);
}

void gen_empty_arr() {
    char expVal[TOKEN_LEN];
    sprintf(expVal, "[]");
    push(NULL, expVal, ARR);
}

void gen_const_arr() {
    char expVal[TOKEN_LEN];
    StackMember m;
    pop(NULL, &m);
    sprintf(expVal, "[%s]", m.token);
    push(NULL, expVal, ARR);
}

void declare(char (*type)[4], char var_name[TOKEN_LEN]) {
     Variable var;
     bool isInt = strcmp(*type, "int") == 0;

     assert_var_status(var_name, false);

     strcpy(var.id, var_name);
     var.type = isInt;
     sprintf(var.arr_size, "%d", isInt);

     insert(NULL, var);
}

/* CODE GENERATORS */

void begin_program() {
    fprintf(fp, "#include <stdio.h>\n");
    fprintf(fp, "#include <malloc.h>\n");
    fprintf(fp, "#include <string.h>\n\n");
    
    tab_print(1);
    fprintf(fp, "int add_arrays(int *arr1, int len1, int *arr2, int len2, int** total) {\n");
    tab_print(0);
    fprintf(fp, "int i, min, max;\n");
    tab_print(0);
    fprintf(fp, "min = (len1 < len2) ? len1 : len2;\n");
    tab_print(0);
    fprintf(fp, "max = (len1 > len2) ? len1 : len2;\n");
    tab_print(0);
    fprintf(fp, "*total = malloc(sizeof(int) * max);\n");
    tab_print(1);
    fprintf(fp, "for(i = 0; i < min; i++) {\n");  
    tab_print(0);
    fprintf(fp, "(*total)[i] = arr1[i] + arr2[i];\n");
    tab_print(-1);
    fprintf(fp, "}\n");
    tab_print(1);
    fprintf(fp, "for(int *pMax = ((len1 > len2) ? arr1 : arr2);i < max; i++) {\n");
    tab_print(0);
    fprintf(fp, "(*total)[i] = pMax[i];\n");
    tab_print(-1);
    fprintf(fp, "}\n");
    tab_print(0);
    fprintf(fp, "return max;\n");
    tab_print(-1);
    fprintf(fp, "}\n\n");

    tab_print(1);
    fprintf(fp, "int sub_arrays(int *arr1, int len1, int *arr2, int len2, int** total) {\n");
    tab_print(0);
    fprintf(fp, "int i, min, max;\n");
    tab_print(0);
    fprintf(fp, "min = (len1 < len2) ? len1 : len2;\n");
    tab_print(0);
    fprintf(fp, "max = (len1 > len2) ? len1 : len2;\n");
    tab_print(0);
    fprintf(fp, "*total = malloc(sizeof(int) * max);\n");
    tab_print(1);
    fprintf(fp, "for(i = 0; i < min; i++) {\n");
    tab_print(0);
    fprintf(fp, "(*total)[i] = arr1[i] - arr2[i];\n");
    tab_print(-1);
    fprintf(fp, "}\n");
    tab_print(1);
    fprintf(fp, "for(int *pMax = ((len1 > len2) ? arr1 : arr2);i < max; i++) {\n");
    tab_print(0);
    fprintf(fp, "(*total)[i] = pMax[i] * ((len1 > len2) ? 1 : -1);\n");
    tab_print(-1);
    fprintf(fp, "}\n");
    tab_print(0);
    fprintf(fp, "return max;\n");
    tab_print(-1);
    fprintf(fp, "}\n\n");

    tab_print(1);
    fprintf(fp, "int mul_arrays(int *arr1, int len1, int *arr2, int len2, int** total) {\n");
    tab_print(0);
    fprintf(fp, "int i, min, max;\n");
    tab_print(0);
    fprintf(fp, "min = (len1 < len2) ? len1 : len2;\n");
    tab_print(0);
    fprintf(fp, "max = (len1 > len2) ? len1 : len2;\n");
    tab_print(0);
    fprintf(fp, "*total = malloc(sizeof(int) * max);\n");
    tab_print(1);
    fprintf(fp, "for(i = 0; i < min; i++) {\n");
    tab_print(0);
    fprintf(fp, "(*total)[i] = arr1[i] * arr2[i];\n");
    tab_print(-1);
    fprintf(fp, "}\n");
    tab_print(1);
    fprintf(fp, "for(;i < max; i++) {\n");
    tab_print(0);
    fprintf(fp, "(*total)[i] = 0;\n");
    tab_print(-1);
    fprintf(fp, "}\n");
    tab_print(0);
    fprintf(fp, "return max;\n");
    tab_print(-1);
    fprintf(fp, "}\n\n");

    tab_print(1);
    fprintf(fp, "int div_arrays(int *arr1, int len1, int *arr2, int len2, int** total) {\n");
    tab_print(0);
    fprintf(fp, "int i, min, max;\n");
    tab_print(0);
    fprintf(fp, "min = (len1 < len2) ? len1 : len2;\n");
    tab_print(0);
    fprintf(fp, "max = (len1 > len2) ? len1 : len2;\n");
    tab_print(0);
    fprintf(fp, "*total = malloc(sizeof(int) * max);\n");
    tab_print(1);
    fprintf(fp, "for(i = 0; i < min; i++) {\n");
    tab_print(0);
    fprintf(fp, "(*total)[i] = arr1[i] / arr2[i];\n");
    tab_print(-1);
    fprintf(fp, "}\n");
    tab_print(1);
    fprintf(fp, "for(int *pMax = ((len1 > len2) ? arr1 : arr2);i < max; i++) {\n");
    tab_print(1);
    fprintf(fp, "if(len1 > len2) {\n");
    tab_print(0);
    fprintf(fp, "fprintf(stderr, \"Division by zero: longer array divided by a shorter\\n\");\n");
    tab_print(0);
    fprintf(fp, "exit(1);\n");
    tab_print(-1);
    fprintf(fp, "}\n");
    tab_print(1);
    fprintf(fp, "else {\n");
    tab_print(0);
    fprintf(fp, "(*total)[i] = 0 / pMax[i];\n");
    tab_print(-1);
    fprintf(fp, "}\n");
    tab_print(-1);
    fprintf(fp, "}\n");
    tab_print(0);
    fprintf(fp, "return max;\n");
    tab_print(-1);
    fprintf(fp, "}\n\n");
    
    tab_print(1);
    fprintf(fp, "int dot_product_arrays(int *arr1, int len1, int *arr2, int len2) {\n");
	tab_print(0);
    fprintf(fp, "int sum = 0;\n");
	tab_print(1);
    fprintf(fp, "for(int i = 0; i < ((len1 < len2) ? len1 : len2); i++) {\n");
	tab_print(0);
    fprintf(fp, "sum += arr1[i] * arr2[i];\n");
	tab_print(-1);
    fprintf(fp, "}\n");
    tab_print(0);
	fprintf(fp, "return sum;\n");
    tab_print(-1);
    fprintf(fp, "}\n");

    fprintf(fp, "\n");
    tab_print(1);
    fprintf(fp, "int main() {\n");
    tab_print(0);
    fprintf(fp, "int **ts = NULL;\n");
    tab_print(0);
    fprintf(fp, "int *ls = NULL;\n");
    tab_print(0);
    fprintf(fp, "int lts = 0;\n\n");
}

void begin_block() {
    tab_print(1);
    fprintf(fp, "{\n"); 
}

void end_block() {
    
    tab_print(-1);
    fprintf(fp, "}\n");
}

void end_program() {
    fprintf(fp, "\n");
    codegen_free();
    tab_print(-1);
    fprintf(fp, "}\n");
}

void codegen_declare(char (*type)[TYPE_LEN], char var_name[TOKEN_LEN]) {
    declare(type, var_name);

    tab_print(0);
    if (strcmp(*type, "arr") == 0) {
        fprintf(fp, "int* %s = NULL;\n", yytext);
    } else {
        fprintf(fp, "int %s = 0;\n", yytext);
    }
}

void codegen_assign() {
    StackMember var_name, exp;
    pop(NULL, &exp);
    pop(NULL, &var_name);
    if(var_name.type == INT) {
        tab_print(0);
        fprintf(fp, "%s = %s;\n", var_name.token, exp.token);
    } else {
        tab_print(0);
        fprintf(fp, "%s = realloc(%s, sizeof(int) * ls[%d]);\n", var_name.token, var_name.token, lts - 1);
        tab_print(1);
        fprintf(fp, "for(int i = 0; i < ls[%d]; i++) {\n", lts - 1);
        tab_print(0);
        fprintf(fp, "%s[i] = ts[%d][i];\n", var_name.token, lts - 1);
        tab_print(-1);
        fprintf(fp, "}\n");
        update(NULL, var_name.token, ls_last);
    }
}

void codegen_arithmetic() {
    StackMember m1, m2, m3;
    char expVal[TOKEN_LEN];

    pop(NULL, &m3);
    pop(NULL, &m2);
    pop(NULL, &m1);

    if((m1.type != m3.type) || (m1.type == m3.type && m2.type == REL_OPERATOR && m1.type != INT)) {
        error("Type Mismatch.");
        exit(1);
    }

    switch(m1.type) {
    case INT:
        if(m2.type == REL_OPERATOR) {
            sprintf(expVal, "%s %s %s", m1.token, m2.token, m3.token);
        } else {
        tab_print(0);
        fprintf(fp, "lts++;\n");
        tab_print(0);
        fprintf(fp, "ts = realloc(ts, sizeof(int*) * lts);\n");
        tab_print(0);
        fprintf(fp, "ls = realloc(ls, sizeof(int) * lts);\n");
        tab_print(0);
        fprintf(fp, "ls[%d] = 1;\n", lts);
        tab_print(0);
        fprintf(fp, "ts[%d] = malloc(sizeof(int) * ls[%d]);\n", lts, lts);
        tab_print(0);
        fprintf(fp, "ts[%d][0] = %s %s %s;\n", lts, m1.token, m2.token, m3.token);
        Variable var;
        sprintf(var.id, "ts[%d]", lts);
        var.type = INT;
        strcpy(var.arr_size, ls_last);
        insert(NULL, var);
        sprintf(expVal, "ts[%d][0]", lts++);
        }
        push(NULL, expVal, INT);
        break;
    case ARR:
        char l1[TOKEN_LEN], l3[TOKEN_LEN];
        switch(m2.token[0]) {
            case '+':
                strcpy(m2.token, "add");
                break;
            case '-':
                strcpy(m2.token, "sub");
                break;
            case '*':
                strcpy(m2.token, "mul");
                break;
            case '/':
                strcpy(m2.token, "div");
                break;
        }
        if(isConstArray(m1.token)) {
            sprintf(l1,"%d", getConstArrSize(m1.token));
            push(NULL, m1.token, m1.type);
            codegen_const_arr();
            pop(NULL, &m1);
        } else {
            Variable var;
            get(NULL, &var, m1.token, 0);
            strcpy(l1, var.arr_size);
        }
        if(isConstArray(m3.token)) {
            sprintf(l3, "%d", getConstArrSize(m3.token));
            push(NULL, m3.token, m3.type);
            codegen_const_arr();
            pop(NULL, &m3);
        } else {
            Variable var;
            get(NULL, &var, m3.token, 0);
            strcpy(l3, var.arr_size);
        }
        tab_print(0);
        fprintf(fp, "lts++;\n");
        tab_print(0);
        fprintf(fp, "ts = realloc(ts, sizeof(int*) * lts);\n");
        tab_print(0);
        fprintf(fp, "ls = realloc(ls, sizeof(int) * lts);\n");
        tab_print(0);
        fprintf(fp, "ls[%d] = %s_arrays(%s, %s, %s, %s, &(ts[%d]));", lts, m2.token, m1.token, l1, m3.token, l3, lts);
        sprintf(ls_last, "((%s > %s) ? %s : %s)",l1, l3, l1, l3);
        Variable var;
        sprintf(var.id, "ts[%d]", lts);
        var.type = ARRAY;
        strcpy(var.arr_size, ls_last);
        insert(NULL, var);
        sprintf(expVal, "ts[%d]", lts++);
        push(NULL, expVal, INT);
        break;
    case OPERATOR:
        push(NULL, m2.token, m2.type);
        break;
    }
}

void codegen_dotproduct() {
    StackMember m1, m3;
    char l1[TOKEN_LEN], l3[TOKEN_LEN];
    char expVal[TOKEN_LEN];

    pop(NULL, &m3);
    pop(NULL, &m1);

    if((m1.type != m3.type) || (m1.type != ARR)) {
        error("Type Mismatch.");
        exit(1);
    }
    if(isConstArray(m1.token)) {
        sprintf(l1, "%d", getConstArrSize(m1.token));
        push(NULL, m1.token, m1.type);
        codegen_const_arr();
        pop(NULL, &m1);
    } else {
        Variable var;
        get(NULL, &var, m1.token, 0);
        strcpy(l1, var.arr_size);
    }
    if(isConstArray(m3.token)) {
        fprintf(stderr, "m3 const\n");
        sprintf(l3, "%d", getConstArrSize(m3.token));
        push(NULL, m3.token, m3.type);
        codegen_const_arr();
        pop(NULL, &m3);
    } else {
        Variable var;
        get(NULL, &var, m3.token, 0);
        strcpy(l3, var.arr_size);
    }
    tab_print(0);
    fprintf(fp, "lts++;\n");
    tab_print(0);
    fprintf(fp, "ts = realloc(ts, sizeof(int*) * lts);\n");
    tab_print(0);
    fprintf(fp, "ls = realloc(ls, sizeof(int) * lts);\n");
    tab_print(0);
    fprintf(fp, "ls[%d] = 1;\n", lts);
    tab_print(0);
    fprintf(fp, "ts[%d] = malloc(sizeof(int) * ls[%d]);\n", lts, lts);
    tab_print(0);
    fprintf(fp, "*ts[%d] = dot_product_arrays(%s, %s, %s, %s);\n", lts, m1.token, l1, m3.token, l3);
    Variable var;
    sprintf(var.id, "ts[%d]", lts);
    var.type = INTEGER;
    sprintf(var.arr_size, "%d", 1);
    strcpy(ls_last, var.arr_size);
    insert(NULL, var);
    sprintf(expVal, "*ts[%d]", lts++);
    push(NULL, expVal, INT);
}

void codegen_const_arr() {
    StackMember m;
    Variable var;
    pop(NULL, &m);

    char temp[TOKEN_LEN] = {0};
    strncpy(temp, m.token + 1, strlen(m.token) - 2);

    sprintf(var.id, "ts[%d]", lts);
    var.type = ARRAY;
    sprintf(var.arr_size, "%d", getConstArrSize(m.token));
    strcpy(ls_last, var.arr_size);
    insert(NULL, var);

    tab_print(0);
    fprintf(fp, "lts++;\n");
    tab_print(0);
    fprintf(fp, "ts = realloc(ts, sizeof(int*) * lts);\n");
    tab_print(0);
    fprintf(fp, "ls = realloc(ls, sizeof(int) * lts);\n");
    tab_print(0);
    fprintf(fp, "ls[%d] = %s;\n", lts, var.arr_size);
    tab_print(0);
    fprintf(fp, "ts[%d] = malloc(sizeof(int)*ls[lts-1]);\n", lts);
    tab_print(0);
    fprintf(fp, "memcpy(ts[%d], (int[]){%s}, sizeof(int) * ls[%d]);\n", lts, temp, lts);
    sprintf(m.token, "ts[%d]", lts++);

    push(NULL, m.token, m.type);
}

void codegen_index() {
    char expVal[TOKEN_LEN];
    StackMember arr, inx;
    Variable var;

    pop(NULL, &inx);
    pop(NULL, &arr);

    get(NULL, &var, arr.token, 0);
    tab_print(1);
    fprintf(fp, "if((%s) >= (%s)) {\n", inx.token, var.arr_size);
    tab_print(0);
    fprintf(fp, "%s = realloc(%s, sizeof(int) * ((%s) + 1));\n", arr.token, arr.token, inx.token);
    tab_print(-1);
    fprintf(fp, "}\n");
    sprintf(expVal, "((((%s) + 1) > ((%s) + 1)) ? (%s) : (%s))", inx.token, var.arr_size, inx.token, var.arr_size);
    update(NULL, arr.token, expVal);
    sprintf(expVal, "%s[%s]", arr.token, inx.token);
    push(NULL, expVal, INT);
}

void codegen_expList() {
    char expVal[TOKEN_LEN];
    if(expListCount) {
        StackMember exp1, exp2;
        pop(NULL, &exp2);
        pop(NULL, &exp1);
        if(exp2.type == ARR) {
            error("can\'t print array like this, please use a loop.");
            exit(1);
        }
        sprintf(expVal, "%s, %s", exp1.token, exp2.token);
    } else {
        StackMember exp;
        pop(NULL, &exp);
        if(exp.type == ARR) {
            error("can\'t print array like this, please use a loop.");
            exit(1);
        }
        sprintf(expVal, "%s", exp.token);
    }
    push(NULL, expVal, EXP_LIST);
    expListCount++; 
}

void codegen_print() {
    if(expListCount == 0) {
        error("can\'t print nothing");
    }

    StackMember expList;
    pop(NULL, &expList);

    tab_print(0);
    fprintf(fp, "printf(\"%c%c", '%', 'd');
    for(int i = 1; i < expListCount; i++) {
        fprintf(fp, ", %c%c", '%', 'd');
    }

    fprintf(fp, "\\n\", %s);\n", expList.token);
    expListCount = 0;
}

void codegen_if() {
    StackMember cond;
    pop(NULL, &cond);
    tab_print(0);
    fprintf(fp, "if(%s)\n", cond.token);
}

void codegen_while() {
    StackMember cond;
    pop(NULL, &cond);
    tab_print(0);
    fprintf(fp, "while(%s)\n", cond.token);
}

void codegen_free() {
    int tSize = size(NULL);
    Variable var;
    for(int i=0; i < tSize; i++) {
        get(NULL, &var, NULL, i);
        if (((var.id[0] == 't') && (var.id[1] == 's')) || var.type == ARRAY) {
            tab_print(0);
            fprintf(fp, "free(%s);\n", var.id);   // free(x)
        }
    }
    tab_print(0);
    fprintf(fp, "free(ls);\n");
    tab_print(0);
    fprintf(fp, "free(ts);\n");
}

void tab_print(int a) {
    static int tabCount = 0;
    if(a < 0)
        tabCount += a;
    for(int i = 0; i < tabCount; i++)
        fprintf(fp, "\t");
    if(a > 0)
        tabCount += a;
}
