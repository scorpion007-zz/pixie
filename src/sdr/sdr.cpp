
/*  A Bison parser, made from ../../../../src/sdr/sdr.y
 by  GNU Bison version 1.25
  */

#define YYBISON 1  /* Identify Bison output.  */

#define alloca

#define yyparse sdrparse
#define yylex sdrlex
#define yyerror sdrerror
#define yylval sdrlval
#define yychar sdrchar
#define yydebug sdrdebug
#define yynerrs sdrnerrs
#define	SCRL_PARAMETERS	258
#define	SCRL_VARIABLES	259
#define	SCRL_INIT	260
#define	SCRL_CODE	261
#define	SCRL_OUTPUT	262
#define	SCRL_VARYING	263
#define	SCRL_UNIFORM	264
#define	SCRL_BOOLEAN	265
#define	SCRL_FLOAT	266
#define	SCRL_COLOR	267
#define	SCRL_VECTOR	268
#define	SCRL_NORMAL	269
#define	SCRL_POINT	270
#define	SCRL_MATRIX	271
#define	SCRL_STRING	272
#define	SCRL_SURFACE	273
#define	SCRL_DISPLACEMENT	274
#define	SCRL_IMAGER	275
#define	SCRL_LIGHTSOURCE	276
#define	SCRL_VOLUME	277
#define	SCRL_GENERIC	278
#define	SCRL_DSO	279
#define	SCRL_DOT	280
#define	SCRL_COLON	281
#define	SCRL_EQUAL	282
#define	SCRL_OPEN_PARANTHESIS	283
#define	SCRL_CLOSE_PARANTHESIS	284
#define	SCRL_OPEN_SQR_PARANTHESIS	285
#define	SCRL_CLOSE_SQR_PARANTHESIS	286
#define	SCRL_COMMA	287
#define	SCRL_NL	288
#define	SCRL_TEXT_VALUE	289
#define	SCRL_IDENTIFIER_VALUE	290
#define	SCRL_LABEL_VALUE	291
#define	SCRL_FLOAT_VALUE	292

#line 1 "../../../../src/sdr/sdr.y"

//////////////////////////////////////////////////////////////////////
//
//                             Pixie
//
// Copyright © 1999 - 2003, Okan Arikan
//
// Contact: okan@cs.utexas.edu
//
//	This library is free software; you can redistribute it and/or
//	modify it under the terms of the GNU Lesser General Public
//	License as published by the Free Software Foundation; either
//	version 2.1 of the License, or (at your option) any later version.
//
//	This library is distributed in the hope that it will be useful,
//	but WITHOUT ANY WARRANTY; without even the implied warranty of
//	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//	Lesser General Public License for more details.
//
//	You should have received a copy of the GNU Lesser General Public
//	License along with this library; if not, write to the Free Software
//	Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
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


#line 97 "../../../../src/sdr/sdr.y"
typedef union slval {
	float			real;
	char			string[64];
	matrix			m;
	vector			v;
	TSdrParameter *parameter;
} YYSTYPE;
#ifndef YYDEBUG
#define YYDEBUG 1
#endif

#include <stdio.h>

#ifndef __cplusplus
#ifndef __STDC__
#define const
#endif
#endif



#define	YYFINAL		313
#define	YYFLAG		32768
#define	YYNTBASE	38

#define YYTRANSLATE(x) ((unsigned)(x) <= 292 ? yytranslate[x] : 98)

static const char yytranslate[] = {     0,
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
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     1,     2,     3,     4,     5,
     6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
    16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
    26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
    36,    37
};

#if YYDEBUG != 0
static const short yyprhs[] = {     0,
     0,    11,    12,    15,    18,    25,    27,    33,    35,    38,
    39,    41,    43,    44,    47,    50,    53,    56,    59,    64,
    68,    69,    70,    74,    75,    78,    80,    82,    84,    86,
    88,    90,    92,    94,    96,    99,   102,   104,   109,   112,
   113,   122,   128,   132,   135,   136,   139,   144,   145,   154,
   160,   164,   167,   168,   169,   174,   175,   184,   190,   191,
   196,   197,   206,   212,   216,   217,   221,   222,   223,   228,
   229,   238,   244,   245,   250,   251,   260,   266,   288,   293,
   296,   297,   306,   312,   316,   336,   339,   340,   345,   348,
   349,   353,   357,   361,   365,   369,   373,   377,   381,   384,
   390,   393,   399,   402,   408,   411,   417,   420,   426,   429,
   435,   438,   444,   447,   453,   457,   461,   465,   466,   467,
   475,   477,   479,   481,   484,   485,   488,   491,   493,   495,
   497,   499,   507,   541
};

static const short yyrhs[] = {    44,
    45,    79,     5,    33,    90,     6,    33,    90,    39,     0,
     0,    33,    39,     0,    34,    37,     0,    34,    30,    37,
    37,    37,    31,     0,    37,     0,    30,    37,    37,    37,
    31,     0,    40,     0,    27,    41,     0,     0,     9,     0,
     8,     0,     0,    18,    33,     0,    19,    33,     0,    21,
    33,     0,    22,    33,     0,    20,    33,     0,     3,    26,
    33,    46,     0,    46,    47,    33,     0,     0,     0,    48,
    51,    50,     0,     0,    49,    50,     0,    52,     0,    56,
     0,    60,     0,    63,     0,    69,     0,    72,     0,    75,
     0,     9,     0,     8,     0,     7,     9,     0,     7,     8,
     0,     7,     0,    11,    35,    27,    37,     0,    11,    35,
     0,     0,    11,    35,    30,    37,    31,    27,    53,    54,
     0,    11,    35,    30,    37,    31,     0,    30,    55,    31,
     0,    55,    37,     0,     0,    17,    35,     0,    17,    35,
    27,    34,     0,     0,    17,    35,    30,    37,    31,    27,
    57,    58,     0,    17,    35,    30,    37,    31,     0,    30,
    59,    31,     0,    59,    34,     0,     0,     0,    12,    35,
    61,    42,     0,     0,    12,    35,    30,    37,    31,    27,
    62,    66,     0,    12,    35,    30,    37,    31,     0,     0,
    13,    35,    64,    42,     0,     0,    13,    35,    30,    37,
    31,    27,    65,    66,     0,    13,    35,    30,    37,    31,
     0,    30,    67,    31,     0,     0,    67,    68,    41,     0,
     0,     0,    14,    35,    70,    42,     0,     0,    14,    35,
    30,    37,    31,    27,    71,    66,     0,    14,    35,    30,
    37,    31,     0,     0,    15,    35,    73,    42,     0,     0,
    15,    35,    30,    37,    31,    27,    74,    66,     0,    15,
    35,    30,    37,    31,     0,    16,    35,    27,    30,    37,
    37,    37,    37,    37,    37,    37,    37,    37,    37,    37,
    37,    37,    37,    37,    37,    31,     0,    16,    35,    27,
    37,     0,    16,    35,     0,     0,    16,    35,    30,    37,
    31,    27,    76,    77,     0,    16,    35,    30,    37,    31,
     0,    30,    78,    31,     0,    78,    30,    37,    37,    37,
    37,    37,    37,    37,    37,    37,    37,    37,    37,    37,
    37,    37,    37,    31,     0,    78,    37,     0,     0,     4,
    26,    33,    80,     0,    80,    81,     0,     0,    43,    82,
    33,     0,    43,    83,    33,     0,    43,    84,    33,     0,
    43,    86,    33,     0,    43,    85,    33,     0,    43,    87,
    33,     0,    43,    88,    33,     0,    43,    89,    33,     0,
    10,    35,     0,    10,    35,    30,    37,    31,     0,    11,
    35,     0,    11,    35,    30,    37,    31,     0,    17,    35,
     0,    17,    35,    30,    37,    31,     0,    13,    35,     0,
    13,    35,    30,    37,    31,     0,    12,    35,     0,    12,
    35,    30,    37,    31,     0,    14,    35,     0,    14,    35,
    30,    37,    31,     0,    15,    35,     0,    15,    35,    30,
    37,    31,     0,    16,    35,     0,    16,    35,    30,    37,
    31,     0,    90,    95,    33,     0,    90,    96,    33,     0,
    90,    91,    33,     0,     0,     0,    24,    35,    92,    28,
    34,    29,    94,     0,    35,     0,    19,     0,    18,     0,
    97,    94,     0,     0,    93,    94,     0,    36,    26,     0,
    34,     0,    36,     0,    35,     0,    37,     0,    28,    37,
    32,    37,    32,    37,    29,     0,    28,    37,    32,    37,
    32,    37,    32,    37,    32,    37,    32,    37,    32,    37,
    32,    37,    32,    37,    32,    37,    32,    37,    32,    37,
    32,    37,    32,    37,    32,    37,    32,    37,    29,     0,
    28,    34,    29,     0
};

