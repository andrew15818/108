/* A Bison parser, made by GNU Bison 3.5.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "first.y"

/* * This is my first attempt * */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//still to define this one
#include "symbolTable.h"
#include "node.h"

extern char* yytext;
extern int line_no;
void yyerror(){
	printf("Error here %d: %s\n", line_no, yytext);
}

//creating the root node from the other header files
extern struct Node* root;

#line 89 "y.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
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
    STRING = 272,
    OF = 273,
    INTEGER = 274,
    REAL = 275,
    FUNCTION = 276,
    PROCEDURE = 277,
    PBEGIN = 278,
    AND = 279,
    OR = 280,
    END = 281,
    ASSIGNOP = 282,
    IF = 283,
    THEN = 284,
    ELSE = 285,
    WHILE = 286,
    DO = 287,
    LESSTHAN = 288,
    GREATERTHAN = 289,
    LEQ = 290,
    GEQ = 291,
    EQUAL = 292,
    NOTEQUAL = 293,
    PLUS = 294,
    MINUS = 295,
    MULTIPLY = 296,
    DIVIDE = 297,
    NOT = 298,
    RANGE = 299,
    BLANK = 300,
    COMMENT = 301,
    IDENTIFIER = 302,
    LPAREN = 303,
    RPAREN = 304
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
#define STRING 272
#define OF 273
#define INTEGER 274
#define REAL 275
#define FUNCTION 276
#define PROCEDURE 277
#define PBEGIN 278
#define AND 279
#define OR 280
#define END 281
#define ASSIGNOP 282
#define IF 283
#define THEN 284
#define ELSE 285
#define WHILE 286
#define DO 287
#define LESSTHAN 288
#define GREATERTHAN 289
#define LEQ 290
#define GEQ 291
#define EQUAL 292
#define NOTEQUAL 293
#define PLUS 294
#define MINUS 295
#define MULTIPLY 296
#define DIVIDE 297
#define NOT 298
#define RANGE 299
#define BLANK 300
#define COMMENT 301
#define IDENTIFIER 302
#define LPAREN 303
#define RPAREN 304

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 20 "first.y"

	struct Node* node;

#line 243 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */



#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))

/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

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

#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
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

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

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
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
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
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   133

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  50
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  28
/* YYNRULES -- Number of rules.  */
#define YYNRULES  65
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  131

#define YYUNDEFTOK  2
#define YYMAXUTOK   304


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    42,    42,    61,    66,    72,    82,    87,    94,   107,
     111,   116,   122,   128,   134,   146,   152,   162,   168,   175,
     183,   196,   200,   205,   215,   220,   224,   230,   235,   238,
     241,   248,   254,   258,   265,   271,   275,   280,   289,   292,
     300,   303,   308,   316,   320,   327,   331,   338,   342,   350,
     356,   364,   368,   372,   377,   382,   388,   392,   398,   403,
     409,   413,   417,   421,   425,   429
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "PROGRAM", "ID", "LPAR", "RPAR",
  "SEMICOLON", "PERIOD", "COMMA", "VAR", "COLON", "ARRAY", "LBRACKET",
  "RBRACKET", "NUM", "STRINGCONST", "STRING", "OF", "INTEGER", "REAL",
  "FUNCTION", "PROCEDURE", "PBEGIN", "AND", "OR", "END", "ASSIGNOP", "IF",
  "THEN", "ELSE", "WHILE", "DO", "LESSTHAN", "GREATERTHAN", "LEQ", "GEQ",
  "EQUAL", "NOTEQUAL", "PLUS", "MINUS", "MULTIPLY", "DIVIDE", "NOT",
  "RANGE", "BLANK", "COMMENT", "IDENTIFIER", "LPAREN", "RPAREN", "$accept",
  "prog", "identifier_list", "declarations", "type", "standard_type",
  "subprogram_declarations", "subprogram_declaration", "subprogram_head",
  "arguments", "parameter_list", "optional_var", "compound_statement",
  "optional_statements", "statement_list", "statement", "variable", "tail",
  "procedure_statement", "expression_list", "expression", "boolexpression",
  "simple_expression", "term", "factor", "addop", "mulop", "relop", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304
};
# endif

