/* A Bison parser, made by GNU Bison 2.1.  */

/* Skeleton parser for Yacc-like parsing with Bison,
   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

/* Written by Richard Stallman by simplifying the original so called
   ``semantic'' parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0

/* Substitute the variable and function names.  */
#define yyparse slparse
#define yylex   sllex
#define yyerror slerror
#define yylval  sllval
#define yychar  slchar
#define yydebug sldebug
#define yynerrs slnerrs


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     SL_SURFACE = 258,
     SL_DISPLACEMENT = 259,
     SL_LIGHT = 260,
     SL_VOLUME = 261,
     SL_TRANSFORMATION = 262,
     SL_IMAGER = 263,
     SL_FOR = 264,
     SL_WHILE = 265,
     SL_IF = 266,
     SL_GATHER = 267,
     SL_ELSE = 268,
     SL_BREAK = 269,
     SL_CONTINUE = 270,
     SL_ILLUMINANCE = 271,
     SL_ILLUMINATE = 272,
     SL_SOLAR = 273,
     SL_RETURN = 274,
     SL_VOID = 275,
     SL_FCN_PI = 276,
     SL_IDENTIFIER_VALUE = 277,
     SL_FLOAT_VALUE = 278,
     SL_COMMA = 279,
     SL_SEMI_COLON = 280,
     SL_OPEN_PARANTHESIS = 281,
     SL_CLOSE_PARANTHESIS = 282,
     SL_OPEN_CRL_PARANTHESIS = 283,
     SL_CLOSE_CRL_PARANTHESIS = 284,
     SL_OPEN_SQR_PARANTHESIS = 285,
     SL_CLOSE_SQR_PARANTHESIS = 286,
     SL_TEXTURE = 287,
     SL_SHADOW = 288,
     SL_ENVIRONMENT = 289,
     SL_BUMP = 290,
     SL_TEXT_VALUE = 291,
     SL_COLON = 292,
     SL_QUESTION = 293,
     SL_STRING = 294,
     SL_MATRIX = 295,
     SL_NORMAL = 296,
     SL_VECTOR = 297,
     SL_POINT = 298,
     SL_COLOR = 299,
     SL_FLOAT = 300,
     SL_COMP_DIFFERENT = 301,
     SL_COMP_EQUAL = 302,
     SL_COMP_LESS_EQUAL = 303,
     SL_COMP_LESS = 304,
     SL_COMP_GREATER_EQUAL = 305,
     SL_COMP_GREATER = 306,
     SL_EQUAL = 307,
     SL_DECREMENT_BY = 308,
     SL_INCREMENT_BY = 309,
     SL_DECREMENT = 310,
     SL_INCREMENT = 311,
     SL_DIVIDE_BY = 312,
     SL_MULTIPLY_BY = 313,
     SL_MINUS = 314,
     SL_PLUS = 315,
     SL_CROSS = 316,
     SL_MULTIPLY = 317,
     SL_DIVIDE = 318,
     SL_DOT = 319,
     SL_OR = 320,
     SL_AND = 321,
     SL_NOT = 322,
     SL_OUTPUT = 323,
     SL_EXTERN = 324,
     SL_UNIFORM = 325,
     SL_VARIABLE = 326
   };
#endif
/* Tokens.  */
#define SL_SURFACE 258
#define SL_DISPLACEMENT 259
#define SL_LIGHT 260
#define SL_VOLUME 261
#define SL_TRANSFORMATION 262
#define SL_IMAGER 263
#define SL_FOR 264
#define SL_WHILE 265
#define SL_IF 266
#define SL_GATHER 267
#define SL_ELSE 268
#define SL_BREAK 269
#define SL_CONTINUE 270
#define SL_ILLUMINANCE 271
#define SL_ILLUMINATE 272
#define SL_SOLAR 273
#define SL_RETURN 274
#define SL_VOID 275
#define SL_FCN_PI 276
#define SL_IDENTIFIER_VALUE 277
#define SL_FLOAT_VALUE 278
#define SL_COMMA 279
#define SL_SEMI_COLON 280
#define SL_OPEN_PARANTHESIS 281
#define SL_CLOSE_PARANTHESIS 282
#define SL_OPEN_CRL_PARANTHESIS 283
#define SL_CLOSE_CRL_PARANTHESIS 284
#define SL_OPEN_SQR_PARANTHESIS 285
#define SL_CLOSE_SQR_PARANTHESIS 286
#define SL_TEXTURE 287
#define SL_SHADOW 288
#define SL_ENVIRONMENT 289
#define SL_BUMP 290
#define SL_TEXT_VALUE 291
#define SL_COLON 292
#define SL_QUESTION 293
#define SL_STRING 294
#define SL_MATRIX 295
#define SL_NORMAL 296
#define SL_VECTOR 297
#define SL_POINT 298
#define SL_COLOR 299
#define SL_FLOAT 300
#define SL_COMP_DIFFERENT 301
#define SL_COMP_EQUAL 302
#define SL_COMP_LESS_EQUAL 303
#define SL_COMP_LESS 304
#define SL_COMP_GREATER_EQUAL 305
#define SL_COMP_GREATER 306
#define SL_EQUAL 307
#define SL_DECREMENT_BY 308
#define SL_INCREMENT_BY 309
#define SL_DECREMENT 310
#define SL_INCREMENT 311
#define SL_DIVIDE_BY 312
#define SL_MULTIPLY_BY 313
#define SL_MINUS 314
#define SL_PLUS 315
#define SL_CROSS 316
#define SL_MULTIPLY 317
#define SL_DIVIDE 318
#define SL_DOT 319
#define SL_OR 320
#define SL_AND 321
#define SL_NOT 322
#define SL_OUTPUT 323
#define SL_EXTERN 324
#define SL_UNIFORM 325
#define SL_VARIABLE 326




/* Copy the first part of user declarations.  */
#line 60 "sl.y"

//////////////////////////////////////////////////////////////////////////
// Misc C definitions
//////////////////////////////////////////////////////////////////////////
#undef alloca
#include	<stdlib.h>
#include	<string.h>

#include	"common/global.h"
#include	"common/os.h"
#include	"opcodes.h"
#include	"sdr.h"

	void				yyerror(char *);				// Forward definition for stupid yacc
	int					yylex(void );					// Forward definition for stupid yacc
														
//////////////////////////////////////////////////////////////////////////
// Here's the only global CVariable
//////////////////////////////////////////////////////////////////////////
	CScriptContext		*sdr;

//////////////////////////////////////////////////////////////////////////




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

#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
#line 85 "sl.y"
typedef union YYSTYPE {
  char					*string;
  CExpression			*code;
  CExpression			*expression;
  float					real;
  int					integer;
  CArray<CExpression *>	*array;
} YYSTYPE;
/* Line 196 of yacc.c.  */
#line 270 "sl.cpp"
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 219 of yacc.c.  */
#line 282 "sl.cpp"

#if ! defined (YYSIZE_T) && defined (__SIZE_TYPE__)
# define YYSIZE_T __SIZE_TYPE__
#endif
#if ! defined (YYSIZE_T) && defined (size_t)
# define YYSIZE_T size_t
#endif
#if ! defined (YYSIZE_T) && (defined (__STDC__) || defined (__cplusplus))
# include <stddef.h> /* INFRINGES ON USER NAME SPACE */
# define YYSIZE_T size_t
#endif
#if ! defined (YYSIZE_T)
# define YYSIZE_T unsigned int
#endif

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

#if ! defined (yyoverflow) || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if defined (__STDC__) || defined (__cplusplus)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     define YYINCLUDED_STDLIB_H
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning. */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2005 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM ((YYSIZE_T) -1)
#  endif
#  ifdef __cplusplus
extern "C" {
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if (! defined (malloc) && ! defined (YYINCLUDED_STDLIB_H) \
	&& (defined (__STDC__) || defined (__cplusplus)))
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if (! defined (free) && ! defined (YYINCLUDED_STDLIB_H) \
	&& (defined (__STDC__) || defined (__cplusplus)))
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifdef __cplusplus
}
#  endif
# endif
#endif /* ! defined (yyoverflow) || YYERROR_VERBOSE */


#if (! defined (yyoverflow) \
     && (! defined (__cplusplus) \
	 || (defined (YYSTYPE_IS_TRIVIAL) && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  short int yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short int) + sizeof (YYSTYPE))			\
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined (__GNUC__) && 1 < __GNUC__
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
      while (0)
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (0)

#endif

#if defined (__STDC__) || defined (__cplusplus)
   typedef signed char yysigned_char;
#else
   typedef short int yysigned_char;
#endif