#endif

#if YYDEBUG != 0
static const short yyrline[] = { 0,
   149,   162,   163,   168,   177,   191,   199,   213,   218,   220,
   229,   232,   236,   241,   247,   253,   259,   265,   273,   280,
   286,   291,   299,   304,   313,   319,   321,   323,   325,   327,
   329,   331,   336,   342,   348,   355,   362,   370,   381,   390,
   407,   407,   425,   436,   449,   452,   461,   472,   489,   489,
   507,   518,   531,   534,   545,   547,   564,   564,   586,   597,
   599,   616,   616,   638,   649,   660,   664,   667,   678,   680,
   697,   697,   719,   730,   732,   749,   749,   771,   816,   844,
   870,   888,   888,   924,   935,   982,  1009,  1012,  1019,  1022,
  1025,  1029,  1033,  1037,  1041,  1045,  1049,  1053,  1059,  1064,
  1075,  1080,  1090,  1095,  1105,  1110,  1120,  1125,  1135,  1140,
  1150,  1155,  1165,  1170,  1180,  1184,  1188,  1192,  1196,  1201,
  1208,  1212,  1216,  1222,  1227,  1232,  1239,  1246,  1250,  1254,
  1258,  1262,  1272,  1308
};
#endif


#if YYDEBUG != 0 || defined (YYERROR_VERBOSE)

static const char * const yytname[] = {   "$","error","$undefined.","SCRL_PARAMETERS",
"SCRL_VARIABLES","SCRL_INIT","SCRL_CODE","SCRL_OUTPUT","SCRL_VARYING","SCRL_UNIFORM",
"SCRL_BOOLEAN","SCRL_FLOAT","SCRL_COLOR","SCRL_VECTOR","SCRL_NORMAL","SCRL_POINT",
"SCRL_MATRIX","SCRL_STRING","SCRL_SURFACE","SCRL_DISPLACEMENT","SCRL_IMAGER",
"SCRL_LIGHTSOURCE","SCRL_VOLUME","SCRL_GENERIC","SCRL_DSO","SCRL_DOT","SCRL_COLON",
"SCRL_EQUAL","SCRL_OPEN_PARANTHESIS","SCRL_CLOSE_PARANTHESIS","SCRL_OPEN_SQR_PARANTHESIS",
"SCRL_CLOSE_SQR_PARANTHESIS","SCRL_COMMA","SCRL_NL","SCRL_TEXT_VALUE","SCRL_IDENTIFIER_VALUE",
"SCRL_LABEL_VALUE","SCRL_FLOAT_VALUE","start","slEmptySpace","slVectorIn","slVector",
"slVectorInit","slContainer","slType","slParameterDefinitions","slParameters",
"slParameter","@1","@2","slRegularParameter","slGlobalParameterContainer","slFloatParameter",
"@3","slFloatArrayInitializer","slFloatArrayInitializerItems","slStringParameter",
"@4","slStringArrayInitializer","slStringArrayInitializerItems","slColorParameter",
"@5","@6","slVectorParameter","@7","@8","slVectorArrayInitializer","slVectorArrayInitializerItems",
"@9","slNormalParameter","@10","@11","slPointParameter","@12","@13","slMatrixParameter",
"@14","slMatrixArrayInitializer","slMatrixArrayInitializerItems","slVariableDefinitions",
"slVariables","slVariable","slBooleanVariable","slFloatVariable","slStringVariable",
"slVectorVariable","slColorVariable","slNormalVariable","slPointVariable","slMatrixVariable",
"slCode","slDSO","@15","slOpcode","slOperandList","slStatement","slLabelDefinition",
"slOperand", NULL
};
#endif

static const short yyr1[] = {     0,
    38,    39,    39,    40,    40,    40,    40,    41,    42,    42,
    43,    43,    43,    44,    44,    44,    44,    44,    45,    46,
    46,    48,    47,    49,    47,    50,    50,    50,    50,    50,
    50,    50,    51,    51,    51,    51,    51,    52,    52,    53,
    52,    52,    54,    55,    55,    56,    56,    57,    56,    56,
    58,    59,    59,    61,    60,    62,    60,    60,    64,    63,
    65,    63,    63,    66,    68,    67,    67,    70,    69,    71,
    69,    69,    73,    72,    74,    72,    72,    75,    75,    75,
    76,    75,    75,    77,    78,    78,    78,    79,    80,    80,
    81,    81,    81,    81,    81,    81,    81,    81,    82,    82,
    83,    83,    84,    84,    85,    85,    86,    86,    87,    87,
    88,    88,    89,    89,    90,    90,    90,    90,    92,    91,
    93,    93,    93,    94,    94,    95,    96,    97,    97,    97,
    97,    97,    97,    97
};

static const short yyr2[] = {     0,
    10,     0,     2,     2,     6,     1,     5,     1,     2,     0,
     1,     1,     0,     2,     2,     2,     2,     2,     4,     3,
     0,     0,     3,     0,     2,     1,     1,     1,     1,     1,
     1,     1,     1,     1,     2,     2,     1,     4,     2,     0,
     8,     5,     3,     2,     0,     2,     4,     0,     8,     5,
     3,     2,     0,     0,     4,     0,     8,     5,     0,     4,
     0,     8,     5,     3,     0,     3,     0,     0,     4,     0,
     8,     5,     0,     4,     0,     8,     5,    21,     4,     2,
     0,     8,     5,     3,    19,     2,     0,     4,     2,     0,
     3,     3,     3,     3,     3,     3,     3,     3,     2,     5,
     2,     5,     2,     5,     2,     5,     2,     5,     2,     5,
     2,     5,     2,     5,     3,     3,     3,     0,     0,     7,
     1,     1,     1,     2,     0,     2,     2,     1,     1,     1,
     1,     7,    33,     3
};

static const short yydefact[] = {     0,
     0,     0,     0,     0,     0,     0,    14,    15,    18,    16,
    17,     0,     0,     0,     0,     0,    21,     0,     0,    24,
    90,   118,     0,     0,     0,    13,     0,    20,    37,    34,
    33,     0,     0,     0,     0,     0,     0,     0,     0,    25,
    26,    27,    28,    29,    30,    31,    32,    12,    11,     0,
    89,     0,   123,   122,     0,   121,     0,     0,   125,     0,
     0,    36,    35,    23,    39,    54,    59,    68,    73,    80,
    46,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,   118,   119,   127,
   117,     0,   128,   130,   129,   131,   126,   125,   115,   116,
     0,     0,     0,    10,     0,    10,     0,    10,     0,    10,
     0,     0,     0,     0,    99,   101,   107,   105,   109,   111,
   113,   103,    91,    92,    93,    95,    94,    96,    97,    98,
     2,     0,     0,     0,   124,    38,     0,     0,     0,    55,
     0,    60,     0,    69,     0,    74,     0,    79,     0,    47,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     2,
     1,     0,   134,     0,    42,    58,     0,     0,     6,     8,
     9,    63,    72,    77,     0,    83,    50,     0,     0,     0,
     0,     0,     0,     0,     0,     3,     0,     0,    40,    56,
     0,     0,     4,    61,    70,    75,     0,    81,    48,   100,
   102,   108,   106,   110,   112,   114,   104,   125,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,   120,
     0,    45,    41,    67,    57,     0,     0,    62,    71,    76,
     0,    87,    82,    53,    49,   132,     0,     0,    65,     7,
     0,     0,     0,     0,     0,    43,    44,    64,     0,     5,
     0,     0,    84,    86,    51,    52,     0,    66,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,    78,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,    85,     0,     0,     0,     0,     0,     0,     0,   133,
     0,     0,     0
};

static const short yydefgoto[] = {   311,
   161,   170,   171,   140,    50,     6,    13,    20,    23,    24,
    25,    40,    32,    41,   210,   223,   238,    42,   219,   235,
   244,    43,   104,   211,    44,   106,   214,   225,   239,   249,
    45,   108,   215,    46,   110,   216,    47,   218,   233,   243,
    16,    26,    51,    80,    81,    82,    83,    84,    85,    86,
    87,    27,    58,   132,    59,    97,    60,    61,    98
};