#define YYPACT_NINF (-104)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-36)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      17,    26,    51,    67,  -104,    74,  -104,    22,    73,    77,
    -104,  -104,    16,    74,    32,    27,    78,    79,     4,    80,
    -104,    76,    21,    81,    81,     2,     7,     7,  -104,    59,
      82,  -104,    61,  -104,  -104,    16,  -104,    83,  -104,  -104,
    -104,    84,  -104,    85,    86,    87,     7,     7,  -104,     5,
       7,  -104,  -104,  -104,  -104,     7,    60,    19,    30,    15,
    -104,    75,    66,  -104,     4,     7,    32,    88,  -104,  -104,
      93,    74,    -3,  -104,    36,  -104,    90,     7,  -104,    94,
    -104,     4,     7,     7,  -104,  -104,  -104,  -104,  -104,  -104,
       7,     7,  -104,  -104,     7,  -104,     4,  -104,  -104,  -104,
      48,  -104,    62,    95,  -104,     7,    92,    43,  -104,    71,
    -104,  -104,    15,    35,  -104,  -104,    91,    21,  -104,  -104,
    -104,  -104,     4,    96,   100,  -104,    97,    85,    21,  -104,
    -104
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     1,     0,     3,     0,     0,     0,
       6,     4,    13,     0,     0,     0,     0,     0,    32,     0,
       6,     0,     0,    18,    18,    36,     0,     0,    29,     0,
      24,    25,     0,    28,    12,    13,     2,     0,    11,     9,
      10,     0,     7,    22,     0,     0,     0,     0,    33,    35,
       0,    51,    53,    56,    57,     0,     0,    40,    43,    45,
      47,     0,     0,    23,    32,     0,     0,     0,     5,    21,
       0,     0,     0,    16,     0,    38,     0,     0,    49,     0,
      55,    32,     0,     0,    60,    61,    63,    64,    62,    65,
       0,     0,    58,    59,     0,    52,    32,    26,    27,    14,
       0,    17,     0,     0,    37,     0,    35,     0,    54,     0,
      41,    42,    46,    44,    48,    31,     0,     0,    15,    39,
      34,    50,    32,     0,    19,    30,     0,    22,     0,    20,
       8
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
    -104,  -104,   -10,    89,  -103,    39,    98,  -104,  -104,    99,
     -19,  -104,    -8,  -104,  -104,   -62,  -104,   -44,  -104,    37,
     -26,    -6,    25,    23,   -46,   -54,  -104,  -104
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     2,     7,    12,    41,    42,    14,    19,    20,    44,
      70,    71,    28,    29,    30,    31,    32,    48,    33,    74,
      75,    57,    58,    59,    60,    61,    94,    91
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      56,    62,    97,    15,    90,    78,    21,    46,    25,    80,
      77,    49,    50,    38,   124,    47,    39,    40,    47,   109,
       1,    76,    51,    52,    79,   130,    13,    18,     8,   -35,
       3,     9,    26,    37,   115,    27,     9,    38,    22,    98,
      39,    40,   104,    82,    83,   105,    53,    54,   114,   121,
      55,     4,   105,    16,    17,    18,    92,    93,    99,    90,
     125,   102,   120,    84,    85,    86,    87,    88,    89,    53,
      54,     9,     5,   117,    53,    54,   110,   111,     6,   119,
      10,    11,    23,    24,    36,    63,    43,    34,    65,    81,
      95,    68,   116,    64,    73,    69,    67,    72,    96,   101,
     108,   122,   118,   100,   106,    47,   123,   127,   129,    35,
     126,   103,     0,   112,   107,   128,   113,     0,     0,     0,
       0,     0,     0,    45,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    66
};