/* YYFINAL -- State number of the termination state. */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1484

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  72
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  105
/* YYNRULES -- Number of rules. */
#define YYNRULES  248
/* YYNRULES -- Number of states. */
#define YYNSTATES  443

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   326

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const unsigned char yytranslate[] =
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
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const unsigned short int yyprhs[] =
{
       0,     0,     3,     4,     7,     9,    11,    12,    14,    15,
      17,    18,    20,    22,    24,    26,    28,    30,    32,    37,
      40,    42,    46,    50,    55,    57,    58,    62,    65,    67,
      68,    72,    73,    78,    80,    81,    88,    89,    97,   101,
     106,   107,   108,   117,   119,   121,   123,   125,   127,   129,
     131,   132,   136,   139,   141,   142,   146,   149,   152,   153,
     158,   159,   163,   164,   172,   173,   180,   181,   183,   187,
     188,   193,   196,   199,   202,   203,   207,   208,   213,   214,
     221,   222,   230,   233,   235,   237,   239,   241,   244,   245,
     247,   249,   251,   253,   256,   259,   261,   263,   265,   267,
     269,   271,   273,   275,   277,   280,   282,   284,   286,   288,
     290,   292,   294,   296,   300,   303,   307,   310,   314,   317,
     322,   325,   328,   329,   334,   335,   343,   344,   349,   350,
     355,   358,   361,   362,   367,   368,   373,   374,   382,   383,
     391,   397,   403,   404,   412,   413,   421,   423,   433,   443,
     445,   446,   450,   452,   454,   455,   457,   458,   462,   464,
     468,   470,   478,   484,   492,   496,   498,   499,   505,   510,
     513,   518,   520,   526,   534,   544,   556,   562,   570,   580,
     592,   598,   608,   614,   624,   629,   637,   642,   650,   652,
     656,   660,   664,   668,   669,   674,   678,   681,   684,   690,
     694,   698,   700,   702,   704,   706,   708,   710,   712,   717,
     719,   721,   729,   763,   767,   770,   774,   778,   782,   786,
     790,   794,   798,   802,   806,   810,   814,   818,   821,   823,
     825,   828,   831,   834,   838,   840,   842,   846,   847,   855,
     861,   863,   865,   867,   869,   871,   872,   873,   878
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const short int yyrhs[] =
{
      73,     0,    -1,    -1,    74,    80,    -1,    70,    -1,    71,
      -1,    -1,    69,    -1,    -1,    68,    -1,    -1,    45,    -1,
      44,    -1,    42,    -1,    41,    -1,    43,    -1,    40,    -1,
      39,    -1,    76,    77,    75,    78,    -1,    82,    80,    -1,
      91,    -1,    79,    22,    26,    -1,    20,    22,    26,    -1,
      81,    83,    27,   106,    -1,    84,    -1,    -1,    85,    25,
      84,    -1,    85,    25,    -1,    85,    -1,    -1,    79,    86,
      87,    -1,    -1,    22,    88,    24,    87,    -1,    22,    -1,
      -1,    22,    30,    31,    89,    24,    87,    -1,    -1,    22,
      30,    23,    31,    90,    24,    87,    -1,    22,    30,    31,
      -1,    22,    30,    23,    31,    -1,    -1,    -1,    94,    22,
      26,    92,    95,    27,    93,   106,    -1,     3,    -1,     4,
      -1,     5,    -1,     6,    -1,     7,    -1,     8,    -1,    96,
      -1,    -1,    97,    25,    96,    -1,    97,    25,    -1,    97,
      -1,    -1,    79,    98,   105,    -1,    52,   160,    -1,    52,
     162,    -1,    -1,    22,    24,   101,   100,    -1,    -1,    22,
     102,    99,    -1,    -1,    22,    30,    23,    31,    24,   103,
     100,    -1,    -1,    22,    30,    23,    31,   104,    99,    -1,
      -1,   100,    -1,   100,    24,   105,    -1,    -1,    28,   107,
     117,    29,    -1,    79,   110,    -1,    52,   160,    -1,    52,
     162,    -1,    -1,    22,   111,   115,    -1,    -1,    22,   112,
     109,   115,    -1,    -1,    22,    30,    23,    31,   113,   115,
      -1,    -1,    22,    30,    23,    31,   114,   109,   115,    -1,
      24,   110,    -1,    25,    -1,   119,    -1,   118,    -1,     1,
      -1,   117,   116,    -1,    -1,   139,    -1,   124,    -1,   146,
      -1,   151,    -1,   126,    25,    -1,   129,    25,    -1,   120,
      -1,   121,    -1,   122,    -1,   154,    -1,   156,    -1,   158,
      -1,   106,    -1,   108,    -1,    82,    -1,   167,    25,    -1,
      25,    -1,   147,    -1,   152,    -1,   125,    -1,   140,    -1,
     155,    -1,   157,    -1,   159,    -1,    14,    23,    25,    -1,
      14,    25,    -1,    15,    23,    25,    -1,    15,    25,    -1,
      19,   160,    25,    -1,    19,    25,    -1,    10,    26,   166,
      27,    -1,   123,   118,    -1,   123,   119,    -1,    -1,    22,
      52,   127,   160,    -1,    -1,    22,    30,   160,    31,    52,
     128,   160,    -1,    -1,    22,    54,   130,   160,    -1,    -1,
      22,    53,   131,   160,    -1,    22,    56,    -1,    22,    55,
      -1,    -1,    22,    58,   132,   160,    -1,    -1,    22,    57,
     133,   160,    -1,    -1,    22,    30,   160,    31,    54,   134,
     160,    -1,    -1,    22,    30,   160,    31,    53,   135,   160,
      -1,    22,    30,   160,    31,    56,    -1,    22,    30,   160,
      31,    55,    -1,    -1,    22,    30,   160,    31,    58,   136,
     160,    -1,    -1,    22,    30,   160,    31,    57,   137,   160,
      -1,     9,    -1,   138,    26,   141,    25,   143,    25,   144,
      27,   118,    -1,   138,    26,   141,    25,   143,    25,   144,
      27,   119,    -1,   142,    -1,    -1,   126,    24,   142,    -1,
     126,    -1,   166,    -1,    -1,   145,    -1,    -1,   126,    24,
     145,    -1,   126,    -1,   129,    24,   145,    -1,   129,    -1,
      11,    26,   166,    27,   118,    13,   118,    -1,    11,    26,
     166,    27,   116,    -1,    11,    26,   166,    27,   118,    13,
     119,    -1,   148,    24,   160,    -1,   160,    -1,    -1,    12,
      26,   150,   148,    27,    -1,   149,   118,    13,   118,    -1,
     149,   116,    -1,   149,   118,    13,   119,    -1,    16,    -1,
     153,    26,   160,    27,   118,    -1,   153,    26,   160,    24,
     160,    27,   118,    -1,   153,    26,   160,    24,   160,    24,
     160,    27,   118,    -1,   153,    26,   160,    24,   160,    24,
     160,    24,   160,    27,   118,    -1,   153,    26,   160,    27,
     119,    -1,   153,    26,   160,    24,   160,    27,   119,    -1,
     153,    26,   160,    24,   160,    24,   160,    27,   119,    -1,
     153,    26,   160,    24,   160,    24,   160,    24,   160,    27,
     119,    -1,    17,    26,   160,    27,   118,    -1,    17,    26,
     160,    24,   160,    24,   160,    27,   118,    -1,    17,    26,
     160,    27,   119,    -1,    17,    26,   160,    24,   160,    24,
     160,    27,   119,    -1,    18,    26,    27,   118,    -1,    18,
      26,   160,    24,   160,    27,   118,    -1,    18,    26,    27,
     119,    -1,    18,    26,   160,    24,   160,    27,   119,    -1,
     164,    -1,   160,    60,   160,    -1,   160,    59,   160,    -1,
     160,    62,   160,    -1,   160,    63,   160,    -1,    -1,   160,
      64,   161,   160,    -1,   160,    61,   160,    -1,    60,   160,
      -1,    59,   160,    -1,   166,    38,   160,    37,   160,    -1,
      28,   163,    29,    -1,   160,    24,   163,    -1,   160,    -1,
      21,    -1,   126,    -1,   129,    -1,   165,    -1,   167,    -1,
      22,    -1,    22,    30,   160,    31,    -1,    23,    -1,    36,
      -1,    26,   160,    24,   160,    24,   160,    27,    -1,    26,
     160,    24,   160,    24,   160,    24,   160,    24,   160,    24,
     160,    24,   160,    24,   160,    24,   160,    24,   160,    24,
     160,    24,   160,    24,   160,    24,   160,    24,   160,    24,
     160,    27,    -1,    26,   160,    27,    -1,    79,   160,    -1,
      79,    36,   160,    -1,    26,   166,    27,    -1,   166,    66,
     166,    -1,   166,    65,   166,    -1,   160,    51,   160,    -1,
     160,    49,   160,    -1,   160,    50,   160,    -1,   160,    48,
     160,    -1,   160,    47,   160,    -1,   160,    46,   160,    -1,
     166,    47,   166,    -1,   166,    46,   166,    -1,    67,   166,
      -1,   172,    -1,   169,    -1,    22,    26,    -1,     3,    26,
      -1,     4,    26,    -1,   168,   174,    27,    -1,    36,    -1,
      22,    -1,    30,   160,    31,    -1,    -1,   173,    26,   170,
     171,    24,   174,    27,    -1,   173,    26,   170,   171,    27,
      -1,    32,    -1,    33,    -1,    34,    -1,    35,    -1,   175,
      -1,    -1,    -1,   160,    24,   176,   175,    -1,   160,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned short int yyrline[] =
{
       0,   247,   247,   247,   255,   260,   265,   272,   277,   283,
     288,   294,   299,   304,   309,   314,   319,   324,   331,   351,
     356,   371,   387,   398,   419,   424,   433,   440,   446,   456,
     455,   483,   482,   494,   506,   503,   521,   517,   537,   548,
     573,   584,   570,   605,   610,   615,   620,   625,   630,   639,
     644,   652,   659,   665,   675,   674,   701,   707,   718,   716,
     729,   728,   744,   739,   763,   759,   780,   787,   792,   805,
     804,   824,   845,   851,   860,   859,   873,   872,   891,   887,
     912,   908,   934,   940,   950,   957,   963,   973,   979,   988,
     993,   998,  1003,  1008,  1013,  1018,  1023,  1028,  1033,  1038,
    1043,  1048,  1053,  1058,  1063,  1068,  1077,  1082,  1087,  1092,
    1097,  1102,  1107,  1116,  1143,  1172,  1199,  1226,  1255,  1279,
    1292,  1302,  1317,  1315,  1340,  1335,  1391,  1389,  1411,  1409,
    1429,  1440,  1453,  1451,  1473,  1471,  1496,  1491,  1519,  1514,
    1537,  1551,  1570,  1565,  1593,  1588,  1615,  1621,  1638,  1657,
    1662,  1670,  1677,  1686,  1691,  1699,  1704,  1712,  1719,  1724,
    1731,  1740,  1755,  1764,  1781,  1788,  1798,  1796,  1812,  1825,
    1832,  1845,  1853,  1864,  1877,  1892,  1911,  1922,  1935,  1950,
    1971,  1982,  1999,  2010,  2029,  2039,  2054,  2064,  2081,  2086,
    2093,  2100,  2133,  2142,  2140,  2151,  2158,  2164,  2170,  2188,
    2197,  2205,  2213,  2218,  2223,  2228,  2233,  2238,  2251,  2291,
    2296,  2301,  2312,  2368,  2378,  2386,  2397,  2404,  2411,  2418,
    2426,  2434,  2442,  2450,  2458,  2466,  2474,  2482,  2493,  2533,
    2542,  2557,  2572,  2589,  2668,  2673,  2684,  2691,  2702,  2726,
    2750,  2763,  2776,  2789,  2806,  2810,  2817,  2815,  2824
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals. */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "SL_SURFACE", "SL_DISPLACEMENT",
  "SL_LIGHT", "SL_VOLUME", "SL_TRANSFORMATION", "SL_IMAGER", "SL_FOR",
  "SL_WHILE", "SL_IF", "SL_GATHER", "SL_ELSE", "SL_BREAK", "SL_CONTINUE",
  "SL_ILLUMINANCE", "SL_ILLUMINATE", "SL_SOLAR", "SL_RETURN", "SL_VOID",
  "SL_FCN_PI", "SL_IDENTIFIER_VALUE", "SL_FLOAT_VALUE", "SL_COMMA",
  "SL_SEMI_COLON", "SL_OPEN_PARANTHESIS", "SL_CLOSE_PARANTHESIS",
  "SL_OPEN_CRL_PARANTHESIS", "SL_CLOSE_CRL_PARANTHESIS",
  "SL_OPEN_SQR_PARANTHESIS", "SL_CLOSE_SQR_PARANTHESIS", "SL_TEXTURE",
  "SL_SHADOW", "SL_ENVIRONMENT", "SL_BUMP", "SL_TEXT_VALUE", "SL_COLON",
  "SL_QUESTION", "SL_STRING", "SL_MATRIX", "SL_NORMAL", "SL_VECTOR",
  "SL_POINT", "SL_COLOR", "SL_FLOAT", "SL_COMP_DIFFERENT", "SL_COMP_EQUAL",
  "SL_COMP_LESS_EQUAL", "SL_COMP_LESS", "SL_COMP_GREATER_EQUAL",
  "SL_COMP_GREATER", "SL_EQUAL", "SL_DECREMENT_BY", "SL_INCREMENT_BY",
  "SL_DECREMENT", "SL_INCREMENT", "SL_DIVIDE_BY", "SL_MULTIPLY_BY",
  "SL_MINUS", "SL_PLUS", "SL_CROSS", "SL_MULTIPLY", "SL_DIVIDE", "SL_DOT",
  "SL_OR", "SL_AND", "SL_NOT", "SL_OUTPUT", "SL_EXTERN", "SL_UNIFORM",
  "SL_VARIABLE", "$accept", "slStart", "@1", "slContainerClass",
  "slInheritanceClass", "slOutputClass", "slTypeSpecifier", "slTypeDecl",
  "slShader", "slFunctionHeader", "slFunction", "slFunctionParameterList",
  "slFunctionParameters", "slFunctionParameter", "@2",
  "slFunctionParameterIdentifierList", "@3", "@4", "@5", "slMain", "@6",
  "@7", "slShaderType", "slShaderParameterList", "slShaderParameters",
  "slShaderParameter", "@8", "slShaderParameterInitializer",
  "slShaderParameterIdentifierToken", "@9", "@10", "@11", "@12",
  "slShaderParameterIdentifierList", "slBlock", "@13",
  "slVariableDeclerations", "slVariableInitializer",
  "slVariableIdentifierList", "@14", "@15", "@16", "@17",
  "slVariableIdentifierTail", "slStatement", "slStatements",
  "slMatchedStatement", "slUnmatchedStatement", "slBreakStatement",
  "slContinueStatement", "slReturnStatement", "slWhileStartStatement",
  "slWhileStatement", "slUnmatchedWhileStatement", "slAssignmentStatement",
  "@18", "@19", "slUpdateStatement", "@20", "@21", "@22", "@23", "@24",
  "@25", "@26", "@27", "slForStartStatement", "slForStatement",
  "slUnmatchedForStatement", "slForInitStatement", "slForInitStatements",
  "slForCheckStatement", "slForIncrementStatement",
  "slForIncrementStatements", "slMatchedIfStatement",
  "slUnmatchedIfStatement", "slGatherParameterList", "slGatherHeader",
  "@28", "slMatchedGatherStatement", "slUnmatchedGatherStatement",
  "slIlluminanceStartStatement", "slIlluminanceStatement",
  "slUnmatchedIlluminanceStatement", "slIlluminateStatement",
  "slUnmatchedIlluminateStatement", "slSolarStatement",
  "slUnmatchedSolarStatement", "slAritmeticExpression", "@29",
  "slArrayList", "slArrayItems", "slAritmeticTerminalValue",
  "slAritmeticTypeCast", "slBooleanExpression", "slFunctionCall",
  "slFunCallHeader", "slFunCall", "slTextureNameSpecifier",
  "slTextureChannelSpecifier", "slTextureCall", "slTextureName",
  "slFunctionCallParameterList", "slFunctionCallParameters", "@30", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const unsigned short int yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned char yyr1[] =
{
       0,    72,    74,    73,    75,    75,    75,    76,    76,    77,
      77,    78,    78,    78,    78,    78,    78,    78,    79,    80,
      80,    81,    81,    82,    83,    83,    84,    84,    84,    86,
      85,    88,    87,    87,    89,    87,    90,    87,    87,    87,
      92,    93,    91,    94,    94,    94,    94,    94,    94,    95,
      95,    96,    96,    96,    98,    97,    99,    99,   101,   100,
     102,   100,   103,   100,   104,   100,   100,   105,   105,   107,
     106,   108,   109,   109,   111,   110,   112,   110,   113,   110,
     114,   110,   115,   115,   116,   116,   116,   117,   117,   118,
     118,   118,   118,   118,   118,   118,   118,   118,   118,   118,
     118,   118,   118,   118,   118,   118,   119,   119,   119,   119,
     119,   119,   119,   120,   120,   121,   121,   122,   122,   123,
     124,   125,   127,   126,   128,   126,   130,   129,   131,   129,
     129,   129,   132,   129,   133,   129,   134,   129,   135,   129,
     129,   129,   136,   129,   137,   129,   138,   139,   140,   141,
     141,   142,   142,   143,   143,   144,   144,   145,   145,   145,
     145,   146,   147,   147,   148,   148,   150,   149,   151,   152,
     152,   153,   154,   154,   154,   154,   155,   155,   155,   155,
     156,   156,   157,   157,   158,   158,   159,   159,   160,   160,
     160,   160,   160,   161,   160,   160,   160,   160,   160,   162,
     163,   163,   164,   164,   164,   164,   164,   164,   164,   164,
     164,   164,   164,   164,   165,   165,   166,   166,   166,   166,
     166,   166,   166,   166,   166,   166,   166,   166,   167,   167,
     168,   168,   168,   169,   170,   170,   171,   171,   172,   172,
     173,   173,   173,   173,   174,   174,   176,   175,   175
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     0,     2,     1,     1,     0,     1,     0,     1,
       0,     1,     1,     1,     1,     1,     1,     1,     4,     2,
       1,     3,     3,     4,     1,     0,     3,     2,     1,     0,
       3,     0,     4,     1,     0,     6,     0,     7,     3,     4,
       0,     0,     8,     1,     1,     1,     1,     1,     1,     1,
       0,     3,     2,     1,     0,     3,     2,     2,     0,     4,
       0,     3,     0,     7,     0,     6,     0,     1,     3,     0,
       4,     2,     2,     2,     0,     3,     0,     4,     0,     6,
       0,     7,     2,     1,     1,     1,     1,     2,     0,     1,
       1,     1,     1,     2,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     2,     3,     2,     3,     2,     4,
       2,     2,     0,     4,     0,     7,     0,     4,     0,     4,
       2,     2,     0,     4,     0,     4,     0,     7,     0,     7,
       5,     5,     0,     7,     0,     7,     1,     9,     9,     1,
       0,     3,     1,     1,     0,     1,     0,     3,     1,     3,
       1,     7,     5,     7,     3,     1,     0,     5,     4,     2,
       4,     1,     5,     7,     9,    11,     5,     7,     9,    11,
       5,     9,     5,     9,     4,     7,     4,     7,     1,     3,
       3,     3,     3,     0,     4,     3,     2,     2,     5,     3,
       3,     1,     1,     1,     1,     1,     1,     1,     4,     1,
       1,     7,    33,     3,     2,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     2,     1,     1,
       2,     2,     2,     3,     1,     1,     3,     0,     7,     5,
       1,     1,     1,     1,     1,     0,     0,     4,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const unsigned char yydefact[] =
{
       2,     0,     8,     1,    43,    44,    45,    46,    47,    48,
       0,     7,    10,     0,     3,     8,     8,    20,     0,     0,
       9,     6,     0,    29,     0,    24,    28,    19,     0,    22,
       4,     5,     0,    21,     0,     0,     8,    40,    17,    16,
      14,    13,    15,    12,    11,    18,    33,    30,    69,    23,
      26,     8,     0,     0,    88,    54,     0,    49,    53,     0,
      38,     0,     0,    66,    41,     8,    39,     0,    32,    86,
       0,     0,   146,     0,     0,     0,     0,     0,   171,     0,
       0,     8,     0,   105,    70,   240,   241,   242,   243,     0,
     103,   101,   102,    87,    85,    84,    95,    96,    97,     8,
      90,   108,     0,     0,     0,    89,   109,    91,   106,     0,
      92,   107,     0,    98,   110,    99,   111,   100,   112,     0,
       8,   229,   228,     0,    60,    67,    55,     0,    51,     0,
       0,   231,   232,     8,     8,   166,     0,   114,     0,   116,
       8,     8,   202,   207,   209,   118,     8,   210,     8,     8,
       8,     8,   203,   204,     0,   188,   205,     0,   206,   230,
       8,   122,   128,   126,   131,   130,   134,   132,    74,    71,
     120,   121,    93,    94,   150,   169,    85,     8,   104,   248,
       0,   244,     0,    58,     0,     0,    66,    42,     0,    35,
       0,     0,     0,     8,   113,   115,     0,     8,     0,     8,
       0,     0,   197,   196,   227,   210,   214,   117,     8,     8,
       8,     8,     8,     8,     8,     8,     8,     8,     8,   193,
       8,     8,     8,     8,     8,     0,     8,     8,     8,     8,
       8,     0,     0,     0,     0,   152,     0,   149,     8,     0,
     246,   233,   235,   234,   237,    66,     0,     8,    61,    68,
      37,   119,     0,     0,   165,     8,     8,   184,   186,     8,
       0,     8,   213,   216,   215,   224,   223,   222,   220,   221,
     219,   190,   189,   195,   191,   192,     8,     0,   226,   225,
     218,   217,     0,   123,   129,   127,   135,   133,     0,     0,
      83,    75,     8,     0,     8,     0,     8,   168,   170,     8,
       8,     8,     8,     0,    59,    64,     8,    56,    57,   162,
      85,     8,   167,     0,   180,   182,     0,   208,     0,   194,
       8,   124,   138,   136,   141,   140,   144,   142,    78,    74,
      82,    72,    73,    77,     0,   151,     0,   153,     0,   172,
     176,   247,     0,     8,   239,    62,     0,   201,     0,     8,
     164,     8,     8,     8,   198,     8,     8,     8,     8,     8,
       0,     0,     0,   156,     8,     8,   236,     0,    66,    65,
       8,   199,   161,   163,     0,   185,   187,     0,   125,   139,
     137,   145,   143,    79,     0,     0,   158,   160,     0,   155,
       0,   173,   177,   238,    63,   200,     8,     8,   211,    81,
       0,     0,     8,     8,     8,   181,   183,     0,   157,   159,
     147,   148,     0,   174,   178,     8,     8,     0,   175,   179,
       8,     0,     8,     0,     8,     0,     8,     0,     8,     0,
       8,     0,     8,     0,     8,     0,     8,     0,     8,     0,
       8,     0,   212
};

/* YYDEFGOTO[NTERM-NUM]. */
static const short int yydefgoto[] =
{
      -1,     1,     2,    32,    12,    21,    45,   151,    14,    15,
      90,    24,    25,    26,    34,    47,    53,    67,   129,    17,
      51,   127,    18,    56,    57,    58,    63,   248,   125,   245,
     185,   368,   346,   126,    91,    54,    92,   293,   169,   232,
     233,   360,   361,   291,    93,    62,    94,    95,    96,    97,
      98,    99,   100,   101,   152,   226,   355,   153,   228,   227,
     230,   229,   357,   356,   359,   358,   104,   105,   106,   236,
     237,   336,   388,   389,   107,   108,   253,   109,   193,   110,
     111,   112,   113,   114,   115,   116,   117,   118,   190,   276,
     308,   348,   155,   156,   157,   158,   120,   121,   244,   303,
     122,   123,   180,   181,   301
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -279
static const short int yypact[] =
{
    -279,    29,    34,  -279,  -279,  -279,  -279,  -279,  -279,  -279,
      14,  -279,    -9,    58,  -279,   -23,    34,  -279,    72,    70,
    -279,     2,    79,  -279,   107,  -279,    66,  -279,   109,  -279,
    -279,  -279,    69,  -279,   114,   110,   -19,  -279,  -279,  -279,
    -279,  -279,  -279,  -279,  -279,  -279,    32,  -279,  -279,  -279,
    -279,   -18,    -1,   133,  -279,  -279,   142,  -279,   146,   139,
     156,   114,   521,   162,  -279,   -17,   164,   165,  -279,  -279,
     160,   168,  -279,   170,   172,   176,    60,    65,  -279,   177,
     179,   383,   262,  -279,  -279,  -279,  -279,  -279,  -279,   184,
    -279,  -279,  -279,  -279,  -279,  -279,  -279,  -279,  -279,   704,
    -279,  -279,   183,   188,   197,  -279,  -279,  -279,  -279,   584,
    -279,  -279,   198,  -279,  -279,  -279,  -279,  -279,  -279,   200,
     724,  -279,  -279,   203,    51,   166,  -279,   110,  -279,   185,
     114,  -279,  -279,   846,   846,  -279,   201,  -279,   206,  -279,
     846,   745,  -279,   518,  -279,  -279,   846,  -279,   846,   846,
     846,   867,  -279,  -279,   637,  -279,  -279,   -21,  -279,  -279,
     846,  -279,  -279,  -279,  -279,  -279,  -279,  -279,     1,  -279,
    -279,  -279,  -279,  -279,   211,  -279,   221,   846,  -279,   945,
     208,  -279,   -15,  -279,   219,   191,   162,  -279,   114,  -279,
    1420,    95,   135,   846,  -279,  -279,   214,   704,   973,   846,
     586,   145,   115,   115,  -279,   635,  1420,  -279,   846,   846,
     846,   846,   846,   846,   846,   846,   846,   846,   846,  -279,
     846,   846,   846,   846,   846,  1346,   846,   846,   846,   846,
     846,   222,    23,   194,     3,   223,   226,  -279,   704,   797,
    -279,  -279,  -279,  -279,   218,   162,   224,   766,  -279,  -279,
    -279,  -279,   584,    -4,  1420,   846,   704,  -279,  -279,   846,
    1367,   846,  -279,  -279,  1420,   437,   437,   437,   437,   437,
     437,   115,   115,    64,   189,   189,   846,  1401,    11,    11,
     186,  -279,   163,    57,    57,    57,    57,    57,   235,   245,
    -279,  -279,   766,    23,   846,   211,   806,  -279,  -279,   846,
     704,   846,   846,    37,  -279,   233,   846,  1420,  -279,  -279,
     257,   846,  -279,   992,  -279,  -279,   409,   163,  1020,  -279,
     846,  -279,  -279,  -279,  -279,  -279,  -279,  -279,   227,     5,
    -279,  1420,  -279,  -279,  1373,  -279,   246,   -21,   892,  -279,
    -279,  -279,  1394,   724,  -279,  -279,   191,  1026,   251,   704,
    1420,   846,   704,   846,  1420,   846,   846,   846,   846,   846,
      23,   194,   232,   268,   846,   704,  -279,   272,   162,  -279,
     846,  -279,  -279,  -279,  1294,  -279,  -279,   898,    57,    57,
      57,    57,    57,  -279,    23,    13,   276,   277,   278,  -279,
     939,  -279,  -279,  -279,  -279,  -279,   704,   846,  -279,  -279,
     268,   268,   704,   846,   704,  -279,  -279,  1054,  -279,  -279,
    -279,  -279,  1319,  -279,  -279,   846,   704,  1073,  -279,  -279,
     846,  1101,   846,  1107,   846,  1135,   846,  1154,   846,  1182,
     846,  1188,   846,  1216,   846,  1235,   846,  1263,   846,  1269,
     846,  1325,  -279
};

/* YYPGOTO[NTERM-NUM].  */
static const short int yypgoto[] =
{
    -279,  -279,  -279,  -279,  -279,  -279,  -279,    -2,   288,  -279,
      16,  -279,   270,  -279,  -279,   -56,  -279,  -279,  -279,  -279,
    -279,  -279,  -279,  -279,   242,  -279,  -279,   -34,  -243,  -279,
    -279,  -279,  -279,   127,   -32,  -279,  -279,   -40,    33,  -279,
    -279,  -279,  -279,  -278,  -108,  -279,   -93,    88,  -279,  -279,
    -279,  -279,  -279,  -279,    30,  -279,  -279,   113,  -279,  -279,
    -279,  -279,  -279,  -279,  -279,  -279,  -279,  -279,  -279,  -279,
      38,  -279,  -279,  -277,  -279,  -279,  -279,  -279,  -279,  -279,
    -279,  -279,  -279,  -279,  -279,  -279,  -279,  -279,   -62,  -279,
      35,   -46,  -279,  -279,  -122,    31,  -279,  -279,  -279,  -279,
    -279,  -279,   -14,    27,  -279
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -246
static const short int yytable[] =
{
      13,   175,   304,    49,   -25,    68,   170,   242,   -27,   -50,
     -52,   191,   192,    23,    13,   333,   176,   220,    16,   154,
     311,   243,    59,   312,   201,   221,   222,    33,   204,     3,
      60,   231,    16,   294,    23,   231,    19,     4,     5,     6,
       7,     8,     9,   160,   223,   224,    11,   289,   290,    55,
      11,    11,    11,   -76,    10,   161,   -31,   -76,   179,    20,
      89,   343,    52,    55,   344,   161,   162,   163,   164,   165,
     166,   167,    30,    31,   189,   183,   223,   224,   196,   198,
      22,   184,   383,   136,   200,   137,   202,   203,   138,   206,
     139,    36,   102,   119,    28,   187,    29,    89,   225,   278,
     279,   280,   281,    11,   257,    33,   399,    89,    38,    39,
      40,    41,    42,    43,    44,   239,   214,   215,   216,   217,
     218,   219,   251,   408,   409,   394,   217,   218,   219,   102,
     119,   254,   250,   220,    35,    37,    46,   260,    48,   102,
     119,   221,   222,   264,   309,   297,   265,   266,   267,   268,
     269,   270,   271,   272,   273,   274,   275,    61,   277,   310,
     223,   224,   252,   314,   283,   284,   285,   286,   287,    64,
      66,    65,   263,   220,   337,   103,   216,   217,   218,   219,
     -34,   221,   222,   220,   124,   307,   131,   171,   -36,   130,
     186,   221,   222,   313,   132,    89,   133,   316,   134,   318,
     223,   224,   135,   140,   235,   141,   168,   339,   172,   188,
     223,   224,   103,   173,   319,   321,   322,   323,   324,   325,
     326,   327,   103,   174,   177,   178,   194,   102,   119,   182,
     331,   195,   334,   234,   238,   241,    89,   338,   255,   179,
     342,   256,   246,   247,   347,   288,   292,   295,   302,   350,
      89,   296,   224,   219,    89,   305,   372,   345,   354,   375,
     208,   209,   210,   211,   212,   213,   328,   329,   102,   119,
     349,   363,   391,   214,   215,   216,   217,   218,   219,   -80,
     371,   179,   102,   119,   321,   258,   102,   119,   159,   374,
     385,   377,   160,   378,   379,   380,   381,   382,    89,   393,
     400,   401,   390,   405,    27,   402,    50,   128,   347,   410,
     103,   413,   369,   249,   161,   162,   163,   164,   165,   166,
     167,   384,   330,   418,   395,   235,   298,   332,   341,   367,
     102,   119,     0,   335,     0,   407,     0,     0,     0,     0,
       0,   412,     0,     0,   315,     0,     0,    89,     0,     0,
      89,   103,     0,   417,     0,     0,     0,     0,   421,     0,
     423,     0,   425,    89,   427,   103,   429,     0,   431,   103,
     433,     0,   435,     0,   437,     0,   439,     0,   441,   102,
     119,     0,   102,   119,     0,     0,    70,    71,   340,     0,
       0,     0,     0,   386,    89,   102,   119,     0,     0,     0,
      89,     0,    89,     0,   142,   143,   144,     0,   145,   146,
       0,     0,     0,   103,    89,    85,    86,    87,    88,   147,
       0,     0,     0,     0,     0,     0,   102,   119,     0,     0,
     386,   386,   102,   119,   102,   119,   352,   373,     0,     0,
     376,     0,   148,   149,     0,     0,   102,   119,     0,     0,
     150,     0,    11,   392,     0,   208,   209,   210,   211,   212,
     213,     0,   103,     0,     0,   103,     0,     0,   214,   215,
     216,   217,   218,   219,     0,     0,   387,     0,   103,     0,
       0,     0,     0,     0,   406,   210,   211,   212,   213,     0,
     411,     0,   414,     0,     0,     0,   214,   215,   216,   217,
     218,   219,     0,     0,   419,     0,     0,     0,     0,   103,
       0,     0,     0,   387,   387,   103,     0,   103,     0,     0,
       0,     0,    69,     0,    70,    71,     0,     0,     0,   103,
      72,    73,    74,    75,     0,    76,    77,    78,    79,    80,
      81,    10,     0,    82,   159,     0,    83,     0,   199,    48,
      84,     0,     0,    85,    86,    87,    88,     0,     0,     0,
      -8,    -8,    -8,    -8,    -8,    -8,    -8,     0,     0,     0,
     161,   162,   163,   164,   165,   166,   167,     0,     0,     0,
       0,     0,     0,     0,     0,    69,     0,    70,    71,    -8,
      11,    -8,    -8,    72,    73,    74,    75,     0,    76,    77,
      78,    79,    80,    81,    10,     0,    82,     0,     0,    83,
     261,     0,    48,   262,     0,     0,    85,    86,    87,    88,
       0,     0,     0,    -8,    -8,    -8,    -8,    -8,    -8,    -8,
       0,     0,   208,   209,   210,   211,   212,   213,    70,    71,
       0,     0,     0,     0,     0,   214,   215,   216,   217,   218,
     219,     0,    -8,    11,    -8,    -8,   142,   143,   144,     0,
       0,   146,   207,     0,     0,     0,     0,    85,    86,    87,
      88,   147,     0,     0,    -8,    -8,    -8,    -8,    -8,    -8,
      -8,     0,     0,   208,   209,   210,   211,   212,   213,     0,
       0,     0,     0,     0,   148,   149,   214,   215,   216,   217,
     218,   219,   150,    -8,    11,    -8,    -8,    70,    71,     0,
       0,     0,     0,    72,    73,    74,    75,     0,    76,    77,
      78,    79,    80,    81,    10,     0,    82,    70,    71,    83,
       0,     0,    48,     0,     0,     0,    85,    86,    87,    88,
       0,     0,     0,     0,     0,   142,   143,   144,    70,    71,
     146,  -245,     0,     0,     0,     0,    85,    86,    87,    88,
     147,     0,     0,     0,     0,     0,   142,   143,   144,    70,
      71,   146,   197,    11,     0,     0,     0,    85,    86,    87,
      88,   147,     0,   148,   149,     0,     0,   142,   143,   144,
       0,   150,   146,    11,   306,     0,     0,     0,    85,    86,
      87,    88,   147,     0,   148,   149,     0,     0,     0,    70,
      71,     0,   150,     0,    11,     0,     0,     0,     0,     0,
       0,   299,     0,     0,   300,   148,   149,   142,   143,   144,
       0,  -154,   146,   150,     0,    11,     0,     0,    85,    86,
      87,    88,   147,   208,   209,   210,   211,   212,   213,    70,
      71,     0,     0,     0,     0,     0,   214,   215,   216,   217,
     218,   219,     0,     0,     0,   148,   149,   142,   143,   144,
      70,    71,   146,   150,     0,    11,     0,     0,    85,    86,
      87,    88,   147,     0,     0,     0,     0,     0,   142,   143,
     144,     0,     0,   146,     0,     0,     0,     0,     0,    85,
      86,    87,    88,   205,     0,   148,   149,     0,     0,     0,
       0,     0,     0,   150,     0,    11,   364,     0,     0,   365,
       0,     0,   397,     0,     0,   398,   148,   149,     0,     0,
       0,     0,     0,     0,   150,     0,    11,     0,   208,   209,
     210,   211,   212,   213,   208,   209,   210,   211,   212,   213,
       0,   214,   215,   216,   217,   218,   219,   214,   215,   216,
     217,   218,   219,   403,     0,     0,   404,     0,     0,   240,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   208,   209,   210,   211,   212,
     213,   208,   209,   210,   211,   212,   213,   259,   214,   215,
     216,   217,   218,   219,   214,   215,   216,   217,   218,   219,
       0,     0,     0,     0,     0,     0,   351,     0,     0,   208,
     209,   210,   211,   212,   213,     0,     0,     0,     0,     0,
       0,     0,   214,   215,   216,   217,   218,   219,   208,   209,
     210,   211,   212,   213,   353,     0,     0,     0,     0,     0,
     370,   214,   215,   216,   217,   218,   219,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   208,   209,   210,   211,
     212,   213,   208,   209,   210,   211,   212,   213,   415,   214,
     215,   216,   217,   218,   219,   214,   215,   216,   217,   218,
     219,     0,     0,     0,     0,     0,     0,   420,     0,     0,
     208,   209,   210,   211,   212,   213,     0,     0,     0,     0,
       0,     0,     0,   214,   215,   216,   217,   218,   219,   208,
     209,   210,   211,   212,   213,   422,     0,     0,     0,     0,
       0,   424,   214,   215,   216,   217,   218,   219,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   208,   209,   210,
     211,   212,   213,   208,   209,   210,   211,   212,   213,   426,
     214,   215,   216,   217,   218,   219,   214,   215,   216,   217,
     218,   219,     0,     0,     0,     0,     0,     0,   428,     0,
       0,   208,   209,   210,   211,   212,   213,     0,     0,     0,
       0,     0,     0,     0,   214,   215,   216,   217,   218,   219,
     208,   209,   210,   211,   212,   213,   430,     0,     0,     0,
       0,     0,   432,   214,   215,   216,   217,   218,   219,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   208,   209,
     210,   211,   212,   213,   208,   209,   210,   211,   212,   213,
     434,   214,   215,   216,   217,   218,   219,   214,   215,   216,
     217,   218,   219,     0,     0,     0,     0,     0,     0,   436,
       0,     0,   208,   209,   210,   211,   212,   213,     0,     0,
       0,     0,     0,     0,     0,   214,   215,   216,   217,   218,
     219,   208,   209,   210,   211,   212,   213,   438,     0,     0,
       0,     0,     0,   440,   214,   215,   216,   217,   218,   219,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   208,
     209,   210,   211,   212,   213,   208,   209,   210,   211,   212,
     213,   396,   214,   215,   216,   217,   218,   219,   214,   215,
     216,   217,   218,   219,     0,     0,     0,     0,     0,     0,
     208,   209,   210,   211,   212,   213,   416,     0,     0,     0,
       0,     0,   442,   214,   215,   216,   217,   218,   219,     0,
       0,     0,     0,     0,     0,   208,   209,   210,   211,   212,
     213,   208,   209,   210,   211,   212,   213,   282,   214,   215,
     216,   217,   218,   219,   214,   215,   216,   217,   218,   219,
       0,     0,   208,   209,   210,   211,   212,   213,   317,     0,
       0,     0,     0,     0,   362,   214,   215,   216,   217,   218,
     219,     0,     0,   208,   209,   210,   211,   212,   213,   208,
     209,   210,   211,   212,   213,   366,   214,   215,   216,   217,
     218,   219,   214,   215,   216,   217,   218,   219,   320,     0,
     208,   209,   210,   211,   212,   213,     0,   208,   209,   210,
     211,   212,   213,   214,   215,   216,   217,   218,   219,     0,
     214,   215,   216,   217,   218,   219,   208,   209,   210,   211,
     212,   213,     0,     0,     0,     0,     0,     0,     0,   214,
     215,   216,   217,   218,   219
};

static const short int yycheck[] =
{
       2,   109,   245,    35,    27,    61,    99,    22,    27,    27,
      27,   133,   134,    15,    16,   293,   109,    38,     2,    81,
      24,    36,    23,    27,   146,    46,    47,    26,   150,     0,
      31,    30,    16,    30,    36,    30,    22,     3,     4,     5,
       6,     7,     8,    30,    65,    66,    69,    24,    25,    51,
      69,    69,    69,    52,    20,    52,    24,    52,   120,    68,
      62,    24,    30,    65,    27,    52,    53,    54,    55,    56,
      57,    58,    70,    71,   130,    24,    65,    66,   140,   141,
      22,    30,   360,    23,   146,    25,   148,   149,    23,   151,
      25,    25,    62,    62,    22,   127,    26,    99,   160,   221,
     222,   223,   224,    69,   197,    26,   384,   109,    39,    40,
      41,    42,    43,    44,    45,   177,    59,    60,    61,    62,
      63,    64,    27,   400,   401,   368,    62,    63,    64,    99,
      99,   193,   188,    38,    27,    26,    22,   199,    28,   109,
     109,    46,    47,   205,   252,   238,   208,   209,   210,   211,
     212,   213,   214,   215,   216,   217,   218,    24,   220,   252,
      65,    66,    27,   256,   226,   227,   228,   229,   230,    27,
      31,    25,    27,    38,   296,    62,    61,    62,    63,    64,
      24,    46,    47,    38,    22,   247,    26,    99,    24,    24,
      24,    46,    47,   255,    26,   197,    26,   259,    26,   261,
      65,    66,    26,    26,   174,    26,    22,   300,    25,    24,
      65,    66,    99,    25,   276,    52,    53,    54,    55,    56,
      57,    58,   109,    26,    26,    25,    25,   197,   197,    26,
     292,    25,   294,    22,    13,    27,   238,   299,    24,   301,
     302,    27,    23,    52,   306,    23,    52,    24,    30,   311,
     252,    25,    66,    64,   256,    31,   349,    24,   320,   352,
      46,    47,    48,    49,    50,    51,    31,    22,   238,   238,
      13,    25,   365,    59,    60,    61,    62,    63,    64,    52,
      29,   343,   252,   252,    52,   197,   256,   256,    26,   351,
      22,   353,    30,   355,   356,   357,   358,   359,   300,    27,
      24,    24,   364,   396,    16,    27,    36,    65,   370,   402,
     197,   404,   346,   186,    52,    53,    54,    55,    56,    57,
      58,   361,   289,   416,   370,   295,   238,   292,   301,   343,
     300,   300,    -1,   295,    -1,   397,    -1,    -1,    -1,    -1,
      -1,   403,    -1,    -1,   256,    -1,    -1,   349,    -1,    -1,
     352,   238,    -1,   415,    -1,    -1,    -1,    -1,   420,    -1,
     422,    -1,   424,   365,   426,   252,   428,    -1,   430,   256,
     432,    -1,   434,    -1,   436,    -1,   438,    -1,   440,   349,
     349,    -1,   352,   352,    -1,    -1,     3,     4,   300,    -1,
      -1,    -1,    -1,   363,   396,   365,   365,    -1,    -1,    -1,
     402,    -1,   404,    -1,    21,    22,    23,    -1,    25,    26,
      -1,    -1,    -1,   300,   416,    32,    33,    34,    35,    36,
      -1,    -1,    -1,    -1,    -1,    -1,   396,   396,    -1,    -1,
     400,   401,   402,   402,   404,   404,    27,   349,    -1,    -1,
     352,    -1,    59,    60,    -1,    -1,   416,   416,    -1,    -1,
      67,    -1,    69,   365,    -1,    46,    47,    48,    49,    50,
      51,    -1,   349,    -1,    -1,   352,    -1,    -1,    59,    60,
      61,    62,    63,    64,    -1,    -1,   363,    -1,   365,    -1,
      -1,    -1,    -1,    -1,   396,    48,    49,    50,    51,    -1,
     402,    -1,   404,    -1,    -1,    -1,    59,    60,    61,    62,
      63,    64,    -1,    -1,   416,    -1,    -1,    -1,    -1,   396,
      -1,    -1,    -1,   400,   401,   402,    -1,   404,    -1,    -1,
      -1,    -1,     1,    -1,     3,     4,    -1,    -1,    -1,   416,
       9,    10,    11,    12,    -1,    14,    15,    16,    17,    18,
      19,    20,    -1,    22,    26,    -1,    25,    -1,    30,    28,
      29,    -1,    -1,    32,    33,    34,    35,    -1,    -1,    -1,
      39,    40,    41,    42,    43,    44,    45,    -1,    -1,    -1,
      52,    53,    54,    55,    56,    57,    58,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     1,    -1,     3,     4,    68,
      69,    70,    71,     9,    10,    11,    12,    -1,    14,    15,
      16,    17,    18,    19,    20,    -1,    22,    -1,    -1,    25,
      24,    -1,    28,    27,    -1,    -1,    32,    33,    34,    35,
      -1,    -1,    -1,    39,    40,    41,    42,    43,    44,    45,
      -1,    -1,    46,    47,    48,    49,    50,    51,     3,     4,
      -1,    -1,    -1,    -1,    -1,    59,    60,    61,    62,    63,
      64,    -1,    68,    69,    70,    71,    21,    22,    23,    -1,
      -1,    26,    25,    -1,    -1,    -1,    -1,    32,    33,    34,
      35,    36,    -1,    -1,    39,    40,    41,    42,    43,    44,
      45,    -1,    -1,    46,    47,    48,    49,    50,    51,    -1,
      -1,    -1,    -1,    -1,    59,    60,    59,    60,    61,    62,
      63,    64,    67,    68,    69,    70,    71,     3,     4,    -1,
      -1,    -1,    -1,     9,    10,    11,    12,    -1,    14,    15,
      16,    17,    18,    19,    20,    -1,    22,     3,     4,    25,
      -1,    -1,    28,    -1,    -1,    -1,    32,    33,    34,    35,
      -1,    -1,    -1,    -1,    -1,    21,    22,    23,     3,     4,
      26,    27,    -1,    -1,    -1,    -1,    32,    33,    34,    35,
      36,    -1,    -1,    -1,    -1,    -1,    21,    22,    23,     3,
       4,    26,    27,    69,    -1,    -1,    -1,    32,    33,    34,
      35,    36,    -1,    59,    60,    -1,    -1,    21,    22,    23,
      -1,    67,    26,    69,    28,    -1,    -1,    -1,    32,    33,
      34,    35,    36,    -1,    59,    60,    -1,    -1,    -1,     3,
       4,    -1,    67,    -1,    69,    -1,    -1,    -1,    -1,    -1,
      -1,    24,    -1,    -1,    27,    59,    60,    21,    22,    23,
      -1,    25,    26,    67,    -1,    69,    -1,    -1,    32,    33,
      34,    35,    36,    46,    47,    48,    49,    50,    51,     3,
       4,    -1,    -1,    -1,    -1,    -1,    59,    60,    61,    62,
      63,    64,    -1,    -1,    -1,    59,    60,    21,    22,    23,
       3,     4,    26,    67,    -1,    69,    -1,    -1,    32,    33,
      34,    35,    36,    -1,    -1,    -1,    -1,    -1,    21,    22,
      23,    -1,    -1,    26,    -1,    -1,    -1,    -1,    -1,    32,
      33,    34,    35,    36,    -1,    59,    60,    -1,    -1,    -1,
      -1,    -1,    -1,    67,    -1,    69,    24,    -1,    -1,    27,
      -1,    -1,    24,    -1,    -1,    27,    59,    60,    -1,    -1,
      -1,    -1,    -1,    -1,    67,    -1,    69,    -1,    46,    47,
      48,    49,    50,    51,    46,    47,    48,    49,    50,    51,
      -1,    59,    60,    61,    62,    63,    64,    59,    60,    61,
      62,    63,    64,    24,    -1,    -1,    27,    -1,    -1,    24,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    46,    47,    48,    49,    50,
      51,    46,    47,    48,    49,    50,    51,    24,    59,    60,
      61,    62,    63,    64,    59,    60,    61,    62,    63,    64,
      -1,    -1,    -1,    -1,    -1,    -1,    24,    -1,    -1,    46,
      47,    48,    49,    50,    51,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    59,    60,    61,    62,    63,    64,    46,    47,
      48,    49,    50,    51,    24,    -1,    -1,    -1,    -1,    -1,
      24,    59,    60,    61,    62,    63,    64,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    46,    47,    48,    49,
      50,    51,    46,    47,    48,    49,    50,    51,    24,    59,
      60,    61,    62,    63,    64,    59,    60,    61,    62,    63,
      64,    -1,    -1,    -1,    -1,    -1,    -1,    24,    -1,    -1,
      46,    47,    48,    49,    50,    51,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    59,    60,    61,    62,    63,    64,    46,
      47,    48,    49,    50,    51,    24,    -1,    -1,    -1,    -1,
      -1,    24,    59,    60,    61,    62,    63,    64,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    46,    47,    48,
      49,    50,    51,    46,    47,    48,    49,    50,    51,    24,
      59,    60,    61,    62,    63,    64,    59,    60,    61,    62,
      63,    64,    -1,    -1,    -1,    -1,    -1,    -1,    24,    -1,
      -1,    46,    47,    48,    49,    50,    51,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    59,    60,    61,    62,    63,    64,
      46,    47,    48,    49,    50,    51,    24,    -1,    -1,    -1,
      -1,    -1,    24,    59,    60,    61,    62,    63,    64,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    46,    47,
      48,    49,    50,    51,    46,    47,    48,    49,    50,    51,
      24,    59,    60,    61,    62,    63,    64,    59,    60,    61,
      62,    63,    64,    -1,    -1,    -1,    -1,    -1,    -1,    24,
      -1,    -1,    46,    47,    48,    49,    50,    51,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    59,    60,    61,    62,    63,
      64,    46,    47,    48,    49,    50,    51,    24,    -1,    -1,
      -1,    -1,    -1,    24,    59,    60,    61,    62,    63,    64,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    46,
      47,    48,    49,    50,    51,    46,    47,    48,    49,    50,
      51,    27,    59,    60,    61,    62,    63,    64,    59,    60,
      61,    62,    63,    64,    -1,    -1,    -1,    -1,    -1,    -1,
      46,    47,    48,    49,    50,    51,    27,    -1,    -1,    -1,
      -1,    -1,    27,    59,    60,    61,    62,    63,    64,    -1,
      -1,    -1,    -1,    -1,    -1,    46,    47,    48,    49,    50,
      51,    46,    47,    48,    49,    50,    51,    31,    59,    60,
      61,    62,    63,    64,    59,    60,    61,    62,    63,    64,
      -1,    -1,    46,    47,    48,    49,    50,    51,    31,    -1,
      -1,    -1,    -1,    -1,    31,    59,    60,    61,    62,    63,
      64,    -1,    -1,    46,    47,    48,    49,    50,    51,    46,
      47,    48,    49,    50,    51,    31,    59,    60,    61,    62,
      63,    64,    59,    60,    61,    62,    63,    64,    37,    -1,
      46,    47,    48,    49,    50,    51,    -1,    46,    47,    48,
      49,    50,    51,    59,    60,    61,    62,    63,    64,    -1,
      59,    60,    61,    62,    63,    64,    46,    47,    48,    49,
      50,    51,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    59,
      60,    61,    62,    63,    64
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,    73,    74,     0,     3,     4,     5,     6,     7,     8,
      20,    69,    76,    79,    80,    81,    82,    91,    94,    22,
      68,    77,    22,    79,    83,    84,    85,    80,    22,    26,
      70,    71,    75,    26,    86,    27,    25,    26,    39,    40,
      41,    42,    43,    44,    45,    78,    22,    87,    28,   106,
      84,    92,    30,    88,   107,    79,    95,    96,    97,    23,
      31,    24,   117,    98,    27,    25,    31,    89,    87,     1,
       3,     4,     9,    10,    11,    12,    14,    15,    16,    17,
      18,    19,    22,    25,    29,    32,    33,    34,    35,    79,
      82,   106,   108,   116,   118,   119,   120,   121,   122,   123,
     124,   125,   126,   129,   138,   139,   140,   146,   147,   149,
     151,   152,   153,   154,   155,   156,   157,   158,   159,   167,
     168,   169,   172,   173,    22,   100,   105,    93,    96,    90,
      24,    26,    26,    26,    26,    26,    23,    25,    23,    25,
      26,    26,    21,    22,    23,    25,    26,    36,    59,    60,
      67,    79,   126,   129,   160,   164,   165,   166,   167,    26,
      30,    52,    53,    54,    55,    56,    57,    58,    22,   110,
     118,   119,    25,    25,    26,   116,   118,    26,    25,   160,
     174,   175,    26,    24,    30,   102,    24,   106,    24,    87,
     160,   166,   166,   150,    25,    25,   160,    27,   160,    30,
     160,   166,   160,   160,   166,    36,   160,    25,    46,    47,
      48,    49,    50,    51,    59,    60,    61,    62,    63,    64,
      38,    46,    47,    65,    66,   160,   127,   131,   130,   133,
     132,    30,   111,   112,    22,   126,   141,   142,    13,   160,
      24,    27,    22,    36,   170,   101,    23,    52,    99,   105,
      87,    27,    27,   148,   160,    24,    27,   118,   119,    24,
     160,    24,    27,    27,   160,   160,   160,   160,   160,   160,
     160,   160,   160,   160,   160,   160,   161,   160,   166,   166,
     166,   166,    31,   160,   160,   160,   160,   160,    23,    24,
      25,   115,    52,   109,    30,    24,    25,   118,   119,    24,
      27,   176,    30,   171,   100,    31,    28,   160,   162,   116,
     118,    24,    27,   160,   118,   119,   160,    31,   160,   160,
      37,    52,    53,    54,    55,    56,    57,    58,    31,    22,
     110,   160,   162,   115,   160,   142,   143,   166,   160,   118,
     119,   175,   160,    24,    27,    24,   104,   160,   163,    13,
     160,    24,    27,    24,   160,   128,   135,   134,   137,   136,
     113,   114,    31,    25,    24,    27,    31,   174,   103,    99,
      24,    29,   118,   119,   160,   118,   119,   160,   160,   160,
     160,   160,   160,   115,   109,    22,   126,   129,   144,   145,
     160,   118,   119,    27,   100,   163,    27,    24,    27,   115,
      24,    24,    27,    24,    27,   118,   119,   160,   145,   145,
     118,   119,   160,   118,   119,    24,    27,   160,   118,   119,
      24,   160,    24,   160,    24,   160,    24,   160,    24,   160,
      24,   160,    24,   160,    24,   160,    24,   160,    24,   160,
      24,   160,    27
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
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (0)


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (N)								\
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
    while (0)
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
} while (0)

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)		\
do {								\
  if (yydebug)							\
    {								\
      YYFPRINTF (stderr, "%s ", Title);				\
      yysymprint (stderr,					\
                  Type, Value);	\
      YYFPRINTF (stderr, "\n");					\
    }								\
} while (0)

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_stack_print (short int *bottom, short int *top)
#else
static void
yy_stack_print (bottom, top)
    short int *bottom;
    short int *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (/* Nothing. */; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_reduce_print (int yyrule)
#else
static void
yy_reduce_print (yyrule)
    int yyrule;
#endif
{
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu), ",
             yyrule - 1, yylno);
  /* Print the symbols being reduced, and their result.  */
  for (yyi = yyprhs[yyrule]; 0 <= yyrhs[yyi]; yyi++)
    YYFPRINTF (stderr, "%s ", yytname[yyrhs[yyi]]);
  YYFPRINTF (stderr, "-> %s\n", yytname[yyr1[yyrule]]);
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (Rule);		\
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
#  if defined (__GLIBC__) && defined (_STRING_H)
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
#   if defined (__STDC__) || defined (__cplusplus)
yystrlen (const char *yystr)
#   else
yystrlen (yystr)
     const char *yystr;
#   endif
{
  const char *yys = yystr;

  while (*yys++ != '\0')
    continue;

  return yys - yystr - 1;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined (__GLIBC__) && defined (_STRING_H) && defined (_GNU_SOURCE)
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
#   if defined (__STDC__) || defined (__cplusplus)
yystpcpy (char *yydest, const char *yysrc)
#   else
yystpcpy (yydest, yysrc)
     char *yydest;
     const char *yysrc;
#   endif
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
      size_t yyn = 0;
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

#endif /* YYERROR_VERBOSE */



#if YYDEBUG
/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yysymprint (FILE *yyoutput, int yytype, YYSTYPE *yyvaluep)
#else
static void
yysymprint (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;

  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);


# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  switch (yytype)
    {
      default:
        break;
    }
  YYFPRINTF (yyoutput, ")");
}

#endif /* ! YYDEBUG */
/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;

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
# if defined (__STDC__) || defined (__cplusplus)
int yyparse (void *YYPARSE_PARAM);
# else
int yyparse ();
# endif
#else /* ! YYPARSE_PARAM */
#if defined (__STDC__) || defined (__cplusplus)
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
int yyparse (void *YYPARSE_PARAM)
# else
int yyparse (YYPARSE_PARAM)
  void *YYPARSE_PARAM;
# endif
#else /* ! YYPARSE_PARAM */
#if defined (__STDC__) || defined (__cplusplus)
int
yyparse (void)
#else
int
yyparse ()
    ;
#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  short int yyssa[YYINITDEPTH];
  short int *yyss = yyssa;
  short int *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK   (yyvsp--, yyssp--)

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* When reducing, the number of symbols on the RHS of the reduced
     rule.  */
  int yylen;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

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
     have just been pushed. so pushing a state here evens the stacks.
     */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack. Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	short int *yyss1 = yyss;


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
	short int *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

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

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

/* Do appropriate processing given the current state.  */
/* Read a look-ahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to look-ahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
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

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;


  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  yystate = yyn;
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
#line 247 "sl.y"
    {
			;}
    break;

  case 3:
#line 250 "sl.y"
    {
			;}
    break;

  case 4:
#line 256 "sl.y"
    {
				(yyval.integer)	=	SLC_UNIFORM;
			;}
    break;

  case 5:
#line 261 "sl.y"
    {
				(yyval.integer)	=	SLC_VARYING;
			;}
    break;

  case 6:
#line 265 "sl.y"
    {
				(yyval.integer)	=	0;
			;}
    break;

  case 7:
#line 273 "sl.y"
    {
				(yyval.integer)	=	SLC_EXTERN;
			;}
    break;

  case 8:
#line 277 "sl.y"
    {
				(yyval.integer)	=	0;
			;}
    break;

  case 9:
#line 284 "sl.y"
    {
				(yyval.integer)	=	SLC_OUTPUT;
			;}
    break;

  case 10:
#line 288 "sl.y"
    {
				(yyval.integer)	=	0;
			;}
    break;

  case 11:
#line 295 "sl.y"
    {
				(yyval.integer)	=	SLC_FLOAT;
			;}
    break;

  case 12:
#line 300 "sl.y"
    {
				(yyval.integer)	=	SLC_VECTOR | SLC_VCOLOR;
			;}
    break;

  case 13:
#line 305 "sl.y"
    {
				(yyval.integer)	=	SLC_VECTOR | SLC_VVECTOR;
			;}
    break;

  case 14:
#line 310 "sl.y"
    {
				(yyval.integer)	=	SLC_VECTOR | SLC_VNORMAL;
			;}
    break;

  case 15:
#line 315 "sl.y"
    {
				(yyval.integer)	=	SLC_VECTOR | SLC_VPOINT;
			;}
    break;

  case 16:
#line 320 "sl.y"
    {
				(yyval.integer)	=	SLC_MATRIX;
			;}
    break;

  case 17:
#line 325 "sl.y"
    {
				(yyval.integer)	=	SLC_STRING | SLC_UNIFORM;
			;}
    break;

  case 18:
#line 335 "sl.y"
    {
				(yyval.integer)	=	(yyvsp[-3].integer) | (yyvsp[-2].integer) | (yyvsp[-1].integer) | (yyvsp[0].integer);
				sdr->desire((yyval.integer));
			;}
    break;

  case 19:
#line 353 "sl.y"
    {
		;}
    break;

  case 20:
#line 357 "sl.y"
    {
		;}
    break;

  case 21:
#line 374 "sl.y"
    {
			CFunction	*thisFunction	=	sdr->newFunction((yyvsp[-1].string));
			
			if ((yyvsp[-2].integer) & (SLC_OUTPUT | SLC_EXTERN | SLC_RDONLY)) {
				sdr->error("Invalid return type for function %s\n",(yyvsp[-1].string));
				(yyvsp[-2].integer)	&=	~(SLC_OUTPUT | SLC_EXTERN | SLC_RDONLY);
			}

			thisFunction->returnValue	=	new CParameter((yyvsp[-1].string),(yyvsp[-2].integer),1);

			sdr->undesire();
		;}
    break;

  case 22:
#line 390 "sl.y"
    {
			CFunction	*thisFunction	=	sdr->newFunction((yyvsp[-1].string));
			
			thisFunction->returnValue	=	NULL;
		;}
    break;

  case 23:
#line 402 "sl.y"
    {
			CFunction	*cFun		=	sdr->popFunction();

			cFun->initExpression	=	(yyvsp[-2].code);
			cFun->code				=	(yyvsp[0].code);

			if (cFun->returnValue != NULL)
				if (cFun->returnValueGiven == FALSE) 
					sdr->error("Return value not given for %s\n",cFun->symbolName);

		;}
    break;

  case 24:
#line 420 "sl.y"
    {
			(yyval.code)	=	(yyvsp[0].code);
		;}
    break;

  case 25:
#line 424 "sl.y"
    {
			(yyval.code)	=	new CNullExpression;
		;}
    break;

  case 26:
#line 436 "sl.y"
    {
			(yyval.code)	=	new CTwoExpressions((yyvsp[-2].code),(yyvsp[0].code));
		;}
    break;

  case 27:
#line 442 "sl.y"
    {
			(yyval.code)	=	(yyvsp[-1].code);
		;}
    break;

  case 28:
#line 447 "sl.y"
    {
			(yyval.code)	=	(yyvsp[0].code);
		;}
    break;

  case 29:
#line 456 "sl.y"
    {
			int	type	=	sdr->desired();

			if (type & (SLC_EXTERN)) {
				sdr->error("Invalid parameter type\n");
				type	&=	~(SLC_EXTERN);
			}

			if (type & SLC_OUTPUT) {
				sdr->undesire();
				sdr->desire(type);					// Make sure we mark the desired type as READ-ONLY
			} else {
				sdr->undesire();
				sdr->desire(type | SLC_RDONLY);		// Make sure we mark the desired type as READ-ONLY
			}
		;}
    break;

  case 30:
#line 473 "sl.y"
    {
			(yyval.code)					=	(yyvsp[0].code);
			sdr->undesire();						// We're done with the type
		;}
    break;

  case 31:
#line 483 "sl.y"
    {
			CParameter	*cParameter;
			
			cParameter	=	sdr->newParameter((yyvsp[0].string),sdr->desired(),1);	// Add the Parameter to the current CFunction
		;}
    break;

  case 32:
#line 490 "sl.y"
    {
			(yyval.code)	=	(yyvsp[0].code);
		;}
    break;

  case 33:
#line 495 "sl.y"
    {
			CParameter	*cParameter;
			
			cParameter	=	sdr->newParameter((yyvsp[0].string),sdr->desired(),1);
	
			(yyval.code)			=	new CNullExpression;
		;}
    break;

  case 34:
#line 506 "sl.y"
    {
			CParameter	*cParameter;
			
			cParameter	=	sdr->newParameter((yyvsp[-2].string),sdr->desired() | SLC_ARRAY,-1);
		;}
    break;

  case 35:
#line 513 "sl.y"
    {
			(yyval.code)	=	(yyvsp[0].code);
		;}
    break;

  case 36:
#line 521 "sl.y"
    {
			CParameter	*cParameter;
			
			cParameter	=	sdr->newParameter((yyvsp[-3].string),sdr->desired() | SLC_ARRAY, atoi((yyvsp[-1].string)));
			
			if (cParameter->numItems <= 0) {
				sdr->error("Array size for %s is invalid (%s)\n",(yyvsp[-3].string),(yyvsp[-1].string));
				cParameter->numItems	=	1;
			}
		;}
    break;

  case 37:
#line 533 "sl.y"
    {
			(yyval.code)	=	(yyvsp[0].code);
		;}
    break;

  case 38:
#line 540 "sl.y"
    {
			CParameter	*cParameter;
			
			cParameter	=	sdr->newParameter((yyvsp[-2].string),sdr->desired() | SLC_ARRAY, -1);
			
			(yyval.code)	=	new CNullExpression;
		;}
    break;

  case 39:
#line 552 "sl.y"
    {
			CParameter	*cParameter;
			
			cParameter	=	sdr->newParameter((yyvsp[-3].string),sdr->desired() | SLC_ARRAY, atoi((yyvsp[-1].string)));
			
			if (cParameter->numItems <= 0) {
				sdr->error("Array size for %s is invalid (%s)\n",(yyvsp[-3].string),(yyvsp[-1].string));
				cParameter->numItems	=	1;
			}

			(yyval.code)	=	new CNullExpression;
		;}
    break;

  case 40:
#line 573 "sl.y"
    {
			CFunction		*mainFunction	=	sdr->newFunction(constantShaderMain);

			mainFunction->returnValue		=	NULL;

			sdr->shaderName					=	strdup((yyvsp[-1].string));
			sdr->shaderType					=	(yyvsp[-2].integer);
			sdr->shaderFunction				=	mainFunction;
		;}
    break;

  case 41:
#line 584 "sl.y"
    {
			sdr->restoreParameters();
		;}
    break;

  case 42:
#line 588 "sl.y"
    {
			CFunction	*cFun			=	sdr->popFunction();
			CParameter	*cParameter;

			for (cParameter=cFun->parameters->first();cParameter!=NULL;cParameter=cFun->parameters->next()) {
				sdr->variables->push(cParameter);
			}

			assert(cFun == sdr->shaderFunction);

			cFun->initExpression	=	(yyvsp[-3].code);
			cFun->code				=	(yyvsp[0].code);
		;}
    break;

  case 43:
#line 606 "sl.y"
    {
			(yyval.integer)	=	SLC_SURFACE;
		;}
    break;

  case 44:
#line 611 "sl.y"
    {
			(yyval.integer)	=	SLC_DISPLACEMENT;
		;}
    break;

  case 45:
#line 616 "sl.y"
    {
			(yyval.integer)	=	SLC_LIGHT;
		;}
    break;

  case 46:
#line 621 "sl.y"
    {
			(yyval.integer)	=	SLC_VOLUME;
		;}
    break;

  case 47:
#line 626 "sl.y"
    {
			(yyval.integer)	=	SLC_TRANSFORMATION;
		;}
    break;

  case 48:
#line 631 "sl.y"
    {
			(yyval.integer)	=	SLC_IMAGER;
		;}
    break;

  case 49:
#line 640 "sl.y"
    {
			(yyval.code)	=	(yyvsp[0].code);
		;}
    break;

  case 50:
#line 644 "sl.y"
    {
			(yyval.code)	=	new CNullExpression;
		;}
    break;

  case 51:
#line 655 "sl.y"
    {
			(yyval.code)	=	new CTwoExpressions((yyvsp[-2].code),(yyvsp[0].code));
		;}
    break;

  case 52:
#line 661 "sl.y"
    {
			(yyval.code)	=	(yyvsp[-1].code);
		;}
    break;

  case 53:
#line 666 "sl.y"
    {
			(yyval.code)	=	(yyvsp[0].code);
		;}
    break;

  case 54:
#line 675 "sl.y"
    {
			int	type	=	(yyvsp[0].integer);

			if (type & SLC_VARYING) {
			} else {
				type |= SLC_UNIFORM;
			}

			sdr->undesire();
			sdr->desire(type);
		;}
    break;

  case 55:
#line 687 "sl.y"
    {
			(yyval.code)	=	(yyvsp[0].code);
		
			if ((yyvsp[-2].integer) & (SLC_EXTERN)) {
				sdr->error("Invalid parameter type for the shader\n");
			}

			sdr->undesire();
		;}
    break;

  case 56:
#line 703 "sl.y"
    {
			(yyval.code)	=	getAssignment(sdr->variableList,(yyvsp[0].expression));
		;}
    break;

  case 57:
#line 709 "sl.y"
    {
			(yyval.code)	=	getAssignment(sdr->variableList,(yyvsp[0].array));
		;}
    break;

  case 58:
#line 718 "sl.y"
    {
			CParameter	*cParameter	=	sdr->newParameter((yyvsp[-1].string),sdr->desired() | SLC_PARAMETER,1);

			sdr->variableList->push(cParameter);	// Save the parameter so that we can generate init code later
		;}
    break;

  case 59:
#line 724 "sl.y"
    {
			(yyval.code)	=	(yyvsp[0].code);
		;}
    break;

  case 60:
#line 729 "sl.y"
    {
			CParameter	*cParameter	=	sdr->newParameter((yyvsp[0].string),sdr->desired() | SLC_PARAMETER,1);

			sdr->variableList->push(cParameter);
		;}
    break;

  case 61:
#line 735 "sl.y"
    {
			(yyval.code)	=	(yyvsp[0].code);
		;}
    break;

  case 62:
#line 744 "sl.y"
    {
			CParameter	*cParameter	=	sdr->newParameter((yyvsp[-4].string),sdr->desired() | SLC_PARAMETER | SLC_ARRAY,atoi((yyvsp[-2].string)));

			if (cParameter->numItems <= 0) {
				sdr->error("Array size for %s is invalid (%s)\n",(yyvsp[-4].string),(yyvsp[-2].string));
				cParameter->numItems	=	1;
			}

			sdr->variableList->push(cParameter);
		;}
    break;

  case 63:
#line 755 "sl.y"
    {
			(yyval.code)	=	(yyvsp[0].code);
		;}
    break;

  case 64:
#line 763 "sl.y"
    {
			CParameter	*cParameter	=	sdr->newParameter((yyvsp[-3].string),sdr->desired() | SLC_PARAMETER | SLC_ARRAY,atoi((yyvsp[-1].string)));

			// Get the parameter
			if (cParameter->numItems <= 0)	{
				sdr->error("Array size for %s is invalid (%s)\n",(yyvsp[-3].string),(yyvsp[-1].string));
				cParameter->numItems	=	1;
			}

			sdr->variableList->push(cParameter);
		;}
    break;

  case 65:
#line 775 "sl.y"
    {
			(yyval.code)	=	(yyvsp[0].code);
		;}
    break;

  case 66:
#line 780 "sl.y"
    {
			(yyval.code)	=	new CNullExpression;
		;}
    break;

  case 67:
#line 788 "sl.y"
    {
			(yyval.code)	=	(yyvsp[0].code);
		;}
    break;

  case 68:
#line 795 "sl.y"
    {
			(yyval.code)	=	new CTwoExpressions((yyvsp[-2].code),(yyvsp[0].code));
		;}
    break;

  case 69:
#line 805 "sl.y"
    {
			CFunction	*cFun	=	sdr->newFunction(constantBlockName);
		;}
    break;

  case 70:
#line 810 "sl.y"
    {
			CFunction	*cFun	=	sdr->popFunction();

			cFun->code			=	(yyvsp[-1].code);

			(yyval.code)	=	new	CFuncallExpression(cFun,NULL);
		;}
    break;

  case 71:
#line 826 "sl.y"
    {
			CVariable	*cVar;

			if ((yyvsp[-1].integer) & (SLC_OUTPUT | SLC_RDONLY)) {
				sdr->error("Invalid container class for local variables\n");
			}

			// Remove the uninitialized variables from the list
			while((cVar = (CVariable *) sdr->variableList->pop()) != NULL);

			sdr->undesire();

			(yyval.code)	=	(yyvsp[0].code);
		;}
    break;

  case 72:
#line 847 "sl.y"
    {
			(yyval.code)	=	getAssignment(sdr->variableList,(yyvsp[0].expression));
		;}
    break;

  case 73:
#line 853 "sl.y"
    {
			(yyval.code)	=	getAssignment(sdr->variableList,(yyvsp[0].array));
		;}
    break;

  case 74:
#line 860 "sl.y"
    {
			CVariable	*cVar;

			cVar	=	sdr->newVariable((yyvsp[0].string),sdr->desired(),1);

			sdr->variableList->push(cVar);
		;}
    break;

  case 75:
#line 868 "sl.y"
    {
			(yyval.code)	=	(yyvsp[0].code);
		;}
    break;

  case 76:
#line 873 "sl.y"
    {
			CVariable	*cVar;

			cVar	=	sdr->newVariable((yyvsp[0].string),sdr->desired(),1);

			sdr->variableList->push(cVar);
		;}
    break;

  case 77:
#line 882 "sl.y"
    {
			(yyval.code)	=	new CTwoExpressions((yyvsp[-1].code),(yyvsp[0].code));
		;}
    break;

  case 78:
#line 891 "sl.y"
    {
			CVariable	*cVar;

			cVar	=	sdr->newVariable((yyvsp[-3].string),sdr->desired() | SLC_ARRAY,atoi((yyvsp[-1].string)));

			if (cVar->numItems <= 0) {
				sdr->error("Array size is invalid for %s (%s)\n",(yyvsp[-3].string),(yyvsp[-1].string));
				cVar->numItems	=	1;
			}

			sdr->variableList->push(cVar);
		;}
    break;

  case 79:
#line 904 "sl.y"
    {
			(yyval.code)	=	(yyvsp[0].code);
		;}
    break;

  case 80:
#line 912 "sl.y"
    {
			CVariable	*cVar;

			cVar	=	sdr->newVariable((yyvsp[-3].string),sdr->desired() | SLC_ARRAY,atoi((yyvsp[-1].string)));

		
			if (cVar->numItems <= 0) {
				sdr->error("Array size is invalid for %s (%s)\n",(yyvsp[-3].string),(yyvsp[-1].string));
				cVar->numItems	=	1;
			}

			sdr->variableList->push(cVar);
		;}
    break;

  case 81:
#line 928 "sl.y"
    {
			(yyval.code)	=	new CTwoExpressions((yyvsp[-1].code),(yyvsp[0].code));
		;}
    break;

  case 82:
#line 936 "sl.y"
    {
			(yyval.code)	=	(yyvsp[0].code);
		;}
    break;

  case 83:
#line 941 "sl.y"
    {
			(yyval.code)	=	new CNullExpression;
		;}
    break;

  case 84:
#line 951 "sl.y"
    {

			(yyval.code)	=	(yyvsp[0].code);
			assert(sdr->desired() & SLC_NONE);
		;}
    break;

  case 85:
#line 958 "sl.y"
    {
			(yyval.code)	=	(yyvsp[0].code);
			assert(sdr->desired() & SLC_NONE);
		;}
    break;

  case 86:
#line 964 "sl.y"
    {
			// Recoverable error happened
			(yyval.code)	=	new CNullExpression;
			assert(sdr->desired() & SLC_NONE);
		;}
    break;

  case 87:
#line 975 "sl.y"
    {
			(yyval.code)	=	new CTwoExpressions((yyvsp[-1].code),(yyvsp[0].code));
		;}
    break;

  case 88:
#line 979 "sl.y"
    {
			(yyval.code)	=	new CNullExpression;
		;}
    break;

  case 89:
#line 989 "sl.y"
    {
			(yyval.code)	=	(yyvsp[0].code);
		;}
    break;

  case 90:
#line 994 "sl.y"
    {
			(yyval.code)	=	(yyvsp[0].code);
		;}
    break;

  case 91:
#line 999 "sl.y"
    {
			(yyval.code)	=	(yyvsp[0].code);
		;}
    break;

  case 92:
#line 1004 "sl.y"
    {
			(yyval.code)	=	(yyvsp[0].code);
		;}
    break;

  case 93:
#line 1009 "sl.y"
    {
			(yyval.code)	=	(yyvsp[-1].expression);
		;}
    break;

  case 94:
#line 1014 "sl.y"
    {
			(yyval.code)	=	(yyvsp[-1].expression);
		;}
    break;

  case 95:
#line 1019 "sl.y"
    {
			(yyval.code)	=	(yyvsp[0].code);
		;}
    break;

  case 96:
#line 1024 "sl.y"
    {
			(yyval.code)	=	(yyvsp[0].code);
		;}
    break;

  case 97:
#line 1029 "sl.y"
    {
			(yyval.code)	=	(yyvsp[0].code);
		;}
    break;

  case 98:
#line 1034 "sl.y"
    {
			(yyval.code)	=	(yyvsp[0].code);
		;}
    break;

  case 99:
#line 1039 "sl.y"
    {
			(yyval.code)	=	(yyvsp[0].code);
		;}
    break;

  case 100:
#line 1044 "sl.y"
    {
			(yyval.code)	=	(yyvsp[0].code);
		;}
    break;

  case 101:
#line 1049 "sl.y"
    {
			(yyval.code)	=	(yyvsp[0].code);
		;}
    break;

  case 102:
#line 1054 "sl.y"
    {
			(yyval.code)	=	(yyvsp[0].code);
		;}
    break;

  case 103:
#line 1059 "sl.y"
    {
			(yyval.code)	=	new CNullExpression;
		;}
    break;

  case 104:
#line 1064 "sl.y"
    {
			(yyval.code)	=	(yyvsp[-1].expression);
		;}
    break;

  case 105:
#line 1069 "sl.y"
    {
			(yyval.code)					=	new CNullExpression;
		;}
    break;

  case 106:
#line 1078 "sl.y"
    {
			(yyval.code)	=	(yyvsp[0].code);
		;}
    break;

  case 107:
#line 1083 "sl.y"
    {
			(yyval.code)	=	(yyvsp[0].code);
		;}
    break;

  case 108:
#line 1088 "sl.y"
    {
			(yyval.code)	=	(yyvsp[0].code);
		;}
    break;

  case 109:
#line 1093 "sl.y"
    {
			(yyval.code)	=	(yyvsp[0].code);
		;}
    break;

  case 110:
#line 1098 "sl.y"
    {
			(yyval.code)	=	(yyvsp[0].code);
		;}
    break;

  case 111:
#line 1103 "sl.y"
    {
			(yyval.code)	=	(yyvsp[0].code);
		;}
    break;

  case 112:
#line 1108 "sl.y"
    {
			(yyval.code)	=	(yyvsp[0].code);
		;}
    break;

  case 113:
#line 1117 "sl.y"
    {
			CFunction	*cFunction;
			int			bc;
			char		tmp[256];

			if (sscanf((yyvsp[-1].string),"%d",&bc) != 1) sdr->error("Invalid break count: %s\n",(yyvsp[-1].string));

			if (bc <= 0) sdr->error("Bad break count: %s\n",(yyvsp[-1].string));

			for(cFunction = sdr->functionStack->last(); cFunction != NULL; cFunction = sdr->functionStack->prev()) {
				if (strcmp(cFunction->symbolName,constantLoopName) == 0) bc--;
				else if (strcmp(cFunction->symbolName,constantBlockName) == 0) continue;

				if (bc == 0) break;

				sdr->error("Break target not found\n");
				break;
			}

			if (cFunction == NULL) sdr->error("Break target not found\n");

			sprintf(tmp,"%s\t%s\n",opcodeBreak,(yyvsp[-1].string));

			(yyval.code)	=	new CFixedExpression(tmp);
		;}
    break;

  case 114:
#line 1144 "sl.y"
    {
			CFunction	*cFunction;
			char		tmp[256];
			int			bc	=	(int) 1;

			sdr->functionStack->push(sdr->lastFunction);
			for(cFunction = sdr->functionStack->last(); cFunction != NULL; cFunction = sdr->functionStack->prev()) {
				if (strcmp(cFunction->symbolName,constantLoopName) == 0) bc--;
				else if (strcmp(cFunction->symbolName,constantBlockName) == 0) continue;

				if (bc == 0) break;

				sdr->error("Break target not found\n");
				break;
			}
			sdr->lastFunction	=	sdr->functionStack->pop();

			if (cFunction == NULL) sdr->error("Break target not found\n");

			sprintf(tmp,"%s\t1\n",opcodeBreak);

			(yyval.code)	=	new CFixedExpression(tmp);
		;}
    break;

  case 115:
#line 1173 "sl.y"
    {
			CFunction	*cFunction;
			char		tmp[256];
			int			bc;

			if (sscanf((yyvsp[-1].string),"%d",&bc) != 1) sdr->error("Bad continue count: %s\n",(yyvsp[-1].string));

			if (bc <= 0) sdr->error("Bad continue count: %s\n",(yyvsp[-1].string));

			for(cFunction = sdr->functionStack->last(); cFunction != NULL; cFunction = sdr->functionStack->prev()) {
				if (strcmp(cFunction->symbolName,constantLoopName) == 0) bc--;
				else if (strcmp(cFunction->symbolName,constantBlockName) == 0) continue;

				if (bc == 0) break;

				sdr->error("Continue target not found\n");
				break;
			}

			if (cFunction == NULL) sdr->error("Continue target not found\n");

			sprintf(tmp,"%s\t%s\n",opcodeContinue,(yyvsp[-1].string));

			(yyval.code)	=	new CFixedExpression(tmp);
		;}
    break;

  case 116:
#line 1200 "sl.y"
    {
			CFunction	*cFunction;
			char		tmp[256];
			int			bc	=	(int) 1;

			for(cFunction = sdr->functionStack->last(); cFunction != NULL; cFunction = sdr->functionStack->prev()) {
				if (strcmp(cFunction->symbolName,constantLoopName) == 0) bc--;
				else if (strcmp(cFunction->symbolName,constantBlockName) == 0) continue;

				if (bc == 0) break;
				
				sdr->error("Continue target not found\n");
				break;
			}

			if (cFunction == NULL) sdr->error("Continue target not found\n");

			sprintf(tmp,"%s\t1\n",opcodeContinue);

			(yyval.code)	=	new CFixedExpression(tmp);
		;}
    break;

  case 117:
#line 1227 "sl.y"
    {
			CFunction	*cFun	=	sdr->lastFunction;
			CExpression	*c;

			// Skip over loops
			for (cFun = sdr->functionStack->last(); cFun != NULL; cFun = sdr->functionStack->prev()) {
				if (strcmp(cFun->symbolName,constantBlockName) == 0) continue;
				if (strcmp(cFun->symbolName,constantLoopName) == 0) continue;
				break;
			}

			if (cFun ==	NULL) {
				sdr->error("Return target not found\n");
				(yyval.code)	=	new CNullExpression;
			} else {
				if (cFun->returnValue == NULL) {
					sdr->error("Function %s was not expecting a return value\n",cFun->symbolName);
					c	=	new CNullExpression;
				} else {
					c	=	new CAssignmentExpression(cFun->returnValue,(yyvsp[-1].expression));				
				}

				(yyval.code)	=	c;

				cFun->returnValueGiven	=	TRUE;
			}
		;}
    break;

  case 118:
#line 1256 "sl.y"
    {
			CFunction	*cFun	=	sdr->lastFunction;

			// Skip over loops
			for (cFun = sdr->functionStack->last(); cFun != NULL; cFun = sdr->functionStack->prev()) {
				if (strcmp(cFun->symbolName,constantBlockName) == 0) continue;
				if (strcmp(cFun->symbolName,constantLoopName) == 0) continue;
				break;
			}

			if (cFun ==	NULL)	sdr->error("Return target not found\n");
			else {
				if (cFun->returnValue != NULL) {
					sdr->error("Function %s was expecting a return value\n",cFun->symbolName);
				}
			}
		;}
    break;

  case 119:
#line 1283 "sl.y"
    {
			CFunction	*cFun	=	sdr->newFunction(constantLoopName);
			
			(yyval.expression)	=	(yyvsp[-1].expression);	
		;}
    break;

  case 120:
#line 1294 "sl.y"
    {
			CFunction	*cFun	=	sdr->popFunction();

			(yyval.code)	=	new CForLoop(NULL,(yyvsp[-1].expression),NULL,(yyvsp[0].code));
		;}
    break;

  case 121:
#line 1304 "sl.y"
    {

			CFunction	*cFun	=	sdr->popFunction();

			(yyval.code)	=	new CForLoop(NULL,(yyvsp[-1].expression),NULL,(yyvsp[0].code));
		;}
    break;

  case 122:
#line 1317 "sl.y"
    {
			CVariable	*cVar				=	sdr->getVariable((yyvsp[-1].string));

			if (cVar == NULL)	sdr->error("Identifier %s not found\n",(yyvsp[-1].string));
			else				sdr->desire(cVar->type);
		;}
    break;

  case 123:
#line 1324 "sl.y"
    {
			CVariable			*cVar		=	sdr->getVariable((yyvsp[-3].string));

			if (cVar == NULL) {	
				(yyval.expression)	=	new CNullExpression;
			} else {
				(yyval.expression)	=	new CAssignmentExpression(cVar,(yyvsp[0].expression));
				sdr->undesire();
			}
		;}
    break;

  case 124:
#line 1340 "sl.y"
    {
			CVariable	*cVar				=	sdr->getVariable((yyvsp[-4].string));

			if (cVar == NULL)	sdr->error("Identifier %s not found\n",(yyvsp[-4].string));
			else				sdr->desire(cVar->type);
		;}
    break;

  case 125:
#line 1347 "sl.y"
    {
			CVariable			*cVar		=	sdr->getVariable((yyvsp[-6].string));

			if (cVar == NULL) {
				(yyval.expression)	=	new CNullExpression;
			} else if (cVar->type & SLC_ARRAY) {
				(yyval.expression)	=	new CArrayAssignmentExpression(cVar,(yyvsp[-4].expression),(yyvsp[0].expression));
				sdr->undesire();
			} else {
				CArray<CExpression *>	*dummyParams = new CArray<CExpression *>;
				CFunctionPrototype		*cFun;

				dummyParams->push(new CTerminalExpression(cVar));
				dummyParams->push((yyvsp[-4].expression));
				dummyParams->push((yyvsp[0].expression));

				// Check the builtin functions
				for (cFun = sdr->builtinFunctions->first(); cFun != NULL; cFun = sdr->builtinFunctions->next()) {
					if (cFun->match("setcomp",dummyParams,sdr->desired())) break;
				}
				
				if (cFun == NULL) {
					// Cleanup
					CExpression	*cCode;
					while((cCode = dummyParams->pop()) != NULL) {
						delete cCode;
					}
					delete dummyParams;
					// Report error
					sdr->error("Can't assign to non array\n");
					(yyval.expression)	=	new CNullExpression;
				} else {
					(yyval.expression)	=	new CBuiltinExpression(cFun,dummyParams);
				}
				sdr->undesire();
			}
		;}
    break;

  case 126:
#line 1391 "sl.y"
    {
			CVariable	*cVar				=	sdr->getVariable((yyvsp[-1].string));

			if (cVar == NULL)	sdr->error("Identifier %s not found\n",(yyvsp[-1].string));
			else				sdr->desire(cVar->type);
		;}
    break;

  case 127:
#line 1398 "sl.y"
    {
			CVariable			*cVar		=	sdr->getVariable((yyvsp[-3].string));

			if (cVar == NULL) {
				(yyval.expression)	=	new CNullExpression;
			} else {
				(yyval.expression)	=	new CUpdateExpression(cVar,opcodeAddFloatFloat,opcodeAddVectorVector,FALSE,(yyvsp[0].expression));
				sdr->undesire();
			}
		;}
    break;

  case 128:
#line 1411 "sl.y"
    {
			CVariable	*cVar				=	sdr->getVariable((yyvsp[-1].string));

			if (cVar == NULL)	sdr->error("Identifier %s not found\n",(yyvsp[-1].string));
			else				sdr->desire(cVar->type);
		;}
    break;

  case 129:
#line 1418 "sl.y"
    {
			CVariable			*cVar		=	sdr->getVariable((yyvsp[-3].string));

			if (cVar == NULL) {
				(yyval.expression)	=	new CNullExpression;
			} else {
				(yyval.expression)	=	new CUpdateExpression(cVar,opcodeSubFloatFloat,opcodeSubVectorVector,FALSE,(yyvsp[0].expression));
				sdr->undesire();
			}
		;}
    break;

  case 130:
#line 1431 "sl.y"
    {
			CVariable	*cVar				=	sdr->getVariable((yyvsp[-1].string));

			if (cVar == NULL)	sdr->error("Identifier %s not found\n",(yyvsp[-1].string));
			else {
				(yyval.expression)	=	new CUpdateExpression(cVar,opcodeAddFloatFloat,opcodeAddVectorVector,FALSE,new CConstantTerminalExpression(SLC_FLOAT,strdup("1")));
			}
		;}
    break;

  case 131:
#line 1442 "sl.y"
    {
			CVariable	*cVar				=	sdr->getVariable((yyvsp[-1].string));

			if (cVar == NULL)	sdr->error("Identifier %s not found\n",(yyvsp[-1].string));
			else {
				(yyval.expression)	=	new CUpdateExpression(cVar,opcodeAddFloatFloat,opcodeAddVectorVector,FALSE,new CConstantTerminalExpression(SLC_FLOAT,strdup("-1")));
			}
		;}
    break;

  case 132:
#line 1453 "sl.y"
    {
			CVariable	*cVar				=	sdr->getVariable((yyvsp[-1].string));

			if (cVar == NULL)	sdr->error("Identifier %s not found\n",(yyvsp[-1].string));
			else				sdr->desire(cVar->type);
		;}
    break;

  case 133:
#line 1460 "sl.y"
    {
			CVariable			*cVar		=	sdr->getVariable((yyvsp[-3].string));

			if (cVar == NULL) {
				(yyval.expression)	=	new CNullExpression;
			} else {
				(yyval.expression)	=	new CUpdateExpression(cVar,opcodeMulFloatFloat,opcodeMulVectorVector,FALSE,(yyvsp[0].expression));
				sdr->undesire();
			}
		;}
    break;

  case 134:
#line 1473 "sl.y"
    {
			CVariable	*cVar				=	sdr->getVariable((yyvsp[-1].string));

			if (cVar == NULL)	sdr->error("Identifier %s not found\n",(yyvsp[-1].string));
			else				sdr->desire(cVar->type);
		;}
    break;

  case 135:
#line 1480 "sl.y"
    {
			CVariable			*cVar		=	sdr->getVariable((yyvsp[-3].string));

			if (cVar == NULL) {
				(yyval.expression)	=	new CNullExpression;
			} else {
				(yyval.expression)	=	new CUpdateExpression(cVar,opcodeDivFloatFloat,opcodeDivVectorVector,FALSE,(yyvsp[0].expression));
				sdr->undesire();
			}
		;}
    break;

  case 136:
#line 1496 "sl.y"
    {
			CVariable	*cVar				=	sdr->getVariable((yyvsp[-4].string));

			if (cVar == NULL)	sdr->error("Identifier %s not found\n",(yyvsp[-4].string));
			else				sdr->desire(cVar->type);
		;}
    break;

  case 137:
#line 1503 "sl.y"
    {
			CVariable			*cVar		=	sdr->getVariable((yyvsp[-6].string));
			
			if (cVar == NULL) {
				(yyval.expression)	=	new CNullExpression;
			} else {
				(yyval.expression)	=	new CArrayUpdateExpression(cVar,(yyvsp[-4].expression),(yyvsp[0].expression),opcodeAddFloatFloat,opcodeAddVectorVector,opcodeAddMatrixMatrix);
				sdr->undesire();
			}
		;}
    break;

  case 138:
#line 1519 "sl.y"
    {
			CVariable	*cVar				=	sdr->getVariable((yyvsp[-4].string));

			if (cVar == NULL)	sdr->error("Identifier %s not found\n",(yyvsp[-4].string));
			else				sdr->desire(cVar->type);
		;}
    break;

  case 139:
#line 1526 "sl.y"
    {
			CVariable			*cVar		=	sdr->getVariable((yyvsp[-6].string));

			if (cVar == NULL) {
				(yyval.expression)	=	new CNullExpression;
			} else {
				(yyval.expression)	=	new CArrayUpdateExpression(cVar,(yyvsp[-4].expression),(yyvsp[0].expression),opcodeSubFloatFloat,opcodeSubVectorVector,opcodeSubMatrixMatrix);
				sdr->undesire();
			}
		;}
    break;

  case 140:
#line 1542 "sl.y"
    {
			CVariable	*cVar				=	sdr->getVariable((yyvsp[-4].string));

			if (cVar == NULL)	sdr->error("Identifier %s not found\n",(yyvsp[-4].string));
			else {
				(yyval.expression)	=	new CArrayUpdateExpression(cVar,(yyvsp[-2].expression),new CConstantTerminalExpression(SLC_FLOAT,strdup("1")),opcodeAddFloatFloat,opcodeAddVectorVector,opcodeAddMatrixMatrix);
			}
		;}
    break;

  case 141:
#line 1556 "sl.y"
    {
			CVariable	*cVar				=	sdr->getVariable((yyvsp[-4].string));

			if (cVar == NULL)	sdr->error("Identifier %s not found\n",(yyvsp[-4].string));
			else {
				(yyval.expression)	=	new CArrayUpdateExpression(cVar,(yyvsp[-2].expression),new CConstantTerminalExpression(SLC_FLOAT,strdup("-1")),opcodeAddFloatFloat,opcodeAddVectorVector,opcodeAddMatrixMatrix);
			}
		;}
    break;

  case 142:
#line 1570 "sl.y"
    {
			CVariable	*cVar				=	sdr->getVariable((yyvsp[-4].string));

			if (cVar == NULL)	sdr->error("Identifier %s not found\n",(yyvsp[-4].string));
			else				sdr->desire(cVar->type);
		;}
    break;

  case 143:
#line 1577 "sl.y"
    {
			CVariable			*cVar		=	sdr->getVariable((yyvsp[-6].string));

			if (cVar == NULL) {
				(yyval.expression)	=	new CNullExpression;
			} else {
				(yyval.expression)	=	new CArrayUpdateExpression(cVar,(yyvsp[-4].expression),(yyvsp[0].expression),opcodeMulFloatFloat,opcodeMulVectorVector,opcodeMulMatrixMatrix);
				sdr->undesire();
			}
		;}
    break;

  case 144:
#line 1593 "sl.y"
    {
			CVariable	*cVar				=	sdr->getVariable((yyvsp[-4].string));

			if (cVar == NULL)	sdr->error("Identifier %s not found\n",(yyvsp[-4].string));
			else				sdr->desire(cVar->type);
		;}
    break;

  case 145:
#line 1600 "sl.y"
    {
			CVariable			*cVar		=	sdr->getVariable((yyvsp[-6].string));

			if (cVar == NULL) {
				(yyval.expression)	=	new CNullExpression;
			} else {
				(yyval.expression)	=	new CArrayUpdateExpression(cVar,(yyvsp[-4].expression),(yyvsp[0].expression),opcodeDivFloatFloat,opcodeDivVectorVector,opcodeDivMatrixMatrix);
				sdr->undesire();
			}
		;}
    break;

  case 146:
#line 1616 "sl.y"
    {
			CFunction	*cFun	=	sdr->newFunction(constantLoopName);
		;}
    break;

  case 147:
#line 1630 "sl.y"
    {
			CFunction	*cFun	=	sdr->popFunction();

			(yyval.code)	=	new CForLoop((yyvsp[-6].code),(yyvsp[-4].expression),(yyvsp[-2].code),(yyvsp[0].code));
		;}
    break;

  case 148:
#line 1647 "sl.y"
    {
			CFunction	*cFun	=	sdr->popFunction();

			(yyval.code)	=	new CForLoop((yyvsp[-6].code),(yyvsp[-4].expression),(yyvsp[-2].code),(yyvsp[0].code));
		;}
    break;

  case 149:
#line 1658 "sl.y"
    {
			(yyval.code)	=	(yyvsp[0].code);
		;}
    break;

  case 150:
#line 1662 "sl.y"
    {
			(yyval.code)	=	new CNullExpression;
		;}
    break;

  case 151:
#line 1673 "sl.y"
    {
			(yyval.code)	=	new CTwoExpressions((yyvsp[-2].expression),(yyvsp[0].code));
		;}
    break;

  case 152:
#line 1678 "sl.y"
    {
			(yyval.code)	=	(yyvsp[0].expression);
		;}
    break;

  case 153:
#line 1687 "sl.y"
    {
			(yyval.expression)	=	getConversion(SLC_BOOLEAN,(yyvsp[0].expression));
		;}
    break;

  case 154:
#line 1691 "sl.y"
    {
			(yyval.expression)	=	new CConstantTerminalExpression(SLC_BOOLEAN | SLC_UNIFORM,strdup("true"));
		;}
    break;

  case 155:
#line 1700 "sl.y"
    {
			(yyval.code)	=	(yyvsp[0].code);
		;}
    break;

  case 156:
#line 1704 "sl.y"
    {
			(yyval.code)	=	new CNullExpression;
		;}
    break;

  case 157:
#line 1715 "sl.y"
    {
			(yyval.code)	=	new CTwoExpressions((yyvsp[-2].expression),(yyvsp[0].code));
		;}
    break;

  case 158:
#line 1720 "sl.y"
    {
			(yyval.code)	=	(yyvsp[0].expression);
		;}
    break;

  case 159:
#line 1727 "sl.y"
    {
			(yyval.code)	=	new CTwoExpressions((yyvsp[-2].expression),(yyvsp[0].code));
		;}
    break;

  case 160:
#line 1732 "sl.y"
    {
			(yyval.code)	=	(yyvsp[0].expression);
		;}
    break;

  case 161:
#line 1747 "sl.y"
    {
			(yyval.code)	=	new CIfThenElse((yyvsp[-4].expression),(yyvsp[-2].code),(yyvsp[0].code));
		;}
    break;

  case 162:
#line 1760 "sl.y"
    {
			(yyval.code)	=	new CIfThenElse((yyvsp[-2].expression),(yyvsp[0].code),NULL);
		;}
    break;

  case 163:
#line 1771 "sl.y"
    {
			(yyval.code)	=	new CIfThenElse((yyvsp[-4].expression),(yyvsp[-2].code),(yyvsp[0].code));
		;}
    break;

  case 164:
#line 1784 "sl.y"
    {
			(yyval.array)->push((yyvsp[0].expression));
		;}
    break;

  case 165:
#line 1789 "sl.y"
    {
			sdr->actualParameters->push((yyvsp[0].expression));
			(yyval.array)	=	sdr->actualParameters;
		;}
    break;

  case 166:
#line 1798 "sl.y"
    {
			sdr->actualParameterStack->push(sdr->actualParameters);
			sdr->actualParameters	=	new CArray<CExpression *>;
		;}
    break;

  case 167:
#line 1804 "sl.y"
    {
			(yyval.array)	=	(yyvsp[-1].array);
		;}
    break;

  case 168:
#line 1816 "sl.y"
    {
			(yyval.code)	=	new CGatherThenElse((yyvsp[-3].array),(yyvsp[-2].code),(yyvsp[0].code));
			sdr->actualParameters	=	sdr->actualParameterStack->pop();
		;}
    break;

  case 169:
#line 1827 "sl.y"
    {
			(yyval.code)	=	new CGatherThenElse((yyvsp[-1].array),(yyvsp[0].code),NULL);
			sdr->actualParameters	=	sdr->actualParameterStack->pop();
		;}
    break;

  case 170:
#line 1836 "sl.y"
    {
			(yyval.code)	=	new CGatherThenElse((yyvsp[-3].array),(yyvsp[-2].code),(yyvsp[0].code));
			sdr->actualParameters	=	sdr->actualParameterStack->pop();
		;}
    break;

  case 171:
#line 1846 "sl.y"
    {
			CFunction	*cCFunction	=	sdr->newFunction(constantLoopName);

			sdr->requiredShaderContext	|=	SLC_SURFACE;
		;}
    break;

  case 172:
#line 1858 "sl.y"
    {
			CFunction	*cFun	=	sdr->popFunction();

			(yyval.code)	=	new CIlluminationLoop(NULL,(yyvsp[-2].expression),NULL,NULL,(yyvsp[0].code));
		;}
    break;

  case 173:
#line 1871 "sl.y"
    {
			CFunction	*cFun	=	sdr->popFunction();

			(yyval.code)	=	new CIlluminationLoop((yyvsp[-4].expression),(yyvsp[-2].expression),NULL,NULL,(yyvsp[0].code));
		;}
    break;

  case 174:
#line 1886 "sl.y"
    {
			CFunction	*cFun	=	sdr->popFunction();

			(yyval.code)	=	new CIlluminationLoop(NULL,(yyvsp[-6].expression),(yyvsp[-4].expression),(yyvsp[-2].expression),(yyvsp[0].code));
		;}
    break;

  case 175:
#line 1903 "sl.y"
    {
			CFunction	*cFun	=	sdr->popFunction();

			(yyval.code)	=	new CIlluminationLoop((yyvsp[-8].expression),(yyvsp[-6].expression),(yyvsp[-4].expression),(yyvsp[-2].expression),(yyvsp[0].code));
		;}
    break;

  case 176:
#line 1916 "sl.y"
    {
			CFunction	*cFun	=	sdr->popFunction();

			(yyval.code)	=	new CIlluminationLoop(NULL,(yyvsp[-2].expression),NULL,NULL,(yyvsp[0].code));
		;}
    break;

  case 177:
#line 1929 "sl.y"
    {
			CFunction	*cFun	=	sdr->popFunction();

			(yyval.code)	=	new CIlluminationLoop((yyvsp[-4].expression),(yyvsp[-2].expression),NULL,NULL,(yyvsp[0].code));
		;}
    break;

  case 178:
#line 1944 "sl.y"
    {
			CFunction	*cFun	=	sdr->popFunction();

			(yyval.code)	=	new CIlluminationLoop(NULL,(yyvsp[-6].expression),(yyvsp[-4].expression),(yyvsp[-2].expression),(yyvsp[0].code));
		;}
    break;

  case 179:
#line 1961 "sl.y"
    {
			CFunction	*cFun	=	sdr->popFunction();

			(yyval.code)	=	new CIlluminationLoop((yyvsp[-8].expression),(yyvsp[-6].expression),(yyvsp[-4].expression),(yyvsp[-2].expression),(yyvsp[0].code));
		;}
    break;

  case 180:
#line 1976 "sl.y"
    {
			sdr->requiredShaderContext	|=	SLC_LIGHT;

			(yyval.code)	=	new CIlluminateSolar(opcodeIlluminate,opcodeEndIlluminate,(yyvsp[-2].expression),NULL,NULL,(yyvsp[0].code));
		;}
    break;

  case 181:
#line 1991 "sl.y"
    {
			sdr->requiredShaderContext	|=	SLC_LIGHT;

			(yyval.code)	=	new CIlluminateSolar(opcodeIlluminate,opcodeEndIlluminate,(yyvsp[-6].expression),(yyvsp[-4].expression),(yyvsp[-2].expression),(yyvsp[0].code));
		;}
    break;

  case 182:
#line 2004 "sl.y"
    {
			sdr->requiredShaderContext	|=	SLC_LIGHT;

			(yyval.code)	=	new CIlluminateSolar(opcodeIlluminate,opcodeEndIlluminate,(yyvsp[-2].expression),NULL,NULL,(yyvsp[0].code));
		;}
    break;

  case 183:
#line 2019 "sl.y"
    {
			sdr->requiredShaderContext	|=	SLC_LIGHT;

			(yyval.code)	=	new CIlluminateSolar(opcodeIlluminate,opcodeEndIlluminate,(yyvsp[-6].expression),(yyvsp[-4].expression),(yyvsp[-2].expression),(yyvsp[0].code));
		;}
    break;

  case 184:
#line 2033 "sl.y"
    {
			sdr->requiredShaderContext	|=	SLC_LIGHT;

			(yyval.code)	=	new CIlluminateSolar(opcodeSolar,opcodeEndSolar,NULL,NULL,NULL,(yyvsp[0].code));
		;}
    break;

  case 185:
#line 2046 "sl.y"
    {
			sdr->requiredShaderContext	|=	SLC_LIGHT;

			(yyval.code)	=	new CIlluminateSolar(opcodeSolar,opcodeEndSolar,(yyvsp[-4].expression),(yyvsp[-2].expression),NULL,(yyvsp[0].code));
		;}
    break;

  case 186:
#line 2058 "sl.y"
    {
			sdr->requiredShaderContext	|=	SLC_LIGHT;

			(yyval.code)	=	new CIlluminateSolar(opcodeSolar,opcodeEndSolar,NULL,NULL,NULL,(yyvsp[0].code));
		;}
    break;

  case 187:
#line 2071 "sl.y"
    {
			sdr->requiredShaderContext	|=	SLC_LIGHT;

			(yyval.code)	=	new CIlluminateSolar(opcodeSolar,opcodeEndSolar,(yyvsp[-4].expression),(yyvsp[-2].expression),NULL,(yyvsp[0].code));
		;}
    break;

  case 188:
#line 2082 "sl.y"
    {
			(yyval.expression)	=	(yyvsp[0].expression);
		;}
    break;

  case 189:
#line 2089 "sl.y"
    {
			(yyval.expression)	=	getOperation((yyvsp[-2].expression),(yyvsp[0].expression),opcodeAddFloatFloat,opcodeAddVectorVector,opcodeAddMatrixMatrix,NULL,NULL);
		;}
    break;

  case 190:
#line 2096 "sl.y"
    {
			(yyval.expression)	=	getOperation((yyvsp[-2].expression),(yyvsp[0].expression),opcodeSubFloatFloat,opcodeSubVectorVector,opcodeSubMatrixMatrix,NULL,NULL);
		;}
    break;

  case 191:
#line 2103 "sl.y"
    {
			(yyval.expression)	=	NULL;

			if ((yyvsp[-2].expression)->type & SLC_MATRIX) {
				if ((yyvsp[0].expression)->type & SLC_VVECTOR) {
					(yyval.expression)	=	new CBinaryExpression(SLC_VECTOR | SLC_VVECTOR,opcodeMulMatrixVector,(yyvsp[-2].expression),getConversion(SLC_VECTOR,(yyvsp[0].expression)));
				} else if ((yyvsp[0].expression)->type & SLC_VPOINT) {
					(yyval.expression)	=	new CBinaryExpression(SLC_VECTOR | SLC_VPOINT,opcodeMulMatrixPoint,(yyvsp[-2].expression),getConversion(SLC_VECTOR,(yyvsp[0].expression)));
				} else if ((yyvsp[0].expression)->type & SLC_VNORMAL) {
					(yyval.expression)	=	new CBinaryExpression(SLC_VECTOR | SLC_VNORMAL,opcodeMulMatrixNormal,(yyvsp[-2].expression),getConversion(SLC_VECTOR,(yyvsp[0].expression)));
				}
			}

			if ((yyval.expression) == NULL) {
				if ((yyvsp[0].expression)->type & SLC_MATRIX) {
					if ((yyvsp[-2].expression)->type & SLC_VVECTOR) {
						(yyval.expression)	=	new CBinaryExpression(SLC_VECTOR | SLC_VVECTOR,opcodeMulVectorMatrix,(yyvsp[-2].expression),getConversion(SLC_VECTOR,(yyvsp[0].expression)));
					} else if ((yyvsp[-2].expression)->type & SLC_VPOINT) {
						(yyval.expression)	=	new CBinaryExpression(SLC_VECTOR | SLC_VPOINT,opcodeMulPointMatrix,(yyvsp[-2].expression),getConversion(SLC_VECTOR,(yyvsp[0].expression)));
					} else if ((yyvsp[-2].expression)->type & SLC_VNORMAL) {
						(yyval.expression)	=	new CBinaryExpression(SLC_VECTOR | SLC_VNORMAL,opcodeMulNormalMatrix,(yyvsp[-2].expression),getConversion(SLC_VECTOR,(yyvsp[0].expression)));
					}
				}
			}


			if ((yyval.expression) == NULL)
				(yyval.expression)	=	getOperation((yyvsp[-2].expression),(yyvsp[0].expression),opcodeMulFloatFloat,opcodeMulVectorVector,opcodeMulMatrixMatrix,NULL,NULL);
		;}
    break;

  case 192:
#line 2136 "sl.y"
    {
			(yyval.expression)	=	getOperation((yyvsp[-2].expression),(yyvsp[0].expression),opcodeDivFloatFloat,opcodeDivVectorVector,opcodeDivMatrixMatrix,NULL,NULL);
		;}
    break;

  case 193:
#line 2142 "sl.y"
    {
			sdr->desire(SLC_VECTOR | SLC_VVECTOR);
		;}
    break;

  case 194:
#line 2146 "sl.y"
    {
			sdr->undesire();
			(yyval.expression)	=	new CBinaryExpression(SLC_FLOAT,opcodeDotProduct,getConversion(SLC_VECTOR,(yyvsp[-3].expression)),getConversion(SLC_VECTOR,(yyvsp[0].expression)));
		;}
    break;

  case 195:
#line 2154 "sl.y"
    {
			(yyval.expression)	=	new CBinaryExpression(SLC_VECTOR,opcodeCrossProduct,getConversion(SLC_VECTOR,(yyvsp[-2].expression)),getConversion(SLC_VECTOR,(yyvsp[0].expression)));
		;}
    break;

  case 196:
#line 2160 "sl.y"
    {
			(yyval.expression)	=	(yyvsp[0].expression);	
		;}
    break;

  case 197:
#line 2166 "sl.y"
    {
			(yyval.expression)	=	getOperation((yyvsp[0].expression),opcodeNegFloat,opcodeNegVector,opcodeNegMatrix,NULL,NULL);
		;}
    break;

  case 198:
#line 2175 "sl.y"
    {
			int	ft	=	(yyvsp[-2].expression)->type;
			int	st	=	(yyvsp[0].expression)->type;

			if (((yyvsp[-2].expression)->type & SLC_TYPE_MASK) == ((yyvsp[0].expression)->type & SLC_TYPE_MASK)) {
				(yyval.expression)	=	new CConditionalExpression((yyvsp[-2].expression)->type,(yyvsp[-4].expression),(yyvsp[-2].expression),(yyvsp[0].expression));
			} else {
				sdr->error("Type mismatch in conditional execution\n");
			}
		;}
    break;

  case 199:
#line 2191 "sl.y"
    {
			(yyval.array)	=	(yyvsp[-1].array);
		;}
    break;

  case 200:
#line 2200 "sl.y"
    {
			(yyval.array)	=	(yyvsp[0].array);
			(yyval.array)->push((yyvsp[-2].expression));
		;}
    break;

  case 201:
#line 2206 "sl.y"
    {
			(yyval.array)	=	new CArray<CExpression *>;
			(yyval.array)->push((yyvsp[0].expression));
		;}
    break;

  case 202:
#line 2214 "sl.y"
    {
			(yyval.expression)	=	new CConstantTerminalExpression(SLC_FLOAT | SLC_UNIFORM,strdup("3.141592654"));
		;}
    break;

  case 203:
#line 2219 "sl.y"
    {
			(yyval.expression)	=	(yyvsp[0].expression);
		;}
    break;

  case 204:
#line 2224 "sl.y"
    {
			(yyval.expression)	=	(yyvsp[0].expression);
		;}
    break;

  case 205:
#line 2229 "sl.y"
    {
			(yyval.expression)	=	(yyvsp[0].expression);
		;}
    break;

  case 206:
#line 2234 "sl.y"
    {
			(yyval.expression)	=	(yyvsp[0].expression);
		;}
    break;

  case 207:
#line 2239 "sl.y"
    {
	
			CVariable	*cVar	=	sdr->getVariable((yyvsp[0].string));

			if (cVar == NULL) {
				sdr->error("Identifier %s not found\n",(yyvsp[0].string));
				(yyval.expression)	=	new CNullExpression;
			} else { 
				(yyval.expression)	=	new CTerminalExpression(cVar);
			}
		;}
    break;

  case 208:
#line 2255 "sl.y"
    {
			CVariable *cVar	=	sdr->getVariable((yyvsp[-3].string));

			if (cVar == NULL) {
				sdr->error("Identifier %s not found\n",(yyvsp[-3].string));
				(yyval.expression)	=	new CNullExpression;
			} else if (cVar->type & SLC_ARRAY) { 
				(yyval.expression)	=	new CArrayExpression(cVar,(yyvsp[-1].expression));
			} else {
				CArray<CExpression *>	*dummyParams = new CArray<CExpression *>;
				CFunctionPrototype		*cFun;

				dummyParams->push(new CTerminalExpression(cVar));
				dummyParams->push((yyvsp[-1].expression));

				// Check the builtin functions
				for (cFun = sdr->builtinFunctions->first(); cFun != NULL; cFun = sdr->builtinFunctions->next()) {
					if (cFun->match("comp",dummyParams,SLC_FLOAT)) break;
				}
				
				if (cFun == NULL) {
					// Cleanup
					CExpression	*cCode;
					while((cCode = dummyParams->pop()) != NULL) {
						delete cCode;
					}
					delete dummyParams;
					// Report error
					sdr->error("Can't index non array\n");
					(yyval.expression)	=	new CNullExpression;
				} else {
					(yyval.expression)	=	new CBuiltinExpression(cFun,dummyParams);
				}
			}
		;}
    break;

  case 209:
#line 2292 "sl.y"
    {
			(yyval.expression)	=	new CConstantTerminalExpression(SLC_FLOAT,strdup((yyvsp[0].string)));
		;}
    break;

  case 210:
#line 2297 "sl.y"
    {
			(yyval.expression)	=	new CConstantTerminalExpression(SLC_STRING,strdup((yyvsp[0].string)));
		;}
    break;

  case 211:
#line 2308 "sl.y"
    {
			(yyval.expression)	=	new CVectorExpression((yyvsp[-5].expression),(yyvsp[-3].expression),(yyvsp[-1].expression));
		;}
    break;

  case 212:
#line 2345 "sl.y"
    {
			CExpression	*elements[16];

			elements[0]		=	(yyvsp[-31].expression);
			elements[1]		=	(yyvsp[-29].expression);
			elements[2]		=	(yyvsp[-27].expression);
			elements[3]		=	(yyvsp[-25].expression);
			elements[4]		=	(yyvsp[-23].expression);
			elements[5]		=	(yyvsp[-21].expression);
			elements[6]		=	(yyvsp[-19].expression);
			elements[7]		=	(yyvsp[-17].expression);
			elements[8]		=	(yyvsp[-15].expression);
			elements[9]		=	(yyvsp[-13].expression);
			elements[10]	=	(yyvsp[-11].expression);
			elements[11]	=	(yyvsp[-9].expression);
			elements[12]	=	(yyvsp[-7].expression);
			elements[13]	=	(yyvsp[-5].expression);
			elements[14]	=	(yyvsp[-3].expression);
			elements[15]	=	(yyvsp[-1].expression);

			(yyval.expression)				=	new CMatrixExpression(elements);
		;}
    break;

  case 213:
#line 2371 "sl.y"
    {	
			(yyval.expression)	=	(yyvsp[-1].expression);
		;}
    break;

  case 214:
#line 2380 "sl.y"
    {
			(yyval.expression)	=	getConversion((yyvsp[-1].integer),(yyvsp[0].expression));

			sdr->undesire();
		;}
    break;

  case 215:
#line 2389 "sl.y"
    {
			(yyval.expression)	=	getConversion((yyvsp[-2].integer),(yyvsp[-1].string),(yyvsp[0].expression));

			sdr->undesire();
		;}
    break;

  case 216:
#line 2400 "sl.y"
    {
			(yyval.expression)	=	(yyvsp[-1].expression);
		;}
    break;

  case 217:
#line 2407 "sl.y"
    {
			(yyval.expression)	=	getOperation((yyvsp[-2].expression),(yyvsp[0].expression),NULL,NULL,NULL,NULL,opcodeAnd);
		;}
    break;

  case 218:
#line 2414 "sl.y"
    {
			(yyval.expression)	=	getOperation((yyvsp[-2].expression),(yyvsp[0].expression),NULL,NULL,NULL,NULL,opcodeOr);
		;}
    break;

  case 219:
#line 2421 "sl.y"
    {
			(yyval.expression)			=	getOperation((yyvsp[-2].expression),(yyvsp[0].expression),opcodeFloatGreater,opcodeVectorGreater,NULL,NULL,NULL);
			(yyval.expression)->type	=	SLC_BOOLEAN | ((yyvsp[-2].expression)->type & (yyvsp[0].expression)->type & SLC_UNIFORM);
		;}
    break;

  case 220:
#line 2429 "sl.y"
    {
			(yyval.expression)			=	getOperation((yyvsp[-2].expression),(yyvsp[0].expression),opcodeFloatLess,opcodeVectorLess,NULL,NULL,NULL);
			(yyval.expression)->type	=	SLC_BOOLEAN | ((yyvsp[-2].expression)->type & (yyvsp[0].expression)->type & SLC_UNIFORM);
		;}
    break;

  case 221:
#line 2437 "sl.y"
    {
			(yyval.expression)			=	getOperation((yyvsp[-2].expression),(yyvsp[0].expression),opcodeFloatEGreater,opcodeVectorEGreater,NULL,NULL,NULL);
			(yyval.expression)->type	=	SLC_BOOLEAN | ((yyvsp[-2].expression)->type & (yyvsp[0].expression)->type & SLC_UNIFORM);
		;}
    break;

  case 222:
#line 2445 "sl.y"
    {
			(yyval.expression)			=	getOperation((yyvsp[-2].expression),(yyvsp[0].expression),opcodeFloatELess,opcodeVectorELess,NULL,NULL,NULL);
			(yyval.expression)->type	=	SLC_BOOLEAN | ((yyvsp[-2].expression)->type & (yyvsp[0].expression)->type & SLC_UNIFORM);
		;}
    break;

  case 223:
#line 2453 "sl.y"
    {
			(yyval.expression)			=	getOperation((yyvsp[-2].expression),(yyvsp[0].expression),opcodeFloatEqual,opcodeVectorEqual,NULL,opcodeStringEqual,NULL);
			(yyval.expression)->type	=	SLC_BOOLEAN | ((yyvsp[-2].expression)->type & (yyvsp[0].expression)->type & SLC_UNIFORM);
		;}
    break;

  case 224:
#line 2461 "sl.y"
    {
			(yyval.expression)			=	getOperation((yyvsp[-2].expression),(yyvsp[0].expression),opcodeFloatNotEqual,opcodeVectorNotEqual,NULL,opcodeStringNotEqual,NULL);
			(yyval.expression)->type	=	SLC_BOOLEAN | ((yyvsp[-2].expression)->type & (yyvsp[0].expression)->type & SLC_UNIFORM);
		;}
    break;

  case 225:
#line 2469 "sl.y"
    {
			(yyval.expression)			=	getOperation((yyvsp[-2].expression),(yyvsp[0].expression),NULL,NULL,NULL,NULL,opcodeAnd);
			(yyval.expression)->type	=	SLC_BOOLEAN | ((yyvsp[-2].expression)->type & (yyvsp[0].expression)->type & SLC_UNIFORM);
		;}
    break;

  case 226:
#line 2477 "sl.y"
    {
			(yyval.expression)			=	getOperation((yyvsp[-2].expression),(yyvsp[0].expression),NULL,NULL,NULL,NULL,opcodeXor);
			(yyval.expression)->type	=	SLC_BOOLEAN | ((yyvsp[-2].expression)->type & (yyvsp[0].expression)->type & SLC_UNIFORM);
		;}
    break;

  case 227:
#line 2484 "sl.y"
    {
			(yyval.expression)			=	new CUnaryExpression(SLC_BOOLEAN,opcodeNot,getConversion(SLC_BOOLEAN,(yyvsp[0].expression)));
		;}
    break;

  case 228:
#line 2494 "sl.y"
    {
			CFunctionPrototype		*cFun;
			CArray<CExpression *>	*parameters	=	sdr->actualParameters;	// This is the list of parameters to the function

			char					*funName	=	(yyvsp[0].string);

			// Clear the desired type flags
			sdr->undesire();

			// Restore the old parameters
			sdr->actualParameters		=	sdr->actualParameterStack->pop();


			// Check the builtin functions
			for (cFun = sdr->builtinFunctions->first(); cFun != NULL; cFun = sdr->builtinFunctions->next()) {
				if (cFun->perfectMatch((yyvsp[0].string),parameters,sdr->desired())) break;
			}

			if (cFun == NULL) {
				for (cFun = sdr->builtinFunctions->first(); cFun != NULL; cFun = sdr->builtinFunctions->next()) {
					if (cFun->match((yyvsp[0].string),parameters,sdr->desired())) break;
				}
			}

			if (cFun != NULL) {
				(yyval.expression)	=	new CBuiltinExpression(cFun,parameters);
			} else {
				sdr->error("Function %s not found\n",(yyvsp[0].string));
				if (parameters->numItems != 0) {
					CExpression	*cCode;
					while((cCode = parameters->pop()) != NULL) {
						delete cCode;
					}
				}
				delete parameters;
				(yyval.expression)	=	new CNullExpression;
			}
		;}
    break;

  case 229:
#line 2534 "sl.y"
    {
			(yyval.expression)	=	(yyvsp[0].expression);
		;}
    break;

  case 230:
#line 2544 "sl.y"
    {
			// Save the old parameters
			sdr->actualParameterStack->push(sdr->actualParameters);
			// Start a new parameter list
			sdr->actualParameters	=	new CArray<CExpression *>;

			// Make sure we do not do something stupid with the parameters
			sdr->desire(SLC_NONE);

			// Set the name
			(yyval.string)	=	(yyvsp[-1].string);
		;}
    break;

  case 231:
#line 2559 "sl.y"
    {
			// Save the old parameters
			sdr->actualParameterStack->push(sdr->actualParameters);
			// Start a new parameter list
			sdr->actualParameters	=	new CArray<CExpression *>;

			// Make sure we do not do something stupid with the parameters
			sdr->desire(SLC_NONE);

			// Set the name
			(yyval.string)	=	"surface";
		;}
    break;

  case 232:
#line 2574 "sl.y"
    {
			// Save the old parameters
			sdr->actualParameterStack->push(sdr->actualParameters);
			// Start a new parameter list
			sdr->actualParameters	=	new CArray<CExpression *>;

			// Make sure we do not do something stupid with the parameters
			sdr->desire(SLC_NONE);

			// Set the name
			(yyval.string)	=	"displacement";
		;}
    break;

  case 233:
#line 2592 "sl.y"
    {
			CFunction				*cFun;
			CArray<CExpression *>	*parameters	=	sdr->actualParameters;	// This is the list of parameters to the function

			char					*funName	=	(yyvsp[-2].string);

			// Clear the desired type flags
			sdr->undesire();

			// Restore the old parameters
			sdr->actualParameters		=	sdr->actualParameterStack->pop();

			// Search for the CFunction here....
			cFun	=	sdr->getFunction((yyvsp[-2].string),parameters);

			if (cFun != NULL) {													// Cool, the function exists
				// A function with the same name is defined ... 
				// Try to match the parameters;
				if (cFun->parameters->numItems == parameters->numItems) {	// The number of parameters match
					// A function with the same name is defined and the number of Parameters match
					(yyval.expression)	=	new CFuncallExpression(cFun,parameters);					
				}
			}

			// If not found, check the predefined CFunctions
			if (cFun == NULL) {
				CFunctionPrototype	*cFun;
				char				*fName	=	(yyvsp[-2].string);
				// Check the builtin CFunctions

				for (cFun = sdr->builtinFunctions->first(); cFun != NULL; cFun = sdr->builtinFunctions->next()) {
					if (cFun->perfectMatch((yyvsp[-2].string),parameters,sdr->desired())) break;
				}

				if (cFun == NULL) {
					for (cFun = sdr->builtinFunctions->first(); cFun != NULL; cFun = sdr->builtinFunctions->next()) {
						if (cFun->match((yyvsp[-2].string),parameters,sdr->desired())) break;
					}
				}

				// Check if there is a DSO implementing this function
				if (cFun == NULL) {
					sdr->enumerateDso((yyvsp[-2].string));

					for (cFun = sdr->builtinFunctions->first(); cFun != NULL; cFun = sdr->builtinFunctions->next()) {
						if (cFun->perfectMatch((yyvsp[-2].string),parameters,sdr->desired())) break;
					}

					if (cFun == NULL) {
						for (cFun = sdr->builtinFunctions->first(); cFun != NULL; cFun = sdr->builtinFunctions->next()) {
							if (cFun->match((yyvsp[-2].string),parameters,sdr->desired())) break;
						}
					}
				}

				if (cFun != NULL) {
					(yyval.expression)	=	new CBuiltinExpression(cFun,parameters);
				} else {
					sdr->error("Function %s not found\n",(yyvsp[-2].string));
					if (parameters->numItems != 0) {
						CExpression	*cCode;
						while((cCode = parameters->pop()) != NULL) {
							delete cCode;
						}
					}
					delete parameters;
					(yyval.expression)	=	new CNullExpression;
				}

			}
		;}
    break;

  case 234:
#line 2669 "sl.y"
    {
			(yyval.code)	=	new CConstantTerminalExpression(SLC_STRING | SLC_UNIFORM,strdup((yyvsp[0].string)));
		;}
    break;

  case 235:
#line 2674 "sl.y"
    {
			CVariable	*cVar	=	sdr->getVariable((yyvsp[0].string));

			if (cVar != NULL)	(yyval.code)	=	new CTerminalExpression(cVar);
			else				(yyval.code)	=	new CNullExpression;
		;}
    break;

  case 236:
#line 2687 "sl.y"
    {
			(yyval.code)	=	getConversion(SLC_FLOAT | ((yyvsp[-1].expression)->type & SLC_UNIFORM),(yyvsp[-1].expression));
		;}
    break;

  case 237:
#line 2691 "sl.y"
    {
			(yyval.code)	=	new CConstantTerminalExpression(SLC_FLOAT | SLC_UNIFORM,strdup("0"));
		;}
    break;

  case 238:
#line 2709 "sl.y"
    {
			// Fake the parameters
			CArray<CExpression *>	*parameters	=	sdr->actualParameters;	// This is the list of parameters to the function
			CArray<CExpression *>	*pl			=	new CArray<CExpression *>;
			CExpression				*cExpression;

			pl->push((yyvsp[-4].code));
			pl->push((yyvsp[-3].code));
			for (cExpression=parameters->first();cExpression!=NULL;cExpression=parameters->next())
				pl->push(cExpression);

			delete parameters;
			sdr->actualParameters	=	pl;

			(yyval.string)						=	(yyvsp[-6].string);
		;}
    break;

  case 239:
#line 2731 "sl.y"
    {
			// Fake the parameters
			CArray<CExpression *>	*parameters	=	sdr->actualParameters;	// This is the list of parameters to the function
			CArray<CExpression *>	*pl			=	new CArray<CExpression *>;
			CExpression				*cExpression;

			pl->push((yyvsp[-2].code));
			pl->push((yyvsp[-1].code));
			for (cExpression=parameters->first();cExpression!=NULL;cExpression=parameters->next())
				pl->push(cExpression);

			delete parameters;
			sdr->actualParameters	=	pl;

			(yyval.string)						=	(yyvsp[-4].string);
		;}
    break;

  case 240:
#line 2751 "sl.y"
    {
			(yyval.string)	=	"texture";

			// Save the old parameters
			sdr->actualParameterStack->push(sdr->actualParameters);
			// Start a new parameter list
			sdr->actualParameters	=	new CArray<CExpression *>;

			// Make sure we do not do something stupid with the parameters
			sdr->desire(SLC_NONE);
		;}
    break;

  case 241:
#line 2764 "sl.y"
    {
			(yyval.string)	=	"shadow";

			// Save the old parameters
			sdr->actualParameterStack->push(sdr->actualParameters);
			// Start a new parameter list
			sdr->actualParameters	=	new CArray<CExpression *>;

			// Make sure we do not do something stupid with the parameters
			sdr->desire(SLC_NONE);
		;}
    break;

  case 242:
#line 2777 "sl.y"
    {
			(yyval.string)	=	"environment";

			// Save the old parameters
			sdr->actualParameterStack->push(sdr->actualParameters);
			// Start a new parameter list
			sdr->actualParameters	=	new CArray<CExpression *>;

			// Make sure we do not do something stupid with the parameters
			sdr->desire(SLC_NONE);
		;}
    break;

  case 243:
#line 2790 "sl.y"
    {
			(yyval.string)	=	"bump";

			// Save the old parameters
			sdr->actualParameterStack->push(sdr->actualParameters);
			// Start a new parameter list
			sdr->actualParameters	=	new CArray<CExpression *>;

			// Make sure we do not do something stupid with the parameters
			sdr->desire(SLC_NONE);
		;}
    break;

  case 244:
#line 2807 "sl.y"
    {
		;}
    break;

  case 245:
#line 2810 "sl.y"
    {
		;}
    break;

  case 246:
#line 2817 "sl.y"
    {
			sdr->actualParameters->push((yyvsp[-1].expression));
		;}
    break;

  case 247:
#line 2821 "sl.y"
    {
		;}
    break;

  case 248:
#line 2825 "sl.y"
    {
			sdr->actualParameters->push((yyvsp[0].expression));
		;}
    break;


      default: break;
    }

/* Line 1126 of yacc.c.  */
#line 4440 "sl.cpp"

  yyvsp -= yylen;
  yyssp -= yylen;


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
#if YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (YYPACT_NINF < yyn && yyn < YYLAST)
	{
	  int yytype = YYTRANSLATE (yychar);
	  YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
	  YYSIZE_T yysize = yysize0;
	  YYSIZE_T yysize1;
	  int yysize_overflow = 0;
	  char *yymsg = 0;
#	  define YYERROR_VERBOSE_ARGS_MAXIMUM 5
	  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
	  int yyx;

#if 0
	  /* This is so xgettext sees the translatable formats that are
	     constructed on the fly.  */
	  YY_("syntax error, unexpected %s");
	  YY_("syntax error, unexpected %s, expecting %s");
	  YY_("syntax error, unexpected %s, expecting %s or %s");
	  YY_("syntax error, unexpected %s, expecting %s or %s or %s");
	  YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
#endif
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
	  int yychecklim = YYLAST - yyn;
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
		yysize_overflow |= yysize1 < yysize;
		yysize = yysize1;
		yyfmt = yystpcpy (yyfmt, yyprefix);
		yyprefix = yyor;
	      }

	  yyf = YY_(yyformat);
	  yysize1 = yysize + yystrlen (yyf);
	  yysize_overflow |= yysize1 < yysize;
	  yysize = yysize1;

	  if (!yysize_overflow && yysize <= YYSTACK_ALLOC_MAXIMUM)
	    yymsg = (char *) YYSTACK_ALLOC (yysize);
	  if (yymsg)
	    {
	      /* Avoid sprintf, as that infringes on the user's name space.
		 Don't have undefined behavior even if the translation
		 produced a string with the wrong number of "%s"s.  */
	      char *yyp = yymsg;
	      int yyi = 0;
	      while ((*yyp = *yyf))
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
	      yyerror (yymsg);
	      YYSTACK_FREE (yymsg);
	    }
	  else
	    {
	      yyerror (YY_("syntax error"));
	      goto yyexhaustedlab;
	    }
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror (YY_("syntax error"));
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
        {
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
        }
      else
	{
	  yydestruct ("Error: discarding", yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (0)
     goto yyerrorlab;

yyvsp -= yylen;
  yyssp -= yylen;
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


      yydestruct ("Error: popping", yystos[yystate], yyvsp);
      YYPOPSTACK;
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


  /* Shift the error token. */
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

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK;
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  return yyresult;
}


#line 2830 "sl.y"



#include	"lex.sl.cpp"



int	CScriptContext::compile(FILE *in,char *outName) {
	
	sdr		=	this;

	slin	=	in;

	slparse();

	if (compileError == 0) {
		char		*tmp;

		if (outName == NULL) {
			// If there's no compile error, dump the compiled code
			tmp	=	new char[strlen(sdr->shaderName)+5];

			strcpy(tmp,sdr->shaderName);
			strcat(tmp,".sdr");
		} else {
			tmp	=	outName;
		}

		sdr->generateCode(tmp);

		if (tmp != outName) delete [] tmp;

		return TRUE;
	}
	return FALSE;
}


void	yyerror(char *mes) {
	sdr->error("Parse error\n");
}



