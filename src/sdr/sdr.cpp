/* A Bison parser, made by GNU Bison 2.0.  */

/* Skeleton parser for Yacc-like parsing with Bison,
   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004 Free Software Foundation, Inc.

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
   Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

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

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0

/* Substitute the variable and function names.  */
#define yyparse sdrparse
#define yylex   sdrlex
#define yyerror sdrerror
#define yylval  sdrlval
#define yychar  sdrchar
#define yydebug sdrdebug
#define yynerrs sdrnerrs


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     SCRL_PARAMETERS = 258,
     SCRL_VARIABLES = 259,
     SCRL_INIT = 260,
     SCRL_CODE = 261,
     SCRL_OUTPUT = 262,
     SCRL_VARYING = 263,
     SCRL_UNIFORM = 264,
     SCRL_BOOLEAN = 265,
     SCRL_FLOAT = 266,
     SCRL_COLOR = 267,
     SCRL_VECTOR = 268,
     SCRL_NORMAL = 269,
     SCRL_POINT = 270,
     SCRL_MATRIX = 271,
     SCRL_STRING = 272,
     SCRL_SURFACE = 273,
     SCRL_DISPLACEMENT = 274,
     SCRL_IMAGER = 275,
     SCRL_LIGHTSOURCE = 276,
     SCRL_VOLUME = 277,
     SCRL_GENERIC = 278,
     SCRL_DSO = 279,
     SCRL_DOT = 280,
     SCRL_COLON = 281,
     SCRL_EQUAL = 282,
     SCRL_OPEN_PARANTHESIS = 283,
     SCRL_CLOSE_PARANTHESIS = 284,
     SCRL_OPEN_SQR_PARANTHESIS = 285,
     SCRL_CLOSE_SQR_PARANTHESIS = 286,
     SCRL_COMMA = 287,
     SCRL_NL = 288,
     SCRL_TEXT_VALUE = 289,
     SCRL_IDENTIFIER_VALUE = 290,
     SCRL_LABEL_VALUE = 291,
     SCRL_FLOAT_VALUE = 292
   };
#endif
#define SCRL_PARAMETERS 258
#define SCRL_VARIABLES 259
#define SCRL_INIT 260
#define SCRL_CODE 261
#define SCRL_OUTPUT 262
#define SCRL_VARYING 263
#define SCRL_UNIFORM 264
#define SCRL_BOOLEAN 265
#define SCRL_FLOAT 266
#define SCRL_COLOR 267
#define SCRL_VECTOR 268
#define SCRL_NORMAL 269
#define SCRL_POINT 270
#define SCRL_MATRIX 271
#define SCRL_STRING 272
#define SCRL_SURFACE 273
#define SCRL_DISPLACEMENT 274
#define SCRL_IMAGER 275
#define SCRL_LIGHTSOURCE 276
#define SCRL_VOLUME 277
#define SCRL_GENERIC 278
#define SCRL_DSO 279
#define SCRL_DOT 280
#define SCRL_COLON 281
#define SCRL_EQUAL 282
#define SCRL_OPEN_PARANTHESIS 283
#define SCRL_CLOSE_PARANTHESIS 284
#define SCRL_OPEN_SQR_PARANTHESIS 285
#define SCRL_CLOSE_SQR_PARANTHESIS 286
#define SCRL_COMMA 287
#define SCRL_NL 288
#define SCRL_TEXT_VALUE 289
#define SCRL_IDENTIFIER_VALUE 290
#define SCRL_LABEL_VALUE 291
#define SCRL_FLOAT_VALUE 292




/* Copy the first part of user declarations.  */
#line 1 "sdr.y"

//////////////////////////////////////////////////////////////////////
//
//                             Pixie
//
// Copyright © 1999 - 2003, Okan Arikan
//
// Contact: okan@cs.berkeley.edu
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public
// License as published by the Free Software Foundation; either
// version 2 of the License, or (at your option) any later version.
// 
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
// 
// You should have received a copy of the GNU General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
//
//  File				:	sl.y
//  Classes				:	-
//  Description			:	This is the parser file for CShader
//
////////////////////////////////////////////////////////////////////////
#undef alloca
#include <math.h>
#include <string.h>

#include "common/algebra.h"
#include "common/os.h"
#include "sdr.h"

/////////////////////////////////////////////////////////////////////////////////////
//   First some temporary data structures used during the script parsing


// Some forward definitions
		void							sdrerror(char *);			// Forward definition for stupid yacc
		int								sdrlex(void );				// Forward definition for stupid yacc

///////////////////////////////////////////////////////////////////////
// Function				:
// Description			:
// Return Value			:
// Comments				:
// Date last edited		:
static	void	processEscapes(char *str) {
	char	*cstr;

	while((cstr = strchr(str,'\\')) != NULL) {
		switch(cstr[1]) {
		case 'n':
			cstr[0]	=	'\n';
			break;
		case 't':
			cstr[0]	=	'\t';
			break;
		case 'r':
			cstr[0]	=	'\r';
			break;
		default:
			if (((cstr[1] >= 'a') && (cstr[1] <= 'z')) || ((cstr[1] >= 'A') && (cstr[1] <= 'Z'))) {
				// Unrecognised escape sequence
				sdrerror("Unrecognised escape sequence");
			} else {
				cstr[0]	=	cstr[1];
			}
		}

		{
			int i;

			for (i=2;cstr[i] != '\0';i++) {
				cstr[i-1]	=	cstr[i];
			}

			cstr[i-1]	=	cstr[i];
		}
	}
}



		TSdrParameter	*parameters;
		TSdrParameter	*currentParameter;
		UDefaultVal		*currentDefaultItem;
		int				numArrayItemsRemaining;
		ESdrShaderType	shaderType;



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

#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
#line 98 "sdr.y"
typedef union slval {
	float			real;
	char			string[64];
	matrix			m;
	vector			v;
	TSdrParameter *parameter;
} YYSTYPE;
/* Line 190 of yacc.c.  */
#line 264 "sdr.cpp"
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 213 of yacc.c.  */
#line 276 "sdr.cpp"

#if ! defined (yyoverflow) || YYERROR_VERBOSE

# ifndef YYFREE
#  define YYFREE free
# endif
# ifndef YYMALLOC
#  define YYMALLOC malloc
# endif

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   else
#    define YYSTACK_ALLOC alloca
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning. */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
# else
#  if defined (__STDC__) || defined (__cplusplus)
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   define YYSIZE_T size_t
#  endif
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
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
	  register YYSIZE_T yyi;		\
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
#define YYFINAL  13
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   279

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  38
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  61
/* YYNRULES -- Number of rules. */
#define YYNRULES  135
/* YYNRULES -- Number of states. */
#define YYNSTATES  313

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   292