static const short yypact[] = {    24,
    26,    31,    44,    53,    54,    55,-32768,-32768,-32768,-32768,
-32768,    48,    74,    56,    62,    85,-32768,    58,    59,    -2,
-32768,-32768,    60,    73,    38,    52,    -5,-32768,    19,-32768,
-32768,    38,    61,    63,    64,    65,    66,    67,    68,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,    22,
-32768,    71,-32768,-32768,    70,-32768,    69,    75,   -12,    76,
    78,-32768,-32768,-32768,    -1,    77,    82,    83,    84,    39,
    41,    80,    81,    86,    87,    88,    89,    90,    91,    94,
    95,    96,    97,    98,    99,   100,   101,-32768,-32768,-32768,
-32768,    36,-32768,-32768,-32768,-32768,-32768,   -12,-32768,-32768,
    57,   102,   103,    79,   104,    79,   105,    79,   106,    79,
    10,   107,   111,   109,   108,   117,   118,   119,   120,   121,
   122,   123,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
   -15,    92,   125,   124,-32768,-32768,   126,   127,   -22,-32768,
   128,-32768,   129,-32768,   130,-32768,   131,-32768,   132,-32768,
   133,   134,   135,   136,   137,   138,   139,   140,   141,   146,
-32768,   147,-32768,   143,   110,   142,   145,    11,-32768,-32768,
-32768,   156,   157,   158,   149,   160,   161,   159,   162,   163,
   164,   165,   166,   167,   168,-32768,   171,   169,-32768,-32768,
   152,   154,-32768,-32768,-32768,-32768,   155,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,   -12,   170,   172,
   173,   174,   175,   173,   173,   173,   176,   178,   179,-32768,
    43,-32768,-32768,-32768,-32768,   183,   180,-32768,-32768,-32768,
   181,-32768,-32768,-32768,-32768,-32768,   182,    25,   184,-32768,
   185,   186,   -20,    45,   188,-32768,-32768,-32768,   -22,-32768,
   187,   189,-32768,-32768,-32768,-32768,   190,-32768,   191,   192,
   193,   194,   195,   196,   197,   198,   204,   200,   201,   202,
   203,   205,   209,   206,   207,   208,   210,   211,   214,   212,
   213,   215,   216,   217,   219,   199,   218,   220,-32768,   221,
   224,   222,   223,   225,   229,   226,   227,   228,   234,   236,
   231,-32768,   237,   233,   239,   235,   241,   238,   177,-32768,
   274,   276,-32768
};

static const short yypgoto[] = {-32768,
   -63,-32768,  -132,   -43,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,   245,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,  -131,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,    30,-32768,-32768,-32768,   -98,-32768,-32768,-32768
};


#define	YYLAST		277


static const short yytable[] = {   135,
    52,   -19,    53,    54,   -22,   -22,   -22,   167,    55,   252,
   253,   168,    53,    54,   169,    92,   254,   160,    55,    56,
    57,    93,    94,    95,    96,   101,    62,    63,   102,    56,
    57,    72,    73,    74,    75,    76,    77,    78,    79,   147,
   192,     1,     2,     3,     4,     5,   148,   193,    33,    34,
    35,    36,    37,    38,    39,   246,   -88,    12,     7,    48,
    49,   247,   142,     8,   144,   111,   146,   113,   112,   133,
   114,   236,   134,    14,   237,   255,     9,    15,   256,    29,
    30,    31,   228,   229,   230,    10,    11,    18,    17,    19,
    21,    22,    28,   136,    90,    65,   186,    66,    67,    68,
    69,    70,    71,    88,    89,   139,   103,    91,    99,   220,
   100,   105,   107,   109,   115,   116,   258,   131,     0,   162,
   117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
   127,   128,   129,   130,     0,     0,   189,   152,   137,   138,
   141,   143,   145,   149,   150,   151,   153,   154,   155,   156,
   157,   158,   159,   163,     0,   164,   165,   166,   172,   173,
   174,     0,   176,   177,     0,     0,     0,   175,   190,     0,
   178,   179,   180,   181,   182,   183,   184,   185,   160,   188,
   187,   191,   194,   195,   196,   197,   198,   199,   212,   200,
   213,   217,   201,   202,   203,   204,   205,   206,   207,   208,
   209,   222,   224,     0,     0,   310,   221,   232,   234,     0,
   226,   227,   231,   240,   248,   250,   241,   242,   245,   257,
     0,     0,   251,   259,   264,   260,   261,   262,   263,   289,
   265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
   276,   275,   277,   278,   279,   282,   280,   281,   283,   284,
   288,   285,   286,   287,   290,   293,   291,   292,   294,   295,
   297,   296,   298,   299,   300,   301,   302,   303,   304,   305,
   306,   307,   308,   312,   309,   313,    64
};

static const short yycheck[] = {    98,
     6,     4,    18,    19,     7,     8,     9,    30,    24,    30,
    31,    34,    18,    19,    37,    28,    37,    33,    24,    35,
    36,    34,    35,    36,    37,    27,     8,     9,    30,    35,
    36,    10,    11,    12,    13,    14,    15,    16,    17,    30,
    30,    18,    19,    20,    21,    22,    37,    37,    11,    12,
    13,    14,    15,    16,    17,    31,     5,     3,    33,     8,
     9,    37,   106,    33,   108,    27,   110,    27,    30,    34,
    30,    29,    37,    26,    32,    31,    33,     4,    34,     7,
     8,     9,   214,   215,   216,    33,    33,    26,    33,     5,
    33,    33,    33,    37,    26,    35,   160,    35,    35,    35,
    35,    35,    35,    33,    35,    27,    30,    33,    33,   208,
    33,    30,    30,    30,    35,    35,   249,    88,    -1,    28,
    35,    35,    35,    35,    35,    35,    33,    33,    33,    33,
    33,    33,    33,    33,    -1,    -1,    27,    30,    37,    37,
    37,    37,    37,    37,    34,    37,    30,    30,    30,    30,
    30,    30,    30,    29,    -1,    32,    31,    31,    31,    31,
    31,    -1,    31,    31,    -1,    -1,    -1,    37,    27,    -1,
    37,    37,    37,    37,    37,    37,    37,    37,    33,    37,
    34,    37,    27,    27,    27,    37,    27,    27,    37,    31,
    37,    37,    31,    31,    31,    31,    31,    31,    31,    29,
    32,    30,    30,    -1,    -1,    29,    37,    30,    30,    -1,
    37,    37,    37,    31,    31,    31,    37,    37,    37,    32,
    -1,    -1,    37,    37,    32,    37,    37,    37,    37,    31,
    37,    37,    37,    37,    37,    32,    37,    37,    37,    37,
    32,    37,    37,    37,    37,    32,    37,    37,    37,    37,
    32,    37,    37,    37,    37,    32,    37,    37,    37,    37,
    32,    37,    37,    37,    37,    32,    31,    37,    32,    37,
    32,    37,    32,     0,    37,     0,    32
};
/* -*-C-*-  Note some compilers choke on comments on `#line' lines.  */

/* Skeleton output parser for bison,
   Copyright (C) 1984, 1989, 1990 Free Software Foundation, Inc.

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
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

#ifndef alloca
#ifdef __GNUC__
#define alloca __builtin_alloca
#else /* not GNU C.  */
#if (!defined (__STDC__) && defined (sparc)) || defined (__sparc__) || defined (__sparc) || defined (__sgi)
#include <alloca.h>
#else /* not sparc */
#if defined (MSDOS) && !defined (__TURBOC__)
#include <malloc.h>
#else /* not MSDOS, or __TURBOC__ */
#if defined(_AIX)
#include <malloc.h>
 #pragma alloca
#else /* not MSDOS, __TURBOC__, or _AIX */
#ifdef __hpux
#ifdef __cplusplus
extern "C" {
void *alloca (unsigned int);
};
#else /* not __cplusplus */
void *alloca ();
#endif /* not __cplusplus */
#endif /* __hpux */
#endif /* not _AIX */
#endif /* not MSDOS, or __TURBOC__ */
#endif /* not sparc.  */
#endif /* not GNU C.  */
#endif /* alloca not defined.  */

/* This is the parser code that is written into each bison parser
  when the %semantic_parser declaration is not specified in the grammar.
  It was written by Richard Stallman by simplifying the hairy parser
  used when %semantic_parser is specified.  */