static const yytype_int16 yycheck[] =
{
      26,    27,    64,    13,    58,    49,    14,     5,     4,    55,
       5,     4,     5,    16,   117,    13,    19,    20,    13,    81,
       3,    47,    15,    16,    50,   128,    10,    23,     6,    27,
       4,     9,    28,    12,    96,    31,     9,    16,    11,    65,
      19,    20,     6,    24,    25,     9,    39,    40,    94,     6,
      43,     0,     9,    21,    22,    23,    41,    42,    66,   113,
     122,    71,   106,    33,    34,    35,    36,    37,    38,    39,
      40,     9,     5,    11,    39,    40,    82,    83,     4,   105,
       7,     4,     4,     4,     8,    26,     5,     7,    27,    29,
      15,     7,    44,    11,     7,    10,    13,    11,    32,     6,
       6,    30,     7,    15,    14,    13,    15,     7,   127,    20,
      14,    72,    -1,    90,    77,    18,    91,    -1,    -1,    -1,
      -1,    -1,    -1,    24,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    35
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,    51,     4,     0,     5,     4,    52,     6,     9,
       7,     4,    53,    10,    56,    52,    21,    22,    23,    57,
      58,    62,    11,     4,     4,     4,    28,    31,    62,    63,
      64,    65,    66,    68,     7,    53,     8,    12,    16,    19,
      20,    54,    55,     5,    59,    59,     5,    13,    67,     4,
       5,    15,    16,    39,    40,    43,    70,    71,    72,    73,
      74,    75,    70,    26,    11,    27,    56,    13,     7,    10,
      60,    61,    11,     7,    69,    70,    70,     5,    67,    70,
      74,    29,    24,    25,    33,    34,    35,    36,    37,    38,
      75,    77,    41,    42,    76,    15,    32,    65,    70,    62,
      15,     6,    52,    55,     6,     9,    14,    69,     6,    65,
      71,    71,    73,    72,    74,    65,    44,    11,     7,    70,
      67,     6,    30,    15,    54,    65,    14,     7,    18,    60,
      54
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    50,    51,    52,    52,    53,    53,    54,    54,    55,
      55,    55,    56,    56,    57,    58,    58,    59,    59,    60,
      60,    61,    61,    62,    63,    64,    64,    65,    65,    65,
      65,    65,    65,    66,    67,    67,    68,    68,    69,    69,
      70,    70,    70,    71,    71,    72,    72,    73,    73,    74,
      74,    74,    74,    74,    74,    74,    75,    75,    76,    76,
      77,    77,    77,    77,    77,    77
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,    10,     1,     3,     6,     0,     1,     8,     1,
       1,     1,     3,     0,     4,     6,     4,     3,     0,     4,
       6,     1,     0,     3,     1,     1,     3,     3,     1,     1,
       6,     4,     0,     2,     4,     0,     1,     4,     1,     3,
       1,     3,     3,     1,     3,     1,     3,     1,     3,     2,
       4,     1,     2,     1,     3,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
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


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
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
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
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
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
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
            else
              goto append;

          append:
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

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
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
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

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
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
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
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
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
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
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
          ++yyp;
          ++yyformat;
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
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

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
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
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
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
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
#line 45 "first.y"
              {
		root = (yyval.node)  = newNode(prog);	
		addNewChild((yyval.node), (yyvsp[-8].node));
		addNewChild((yyval.node), (yyvsp[-6].node));
		addNewChild((yyval.node), (yyvsp[-3].node));
		addNewChild((yyval.node), (yyvsp[-2].node));
		addNewChild((yyval.node), (yyvsp[-1].node));
		deleteNode((yyvsp[-9].node));
		deleteNode((yyvsp[-7].node));
		deleteNode((yyvsp[-5].node));
		deleteNode((yyvsp[-4].node));
		deleteNode((yyvsp[0].node));
	  }
#line 1524 "y.tab.c"
    break;

  case 3:
#line 61 "first.y"
                     {
		(yyval.node) = newNode(identifier_list);		
		printf("creating a new id List at %s\n", (yyvsp[0].node)->name);
		addNewChild((yyval.node), (yyvsp[0].node));
	  }
#line 1534 "y.tab.c"
    break;

  case 4:
#line 66 "first.y"
                          {
		printf("%s\n", (yyvsp[0].node)->name);
		(yyval.node) = (yyvsp[-2].node);		
		addNewChild((yyval.node), (yyvsp[0].node));
	  }
#line 1544 "y.tab.c"
    break;

  case 5:
#line 72 "first.y"
                                                                    {
		(yyval.node) = (yyvsp[-5].node);		
		//$$ = newNode(declarations);
		//addNewChild($$, $1);	
		addNewChild((yyval.node), (yyvsp[-3].node));	
		addNewChild((yyval.node), (yyvsp[-1].node));

		deleteNode((yyvsp[-2].node));
		deleteNode((yyvsp[0].node));
	  }
#line 1559 "y.tab.c"
    break;

  case 6:
#line 82 "first.y"
             {
		(yyval.node) = newNode(declarations);	
	  }
#line 1567 "y.tab.c"
    break;

  case 7:
#line 87 "first.y"
                    {
		//$$ = newNode(type);	
		(yyval.node) = (yyvsp[0].node);	
		//addNewChild($$, $1);
		//fprintf(stdout, "%d\n",$1->type);
	  }
#line 1578 "y.tab.c"
    break;

  case 8:
#line 94 "first.y"
                                               {
		(yyval.node) = newNode(array);
		//$$->specificType = array;
		addNewChild((yyval.node), (yyvsp[0].node));	
		addNewChild((yyval.node), (yyvsp[-5].node));
		addNewChild((yyval.node), (yyvsp[-3].node));
		deleteNode((yyvsp[-6].node));
		deleteNode((yyvsp[-4].node));
		deleteNode((yyvsp[-2].node));
		deleteNode((yyvsp[-1].node));
	  }
#line 1594 "y.tab.c"
    break;

  case 9:
#line 107 "first.y"
                       {
		(yyval.node) = newNode(integer_type);
		(yyval.node)->value = (yyvsp[0].node)->value;
	  }
#line 1603 "y.tab.c"
    break;

  case 10:
#line 111 "first.y"
      {
		(yyval.node) = newNode(real_type);
		addNewChild((yyval.node), (yyvsp[0].node));
	  }
#line 1612 "y.tab.c"
    break;

  case 11:
#line 116 "first.y"
              {
		(yyval.node) = newNode(string_type);	
		addNewChild((yyval.node), (yyvsp[0].node));
	  }
#line 1621 "y.tab.c"
    break;

  case 12:
#line 123 "first.y"
                                                                                {
		(yyval.node) = (yyvsp[-2].node);		
		addNewChild((yyval.node), (yyvsp[-1].node));
		deleteNode((yyvsp[0].node));
	  }
#line 1631 "y.tab.c"
    break;

  case 13:
#line 128 "first.y"
              {
	//am I even sure I exist? :'(
		(yyval.node) = newNode(subprogram_declarations);
	  }
#line 1640 "y.tab.c"
    break;

  case 14:
#line 137 "first.y"
                                                             {
		(yyval.node) = newNode(subprogram_declaration);		
		addNewChild((yyval.node), (yyvsp[-3].node));
		addNewChild((yyval.node), (yyvsp[-2].node));
		addNewChild((yyval.node), (yyvsp[-1].node));
		addNewChild((yyval.node), (yyvsp[0].node));
	  }
#line 1652 "y.tab.c"
    break;

  case 15:
#line 146 "first.y"
                                                                      {
			(yyval.node) = newNode(function);	
			addNewChild((yyval.node), (yyvsp[-4].node));
			addNewChild((yyval.node), (yyvsp[-3].node));
			addNewChild((yyval.node), (yyvsp[-1].node));
	  }
#line 1663 "y.tab.c"
    break;

  case 16:
#line 152 "first.y"
                                  {
		(yyval.node) = newNode(procedure);	
		printf("procedure\n");
		addNewChild((yyval.node), (yyvsp[-2].node));
		addNewChild((yyval.node), (yyvsp[-1].node));
		deleteNode((yyvsp[-3].node));
		deleteNode((yyvsp[0].node));
	  }
#line 1676 "y.tab.c"
    break;

  case 17:
#line 162 "first.y"
                                    {

		addNewChild((yyval.node), (yyvsp[-1].node));
		deleteNode((yyvsp[-2].node));
		deleteNode((yyvsp[0].node));
	  }
#line 1687 "y.tab.c"
    break;

  case 18:
#line 168 "first.y"
            {
		(yyval.node) = newNode(arguments);
	  }
#line 1695 "y.tab.c"
    break;

  case 19:
#line 175 "first.y"
                                                         {
		(yyval.node) = newNode(parameter_list);

		addNewChild((yyval.node), (yyvsp[-3].node));
		addNewChild((yyval.node), (yyvsp[-2].node));
		addNewChild((yyval.node), (yyvsp[0].node));
		deleteNode((yyvsp[-1].node));
	  }
#line 1708 "y.tab.c"
    break;

  case 20:
#line 183 "first.y"
                                                                    {
		//$$ = newNode(parameter_list);
		addNewChild((yyval.node), (yyvsp[-5].node));
		addNewChild((yyval.node), (yyvsp[-4].node));
		addNewChild((yyval.node), (yyvsp[-2].node));
		addNewChild((yyval.node), (yyvsp[0].node));
		deleteNode((yyvsp[-3].node));
		deleteNode((yyvsp[-1].node));
	  }
#line 1722 "y.tab.c"
    break;

  case 21:
#line 196 "first.y"
                  {
		//$$ = $1;
		addNewChild((yyval.node), (yyvsp[0].node));
	  }
#line 1731 "y.tab.c"
    break;

  case 22:
#line 200 "first.y"
             {
		(yyval.node) = newNode(optional_var);
	  }
#line 1739 "y.tab.c"
    break;

  case 23:
#line 207 "first.y"
                                           {
		 (yyval.node) = newNode(compound_statement);	
		 addNewChild((yyval.node), (yyvsp[-1].node));
		 deleteNode((yyvsp[-2].node));
		 deleteNode((yyvsp[0].node));
	  }
#line 1750 "y.tab.c"
    break;

  case 24:
#line 215 "first.y"
                                    {
		(yyval.node) = newNode(optional_statements);
		addNewChild((yyval.node), (yyvsp[0].node));
	  }
#line 1759 "y.tab.c"
    break;

  case 25:
#line 220 "first.y"
                         {
		(yyval.node) = newNode(statement_list);			  
		addNewChild((yyval.node), (yyvsp[0].node));
	}
#line 1768 "y.tab.c"
    break;

  case 26:
#line 224 "first.y"
                               {
		(yyval.node) = (yyvsp[-2].node);
		addNewChild((yyvsp[-2].node), (yyvsp[0].node));
	}
#line 1777 "y.tab.c"
    break;

  case 27:
#line 230 "first.y"
                                        {
		(yyval.node) = newNode(ASSIGNOP);
		addNewChild((yyval.node),(yyvsp[-2].node));
		addNewChild((yyval.node),(yyvsp[0].node));
	}
#line 1787 "y.tab.c"
    break;

  case 28:
#line 235 "first.y"
                     {
		(yyval.node) = (yyvsp[0].node);
	}
#line 1795 "y.tab.c"
    break;

  case 29:
#line 238 "first.y"
                    {
		(yyval.node) = (yyvsp[0].node);	
	}
#line 1803 "y.tab.c"
    break;

  case 30:
#line 241 "first.y"
                                                   {
		printf("if statement\n");
		(yyval.node) = newNode(IF);
		addNewChild((yyval.node), (yyvsp[-4].node));
		addNewChild((yyval.node), (yyvsp[-2].node));
		addNewChild((yyval.node), (yyvsp[0].node));
	}
#line 1815 "y.tab.c"
    break;

  case 31:
#line 248 "first.y"
                               {
		printf("while looperino\n");
		(yyval.node) = newNode(WHILE);
		addNewChild((yyval.node), (yyvsp[-2].node));
		addNewChild((yyval.node), (yyvsp[0].node));
	}
#line 1826 "y.tab.c"
    break;

  case 32:
#line 254 "first.y"
             {
		(yyval.node) = newNode(statement);
		}
#line 1834 "y.tab.c"
    break;

  case 33:
#line 258 "first.y"
                  {
		 (yyval.node) = newNode(variable);
		 addNewChild((yyval.node), (yyvsp[-1].node));
		 addNewChild((yyval.node), (yyvsp[0].node));
	  }
#line 1844 "y.tab.c"
    break;

  case 34:
#line 265 "first.y"
                                        {
		addNewChild((yyval.node), (yyvsp[-2].node));
		addNewChild((yyval.node), (yyvsp[0].node));
		deleteNode((yyvsp[-3].node));
		deleteNode((yyvsp[-1].node));
	  }
#line 1855 "y.tab.c"
    break;

  case 35:
#line 271 "first.y"
              {
		(yyval.node) = newNode(tail);	
	  }
#line 1863 "y.tab.c"
    break;

  case 36:
#line 275 "first.y"
                         {
		(yyval.node) = newNode(procedure_statement);
		printf("in procedure statement\n");
		addNewChild((yyval.node), (yyvsp[0].node));
	  }
#line 1873 "y.tab.c"
    break;

  case 37:
#line 280 "first.y"
                              {
		printf("hello from procedure statement\n\n\n");
		addNewChild((yyval.node), (yyvsp[-3].node));
		addNewChild((yyval.node), (yyvsp[-1].node));
		deleteNode((yyvsp[-2].node));
		deleteNode((yyvsp[0].node));
	  }
#line 1885 "y.tab.c"
    break;

  case 38:
#line 289 "first.y"
                            {
		addNewChild((yyval.node), (yyvsp[0].node));
	  }
#line 1893 "y.tab.c"
    break;

  case 39:
#line 292 "first.y"
                                   {
		(yyval.node) = (yyvsp[-2].node);
		addNewChild((yyval.node), (yyvsp[0].node));
		deleteNode((yyvsp[-1].node));
	  }
#line 1903 "y.tab.c"
    break;

  case 40:
#line 300 "first.y"
                           {
		(yyval.node) = newNode(expression); 
	  }
#line 1911 "y.tab.c"
    break;

  case 41:
#line 303 "first.y"
                                   {
		addNewChild((yyval.node), (yyvsp[-2].node));
		addNewChild((yyval.node), (yyvsp[-1].node));
		addNewChild((yyval.node), (yyvsp[0].node));
	  }
#line 1921 "y.tab.c"
    break;

  case 42:
#line 308 "first.y"
                                  {
		addNewChild((yyval.node), (yyvsp[-2].node));
		addNewChild((yyval.node), (yyvsp[-1].node));
		addNewChild((yyval.node), (yyvsp[0].node));
	  }
#line 1931 "y.tab.c"
    break;

  case 43:
#line 316 "first.y"
                                  {
		(yyval.node) = newNode(boolexpression);
		addNewChild((yyval.node), (yyvsp[0].node));
	  }
#line 1940 "y.tab.c"
    break;

  case 44:
#line 320 "first.y"
                                           {
		addNewChild((yyval.node), (yyvsp[-2].node));
		addNewChild((yyval.node), (yyvsp[-1].node));
		addNewChild((yyval.node), (yyvsp[0].node));
	  }
#line 1950 "y.tab.c"
    break;

  case 45:
#line 327 "first.y"
                        {
		(yyval.node) = newNode(simple_expression);
		addNewChild((yyval.node), (yyvsp[0].node));
	  }
#line 1959 "y.tab.c"
    break;

  case 46:
#line 331 "first.y"
                              {
		(yyval.node) = (yyvsp[-2].node);	
		addNewChild((yyval.node), (yyvsp[-1].node));
		addNewChild((yyval.node), (yyvsp[0].node));
	  }
#line 1969 "y.tab.c"
    break;

  case 47:
#line 338 "first.y"
             {
	 	(yyval.node) = newNode(term);
		addNewChild((yyval.node), (yyvsp[0].node));
  	  }
#line 1978 "y.tab.c"
    break;

  case 48:
#line 342 "first.y"
                   {
		(yyval.node) = (yyvsp[-2].node);
		addNewChild((yyval.node), (yyvsp[-1].node));	
		addNewChild((yyval.node), (yyvsp[0].node));	
	  }
#line 1988 "y.tab.c"
    break;

  case 49:
#line 350 "first.y"
                {
		(yyval.node) = newNode(factor);
		printf("in factor prod\n");
		addNewChild((yyval.node), (yyvsp[-1].node));
		addNewChild((yyval.node), (yyvsp[0].node));
	  }
#line 1999 "y.tab.c"
    break;

  case 50:
#line 356 "first.y"
                              {
		(yyval.node) = newNode(factor);
		printf("in factor prod\n");
		addNewChild((yyval.node), (yyvsp[-3].node));
		addNewChild((yyval.node), (yyvsp[-1].node));
		deleteNode((yyvsp[-2].node));
		deleteNode((yyvsp[0].node));
	  }
#line 2012 "y.tab.c"
    break;

  case 51:
#line 364 "first.y"
      {	
		(yyval.node) = newNode(factor);
		addNewChild((yyval.node), (yyvsp[0].node));
	  }
#line 2021 "y.tab.c"
    break;

  case 52:
#line 368 "first.y"
           {
		(yyval.node) = newNode(factor);
		addNewChild((yyval.node), (yyvsp[-1].node));
	}
#line 2030 "y.tab.c"
    break;

  case 53:
#line 372 "first.y"
             {

		(yyval.node) = newNode(factor);
		addNewChild((yyval.node), (yyvsp[0].node));
	}
#line 2040 "y.tab.c"
    break;

  case 54:
#line 377 "first.y"
                      {
		addNewChild((yyval.node),(yyvsp[-1].node));
		deleteNode((yyvsp[-2].node));
		deleteNode((yyvsp[0].node));
	  }
#line 2050 "y.tab.c"
    break;

  case 55:
#line 382 "first.y"
            {
		(yyval.node) = (yyvsp[0].node);
		addNewChild((yyval.node), (yyvsp[-1].node));
	  }
#line 2059 "y.tab.c"
    break;

  case 56:
#line 388 "first.y"
             {
		(yyval.node) = newNode(addop);
		addNewChild((yyval.node), (yyvsp[0].node));	
	  }
#line 2068 "y.tab.c"
    break;

  case 57:
#line 392 "first.y"
       {	
		(yyval.node) = newNode(addop);
		addNewChild((yyval.node), (yyvsp[0].node));	
	  }
#line 2077 "y.tab.c"
    break;

  case 58:
#line 398 "first.y"
                 {
		(yyval.node) = newNode(mulop);
		addNewChild((yyval.node), (yyvsp[0].node));
	  }
#line 2086 "y.tab.c"
    break;

  case 59:
#line 403 "first.y"
        {	
		(yyval.node) = newNode(mulop);
		addNewChild((yyval.node), (yyvsp[0].node));
	  }
#line 2095 "y.tab.c"
    break;

  case 60:
#line 409 "first.y"
                {
		(yyval.node) = newNode(relop);
		addNewChild((yyval.node), (yyvsp[0].node));
	  }
#line 2104 "y.tab.c"
    break;

  case 61:
#line 413 "first.y"
              {
		(yyval.node) = newNode(relop);
		addNewChild((yyval.node), (yyvsp[0].node));
	  }
#line 2113 "y.tab.c"
    break;

  case 62:
#line 417 "first.y"
       {
		(yyval.node) = newNode(relop);
		addNewChild((yyval.node), (yyvsp[0].node));
	  }
#line 2122 "y.tab.c"
    break;

  case 63:
#line 421 "first.y"
     {
		(yyval.node) = newNode(relop);
		addNewChild((yyval.node), (yyvsp[0].node));
	  }
#line 2131 "y.tab.c"
    break;

  case 64:
#line 425 "first.y"
     {
		(yyval.node) = newNode(relop);
		addNewChild((yyval.node), (yyvsp[0].node));
	  }
#line 2140 "y.tab.c"
    break;

  case 65:
#line 429 "first.y"
          {
		(yyval.node) = newNode(relop);
		addNewChild((yyval.node), (yyvsp[0].node));
}
#line 2149 "y.tab.c"
    break;


#line 2153 "y.tab.c"

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
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

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
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

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


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
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
#line 435 "first.y"

struct Node* root;
int main(){

	int hola = yyparse();	
	//traverse(root);
	struct symbolTable* mainTable = newTable();
	
	if(hola > 0){
		printf("after yyparse, res = %d\n", hola);
	}
		printf("********************************\n"
         	"*       No syntax error!       *\n"
         	"********************************\n");

	processNode(mainTable, root);
	//printSymbolTable(mainTable);
	if(hola==0){
		printf("Ok.\n");
	}
	 printf("********************************\n"
         "*       No semantic error!       *\n"
         "********************************\n");
	return hola;
}