#define YYTRANSLATE(YYX) 						\
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
      35,    36,    37
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const unsigned short int yyprhs[] =
{
       0,     0,     3,    14,    15,    18,    21,    28,    30,    36,
      38,    41,    42,    44,    46,    47,    50,    53,    56,    59,
      62,    67,    71,    72,    73,    77,    78,    81,    83,    85,
      87,    89,    91,    93,    95,    97,    99,   102,   105,   107,
     112,   115,   116,   125,   131,   135,   138,   139,   142,   147,
     148,   157,   163,   167,   170,   171,   172,   177,   178,   187,
     193,   194,   199,   200,   209,   215,   219,   220,   224,   225,
     226,   231,   232,   241,   247,   248,   253,   254,   263,   269,
     291,   296,   299,   300,   309,   315,   319,   339,   342,   343,
     348,   351,   352,   356,   360,   364,   368,   372,   376,   380,
     384,   387,   393,   396,   402,   405,   411,   414,   420,   423,
     429,   432,   438,   441,   447,   450,   456,   460,   464,   468,
     469,   470,   478,   480,   482,   484,   487,   488,   491,   494,
     496,   498,   500,   502,   510,   544
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const yysigned_char yyrhs[] =
{
      39,     0,    -1,    45,    46,    80,     5,    33,    91,     6,
      33,    91,    40,    -1,    -1,    33,    40,    -1,    34,    37,
      -1,    34,    30,    37,    37,    37,    31,    -1,    37,    -1,
      30,    37,    37,    37,    31,    -1,    41,    -1,    27,    42,
      -1,    -1,     9,    -1,     8,    -1,    -1,    18,    33,    -1,
      19,    33,    -1,    21,    33,    -1,    22,    33,    -1,    20,
      33,    -1,     3,    26,    33,    47,    -1,    47,    48,    33,
      -1,    -1,    -1,    49,    52,    51,    -1,    -1,    50,    51,
      -1,    53,    -1,    57,    -1,    61,    -1,    64,    -1,    70,
      -1,    73,    -1,    76,    -1,     9,    -1,     8,    -1,     7,
       9,    -1,     7,     8,    -1,     7,    -1,    11,    35,    27,
      37,    -1,    11,    35,    -1,    -1,    11,    35,    30,    37,
      31,    27,    54,    55,    -1,    11,    35,    30,    37,    31,
      -1,    30,    56,    31,    -1,    56,    37,    -1,    -1,    17,
      35,    -1,    17,    35,    27,    34,    -1,    -1,    17,    35,
      30,    37,    31,    27,    58,    59,    -1,    17,    35,    30,
      37,    31,    -1,    30,    60,    31,    -1,    60,    34,    -1,
      -1,    -1,    12,    35,    62,    43,    -1,    -1,    12,    35,
      30,    37,    31,    27,    63,    67,    -1,    12,    35,    30,
      37,    31,    -1,    -1,    13,    35,    65,    43,    -1,    -1,
      13,    35,    30,    37,    31,    27,    66,    67,    -1,    13,
      35,    30,    37,    31,    -1,    30,    68,    31,    -1,    -1,
      68,    69,    42,    -1,    -1,    -1,    14,    35,    71,    43,
      -1,    -1,    14,    35,    30,    37,    31,    27,    72,    67,
      -1,    14,    35,    30,    37,    31,    -1,    -1,    15,    35,
      74,    43,    -1,    -1,    15,    35,    30,    37,    31,    27,
      75,    67,    -1,    15,    35,    30,    37,    31,    -1,    16,
      35,    27,    30,    37,    37,    37,    37,    37,    37,    37,
      37,    37,    37,    37,    37,    37,    37,    37,    37,    31,
      -1,    16,    35,    27,    37,    -1,    16,    35,    -1,    -1,
      16,    35,    30,    37,    31,    27,    77,    78,    -1,    16,
      35,    30,    37,    31,    -1,    30,    79,    31,    -1,    79,
      30,    37,    37,    37,    37,    37,    37,    37,    37,    37,
      37,    37,    37,    37,    37,    37,    37,    31,    -1,    79,
      37,    -1,    -1,     4,    26,    33,    81,    -1,    81,    82,
      -1,    -1,    44,    83,    33,    -1,    44,    84,    33,    -1,
      44,    85,    33,    -1,    44,    87,    33,    -1,    44,    86,
      33,    -1,    44,    88,    33,    -1,    44,    89,    33,    -1,
      44,    90,    33,    -1,    10,    35,    -1,    10,    35,    30,
      37,    31,    -1,    11,    35,    -1,    11,    35,    30,    37,
      31,    -1,    17,    35,    -1,    17,    35,    30,    37,    31,
      -1,    13,    35,    -1,    13,    35,    30,    37,    31,    -1,
      12,    35,    -1,    12,    35,    30,    37,    31,    -1,    14,
      35,    -1,    14,    35,    30,    37,    31,    -1,    15,    35,
      -1,    15,    35,    30,    37,    31,    -1,    16,    35,    -1,
      16,    35,    30,    37,    31,    -1,    91,    96,    33,    -1,
      91,    97,    33,    -1,    91,    92,    33,    -1,    -1,    -1,
      24,    35,    93,    28,    34,    29,    95,    -1,    35,    -1,
      19,    -1,    18,    -1,    98,    95,    -1,    -1,    94,    95,
      -1,    36,    26,    -1,    34,    -1,    36,    -1,    35,    -1,
      37,    -1,    28,    37,    32,    37,    32,    37,    29,    -1,
      28,    37,    32,    37,    32,    37,    32,    37,    32,    37,
      32,    37,    32,    37,    32,    37,    32,    37,    32,    37,
      32,    37,    32,    37,    32,    37,    32,    37,    32,    37,
      32,    37,    29,    -1,    28,    34,    29,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned short int yyrline[] =
{
       0,   151,   151,   163,   165,   169,   179,   193,   201,   214,
     219,   222,   230,   234,   238,   243,   249,   255,   261,   267,
     275,   282,   288,   293,   293,   306,   306,   321,   323,   325,
     327,   329,   331,   333,   338,   344,   350,   357,   364,   372,
     383,   398,   392,   409,   427,   438,   450,   454,   463,   480,
     474,   491,   509,   520,   532,   538,   536,   555,   549,   566,
     590,   588,   607,   601,   618,   640,   652,   651,   665,   671,
     669,   688,   682,   699,   723,   721,   740,   734,   751,   773,
     818,   846,   878,   872,   890,   926,   937,   984,  1010,  1014,
    1021,  1023,  1027,  1031,  1035,  1039,  1043,  1047,  1051,  1055,
    1061,  1066,  1077,  1082,  1092,  1097,  1107,  1112,  1122,  1127,
    1137,  1142,  1152,  1157,  1167,  1172,  1182,  1186,  1190,  1193,
    1199,  1197,  1210,  1214,  1218,  1224,  1229,  1234,  1241,  1248,
    1252,  1256,  1260,  1264,  1274,  1310
};
#endif

#if YYDEBUG || YYERROR_VERBOSE
/* YYTNME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals. */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "SCRL_PARAMETERS", "SCRL_VARIABLES",
  "SCRL_INIT", "SCRL_CODE", "SCRL_OUTPUT", "SCRL_VARYING", "SCRL_UNIFORM",
  "SCRL_BOOLEAN", "SCRL_FLOAT", "SCRL_COLOR", "SCRL_VECTOR", "SCRL_NORMAL",
  "SCRL_POINT", "SCRL_MATRIX", "SCRL_STRING", "SCRL_SURFACE",
  "SCRL_DISPLACEMENT", "SCRL_IMAGER", "SCRL_LIGHTSOURCE", "SCRL_VOLUME",
  "SCRL_GENERIC", "SCRL_DSO", "SCRL_DOT", "SCRL_COLON", "SCRL_EQUAL",
  "SCRL_OPEN_PARANTHESIS", "SCRL_CLOSE_PARANTHESIS",
  "SCRL_OPEN_SQR_PARANTHESIS", "SCRL_CLOSE_SQR_PARANTHESIS", "SCRL_COMMA",
  "SCRL_NL", "SCRL_TEXT_VALUE", "SCRL_IDENTIFIER_VALUE",
  "SCRL_LABEL_VALUE", "SCRL_FLOAT_VALUE", "$accept", "start",
  "slEmptySpace", "slVectorIn", "slVector", "slVectorInit", "slContainer",
  "slType", "slParameterDefinitions", "slParameters", "slParameter", "@1",
  "@2", "slRegularParameter", "slGlobalParameterContainer",
  "slFloatParameter", "@3", "slFloatArrayInitializer",
  "slFloatArrayInitializerItems", "slStringParameter", "@4",
  "slStringArrayInitializer", "slStringArrayInitializerItems",
  "slColorParameter", "@5", "@6", "slVectorParameter", "@7", "@8",
  "slVectorArrayInitializer", "slVectorArrayInitializerItems", "@9",
  "slNormalParameter", "@10", "@11", "slPointParameter", "@12", "@13",
  "slMatrixParameter", "@14", "slMatrixArrayInitializer",
  "slMatrixArrayInitializerItems", "slVariableDefinitions", "slVariables",
  "slVariable", "slBooleanVariable", "slFloatVariable", "slStringVariable",
  "slVectorVariable", "slColorVariable", "slNormalVariable",
  "slPointVariable", "slMatrixVariable", "slCode", "slDSO", "@15",
  "slOpcode", "slOperandList", "slStatement", "slLabelDefinition",
  "slOperand", 0
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
     285,   286,   287,   288,   289,   290,   291,   292
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned char yyr1[] =
{
       0,    38,    39,    40,    40,    41,    41,    41,    41,    42,
      43,    43,    44,    44,    44,    45,    45,    45,    45,    45,
      46,    47,    47,    49,    48,    50,    48,    51,    51,    51,
      51,    51,    51,    51,    52,    52,    52,    52,    52,    53,
      53,    54,    53,    53,    55,    56,    56,    57,    57,    58,
      57,    57,    59,    60,    60,    62,    61,    63,    61,    61,
      65,    64,    66,    64,    64,    67,    69,    68,    68,    71,
      70,    72,    70,    70,    74,    73,    75,    73,    73,    76,
      76,    76,    77,    76,    76,    78,    79,    79,    79,    80,
      81,    81,    82,    82,    82,    82,    82,    82,    82,    82,
      83,    83,    84,    84,    85,    85,    86,    86,    87,    87,
      88,    88,    89,    89,    90,    90,    91,    91,    91,    91,
      93,    92,    94,    94,    94,    95,    95,    96,    97,    98,
      98,    98,    98,    98,    98,    98
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,    10,     0,     2,     2,     6,     1,     5,     1,
       2,     0,     1,     1,     0,     2,     2,     2,     2,     2,
       4,     3,     0,     0,     3,     0,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     2,     1,     4,
       2,     0,     8,     5,     3,     2,     0,     2,     4,     0,
       8,     5,     3,     2,     0,     0,     4,     0,     8,     5,
       0,     4,     0,     8,     5,     3,     0,     3,     0,     0,
       4,     0,     8,     5,     0,     4,     0,     8,     5,    21,
       4,     2,     0,     8,     5,     3,    19,     2,     0,     4,
       2,     0,     3,     3,     3,     3,     3,     3,     3,     3,
       2,     5,     2,     5,     2,     5,     2,     5,     2,     5,
       2,     5,     2,     5,     2,     5,     3,     3,     3,     0,
       0,     7,     1,     1,     1,     2,     0,     2,     2,     1,
       1,     1,     1,     7,    33,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const unsigned char yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,    15,    16,
      19,    17,    18,     1,     0,     0,     0,     0,     0,    22,
       0,     0,    25,    91,   119,     0,     0,     0,    14,     0,
      21,    38,    35,    34,     0,     0,     0,     0,     0,     0,
       0,     0,    26,    27,    28,    29,    30,    31,    32,    33,
      13,    12,     0,    90,     0,   124,   123,     0,   122,     0,
       0,   126,     0,     0,    37,    36,    24,    40,    55,    60,
      69,    74,    81,    47,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     119,   120,   128,   118,     0,   129,   131,   130,   132,   127,
     126,   116,   117,     0,     0,     0,    11,     0,    11,     0,
      11,     0,    11,     0,     0,     0,     0,   100,   102,   108,
     106,   110,   112,   114,   104,    92,    93,    94,    96,    95,
      97,    98,    99,     3,     0,     0,     0,   125,    39,     0,
       0,     0,    56,     0,    61,     0,    70,     0,    75,     0,
      80,     0,    48,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     3,     2,     0,   135,     0,    43,    59,     0,
       0,     7,     9,    10,    64,    73,    78,     0,    84,    51,
       0,     0,     0,     0,     0,     0,     0,     0,     4,     0,
       0,    41,    57,     0,     0,     5,    62,    71,    76,     0,
      82,    49,   101,   103,   109,   107,   111,   113,   115,   105,
     126,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   121,     0,    46,    42,    68,    58,     0,     0,
      63,    72,    77,     0,    88,    83,    54,    50,   133,     0,
       0,    66,     8,     0,     0,     0,     0,     0,    44,    45,
      65,     0,     6,     0,     0,    85,    87,    52,    53,     0,
      67,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    79,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    86,     0,     0,     0,     0,     0,
       0,     0,   134
};

/* YYDEFGOTO[NTERM-NUM]. */
static const short int yydefgoto[] =
{
      -1,     6,   163,   172,   173,   142,    52,     7,    15,    22,
      25,    26,    27,    42,    34,    43,   212,   225,   240,    44,
     221,   237,   246,    45,   106,   213,    46,   108,   216,   227,
     241,   251,    47,   110,   217,    48,   112,   218,    49,   220,
     235,   245,    18,    28,    53,    82,    83,    84,    85,    86,
      87,    88,    89,    29,    60,   134,    61,    99,    62,    63,
     100
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -156
static const short int yypact[] =
{
      24,    26,    31,    44,    53,    54,    58,    71,  -156,  -156,
    -156,  -156,  -156,  -156,    62,    74,    56,    64,    86,  -156,
      59,    60,    -2,  -156,  -156,    61,    73,    38,    52,    -5,
    -156,    19,  -156,  -156,    38,    63,    65,    66,    67,    68,
      69,    70,  -156,  -156,  -156,  -156,  -156,  -156,  -156,  -156,
    -156,  -156,    22,  -156,    75,  -156,  -156,    72,  -156,    80,
      76,   -12,    78,    79,  -156,  -156,  -156,    -1,    83,    84,
      85,    87,    39,    41,    81,    88,    89,    90,    91,    92,
      93,    94,    97,    98,    99,   100,   101,   102,   103,   104,
    -156,  -156,  -156,  -156,    36,  -156,  -156,  -156,  -156,  -156,
     -12,  -156,  -156,    82,   105,   106,    95,   107,    95,   108,
      95,   109,    95,    10,   110,   114,   112,   111,   120,   121,
     122,   123,   124,   125,   126,  -156,  -156,  -156,  -156,  -156,
    -156,  -156,  -156,   -15,   129,   130,   128,  -156,  -156,   127,
     131,   -22,  -156,   132,  -156,   133,  -156,   134,  -156,   135,
    -156,   136,  -156,   137,   138,   139,   140,   141,   142,   143,
     144,   145,   150,  -156,   151,  -156,   147,   113,   146,   149,
      11,  -156,  -156,  -156,   160,   161,   162,   153,   164,   165,
     163,   166,   167,   168,   169,   170,   171,   172,  -156,   175,
     173,  -156,  -156,   156,   158,  -156,  -156,  -156,  -156,   159,
    -156,  -156,  -156,  -156,  -156,  -156,  -156,  -156,  -156,  -156,
     -12,   174,   176,   177,   178,   179,   177,   177,   177,   180,
     182,   183,  -156,    43,  -156,  -156,  -156,  -156,   187,   184,
    -156,  -156,  -156,   185,  -156,  -156,  -156,  -156,  -156,   186,
      25,   188,  -156,   189,   190,   -20,    45,   192,  -156,  -156,
    -156,   -22,  -156,   191,   193,  -156,  -156,  -156,  -156,   194,
    -156,   195,   196,   197,   198,   199,   200,   201,   202,   208,
     204,   205,   206,   207,   209,   213,   210,   211,   212,   214,
     215,   218,   216,   217,   219,   220,   221,   223,   203,   222,
     224,  -156,   225,   228,   226,   227,   229,   233,   230,   231,
     232,   238,   240,   235,  -156,   241,   237,   243,   239,   245,
     242,   181,  -156
};

/* YYPGOTO[NTERM-NUM].  */
static const short int yypgoto[] =
{
    -156,  -156,   -67,  -156,  -155,   -45,  -156,  -156,  -156,  -156,
    -156,  -156,  -156,   244,  -156,  -156,  -156,  -156,  -156,  -156,
    -156,  -156,  -156,  -156,  -156,  -156,  -156,  -156,  -156,  -133,
    -156,  -156,  -156,  -156,  -156,  -156,  -156,  -156,  -156,  -156,
    -156,  -156,  -156,  -156,  -156,  -156,  -156,  -156,  -156,  -156,
    -156,  -156,  -156,     7,  -156,  -156,  -156,  -100,  -156,  -156,
    -156
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -90
static const short int yytable[] =
{
     137,    54,   -20,    55,    56,   -23,   -23,   -23,   169,    57,
     254,   255,   170,    55,    56,   171,    94,   256,   162,    57,
      58,    59,    95,    96,    97,    98,   103,    64,    65,   104,
      58,    59,    74,    75,    76,    77,    78,    79,    80,    81,
     149,   194,     1,     2,     3,     4,     5,   150,   195,    35,
      36,    37,    38,    39,    40,    41,   248,   -89,    13,     8,
      50,    51,   249,   144,     9,   146,   113,   148,   115,   114,
     135,   116,   238,   136,    14,   239,   257,    10,    17,   258,
      31,    32,    33,   230,   231,   232,    11,    12,    16,    19,
      20,    21,    23,    24,    30,   188,   260,   133,    67,     0,
      68,    69,    70,    71,    72,    73,    92,    91,    90,    93,
     222,   101,   102,   105,   107,   109,   117,   111,     0,   138,
       0,     0,   141,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,     0,     0,
     191,   154,   139,   140,   143,   145,   147,   151,   152,   153,
     155,   156,   157,   158,   159,   160,   161,   164,   167,   165,
     166,     0,   168,   174,   175,   176,     0,   178,   179,     0,
       0,     0,   177,   192,     0,   180,   181,   182,   183,   184,
     185,   186,   187,   162,   190,   189,   193,   196,   197,   198,
     199,   200,   201,   214,   202,   215,   219,   203,   204,   205,
     206,   207,   208,   209,   210,   211,   224,   226,     0,     0,
     312,   223,   234,   236,     0,   228,   229,   233,   242,   250,
     252,   243,   244,   247,   259,     0,     0,   253,   261,   266,
     262,   263,   264,   265,   291,   267,   268,   269,   270,   271,
     272,   273,   274,   275,   276,   278,   277,   279,   280,   281,
     284,   282,   283,   285,   286,   290,   287,   288,   289,   292,
     295,   293,   294,   296,   297,   299,   298,   300,   301,   302,
     303,   304,   305,   306,   307,   308,   309,   310,    66,   311
};

static const short int yycheck[] =
{
     100,     6,     4,    18,    19,     7,     8,     9,    30,    24,
      30,    31,    34,    18,    19,    37,    28,    37,    33,    24,
      35,    36,    34,    35,    36,    37,    27,     8,     9,    30,
      35,    36,    10,    11,    12,    13,    14,    15,    16,    17,
      30,    30,    18,    19,    20,    21,    22,    37,    37,    11,
      12,    13,    14,    15,    16,    17,    31,     5,     0,    33,
       8,     9,    37,   108,    33,   110,    27,   112,    27,    30,
      34,    30,    29,    37,     3,    32,    31,    33,     4,    34,
       7,     8,     9,   216,   217,   218,    33,    33,    26,    33,
      26,     5,    33,    33,    33,   162,   251,    90,    35,    -1,
      35,    35,    35,    35,    35,    35,    26,    35,    33,    33,
     210,    33,    33,    30,    30,    30,    35,    30,    -1,    37,
      -1,    -1,    27,    35,    35,    35,    35,    35,    35,    35,
      33,    33,    33,    33,    33,    33,    33,    33,    -1,    -1,
      27,    30,    37,    37,    37,    37,    37,    37,    34,    37,
      30,    30,    30,    30,    30,    30,    30,    28,    31,    29,
      32,    -1,    31,    31,    31,    31,    -1,    31,    31,    -1,
      -1,    -1,    37,    27,    -1,    37,    37,    37,    37,    37,
      37,    37,    37,    33,    37,    34,    37,    27,    27,    27,
      37,    27,    27,    37,    31,    37,    37,    31,    31,    31,
      31,    31,    31,    31,    29,    32,    30,    30,    -1,    -1,
      29,    37,    30,    30,    -1,    37,    37,    37,    31,    31,
      31,    37,    37,    37,    32,    -1,    -1,    37,    37,    32,
      37,    37,    37,    37,    31,    37,    37,    37,    37,    37,
      32,    37,    37,    37,    37,    32,    37,    37,    37,    37,
      32,    37,    37,    37,    37,    32,    37,    37,    37,    37,
      32,    37,    37,    37,    37,    32,    37,    37,    37,    37,
      32,    31,    37,    32,    37,    32,    37,    32,    34,    37
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,    18,    19,    20,    21,    22,    39,    45,    33,    33,
      33,    33,    33,     0,     3,    46,    26,     4,    80,    33,
      26,     5,    47,    33,    33,    48,    49,    50,    81,    91,
      33,     7,     8,     9,    52,    11,    12,    13,    14,    15,
      16,    17,    51,    53,    57,    61,    64,    70,    73,    76,
       8,     9,    44,    82,     6,    18,    19,    24,    35,    36,
      92,    94,    96,    97,     8,     9,    51,    35,    35,    35,
      35,    35,    35,    35,    10,    11,    12,    13,    14,    15,
      16,    17,    83,    84,    85,    86,    87,    88,    89,    90,
      33,    35,    26,    33,    28,    34,    35,    36,    37,    95,
      98,    33,    33,    27,    30,    30,    62,    30,    65,    30,
      71,    30,    74,    27,    30,    27,    30,    35,    35,    35,
      35,    35,    35,    35,    35,    33,    33,    33,    33,    33,
      33,    33,    33,    91,    93,    34,    37,    95,    37,    37,
      37,    27,    43,    37,    43,    37,    43,    37,    43,    30,
      37,    37,    34,    37,    30,    30,    30,    30,    30,    30,
      30,    30,    33,    40,    28,    29,    32,    31,    31,    30,
      34,    37,    41,    42,    31,    31,    31,    37,    31,    31,
      37,    37,    37,    37,    37,    37,    37,    37,    40,    34,
      37,    27,    27,    37,    30,    37,    27,    27,    27,    37,
      27,    27,    31,    31,    31,    31,    31,    31,    31,    31,
      29,    32,    54,    63,    37,    37,    66,    72,    75,    37,
      77,    58,    95,    37,    30,    55,    30,    67,    37,    37,
      67,    67,    67,    37,    30,    78,    30,    59,    29,    32,
      56,    68,    31,    37,    37,    79,    60,    37,    31,    37,
      31,    69,    31,    37,    30,    31,    37,    31,    34,    32,
      42,    37,    37,    37,    37,    37,    32,    37,    37,    37,
      37,    37,    32,    37,    37,    37,    37,    37,    32,    37,
      37,    37,    37,    37,    32,    37,    37,    37,    37,    37,
      32,    31,    37,    37,    37,    32,    37,    37,    37,    32,
      37,    37,    37,    32,    31,    37,    32,    37,    32,    37,
      32,    37,    29
};

#if ! defined (YYSIZE_T) && defined (__SIZE_TYPE__)
# define YYSIZE_T __SIZE_TYPE__
#endif
#if ! defined (YYSIZE_T) && defined (size_t)
# define YYSIZE_T size_t
#endif
#if ! defined (YYSIZE_T)
# if defined (__STDC__) || defined (__cplusplus)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# endif
#endif
#if ! defined (YYSIZE_T)
# define YYSIZE_T unsigned int
#endif

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
    { 								\
      yyerror ("syntax error: cannot back up");\
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
      yysymprint (stderr, 					\
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
  unsigned int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %u), ",
             yyrule - 1, yylno);
  /* Print the symbols being reduced, and their result.  */
  for (yyi = yyprhs[yyrule]; 0 <= yyrhs[yyi]; yyi++)
    YYFPRINTF (stderr, "%s ", yytname [yyrhs[yyi]]);
  YYFPRINTF (stderr, "-> %s\n", yytname [yyr1[yyrule]]);
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
   SIZE_MAX < YYSTACK_BYTES (YYMAXDEPTH)
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
  register const char *yys = yystr;

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
  register char *yyd = yydest;
  register const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

#endif /* !YYERROR_VERBOSE */



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

#endif
#endif
{
  
  register int yystate;
  register int yyn;
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
  register short int *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  register YYSTYPE *yyvsp;



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


  yyvsp[0] = yylval;

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
	yyoverflow ("parser stack overflow",
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyoverflowlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyoverflowlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	short int *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyoverflowlab;
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
        case 5:
#line 171 "sdr.y"
    {
				currentParameter->space			=	strdup((yyvsp[-1].string));
				currentDefaultItem->vector		=	new float[3];
				currentDefaultItem->vector[0]	=	(yyvsp[0].real);
				currentDefaultItem->vector[1]	=	(yyvsp[0].real);
				currentDefaultItem->vector[2]	=	(yyvsp[0].real);
			;}
    break;

  case 6:
#line 185 "sdr.y"
    {
				currentParameter->space			=	strdup((yyvsp[-5].string));
				currentDefaultItem->vector		=	new float[3];
				currentDefaultItem->vector[0]	=	(yyvsp[-3].real);
				currentDefaultItem->vector[1]	=	(yyvsp[-2].real);
				currentDefaultItem->vector[2]	=	(yyvsp[-1].real);
			;}
    break;

  case 7:
#line 194 "sdr.y"
    {
				currentDefaultItem->vector		=	new float[3];
				currentDefaultItem->vector[0]	=	(yyvsp[0].real);
				currentDefaultItem->vector[1]	=	(yyvsp[0].real);
				currentDefaultItem->vector[2]	=	(yyvsp[0].real);
			;}
    break;

  case 8:
#line 206 "sdr.y"
    {
				currentDefaultItem->vector		=	new float[3];
				currentDefaultItem->vector[0]	=	(yyvsp[-3].real);
				currentDefaultItem->vector[1]	=	(yyvsp[-2].real);
				currentDefaultItem->vector[2]	=	(yyvsp[-1].real);
			;}
    break;

  case 9:
#line 215 "sdr.y"
    {
			;}
    break;

  case 11:
#line 222 "sdr.y"
    {
					currentParameter->defaultValue.vector		=	new float[3];
					currentParameter->defaultValue.vector[0]	=	0;
					currentParameter->defaultValue.vector[1]	=	0;
					currentParameter->defaultValue.vector[2]	=	0;
			;}
    break;

  case 12:
#line 231 "sdr.y"
    {
				;}
    break;

  case 13:
#line 235 "sdr.y"
    {
				;}
    break;

  case 14:
#line 238 "sdr.y"
    {
				;}
    break;

  case 15:
#line 245 "sdr.y"
    {
			shaderType	=	SHADER_SURFACE;
		;}
    break;

  case 16:
#line 251 "sdr.y"
    {
			shaderType	=	SHADER_DISPLACEMENT;
		;}
    break;

  case 17:
#line 257 "sdr.y"
    {
			shaderType	=	SHADER_LIGHT;
		;}
    break;

  case 18:
#line 263 "sdr.y"
    {
			shaderType	=	SHADER_VOLUME;
		;}
    break;

  case 19:
#line 269 "sdr.y"
    {
			shaderType	=	SHADER_IMAGER;
		;}
    break;

  case 21:
#line 285 "sdr.y"
    {
		;}
    break;

  case 22:
#line 288 "sdr.y"
    {
		;}
    break;

  case 23:
#line 293 "sdr.y"
    {
			currentParameter						=	new TSdrParameter;
			currentParameter->space					=	NULL;
			currentParameter->numItems				=	1;
			currentParameter->defaultValue.string	=	NULL;
		;}
    break;

  case 24:
#line 301 "sdr.y"
    {
			currentParameter->next	=	parameters;
			parameters				=	currentParameter;
		;}
    break;

  case 25:
#line 306 "sdr.y"
    {
			currentParameter						=	new TSdrParameter;
			currentParameter->space					=	NULL;
			currentParameter->numItems				=	1;
			currentParameter->defaultValue.string	=	NULL;
			currentParameter->container				=	CONTAINER_UNIFORM;
		;}
    break;

  case 26:
#line 314 "sdr.y"
    {
			currentParameter->next	=	parameters;
			parameters				=	currentParameter;
		;}
    break;

  case 34:
#line 339 "sdr.y"
    {
			currentParameter->container	=	CONTAINER_UNIFORM;
			currentParameter->writable	=	FALSE;
		;}
    break;

  case 35:
#line 345 "sdr.y"
    {
			currentParameter->container	=	CONTAINER_VARYING;
			currentParameter->writable	=	FALSE;
		;}
    break;

  case 36:
#line 352 "sdr.y"
    {
			currentParameter->container	=	CONTAINER_UNIFORM;
			currentParameter->writable	=	TRUE;
		;}
    break;

  case 37:
#line 359 "sdr.y"
    {
			currentParameter->container	=	CONTAINER_VARYING;
			currentParameter->writable	=	TRUE;
		;}
    break;

  case 38:
#line 365 "sdr.y"
    {
			currentParameter->container	=	CONTAINER_UNIFORM;
			currentParameter->writable	=	TRUE;
		;}
    break;

  case 39:
#line 376 "sdr.y"
    {
			currentParameter->type					=	TYPE_FLOAT;
			currentParameter->name					=	strdup((yyvsp[-2].string));
			currentParameter->defaultValue.scalar	=	(yyvsp[0].real);
			currentParameter->numItems				=	1;
		;}
    break;

  case 40:
#line 385 "sdr.y"
    {
			currentParameter->type					=	TYPE_FLOAT;
			currentParameter->name					=	strdup((yyvsp[0].string));
			currentParameter->defaultValue.scalar	=	0;
			currentParameter->numItems				=	1;
		;}
    break;

  case 41:
#line 398 "sdr.y"
    {
			currentParameter->type					=	TYPE_FLOAT;
			currentParameter->name					=	strdup((yyvsp[-4].string));
			currentParameter->defaultValue.array	=	new UDefaultVal[(int) (yyvsp[-2].real)];
			currentParameter->numItems				=	(int) (yyvsp[-2].real);
			
			currentDefaultItem = currentParameter->defaultValue.array;
			numArrayItemsRemaining = currentParameter->numItems;
		;}
    break;

  case 43:
#line 414 "sdr.y"
    {
			currentParameter->type					=	TYPE_FLOAT;
			currentParameter->name					=	strdup((yyvsp[-3].string));
			currentParameter->defaultValue.array	=	new UDefaultVal[(int) (yyvsp[-1].real)];
			currentParameter->numItems				=	(int) (yyvsp[-1].real);
			
			currentDefaultItem = currentParameter->defaultValue.array;
			for(int i=0;i<currentParameter->numItems;i++)
				currentDefaultItem[i].scalar = 0;
		;}
    break;

  case 44:
#line 430 "sdr.y"
    {
			if(numArrayItemsRemaining){
				sdrerror("wrong number of items in array initializer\n");
			}
		;}
    break;

  case 45:
#line 440 "sdr.y"
    {
			if(numArrayItemsRemaining){
				currentDefaultItem->scalar = (yyvsp[0].real);
				currentDefaultItem++;
				numArrayItemsRemaining--;
			}
			else{
				sdrerror("wrong number of items in array initializer\n");
			}
		;}
    break;

  case 47:
#line 456 "sdr.y"
    {
			currentParameter->type					=	TYPE_STRING;
			currentParameter->name					=	strdup((yyvsp[0].string));
			currentParameter->defaultValue.array	=	NULL;
			currentParameter->numItems				=	1;
		;}
    break;

  case 48:
#line 467 "sdr.y"
    {
			currentParameter->type					=	TYPE_STRING;
			currentParameter->name					=	strdup((yyvsp[-2].string));
			currentParameter->defaultValue.string	=	strdup((yyvsp[0].string));
			currentParameter->numItems				=	1;
		;}
    break;

  case 49:
#line 480 "sdr.y"
    {
			currentParameter->type					=	TYPE_STRING;
			currentParameter->name					=	strdup((yyvsp[-4].string));
			currentParameter->defaultValue.array	=	new UDefaultVal[(int) (yyvsp[-2].real)];
			currentParameter->numItems				=	(int) (yyvsp[-2].real);
			
			currentDefaultItem = currentParameter->defaultValue.array;
			numArrayItemsRemaining = currentParameter->numItems;
		;}
    break;

  case 51:
#line 496 "sdr.y"
    {
			currentParameter->type					=	TYPE_STRING;
			currentParameter->name					=	strdup((yyvsp[-3].string));
			currentParameter->defaultValue.array	=	new UDefaultVal[(int) (yyvsp[-1].real)];
			currentParameter->numItems				=	(int) (yyvsp[-1].real);
			
			currentDefaultItem = currentParameter->defaultValue.array;
			for(int i=0;i<currentParameter->numItems;i++)
				currentDefaultItem[i].string = NULL;
		;}
    break;

  case 52:
#line 512 "sdr.y"
    {
			if(numArrayItemsRemaining){
				sdrerror("wrong number of items in array initializer\n");
			}
		;}
    break;

  case 53:
#line 522 "sdr.y"
    {
			if(numArrayItemsRemaining){
				currentDefaultItem->string = strdup((yyvsp[0].string));
				currentDefaultItem++;
				numArrayItemsRemaining--;
			}
			else{
				sdrerror("wrong number of items in array initializer\n");
			}
		;}
    break;

  case 55:
#line 538 "sdr.y"
    {
			currentParameter->type					=	TYPE_COLOR;
			currentParameter->name					=	strdup((yyvsp[0].string));
			currentParameter->numItems				=	1;
			
			currentDefaultItem = &currentParameter->defaultValue;
		;}
    break;

  case 56:
#line 546 "sdr.y"
    {
		;}
    break;

  case 57:
#line 555 "sdr.y"
    {
			currentParameter->type					=	TYPE_COLOR;
			currentParameter->name					=	strdup((yyvsp[-4].string));
			currentParameter->defaultValue.array	=	new UDefaultVal[(int) (yyvsp[-2].real)];
			currentParameter->numItems				=	(int) (yyvsp[-2].real);
			
			currentDefaultItem = currentParameter->defaultValue.array;
			numArrayItemsRemaining = currentParameter->numItems;
		;}
    break;

  case 59:
#line 571 "sdr.y"
    {
			currentParameter->type					=	TYPE_COLOR;
			currentParameter->name					=	strdup((yyvsp[-3].string));
			currentParameter->defaultValue.array	=	new UDefaultVal[(int) (yyvsp[-1].real)];
			currentParameter->numItems				=	(int) (yyvsp[-1].real);
			
			currentDefaultItem = currentParameter->defaultValue.array;
			for(int i=0;i<currentParameter->numItems;i++){
				currentDefaultItem[i].vector = new float[3];
				currentDefaultItem[i].vector[0] = 0;
				currentDefaultItem[i].vector[1] = 0;
				currentDefaultItem[i].vector[2] = 0;
			}
		;}
    break;

  case 60:
#line 590 "sdr.y"
    {
			currentParameter->type					=	TYPE_VECTOR;
			currentParameter->name					=	strdup((yyvsp[0].string));
			currentParameter->numItems				=	1;
			
			currentDefaultItem = &currentParameter->defaultValue;
		;}
    break;

  case 61:
#line 598 "sdr.y"
    {
		;}
    break;

  case 62:
#line 607 "sdr.y"
    {
			currentParameter->type					=	TYPE_VECTOR;
			currentParameter->name					=	strdup((yyvsp[-4].string));
			currentParameter->defaultValue.array	=	new UDefaultVal[(int) (yyvsp[-2].real)];
			currentParameter->numItems				=	(int) (yyvsp[-2].real);
			
			currentDefaultItem = currentParameter->defaultValue.array;
			numArrayItemsRemaining = currentParameter->numItems;
		;}
    break;

  case 64:
#line 623 "sdr.y"
    {
			currentParameter->type					=	TYPE_VECTOR;
			currentParameter->name					=	strdup((yyvsp[-3].string));
			currentParameter->defaultValue.array	=	new UDefaultVal[(int) (yyvsp[-1].real)];
			currentParameter->numItems				=	(int) (yyvsp[-1].real);
			
			currentDefaultItem = currentParameter->defaultValue.array;
			for(int i=0;i<currentParameter->numItems;i++){
				currentDefaultItem[i].vector = new float[3];
				currentDefaultItem[i].vector[0] = 0;
				currentDefaultItem[i].vector[1] = 0;
				currentDefaultItem[i].vector[2] = 0;
			}
		;}
    break;

  case 65:
#line 643 "sdr.y"
    {
			if(numArrayItemsRemaining){
				sdrerror("wrong number of items in array initializer\n");
		}
		;}
    break;

  case 66:
#line 652 "sdr.y"
    {
			if(numArrayItemsRemaining){
				currentDefaultItem->vector = new float[3];
			}
			else{
				sdrerror("wrong number of items in array initializer\n");
			}
		;}
    break;

  case 67:
#line 661 "sdr.y"
    {
			currentDefaultItem++;
			numArrayItemsRemaining--;
		;}
    break;

  case 69:
#line 671 "sdr.y"
    {
			currentParameter->type					=	TYPE_NORMAL;
			currentParameter->name					=	strdup((yyvsp[0].string));
			currentParameter->numItems				=	1;
			
			currentDefaultItem = &currentParameter->defaultValue;
		;}
    break;

  case 70:
#line 679 "sdr.y"
    {
		;}
    break;

  case 71:
#line 688 "sdr.y"
    {
			currentParameter->type					=	TYPE_NORMAL;
			currentParameter->name					=	strdup((yyvsp[-4].string));
			currentParameter->defaultValue.array	=	new UDefaultVal[(int) (yyvsp[-2].real)];
			currentParameter->numItems				=	(int) (yyvsp[-2].real);
			
			currentDefaultItem = currentParameter->defaultValue.array;
			numArrayItemsRemaining = currentParameter->numItems;
		;}
    break;

  case 73:
#line 704 "sdr.y"
    {
			currentParameter->type					=	TYPE_NORMAL;
			currentParameter->name					=	strdup((yyvsp[-3].string));
			currentParameter->defaultValue.array	=	new UDefaultVal[(int) (yyvsp[-1].real)];
			currentParameter->numItems				=	(int) (yyvsp[-1].real);
			
			currentDefaultItem = currentParameter->defaultValue.array;
			for(int i=0;i<currentParameter->numItems;i++){
				currentDefaultItem[i].vector = new float[3];
				currentDefaultItem[i].vector[0] = 0;
				currentDefaultItem[i].vector[1] = 0;
				currentDefaultItem[i].vector[3] = 0;
			}
		;}
    break;

  case 74:
#line 723 "sdr.y"
    {
			currentParameter->type					=	TYPE_POINT;
			currentParameter->name					=	strdup((yyvsp[0].string));
			currentParameter->numItems				=	1;
			
			currentDefaultItem = &currentParameter->defaultValue;
		;}
    break;

  case 75:
#line 731 "sdr.y"
    {
		;}
    break;

  case 76:
#line 740 "sdr.y"
    {
			currentParameter->type					=	TYPE_POINT;
			currentParameter->name					=	strdup((yyvsp[-4].string));
			currentParameter->defaultValue.array	=	new UDefaultVal[(int) (yyvsp[-2].real)];
			currentParameter->numItems				=	(int) (yyvsp[-2].real);
			
			currentDefaultItem = currentParameter->defaultValue.array;
			numArrayItemsRemaining = currentParameter->numItems;
		;}
    break;

  case 78:
#line 756 "sdr.y"
    {
			currentParameter->type					=	TYPE_POINT;
			currentParameter->name					=	strdup((yyvsp[-3].string));
			currentParameter->defaultValue.array	=	new UDefaultVal[(int) (yyvsp[-1].real)];
			currentParameter->numItems				=	(int) (yyvsp[-1].real);
			
			currentDefaultItem = currentParameter->defaultValue.array;
			for(int i=0;i<currentParameter->numItems;i++){
				currentDefaultItem[i].vector = new float[3];
				currentDefaultItem[i].vector[0] = 0;
				currentDefaultItem[i].vector[1] = 0;
				currentDefaultItem[i].vector[2] = 0;
			}
		;}
    break;

  case 79:
#line 794 "sdr.y"
    {
			currentParameter->container					=	CONTAINER_UNIFORM;
			currentParameter->type						=	TYPE_MATRIX;
			currentParameter->name						=	strdup((yyvsp[-19].string));
			currentParameter->defaultValue.matrix		=	new float[16];
			currentParameter->defaultValue.matrix[0]	=	(yyvsp[-16].real);
			currentParameter->defaultValue.matrix[1]	=	(yyvsp[-15].real);
			currentParameter->defaultValue.matrix[2]	=	(yyvsp[-14].real);
			currentParameter->defaultValue.matrix[3]	=	(yyvsp[-13].real);
			currentParameter->defaultValue.matrix[4]	=	(yyvsp[-12].real);
			currentParameter->defaultValue.matrix[5]	=	(yyvsp[-11].real);
			currentParameter->defaultValue.matrix[6]	=	(yyvsp[-10].real);
			currentParameter->defaultValue.matrix[7]	=	(yyvsp[-9].real);
			currentParameter->defaultValue.matrix[8]	=	(yyvsp[-8].real);
			currentParameter->defaultValue.matrix[9]	=	(yyvsp[-7].real);
			currentParameter->defaultValue.matrix[10]	=	(yyvsp[-6].real);
			currentParameter->defaultValue.matrix[11]	=	(yyvsp[-5].real);
			currentParameter->defaultValue.matrix[12]	=	(yyvsp[-4].real);
			currentParameter->defaultValue.matrix[13]	=	(yyvsp[-3].real);
			currentParameter->defaultValue.matrix[14]	=	(yyvsp[-2].real);
			currentParameter->defaultValue.matrix[15]	=	(yyvsp[-1].real);
			currentParameter->numItems					=	1;
		;}
    break;

  case 80:
#line 822 "sdr.y"
    {
			currentParameter->container					=	CONTAINER_UNIFORM;
			currentParameter->type						=	TYPE_MATRIX;
			currentParameter->name						=	strdup((yyvsp[-2].string));
			currentParameter->defaultValue.matrix		=	new float[16];
			currentParameter->defaultValue.matrix[0]	=	(yyvsp[0].real);
			currentParameter->defaultValue.matrix[1]	=	0;
			currentParameter->defaultValue.matrix[2]	=	0;
			currentParameter->defaultValue.matrix[3]	=	0;
			currentParameter->defaultValue.matrix[4]	=	0;
			currentParameter->defaultValue.matrix[5]	=	(yyvsp[0].real);
			currentParameter->defaultValue.matrix[6]	=	0;
			currentParameter->defaultValue.matrix[7]	=	0;
			currentParameter->defaultValue.matrix[8]	=	0;
			currentParameter->defaultValue.matrix[9]	=	0;
			currentParameter->defaultValue.matrix[10]	=	(yyvsp[0].real);
			currentParameter->defaultValue.matrix[11]	=	0;
			currentParameter->defaultValue.matrix[12]	=	0;
			currentParameter->defaultValue.matrix[13]	=	0;
			currentParameter->defaultValue.matrix[14]	=	0;
			currentParameter->defaultValue.matrix[15]	=	(yyvsp[0].real);
			currentParameter->numItems					=	1;
		;}
    break;

  case 81:
#line 848 "sdr.y"
    {
			currentParameter->container					=	CONTAINER_UNIFORM;
			currentParameter->type						=	TYPE_MATRIX;
			currentParameter->name						=	strdup((yyvsp[0].string));
			currentParameter->defaultValue.matrix		=	new float[16];
			currentParameter->defaultValue.matrix[0]	=	1;
			currentParameter->defaultValue.matrix[1]	=	0;
			currentParameter->defaultValue.matrix[2]	=	0;
			currentParameter->defaultValue.matrix[3]	=	0;
			currentParameter->defaultValue.matrix[4]	=	0;
			currentParameter->defaultValue.matrix[5]	=	1;
			currentParameter->defaultValue.matrix[6]	=	0;
			currentParameter->defaultValue.matrix[7]	=	0;
			currentParameter->defaultValue.matrix[8]	=	0;
			currentParameter->defaultValue.matrix[9]	=	0;
			currentParameter->defaultValue.matrix[10]	=	1;
			currentParameter->defaultValue.matrix[11]	=	0;
			currentParameter->defaultValue.matrix[12]	=	0;
			currentParameter->defaultValue.matrix[13]	=	0;
			currentParameter->defaultValue.matrix[14]	=	0;
			currentParameter->defaultValue.matrix[15]	=	1;
			currentParameter->numItems					=	1;
		;}
    break;

  case 82:
#line 878 "sdr.y"
    {
			currentParameter->container					=	CONTAINER_UNIFORM;
			currentParameter->type						=	TYPE_MATRIX;
			currentParameter->name						=	strdup((yyvsp[-4].string));
			currentParameter->defaultValue.array		=	new UDefaultVal[(int) (yyvsp[-2].real)];
			currentParameter->numItems					=	(int) (yyvsp[-2].real);
			
			currentDefaultItem = currentParameter->defaultValue.array;
			numArrayItemsRemaining = currentParameter->numItems;
		;}
    break;

  case 84:
#line 895 "sdr.y"
    {
			currentParameter->container					=	CONTAINER_UNIFORM;
			currentParameter->type						=	TYPE_MATRIX;
			currentParameter->name						=	strdup((yyvsp[-3].string));
			currentParameter->defaultValue.array		=	new UDefaultVal[(int) (yyvsp[-1].real)];
			currentParameter->numItems					=	(int) (yyvsp[-1].real);
			
			currentDefaultItem = currentParameter->defaultValue.array;
			for(int i=0;i<currentParameter->numItems;i++){
				currentDefaultItem[i].matrix = new float[16];
				currentDefaultItem[i].matrix[0] = 1;
				currentDefaultItem[i].matrix[1] = 0;
				currentDefaultItem[i].matrix[2] = 0;
				currentDefaultItem[i].matrix[3] = 0;
				currentDefaultItem[i].matrix[4] = 0;
				currentDefaultItem[i].matrix[5] = 1;
				currentDefaultItem[i].matrix[6] = 0;
				currentDefaultItem[i].matrix[7] = 0;
				currentDefaultItem[i].matrix[8] = 0;
				currentDefaultItem[i].matrix[9] = 0;
				currentDefaultItem[i].matrix[10] = 1;
				currentDefaultItem[i].matrix[11] = 0;
				currentDefaultItem[i].matrix[12] = 0;
				currentDefaultItem[i].matrix[13] = 0;
				currentDefaultItem[i].matrix[14] = 0;
				currentDefaultItem[i].matrix[15] = 1;
			}
		;}
    break;

  case 85:
#line 929 "sdr.y"
    {
			if(numArrayItemsRemaining){
				sdrerror("wrong number of items in array initializer\n");
			}
		;}
    break;

  case 86:
#line 956 "sdr.y"
    {
			if(numArrayItemsRemaining){
				currentDefaultItem->matrix = new float[16];
				currentDefaultItem->matrix[0] = (yyvsp[-16].real);
				currentDefaultItem->matrix[1] = (yyvsp[-15].real);
				currentDefaultItem->matrix[2] = (yyvsp[-14].real);
				currentDefaultItem->matrix[3] = (yyvsp[-13].real);
				currentDefaultItem->matrix[4] = (yyvsp[-12].real);
				currentDefaultItem->matrix[5] = (yyvsp[-11].real);
				currentDefaultItem->matrix[6] = (yyvsp[-10].real);
				currentDefaultItem->matrix[7] = (yyvsp[-9].real);
				currentDefaultItem->matrix[8] = (yyvsp[-8].real);
				currentDefaultItem->matrix[9] = (yyvsp[-7].real);
				currentDefaultItem->matrix[10] = (yyvsp[-6].real);
				currentDefaultItem->matrix[11] = (yyvsp[-5].real);
				currentDefaultItem->matrix[12] = (yyvsp[-4].real);
				currentDefaultItem->matrix[13] = (yyvsp[-3].real);
				currentDefaultItem->matrix[14] = (yyvsp[-2].real);
				currentDefaultItem->matrix[15] = (yyvsp[-1].real);
				
				currentDefaultItem++;
				numArrayItemsRemaining--;
			}
			else{
				sdrerror("wrong number of items in array initializer\n");
			}
		;}
    break;

  case 87:
#line 986 "sdr.y"
    {
			if(numArrayItemsRemaining){
				currentDefaultItem->matrix = new float[16];
				currentDefaultItem->matrix[0] = (yyvsp[0].real);
				currentDefaultItem->matrix[1] = 0;
				currentDefaultItem->matrix[2] = 0;
				currentDefaultItem->matrix[3] = 0;
				currentDefaultItem->matrix[4] = 0;
				currentDefaultItem->matrix[5] = (yyvsp[0].real);
				currentDefaultItem->matrix[6] = 0;
				currentDefaultItem->matrix[7] = 0;
				currentDefaultItem->matrix[8] = 0;
				currentDefaultItem->matrix[9] = 0;
				currentDefaultItem->matrix[10] = (yyvsp[0].real);
				currentDefaultItem->matrix[11] = 0;
				currentDefaultItem->matrix[12] = 0;
				currentDefaultItem->matrix[13] = 0;
				currentDefaultItem->matrix[14] = 0;
				currentDefaultItem->matrix[15] = 1;
				
				currentDefaultItem++;
				numArrayItemsRemaining--;
			}
		;}
    break;

  case 100:
#line 1063 "sdr.y"
    {
		;}
    break;

  case 101:
#line 1071 "sdr.y"
    {
		;}
    break;

  case 102:
#line 1079 "sdr.y"
    {
		;}
    break;

  case 103:
#line 1087 "sdr.y"
    {
		;}
    break;

  case 104:
#line 1094 "sdr.y"
    {
		;}
    break;

  case 105:
#line 1102 "sdr.y"
    {
		;}
    break;

  case 106:
#line 1109 "sdr.y"
    {
		;}
    break;

  case 107:
#line 1117 "sdr.y"
    {
		;}
    break;

  case 108:
#line 1124 "sdr.y"
    {
		;}
    break;

  case 109:
#line 1132 "sdr.y"
    {
		;}
    break;

  case 110:
#line 1139 "sdr.y"
    {
		;}
    break;

  case 111:
#line 1147 "sdr.y"
    {
		;}
    break;

  case 112:
#line 1154 "sdr.y"
    {
		;}
    break;

  case 113:
#line 1162 "sdr.y"
    {
		;}
    break;

  case 114:
#line 1169 "sdr.y"
    {
		;}
    break;

  case 115:
#line 1177 "sdr.y"
    {
		;}
    break;

  case 120:
#line 1199 "sdr.y"
    {
		;}
    break;

  case 121:
#line 1205 "sdr.y"
    {
		;}
    break;

  case 122:
#line 1211 "sdr.y"
    {
		;}
    break;

  case 123:
#line 1215 "sdr.y"
    {
		;}
    break;

  case 124:
#line 1219 "sdr.y"
    {
		;}
    break;

  case 125:
#line 1226 "sdr.y"
    {
		;}
    break;

  case 126:
#line 1229 "sdr.y"
    {
		;}
    break;

  case 127:
#line 1236 "sdr.y"
    {
		;}
    break;

  case 128:
#line 1243 "sdr.y"
    {
		;}
    break;

  case 129:
#line 1249 "sdr.y"
    {
		;}
    break;

  case 130:
#line 1253 "sdr.y"
    {
		;}
    break;

  case 131:
#line 1257 "sdr.y"
    {
		;}
    break;

  case 132:
#line 1261 "sdr.y"
    {
		;}
    break;

  case 133:
#line 1271 "sdr.y"
    {
		;}
    break;

  case 134:
#line 1307 "sdr.y"
    {
		;}
    break;

  case 135:
#line 1313 "sdr.y"
    {
		;}
    break;


    }

/* Line 1037 of yacc.c.  */
#line 2414 "sdr.cpp"

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
	  YYSIZE_T yysize = 0;
	  int yytype = YYTRANSLATE (yychar);
	  const char* yyprefix;
	  char *yymsg;
	  int yyx;

	  /* Start YYX at -YYN if negative to avoid negative indexes in
	     YYCHECK.  */
	  int yyxbegin = yyn < 0 ? -yyn : 0;

	  /* Stay within bounds of both yycheck and yytname.  */
	  int yychecklim = YYLAST - yyn;
	  int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
	  int yycount = 0;

	  yyprefix = ", expecting ";
	  for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	      {
		yysize += yystrlen (yyprefix) + yystrlen (yytname [yyx]);
		yycount += 1;
		if (yycount == 5)
		  {
		    yysize = 0;
		    break;
		  }
	      }
	  yysize += (sizeof ("syntax error, unexpected ")
		     + yystrlen (yytname[yytype]));
	  yymsg = (char *) YYSTACK_ALLOC (yysize);
	  if (yymsg != 0)
	    {
	      char *yyp = yystpcpy (yymsg, "syntax error, unexpected ");
	      yyp = yystpcpy (yyp, yytname[yytype]);

	      if (yycount < 5)
		{
		  yyprefix = ", expecting ";
		  for (yyx = yyxbegin; yyx < yyxend; ++yyx)
		    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
		      {
			yyp = yystpcpy (yyp, yyprefix);
			yyp = yystpcpy (yyp, yytname[yyx]);
			yyprefix = " or ";
		      }
		}
	      yyerror (yymsg);
	      YYSTACK_FREE (yymsg);
	    }
	  else
	    yyerror ("syntax error; also virtual memory exhausted");
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror ("syntax error");
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* If at end of input, pop the error token,
	     then the rest of the stack, then return failure.  */
	  if (yychar == YYEOF)
	     for (;;)
	       {

		 YYPOPSTACK;
		 if (yyssp == yyss)
		   YYABORT;
		 yydestruct ("Error: popping",
                             yystos[*yyssp], yyvsp);
	       }
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

#ifdef __GNUC__
  /* Pacify GCC when the user code never invokes YYERROR and the label
     yyerrorlab therefore never appears in user code.  */
  if (0)
     goto yyerrorlab;
#endif

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
  yydestruct ("Error: discarding lookahead",
              yytoken, &yylval);
  yychar = YYEMPTY;
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*----------------------------------------------.
| yyoverflowlab -- parser overflow comes here.  |
`----------------------------------------------*/
yyoverflowlab:
  yyerror ("parser stack overflow");
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  return yyresult;
}


#line 1317 "sdr.y"

#include "lex.sdr.cpp"

int	slLineno	=	0;

///////////////////////////////////////////////////////////////////////
// Function				:	sdrerror
// Description			:	Parser error function
// Return Value			:
// Comments				:
// Date last edited		:	5/20/2003
void			sdrerror(char *s) {
	fprintf(stdout,"%s\n",s);
}


///////////////////////////////////////////////////////////////////////
// Function				:	sdrGet
// Description			:	Parse a shader
// Return Value			:
// Comments				:
// Date last edited		:	5/20/2003
TSdrShader		*sdrGet(const char *in,const char *searchpath) {
	TSdrShader		*cShader;
	char			tmp[512];
	const	char	*currentPath;
	char			*dest;

	memInit();

	sdrin	=	fopen(in,"r");

	if (sdrin == NULL) {
		if (searchpath != NULL) {
			for (dest=tmp,currentPath=searchpath;;) {
				if ((*currentPath == '\0') || (*currentPath == ':')) {		// End of the current path

					if ((dest - tmp) > 0) {		// Do we have anything to record ?
						dest--;

						if ((*dest == '/') || (*dest == '\\')) {	// The last character has to be a slash
							dest++;
						} else {
							dest++;
							*dest++	=	'/';
						}

						sprintf(dest,in);
						if (strstr(dest,".sdr") == NULL) {
							strcat(dest,".sdr");
						}

						osFixSlashes(tmp);

						if (strncmp(tmp,"\\\\",2) == 0) {
							tmp[1]	=	tmp[2];
							tmp[2]	=	':';
							tmp[3]	=	'\\';

							sdrin	=	fopen(tmp+1,"r");
						} else {
							sdrin	=	fopen(tmp,"r");
						}

						if (sdrin != NULL)	break;
					}

					dest			=	tmp;

					if (*currentPath == '\0')	break;

					currentPath++;
				} else if (*currentPath == '%') {
					const	char	*endOfCurrentPath	=	strchr(currentPath+1,'%');
					char			environmentVariable[OS_MAX_PATH_LENGTH];

					if (endOfCurrentPath!=NULL) {
						const	int		environmentLength	=	endOfCurrentPath - currentPath - 1;
						const	char	*value;

						strncpy(environmentVariable,currentPath+1,environmentLength);
						environmentVariable[environmentLength]	=	'\0';

						value		=	osEnvironment(environmentVariable);
						if (value != NULL) {
							strcpy(dest,value);
							dest	+=	strlen(value);
						}

						currentPath	=	endOfCurrentPath+1;
					} else {
						currentPath++;
					}
				} else if ((*currentPath == '@') || (*currentPath == '&')) {
					currentPath++;
				} else {
					*dest++	=	*currentPath++;
				}
			}
		}
	}

	if (sdrin == NULL)	return NULL;

	parameters	=	NULL;

	sdrparse();

	fclose(sdrin);

	cShader	=	new TSdrShader;

	cShader->name		=	strdup(in);
	cShader->type		=	shaderType;
	cShader->parameters	=	parameters;

	return cShader;
}

///////////////////////////////////////////////////////////////////////
// Function				:	sdrDelete
// Description			:	Delete a shader
// Return Value			:
// Comments				:
// Date last edited		:	5/20/2003
void			sdrDelete(TSdrShader *cShader) {
	TSdrParameter	*cParameter;

	while((cParameter = cShader->parameters) != NULL) {
		cShader->parameters	=	cParameter->next;

		free(cParameter->name);
		if (cParameter->space != NULL) {
			free(cParameter->space);
		}

		if (cParameter->numItems == 1) {
			switch(cParameter->type) {
			case TYPE_FLOAT:
				break;
			case TYPE_VECTOR:
			case TYPE_NORMAL:
			case TYPE_POINT:
			case TYPE_COLOR:
				if (cParameter->defaultValue.vector != NULL) {
					delete [] cParameter->defaultValue.vector;
				}
				break;
			case TYPE_MATRIX:
				if (cParameter->defaultValue.matrix != NULL) {
					delete [] cParameter->defaultValue.matrix;
				}
				break;
			case TYPE_STRING:
				if (cParameter->defaultValue.string != NULL) {
					free(cParameter->defaultValue.string);
				}
				break;
			}
		}

		delete cParameter;
	}

	free(cShader->name);
	delete cShader;

	memShutdown();
}