/* Note: there must be only one dollar sign in this file.
   It is replaced by the list of actions, each action
   as one case of the switch.  */

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		-2
#define YYEOF		0
#define YYACCEPT	return(0)
#define YYABORT 	return(1)
#define YYERROR		goto yyerrlab1
/* Like YYERROR except do call yyerror.
   This remains here temporarily to ease the
   transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */
#define YYFAIL		goto yyerrlab
#define YYRECOVERING()  (!!yyerrstatus)
#define YYBACKUP(token, value) \
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    { yychar = (token), yylval = (value);			\
      yychar1 = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { yyerror ("syntax error: cannot back up"); YYERROR; }	\
while (0)

#define YYTERROR	1
#define YYERRCODE	256

#ifndef YYPURE
#define YYLEX		yylex()
#endif

#ifdef YYPURE
#ifdef YYLSP_NEEDED
#ifdef YYLEX_PARAM
#define YYLEX		yylex(&yylval, &yylloc, YYLEX_PARAM)
#else
#define YYLEX		yylex(&yylval, &yylloc)
#endif
#else /* not YYLSP_NEEDED */
#ifdef YYLEX_PARAM
#define YYLEX		yylex(&yylval, YYLEX_PARAM)
#else
#define YYLEX		yylex(&yylval)
#endif
#endif /* not YYLSP_NEEDED */
#endif

/* If nonreentrant, generate the variables here */

#ifndef YYPURE

int	yychar;			/*  the lookahead symbol		*/
YYSTYPE	yylval;			/*  the semantic value of the		*/
				/*  lookahead symbol			*/

#ifdef YYLSP_NEEDED
YYLTYPE yylloc;			/*  location data for the lookahead	*/
				/*  symbol				*/
#endif

int yynerrs;			/*  number of parse errors so far       */
#endif  /* not YYPURE */

#if YYDEBUG != 0
int yydebug;			/*  nonzero means print parse trace	*/
/* Since this is uninitialized, it does not stop multiple parsers
   from coexisting.  */
#endif

/*  YYINITDEPTH indicates the initial size of the parser's stacks	*/

#ifndef	YYINITDEPTH
#define YYINITDEPTH 200
#endif

/*  YYMAXDEPTH is the maximum size the stacks can grow to
    (effective only if the built-in stack extension method is used).  */

#if YYMAXDEPTH == 0
#undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
#define YYMAXDEPTH 10000
#endif

/* Prevent warning if -Wstrict-prototypes.  */
#ifdef __GNUC__
int yyparse (void);
#endif

#if __GNUC__ > 1		/* GNU C and GNU C++ define this.  */
#define __yy_memcpy(TO,FROM,COUNT)	__builtin_memcpy(TO,FROM,COUNT)
#else				/* not GNU C or C++ */
#ifndef __cplusplus

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_memcpy (to, from, count)
     char *to;
     char *from;
     int count;
{
  register char *f = from;
  register char *t = to;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#else /* __cplusplus */

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_memcpy (char *to, char *from, int count)
{
  register char *f = from;
  register char *t = to;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#endif
#endif


/* The user can define YYPARSE_PARAM as the name of an argument to be passed
   into yyparse.  The argument should have type void *.
   It should actually point to an object.
   Grammar actions can access the variable by casting it
   to the proper pointer type.  */

#ifdef YYPARSE_PARAM
#ifdef __cplusplus
#define YYPARSE_PARAM_ARG void *YYPARSE_PARAM
#define YYPARSE_PARAM_DECL
#else /* not __cplusplus */
#define YYPARSE_PARAM_ARG YYPARSE_PARAM
#define YYPARSE_PARAM_DECL void *YYPARSE_PARAM;
#endif /* not __cplusplus */
#else /* not YYPARSE_PARAM */
#define YYPARSE_PARAM_ARG
#define YYPARSE_PARAM_DECL
#endif /* not YYPARSE_PARAM */

int
yyparse(YYPARSE_PARAM_ARG)
     YYPARSE_PARAM_DECL
{
  register int yystate;
  register int yyn;
  register short *yyssp;
  register YYSTYPE *yyvsp;
  int yyerrstatus;	/*  number of tokens to shift before error messages enabled */
  int yychar1 = 0;		/*  lookahead token as an internal (translated) token number */

  short	yyssa[YYINITDEPTH];	/*  the state stack			*/
  YYSTYPE yyvsa[YYINITDEPTH];	/*  the semantic value stack		*/

  short *yyss = yyssa;		/*  refer to the stacks thru separate pointers */
  YYSTYPE *yyvs = yyvsa;	/*  to allow yyoverflow to reallocate them elsewhere */

#ifdef YYLSP_NEEDED
  YYLTYPE yylsa[YYINITDEPTH];	/*  the location stack			*/
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;

#define YYPOPSTACK   (yyvsp--, yyssp--, yylsp--)
#else
#define YYPOPSTACK   (yyvsp--, yyssp--)
#endif

  int yystacksize = YYINITDEPTH;

#ifdef YYPURE
  int yychar;
  YYSTYPE yylval;
  int yynerrs;
#ifdef YYLSP_NEEDED
  YYLTYPE yylloc;
#endif
#endif

  YYSTYPE yyval;		/*  the variable used to return		*/
				/*  semantic values from the action	*/
				/*  routines				*/

  int yylen;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Starting parse\n");
#endif

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss - 1;
  yyvsp = yyvs;
#ifdef YYLSP_NEEDED
  yylsp = yyls;
#endif

/* Push a new state, which is found in  yystate  .  */
/* In all cases, when you get here, the value and location stacks
   have just been pushed. so pushing a state here evens the stacks.  */
yynewstate:

  *++yyssp = yystate;

  if (yyssp >= yyss + yystacksize - 1)
    {
      /* Give user a chance to reallocate the stack */
      /* Use copies of these so that the &'s don't force the real ones into memory. */
      YYSTYPE *yyvs1 = yyvs;
      short *yyss1 = yyss;
#ifdef YYLSP_NEEDED
      YYLTYPE *yyls1 = yyls;
#endif

      /* Get the current used size of the three stacks, in elements.  */
      int size = yyssp - yyss + 1;

#ifdef yyoverflow
      /* Each stack pointer address is followed by the size of
	 the data in use in that stack, in bytes.  */
#ifdef YYLSP_NEEDED
      /* This used to be a conditional around just the two extra args,
	 but that might be undefined if yyoverflow is a macro.  */
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yyls1, size * sizeof (*yylsp),
		 &yystacksize);
#else
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yystacksize);
#endif

      yyss = yyss1; yyvs = yyvs1;
#ifdef YYLSP_NEEDED
      yyls = yyls1;
#endif
#else /* no yyoverflow */
      /* Extend the stack our own way.  */
      if (yystacksize >= YYMAXDEPTH)
	{
	  yyerror("parser stack overflow");
	  return 2;
	}
      yystacksize *= 2;
      if (yystacksize > YYMAXDEPTH)
	yystacksize = YYMAXDEPTH;
      yyss = (short *) alloca (yystacksize * sizeof (*yyssp));
      __yy_memcpy ((char *)yyss, (char *)yyss1, size * sizeof (*yyssp));
      yyvs = (YYSTYPE *) alloca (yystacksize * sizeof (*yyvsp));
      __yy_memcpy ((char *)yyvs, (char *)yyvs1, size * sizeof (*yyvsp));
#ifdef YYLSP_NEEDED
      yyls = (YYLTYPE *) alloca (yystacksize * sizeof (*yylsp));
      __yy_memcpy ((char *)yyls, (char *)yyls1, size * sizeof (*yylsp));
#endif
#endif /* no yyoverflow */

      yyssp = yyss + size - 1;
      yyvsp = yyvs + size - 1;
#ifdef YYLSP_NEEDED
      yylsp = yyls + size - 1;
#endif

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Stack size increased to %d\n", yystacksize);
#endif

      if (yyssp >= yyss + yystacksize - 1)
	YYABORT;
    }

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Entering state %d\n", yystate);
#endif

  goto yybackup;
 yybackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* yychar is either YYEMPTY or YYEOF
     or a valid token in external form.  */

  if (yychar == YYEMPTY)
    {
#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Reading a token: ");
#endif
      yychar = YYLEX;
    }

  /* Convert token to internal form (in yychar1) for indexing tables with */

  if (yychar <= 0)		/* This means end of input. */
    {
      yychar1 = 0;
      yychar = YYEOF;		/* Don't call YYLEX any more */

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Now at end of input.\n");
#endif
    }
  else
    {
      yychar1 = YYTRANSLATE(yychar);

#if YYDEBUG != 0
      if (yydebug)
	{
	  fprintf (stderr, "Next token is %d (%s", yychar, yytname[yychar1]);
	  /* Give the individual parser a way to print the precise meaning
	     of a token, for further debugging info.  */
#ifdef YYPRINT
	  YYPRINT (stderr, yychar, yylval);
#endif
	  fprintf (stderr, ")\n");
	}
#endif
    }

  yyn += yychar1;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != yychar1)
    goto yydefault;

  yyn = yytable[yyn];

  /* yyn is what to do for this token type in this state.
     Negative => reduce, -yyn is rule number.
     Positive => shift, yyn is new state.
       New state is final state => don't bother to shift,
       just return success.
     0, or most negative number => error.  */

  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrlab;

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting token %d (%s), ", yychar, yytname[yychar1]);
#endif

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  /* count tokens shifted since error; after three, turn off error status.  */
  if (yyerrstatus) yyerrstatus--;

  yystate = yyn;
  goto yynewstate;

/* Do the default action for the current state.  */
yydefault:

  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;

/* Do a reduction.  yyn is the number of a rule to reduce with.  */
yyreduce:
  yylen = yyr2[yyn];
  if (yylen > 0)
    yyval = yyvsp[1-yylen]; /* implement default value of the action */

#if YYDEBUG != 0
  if (yydebug)
    {
      int i;

      fprintf (stderr, "Reducing via rule %d (line %d), ",
	       yyn, yyrline[yyn]);

      /* Print the symbols being reduced, and their result.  */
      for (i = yyprhs[yyn]; yyrhs[i] > 0; i++)
	fprintf (stderr, "%s ", yytname[yyrhs[i]]);
      fprintf (stderr, " -> %s\n", yytname[yyr1[yyn]]);
    }
#endif


  switch (yyn) {

case 4:
#line 170 "../../../../src/sdr/sdr.y"
{
				currentParameter->space			=	strdup(yyvsp[-1].string);
				currentDefaultItem->vector		=	new float[3];
				currentDefaultItem->vector[0]	=	yyvsp[0].real;
				currentDefaultItem->vector[1]	=	yyvsp[0].real;
				currentDefaultItem->vector[2]	=	yyvsp[0].real;
			;
    break;}
case 5:
#line 184 "../../../../src/sdr/sdr.y"
{
				currentParameter->space			=	strdup(yyvsp[-5].string);
				currentDefaultItem->vector		=	new float[3];
				currentDefaultItem->vector[0]	=	yyvsp[-3].real;
				currentDefaultItem->vector[1]	=	yyvsp[-2].real;
				currentDefaultItem->vector[2]	=	yyvsp[-1].real;
			;
    break;}
case 6:
#line 193 "../../../../src/sdr/sdr.y"
{
				currentDefaultItem->vector		=	new float[3];
				currentDefaultItem->vector[0]	=	yyvsp[0].real;
				currentDefaultItem->vector[1]	=	yyvsp[0].real;
				currentDefaultItem->vector[2]	=	yyvsp[0].real;
			;
    break;}
case 7:
#line 205 "../../../../src/sdr/sdr.y"
{
				currentDefaultItem->vector		=	new float[3];
				currentDefaultItem->vector[0]	=	yyvsp[-3].real;
				currentDefaultItem->vector[1]	=	yyvsp[-2].real;
				currentDefaultItem->vector[2]	=	yyvsp[-1].real;
			;
    break;}
case 8:
#line 214 "../../../../src/sdr/sdr.y"
{
			;
    break;}
case 10:
#line 221 "../../../../src/sdr/sdr.y"
{
					currentParameter->defaultValue.vector		=	new float[3];
					currentParameter->defaultValue.vector[0]	=	0;
					currentParameter->defaultValue.vector[1]	=	0;
					currentParameter->defaultValue.vector[2]	=	0;
			;
    break;}
case 11:
#line 230 "../../../../src/sdr/sdr.y"
{
				;
    break;}
case 12:
#line 234 "../../../../src/sdr/sdr.y"
{
				;
    break;}
case 13:
#line 237 "../../../../src/sdr/sdr.y"
{
				;
    break;}
case 14:
#line 244 "../../../../src/sdr/sdr.y"
{
			shaderType	=	SHADER_SURFACE;
		;
    break;}
case 15:
#line 250 "../../../../src/sdr/sdr.y"
{
			shaderType	=	SHADER_DISPLACEMENT;
		;
    break;}
case 16:
#line 256 "../../../../src/sdr/sdr.y"
{
			shaderType	=	SHADER_LIGHT;
		;
    break;}
case 17:
#line 262 "../../../../src/sdr/sdr.y"
{
			shaderType	=	SHADER_VOLUME;
		;
    break;}
case 18:
#line 268 "../../../../src/sdr/sdr.y"
{
			shaderType	=	SHADER_IMAGER;
		;
    break;}
case 20:
#line 284 "../../../../src/sdr/sdr.y"
{
		;
    break;}
case 21:
#line 287 "../../../../src/sdr/sdr.y"
{
		;
    break;}
case 22:
#line 292 "../../../../src/sdr/sdr.y"
{
			currentParameter						=	new TSdrParameter;
			currentParameter->space					=	NULL;
			currentParameter->numItems				=	1;
			currentParameter->defaultValue.string	=	NULL;
		;
    break;}
case 23:
#line 300 "../../../../src/sdr/sdr.y"
{
			currentParameter->next	=	parameters;
			parameters				=	currentParameter;
		;
    break;}
case 24:
#line 305 "../../../../src/sdr/sdr.y"
{
			currentParameter						=	new TSdrParameter;
			currentParameter->space					=	NULL;
			currentParameter->numItems				=	1;
			currentParameter->defaultValue.string	=	NULL;
			currentParameter->container				=	CONTAINER_UNIFORM;
		;
    break;}
case 25:
#line 313 "../../../../src/sdr/sdr.y"
{
			currentParameter->next	=	parameters;
			parameters				=	currentParameter;
		;
    break;}
case 33:
#line 338 "../../../../src/sdr/sdr.y"
{
			currentParameter->container	=	CONTAINER_UNIFORM;
			currentParameter->writable	=	FALSE;
		;
    break;}
case 34:
#line 344 "../../../../src/sdr/sdr.y"
{
			currentParameter->container	=	CONTAINER_VARYING;
			currentParameter->writable	=	FALSE;
		;
    break;}
case 35:
#line 351 "../../../../src/sdr/sdr.y"
{
			currentParameter->container	=	CONTAINER_UNIFORM;
			currentParameter->writable	=	TRUE;
		;
    break;}
case 36:
#line 358 "../../../../src/sdr/sdr.y"
{
			currentParameter->container	=	CONTAINER_VARYING;
			currentParameter->writable	=	TRUE;
		;
    break;}
case 37:
#line 364 "../../../../src/sdr/sdr.y"
{
			currentParameter->container	=	CONTAINER_UNIFORM;
			currentParameter->writable	=	TRUE;
		;
    break;}
case 38:
#line 375 "../../../../src/sdr/sdr.y"
{
			currentParameter->type					=	TYPE_FLOAT;
			currentParameter->name					=	strdup(yyvsp[-2].string);
			currentParameter->defaultValue.scalar	=	yyvsp[0].real;
			currentParameter->numItems				=	1;
		;
    break;}
case 39:
#line 384 "../../../../src/sdr/sdr.y"
{
			currentParameter->type					=	TYPE_FLOAT;
			currentParameter->name					=	strdup(yyvsp[0].string);
			currentParameter->defaultValue.scalar	=	0;
			currentParameter->numItems				=	1;
		;
    break;}
case 40:
#line 397 "../../../../src/sdr/sdr.y"
{
			currentParameter->type					=	TYPE_FLOAT;
			currentParameter->name					=	strdup(yyvsp[-4].string);
			currentParameter->defaultValue.array	=	new UDefaultVal[(int) yyvsp[-2].real];
			currentParameter->numItems				=	(int) yyvsp[-2].real;
			
			currentDefaultItem = currentParameter->defaultValue.array;
			numArrayItemsRemaining = currentParameter->numItems;
		;
    break;}
case 42:
#line 413 "../../../../src/sdr/sdr.y"
{
			currentParameter->type					=	TYPE_FLOAT;
			currentParameter->name					=	strdup(yyvsp[-3].string);
			currentParameter->defaultValue.array	=	new UDefaultVal[(int) yyvsp[-1].real];
			currentParameter->numItems				=	(int) yyvsp[-1].real;
			
			currentDefaultItem = currentParameter->defaultValue.array;
			for(int i=0;i<currentParameter->numItems;i++)
				currentDefaultItem[i].scalar = 0;
		;
    break;}
case 43:
#line 429 "../../../../src/sdr/sdr.y"
{
			if(numArrayItemsRemaining){
				sdrerror("wrong number of items in array initializer\n");
			}
		;
    break;}
case 44:
#line 439 "../../../../src/sdr/sdr.y"
{
			if(numArrayItemsRemaining){
				currentDefaultItem->scalar = yyvsp[0].real;
				currentDefaultItem++;
				numArrayItemsRemaining--;
			}
			else{
				sdrerror("wrong number of items in array initializer\n");
			}
		;
    break;}
case 46:
#line 455 "../../../../src/sdr/sdr.y"
{
			currentParameter->type					=	TYPE_STRING;
			currentParameter->name					=	strdup(yyvsp[0].string);
			currentParameter->defaultValue.array	=	NULL;
			currentParameter->numItems				=	1;
		;
    break;}
case 47:
#line 466 "../../../../src/sdr/sdr.y"
{
			currentParameter->type					=	TYPE_STRING;
			currentParameter->name					=	strdup(yyvsp[-2].string);
			currentParameter->defaultValue.string	=	strdup(yyvsp[0].string);
			currentParameter->numItems				=	1;
		;
    break;}
case 48:
#line 479 "../../../../src/sdr/sdr.y"
{
			currentParameter->type					=	TYPE_STRING;
			currentParameter->name					=	strdup(yyvsp[-4].string);
			currentParameter->defaultValue.array	=	new UDefaultVal[(int) yyvsp[-2].real];
			currentParameter->numItems				=	(int) yyvsp[-2].real;
			
			currentDefaultItem = currentParameter->defaultValue.array;
			numArrayItemsRemaining = currentParameter->numItems;
		;
    break;}
case 50:
#line 495 "../../../../src/sdr/sdr.y"
{
			currentParameter->type					=	TYPE_STRING;
			currentParameter->name					=	strdup(yyvsp[-3].string);
			currentParameter->defaultValue.array	=	new UDefaultVal[(int) yyvsp[-1].real];
			currentParameter->numItems				=	(int) yyvsp[-1].real;
			
			currentDefaultItem = currentParameter->defaultValue.array;
			for(int i=0;i<currentParameter->numItems;i++)
				currentDefaultItem[i].string = NULL;
		;
    break;}
case 51:
#line 511 "../../../../src/sdr/sdr.y"
{
			if(numArrayItemsRemaining){
				sdrerror("wrong number of items in array initializer\n");
			}
		;
    break;}
case 52:
#line 521 "../../../../src/sdr/sdr.y"
{
			if(numArrayItemsRemaining){
				currentDefaultItem->string = strdup(yyvsp[0].string);
				currentDefaultItem++;
				numArrayItemsRemaining--;
			}
			else{
				sdrerror("wrong number of items in array initializer\n");
			}
		;
    break;}
case 54:
#line 537 "../../../../src/sdr/sdr.y"
{
			currentParameter->type					=	TYPE_COLOR;
			currentParameter->name					=	strdup(yyvsp[0].string);
			currentParameter->numItems				=	1;
			
			currentDefaultItem = &currentParameter->defaultValue;
		;
    break;}
case 55:
#line 545 "../../../../src/sdr/sdr.y"
{
		;
    break;}
case 56:
#line 554 "../../../../src/sdr/sdr.y"
{
			currentParameter->type					=	TYPE_COLOR;
			currentParameter->name					=	strdup(yyvsp[-4].string);
			currentParameter->defaultValue.array	=	new UDefaultVal[(int) yyvsp[-2].real];
			currentParameter->numItems				=	(int) yyvsp[-2].real;
			
			currentDefaultItem = currentParameter->defaultValue.array;
			numArrayItemsRemaining = currentParameter->numItems;
		;
    break;}
case 58:
#line 570 "../../../../src/sdr/sdr.y"
{
			currentParameter->type					=	TYPE_COLOR;
			currentParameter->name					=	strdup(yyvsp[-3].string);
			currentParameter->defaultValue.array	=	new UDefaultVal[(int) yyvsp[-1].real];
			currentParameter->numItems				=	(int) yyvsp[-1].real;
			
			currentDefaultItem = currentParameter->defaultValue.array;
			for(int i=0;i<currentParameter->numItems;i++){
				currentDefaultItem[i].vector = new float[3];
				currentDefaultItem[i].vector[0] = 0;
				currentDefaultItem[i].vector[1] = 0;
				currentDefaultItem[i].vector[2] = 0;
			}
		;
    break;}
case 59:
#line 589 "../../../../src/sdr/sdr.y"
{
			currentParameter->type					=	TYPE_VECTOR;
			currentParameter->name					=	strdup(yyvsp[0].string);
			currentParameter->numItems				=	1;
			
			currentDefaultItem = &currentParameter->defaultValue;
		;
    break;}
case 60:
#line 597 "../../../../src/sdr/sdr.y"
{
		;
    break;}
case 61:
#line 606 "../../../../src/sdr/sdr.y"
{
			currentParameter->type					=	TYPE_VECTOR;
			currentParameter->name					=	strdup(yyvsp[-4].string);
			currentParameter->defaultValue.array	=	new UDefaultVal[(int) yyvsp[-2].real];
			currentParameter->numItems				=	(int) yyvsp[-2].real;
			
			currentDefaultItem = currentParameter->defaultValue.array;
			numArrayItemsRemaining = currentParameter->numItems;
		;
    break;}
case 63:
#line 622 "../../../../src/sdr/sdr.y"
{
			currentParameter->type					=	TYPE_VECTOR;
			currentParameter->name					=	strdup(yyvsp[-3].string);
			currentParameter->defaultValue.array	=	new UDefaultVal[(int) yyvsp[-1].real];
			currentParameter->numItems				=	(int) yyvsp[-1].real;
			
			currentDefaultItem = currentParameter->defaultValue.array;
			for(int i=0;i<currentParameter->numItems;i++){
				currentDefaultItem[i].vector = new float[3];
				currentDefaultItem[i].vector[0] = 0;
				currentDefaultItem[i].vector[1] = 0;
				currentDefaultItem[i].vector[2] = 0;
			}
		;
    break;}
case 64:
#line 642 "../../../../src/sdr/sdr.y"
{
			if(numArrayItemsRemaining){
				sdrerror("wrong number of items in array initializer\n");
		}
		;
    break;}
case 65:
#line 651 "../../../../src/sdr/sdr.y"
{
			if(numArrayItemsRemaining){
				currentDefaultItem->vector = new float[3];
			}
			else{
				sdrerror("wrong number of items in array initializer\n");
			}
		;
    break;}
case 66:
#line 660 "../../../../src/sdr/sdr.y"
{
			currentDefaultItem++;
			numArrayItemsRemaining--;
		;
    break;}
case 68:
#line 670 "../../../../src/sdr/sdr.y"
{
			currentParameter->type					=	TYPE_NORMAL;
			currentParameter->name					=	strdup(yyvsp[0].string);
			currentParameter->numItems				=	1;
			
			currentDefaultItem = &currentParameter->defaultValue;
		;
    break;}
case 69:
#line 678 "../../../../src/sdr/sdr.y"
{
		;
    break;}
case 70:
#line 687 "../../../../src/sdr/sdr.y"
{
			currentParameter->type					=	TYPE_NORMAL;
			currentParameter->name					=	strdup(yyvsp[-4].string);
			currentParameter->defaultValue.array	=	new UDefaultVal[(int) yyvsp[-2].real];
			currentParameter->numItems				=	(int) yyvsp[-2].real;
			
			currentDefaultItem = currentParameter->defaultValue.array;
			numArrayItemsRemaining = currentParameter->numItems;
		;
    break;}
case 72:
#line 703 "../../../../src/sdr/sdr.y"
{
			currentParameter->type					=	TYPE_NORMAL;
			currentParameter->name					=	strdup(yyvsp[-3].string);
			currentParameter->defaultValue.array	=	new UDefaultVal[(int) yyvsp[-1].real];
			currentParameter->numItems				=	(int) yyvsp[-1].real;
			
			currentDefaultItem = currentParameter->defaultValue.array;
			for(int i=0;i<currentParameter->numItems;i++){
				currentDefaultItem[i].vector = new float[3];
				currentDefaultItem[i].vector[0] = 0;
				currentDefaultItem[i].vector[1] = 0;
				currentDefaultItem[i].vector[3] = 0;
			}
		;
    break;}
case 73:
#line 722 "../../../../src/sdr/sdr.y"
{
			currentParameter->type					=	TYPE_POINT;
			currentParameter->name					=	strdup(yyvsp[0].string);
			currentParameter->numItems				=	1;
			
			currentDefaultItem = &currentParameter->defaultValue;
		;
    break;}
case 74:
#line 730 "../../../../src/sdr/sdr.y"
{
		;
    break;}
case 75:
#line 739 "../../../../src/sdr/sdr.y"
{
			currentParameter->type					=	TYPE_POINT;
			currentParameter->name					=	strdup(yyvsp[-4].string);
			currentParameter->defaultValue.array	=	new UDefaultVal[(int) yyvsp[-2].real];
			currentParameter->numItems				=	(int) yyvsp[-2].real;
			
			currentDefaultItem = currentParameter->defaultValue.array;
			numArrayItemsRemaining = currentParameter->numItems;
		;
    break;}
case 77:
#line 755 "../../../../src/sdr/sdr.y"
{
			currentParameter->type					=	TYPE_POINT;
			currentParameter->name					=	strdup(yyvsp[-3].string);
			currentParameter->defaultValue.array	=	new UDefaultVal[(int) yyvsp[-1].real];
			currentParameter->numItems				=	(int) yyvsp[-1].real;
			
			currentDefaultItem = currentParameter->defaultValue.array;
			for(int i=0;i<currentParameter->numItems;i++){
				currentDefaultItem[i].vector = new float[3];
				currentDefaultItem[i].vector[0] = 0;
				currentDefaultItem[i].vector[1] = 0;
				currentDefaultItem[i].vector[2] = 0;
			}
		;
    break;}
case 78:
#line 793 "../../../../src/sdr/sdr.y"
{
			currentParameter->container					=	CONTAINER_UNIFORM;
			currentParameter->type						=	TYPE_MATRIX;
			currentParameter->name						=	strdup(yyvsp[-19].string);
			currentParameter->defaultValue.matrix		=	new float[16];
			currentParameter->defaultValue.matrix[0]	=	yyvsp[-16].real;
			currentParameter->defaultValue.matrix[1]	=	yyvsp[-15].real;
			currentParameter->defaultValue.matrix[2]	=	yyvsp[-14].real;
			currentParameter->defaultValue.matrix[3]	=	yyvsp[-13].real;
			currentParameter->defaultValue.matrix[4]	=	yyvsp[-12].real;
			currentParameter->defaultValue.matrix[5]	=	yyvsp[-11].real;
			currentParameter->defaultValue.matrix[6]	=	yyvsp[-10].real;
			currentParameter->defaultValue.matrix[7]	=	yyvsp[-9].real;
			currentParameter->defaultValue.matrix[8]	=	yyvsp[-8].real;
			currentParameter->defaultValue.matrix[9]	=	yyvsp[-7].real;
			currentParameter->defaultValue.matrix[10]	=	yyvsp[-6].real;
			currentParameter->defaultValue.matrix[11]	=	yyvsp[-5].real;
			currentParameter->defaultValue.matrix[12]	=	yyvsp[-4].real;
			currentParameter->defaultValue.matrix[13]	=	yyvsp[-3].real;
			currentParameter->defaultValue.matrix[14]	=	yyvsp[-2].real;
			currentParameter->defaultValue.matrix[15]	=	yyvsp[-1].real;
			currentParameter->numItems					=	1;
		;
    break;}
case 79:
#line 821 "../../../../src/sdr/sdr.y"
{
			currentParameter->container					=	CONTAINER_UNIFORM;
			currentParameter->type						=	TYPE_MATRIX;
			currentParameter->name						=	strdup(yyvsp[-2].string);
			currentParameter->defaultValue.matrix		=	new float[16];
			currentParameter->defaultValue.matrix[0]	=	yyvsp[0].real;
			currentParameter->defaultValue.matrix[1]	=	0;
			currentParameter->defaultValue.matrix[2]	=	0;
			currentParameter->defaultValue.matrix[3]	=	0;
			currentParameter->defaultValue.matrix[4]	=	0;
			currentParameter->defaultValue.matrix[5]	=	yyvsp[0].real;
			currentParameter->defaultValue.matrix[6]	=	0;
			currentParameter->defaultValue.matrix[7]	=	0;
			currentParameter->defaultValue.matrix[8]	=	0;
			currentParameter->defaultValue.matrix[9]	=	0;
			currentParameter->defaultValue.matrix[10]	=	yyvsp[0].real;
			currentParameter->defaultValue.matrix[11]	=	0;
			currentParameter->defaultValue.matrix[12]	=	0;
			currentParameter->defaultValue.matrix[13]	=	0;
			currentParameter->defaultValue.matrix[14]	=	0;
			currentParameter->defaultValue.matrix[15]	=	yyvsp[0].real;
			currentParameter->numItems					=	1;
		;
    break;}
case 80:
#line 847 "../../../../src/sdr/sdr.y"
{
			currentParameter->container					=	CONTAINER_UNIFORM;
			currentParameter->type						=	TYPE_MATRIX;
			currentParameter->name						=	strdup(yyvsp[0].string);
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
		;
    break;}
case 81:
#line 877 "../../../../src/sdr/sdr.y"
{
			currentParameter->container					=	CONTAINER_UNIFORM;
			currentParameter->type						=	TYPE_MATRIX;
			currentParameter->name						=	strdup(yyvsp[-4].string);
			currentParameter->defaultValue.array		=	new UDefaultVal[(int) yyvsp[-2].real];
			currentParameter->numItems					=	(int) yyvsp[-2].real;
			
			currentDefaultItem = currentParameter->defaultValue.array;
			numArrayItemsRemaining = currentParameter->numItems;
		;
    break;}
case 83:
#line 894 "../../../../src/sdr/sdr.y"
{
			currentParameter->container					=	CONTAINER_UNIFORM;
			currentParameter->type						=	TYPE_MATRIX;
			currentParameter->name						=	strdup(yyvsp[-3].string);
			currentParameter->defaultValue.array		=	new UDefaultVal[(int) yyvsp[-1].real];
			currentParameter->numItems					=	(int) yyvsp[-1].real;
			
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
		;
    break;}
case 84:
#line 928 "../../../../src/sdr/sdr.y"
{
			if(numArrayItemsRemaining){
				sdrerror("wrong number of items in array initializer\n");
			}
		;
    break;}
case 85:
#line 955 "../../../../src/sdr/sdr.y"
{
			if(numArrayItemsRemaining){
				currentDefaultItem->matrix = new float[16];
				currentDefaultItem->matrix[0] = yyvsp[-16].real;
				currentDefaultItem->matrix[1] = yyvsp[-15].real;
				currentDefaultItem->matrix[2] = yyvsp[-14].real;
				currentDefaultItem->matrix[3] = yyvsp[-13].real;
				currentDefaultItem->matrix[4] = yyvsp[-12].real;
				currentDefaultItem->matrix[5] = yyvsp[-11].real;
				currentDefaultItem->matrix[6] = yyvsp[-10].real;
				currentDefaultItem->matrix[7] = yyvsp[-9].real;
				currentDefaultItem->matrix[8] = yyvsp[-8].real;
				currentDefaultItem->matrix[9] = yyvsp[-7].real;
				currentDefaultItem->matrix[10] = yyvsp[-6].real;
				currentDefaultItem->matrix[11] = yyvsp[-5].real;
				currentDefaultItem->matrix[12] = yyvsp[-4].real;
				currentDefaultItem->matrix[13] = yyvsp[-3].real;
				currentDefaultItem->matrix[14] = yyvsp[-2].real;
				currentDefaultItem->matrix[15] = yyvsp[-1].real;
				
				currentDefaultItem++;
				numArrayItemsRemaining--;
			}
			else{
				sdrerror("wrong number of items in array initializer\n");
			}
		;
    break;}
case 86:
#line 985 "../../../../src/sdr/sdr.y"
{
			if(numArrayItemsRemaining){
				currentDefaultItem->matrix = new float[16];
				currentDefaultItem->matrix[0] = yyvsp[0].real;
				currentDefaultItem->matrix[1] = 0;
				currentDefaultItem->matrix[2] = 0;
				currentDefaultItem->matrix[3] = 0;
				currentDefaultItem->matrix[4] = 0;
				currentDefaultItem->matrix[5] = yyvsp[0].real;
				currentDefaultItem->matrix[6] = 0;
				currentDefaultItem->matrix[7] = 0;
				currentDefaultItem->matrix[8] = 0;
				currentDefaultItem->matrix[9] = 0;
				currentDefaultItem->matrix[10] = yyvsp[0].real;
				currentDefaultItem->matrix[11] = 0;
				currentDefaultItem->matrix[12] = 0;
				currentDefaultItem->matrix[13] = 0;
				currentDefaultItem->matrix[14] = 0;
				currentDefaultItem->matrix[15] = 1;
				
				currentDefaultItem++;
				numArrayItemsRemaining--;
			}
		;
    break;}
case 99:
#line 1062 "../../../../src/sdr/sdr.y"
{
		;
    break;}
case 100:
#line 1070 "../../../../src/sdr/sdr.y"
{
		;
    break;}
case 101:
#line 1078 "../../../../src/sdr/sdr.y"
{
		;
    break;}
case 102:
#line 1086 "../../../../src/sdr/sdr.y"
{
		;
    break;}
case 103:
#line 1093 "../../../../src/sdr/sdr.y"
{
		;
    break;}
case 104:
#line 1101 "../../../../src/sdr/sdr.y"
{
		;
    break;}
case 105:
#line 1108 "../../../../src/sdr/sdr.y"
{
		;
    break;}
case 106:
#line 1116 "../../../../src/sdr/sdr.y"
{
		;
    break;}
case 107:
#line 1123 "../../../../src/sdr/sdr.y"
{
		;
    break;}
case 108:
#line 1131 "../../../../src/sdr/sdr.y"
{
		;
    break;}
case 109:
#line 1138 "../../../../src/sdr/sdr.y"
{
		;
    break;}
case 110:
#line 1146 "../../../../src/sdr/sdr.y"
{
		;
    break;}
case 111:
#line 1153 "../../../../src/sdr/sdr.y"
{
		;
    break;}
case 112:
#line 1161 "../../../../src/sdr/sdr.y"
{
		;
    break;}
case 113:
#line 1168 "../../../../src/sdr/sdr.y"
{
		;
    break;}
case 114:
#line 1176 "../../../../src/sdr/sdr.y"
{
		;
    break;}
case 119:
#line 1198 "../../../../src/sdr/sdr.y"
{
		;
    break;}
case 120:
#line 1204 "../../../../src/sdr/sdr.y"
{
		;
    break;}
case 121:
#line 1210 "../../../../src/sdr/sdr.y"
{
		;
    break;}
case 122:
#line 1214 "../../../../src/sdr/sdr.y"
{
		;
    break;}
case 123:
#line 1218 "../../../../src/sdr/sdr.y"
{
		;
    break;}
case 124:
#line 1225 "../../../../src/sdr/sdr.y"
{
		;
    break;}
case 125:
#line 1228 "../../../../src/sdr/sdr.y"
{
		;
    break;}
case 126:
#line 1235 "../../../../src/sdr/sdr.y"
{
		;
    break;}
case 127:
#line 1242 "../../../../src/sdr/sdr.y"
{
		;
    break;}
case 128:
#line 1248 "../../../../src/sdr/sdr.y"
{
		;
    break;}
case 129:
#line 1252 "../../../../src/sdr/sdr.y"
{
		;
    break;}
case 130:
#line 1256 "../../../../src/sdr/sdr.y"
{
		;
    break;}
case 131:
#line 1260 "../../../../src/sdr/sdr.y"
{
		;
    break;}
case 132:
#line 1270 "../../../../src/sdr/sdr.y"
{
		;
    break;}
case 133:
#line 1306 "../../../../src/sdr/sdr.y"
{
		;
    break;}
case 134:
#line 1312 "../../../../src/sdr/sdr.y"
{
		;
    break;}
}
   /* the action file gets copied in in place of this dollarsign */

  yyvsp -= yylen;
  yyssp -= yylen;
#ifdef YYLSP_NEEDED
  yylsp -= yylen;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

  *++yyvsp = yyval;

#ifdef YYLSP_NEEDED
  yylsp++;
  if (yylen == 0)
    {
      yylsp->first_line = yylloc.first_line;
      yylsp->first_column = yylloc.first_column;
      yylsp->last_line = (yylsp-1)->last_line;
      yylsp->last_column = (yylsp-1)->last_column;
      yylsp->text = 0;
    }
  else
    {
      yylsp->last_line = (yylsp+yylen-1)->last_line;
      yylsp->last_column = (yylsp+yylen-1)->last_column;
    }
#endif

  /* Now "shift" the result of the reduction.
     Determine what state that goes to,
     based on the state we popped back to
     and the rule number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTBASE] + *yyssp;
  if (yystate >= 0 && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTBASE];

  goto yynewstate;

yyerrlab:   /* here on detecting error */

  if (! yyerrstatus)
    /* If not already recovering from an error, report this error.  */
    {
      ++yynerrs;

#ifdef YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (yyn > YYFLAG && yyn < YYLAST)
	{
	  int size = 0;
	  char *msg;
	  int x, count;

	  count = 0;
	  /* Start X at -yyn if nec to avoid negative indexes in yycheck.  */
	  for (x = (yyn < 0 ? -yyn : 0);
	       x < (sizeof(yytname) / sizeof(char *)); x++)
	    if (yycheck[x + yyn] == x)
	      size += strlen(yytname[x]) + 15, count++;
	  msg = (char *) malloc(size + 15);
	  if (msg != 0)
	    {
	      strcpy(msg, "parse error");

	      if (count < 5)
		{
		  count = 0;
		  for (x = (yyn < 0 ? -yyn : 0);
		       x < (sizeof(yytname) / sizeof(char *)); x++)
		    if (yycheck[x + yyn] == x)
		      {
			strcat(msg, count == 0 ? ", expecting `" : " or `");
			strcat(msg, yytname[x]);
			strcat(msg, "'");
			count++;
		      }
		}
	      yyerror(msg);
	      free(msg);
	    }
	  else
	    yyerror ("parse error; also virtual memory exceeded");
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror("parse error");
    }

  goto yyerrlab1;
yyerrlab1:   /* here on error raised explicitly by an action */

  if (yyerrstatus == 3)
    {
      /* if just tried and failed to reuse lookahead token after an error, discard it.  */

      /* return failure if at end of input */
      if (yychar == YYEOF)
	YYABORT;

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Discarding token %d (%s).\n", yychar, yytname[yychar1]);
#endif

      yychar = YYEMPTY;
    }

  /* Else will try to reuse lookahead token
     after shifting the error token.  */

  yyerrstatus = 3;		/* Each real token shifted decrements this */

  goto yyerrhandle;

yyerrdefault:  /* current state does not do anything special for the error token. */

#if 0
  /* This is wrong; only states that explicitly want error tokens
     should shift them.  */
  yyn = yydefact[yystate];  /* If its default is to accept any token, ok.  Otherwise pop it.*/
  if (yyn) goto yydefault;
#endif

yyerrpop:   /* pop the current state because it cannot handle the error token */

  if (yyssp == yyss) YYABORT;
  yyvsp--;
  yystate = *--yyssp;
#ifdef YYLSP_NEEDED
  yylsp--;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "Error: state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

yyerrhandle:

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yyerrdefault;

  yyn += YYTERROR;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != YYTERROR)
    goto yyerrdefault;

  yyn = yytable[yyn];
  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrpop;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrpop;

  if (yyn == YYFINAL)
    YYACCEPT;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting error token, ");
#endif

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  yystate = yyn;
  goto yynewstate;
}
#line 1316 "../../../../src/sdr/sdr.y"

#include "lex.sdr.cpp"

int	slLineno	=	0;

///////////////////////////////////////////////////////////////////////
// Function				:	sdrerror
// Description			:	Parser error function
// Return Value			:
// Comments				:
void			sdrerror(char *s) {
	fprintf(stdout,"%s\n",s);
}


///////////////////////////////////////////////////////////////////////
// Function				:	sdrGet
// Description			:	Parse a shader
// Return Value			:
// Comments				:
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


