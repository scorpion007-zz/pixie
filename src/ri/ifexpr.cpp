
/*  A Bison parser, made from ifexpr.y
    by GNU Bison version 1.28  */

#define YYBISON 1  /* Identify Bison output.  */

#define yyparse ifparse
#define yylex iflex
#define yyerror iferror
#define yylval iflval
#define yychar ifchar
#define yydebug ifdebug
#define yynerrs ifnerrs
#define	IF_OPEN	257
#define	IF_CLOSE	258
#define	IF_PLUS	259
#define	IF_MINUS	260
#define	IF_MUL	261
#define	IF_DIV	262
#define	IF_MULMUL	263
#define	IF_AND	264
#define	IF_POW	265
#define	IF_OR	266
#define	IF_EQUAL	267
#define	IF_NEQUAL	268
#define	IF_LESSE	269
#define	IF_GREATERE	270
#define	IF_LESS	271
#define	IF_GREATER	272
#define	IF_ANDAND	273
#define	IF_OROR	274
#define	IF_NOT	275
#define	IF_DOLLAR	276
#define	IF_MATCH	277
#define	IF_DEFINED	278
#define	IF_CONCAT	279
#define	IF_COMMA	280
#define	IF_TEXT_VALUE	281
#define	IF_IDENTIFIER_VALUE	282
#define	IF_FLOAT_VALUE	283

#line 1 "ifexpr.y"

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
//  File				:	ifexpr.y
//  Classes				:	-
//  Description			:	Parser for the IF expressions
//
////////////////////////////////////////////////////////////////////////
#undef alloca
#include <string.h>

#include "common/os.h"
#include "config.h"
#include "error.h"
#include "rendererc.h"
#include "renderer.h"
#include "rendererContext.h"

int							iflex(void );		// Forward definition for stupid yacc
void						iferror(char *,...);

static	CRendererContext	*context	=	NULL;
static	int					result		=	0;	// 0 - FALSE
												// 1 - TRUE
												// 2 - error



	///////////////////////////////////////////////////////////////////////
	// Class				:	CExpr
	// Description			:	Holds an expression value
	// Comments				:
	class CExpr {
	public:
			EVariableType	type;
			const void		*value;
			float			floatValue;
			int				intValue;
			char			stringValue[128];	// HACK
	};

	///////////////////////////////////////////////////////////////////////
	// Function				:	getString
	// Description			:	Take the expression and form a string
	// Return Value			:	The string
	// Comments				:
	static	inline	const char	*getString(const CExpr &expr) {	
		const void 	*value = expr.value;
		
		switch (expr.type) {
			case TYPE_FLOAT:
			case TYPE_COLOR:
			case TYPE_VECTOR:
			case TYPE_NORMAL:
			case TYPE_POINT:
			case TYPE_MATRIX:
			case TYPE_QUAD:
			case TYPE_DOUBLE:
				break;
			case TYPE_STRING:
				if (value == NULL)	return (const char *) expr.stringValue;
				else				return (const char *) value;
			case TYPE_INTEGER:
			case TYPE_BOOLEAN:
			default:
				break;
		};
		
		error(CODE_SYNTAX,"Unable to cast a string in the epxression");
		
		return "__nonsense__";
	}


	///////////////////////////////////////////////////////////////////////
	// Function				:	getFloat
	// Description			:	Take the expression and form a float
	// Return Value			:	The float
	// Comments				:
	static	inline	float		getFloat(const CExpr &expr) {
		const void	*value = expr.value;
				
		switch (expr.type) {
			case TYPE_FLOAT:
				if (value == NULL)	return expr.floatValue;
				else				return *((float *) value);
			case TYPE_COLOR:
			case TYPE_VECTOR:
			case TYPE_NORMAL:
			case TYPE_POINT:
			case TYPE_MATRIX:
			case TYPE_QUAD:
			case TYPE_DOUBLE:
			case TYPE_STRING:
				break;
			case TYPE_INTEGER:
			case TYPE_BOOLEAN:
				if (value == NULL)	return (float) expr.intValue;
				else				return (float) *((int *) value);
			default:
				break;
		};
		
		error(CODE_SYNTAX,"Unable to cast a float in the epxression");
		
		return 0;
	}

	///////////////////////////////////////////////////////////////////////
	// Function				:	getInt
	// Description			:	Take the expression and form an int
	// Return Value			:	The int
	// Comments				:
	static	inline	int		getInt(const CExpr &expr) {
		const void	*value = expr.value;
		
		switch (expr.type) {
			case TYPE_FLOAT:
				if (value == NULL)	return (int) expr.floatValue;
				else				return (int) *((float *) value);
			case TYPE_COLOR:
			case TYPE_VECTOR:
			case TYPE_NORMAL:
			case TYPE_POINT:
			case TYPE_MATRIX:
			case TYPE_QUAD:
			case TYPE_DOUBLE:
			case TYPE_STRING:
				break;
			case TYPE_INTEGER:
			case TYPE_BOOLEAN:
				if (value == NULL)	return expr.intValue;
				else				return *((int *) value);
			default:
				break;
		};
		
		error(CODE_SYNTAX,"Unable to cast a integer in the epxression");
		
		return 0;
	}

	///////////////////////////////////////////////////////////////////////
	// Function				:	setFloat
	// Description			:	Create a float expression
	// Return Value			:
	// Comments				:
	static	inline	void		setFloat(CExpr &expr,float val) {
		expr.type		=	TYPE_FLOAT;
		expr.value		=	NULL;
		expr.floatValue	=	val;
	}

	///////////////////////////////////////////////////////////////////////
	// Function				:	setInt
	// Description			:	Create an int expression
	// Return Value			:
	// Comments				:
	static	inline	void		setInt(CExpr &expr,int val) {
		expr.type	=	TYPE_INTEGER;
		expr.value	=	NULL;
		expr.intValue	=	val;
	}

	///////////////////////////////////////////////////////////////////////
	// Function				:	findExpr
	// Description			:	Find a float expression
	// Return Value			:
	// Comments				:
	static	void				findExpr(CExpr &expr,const char *name,const char *decl=NULL,int attributes=FALSE,int typeSet=FALSE) {
		const char	*p;
		
		if (strncmp(name,"Attribute:",10) == 0) {
			name	+=	10;
			
			findExpr(expr,name,NULL,TRUE,TRUE);
		} else if (strncmp(name,"Option:",7) == 0) {
			name	+=	7;
			
			findExpr(expr,name,NULL,FALSE,TRUE);
		} else if ((p = strchr(name,':')) != NULL) {
			char category[256];		
				
			assert((p-name) < 255);				// Sanity check
			strncpy(category,name,p-name);		// Copy the category
			category[p-name]		=	'\0';	// Make sure it terminates
			
			findExpr(expr,p+1,category,attributes,typeSet);
		} else {
			
			if (attributes) {
				// Lookup the attributes
				CAttributes	*cAttributes	=	context->getAttributes(TRUE);
				
				if (cAttributes->find(name,decl,expr.type,expr.value,expr.intValue,expr.floatValue) == FALSE) {
					if (typeSet == FALSE) {
						COptions	*cOptions		=	context->getOptions();
						if (cOptions->find(name,decl,expr.type,expr.value,expr.intValue,expr.floatValue) == FALSE) {
							error(CODE_BADTOKEN,"Unable to find variable \"%s\"\n",name);
							result	=	FALSE;
						}
					} else {
						error(CODE_BADTOKEN,"Unable to find variable \"%s\"\n",name);
						result	=	FALSE;
					}
				}
			} else {
				// Lookup the options
				COptions	*cOptions		=	context->getOptions();
				
				if (cOptions->find(name,decl,expr.type,expr.value,expr.intValue,expr.floatValue) == FALSE) {
					if (typeSet == FALSE) {
						CAttributes	*cAttributes	=	context->getAttributes(TRUE);
						if (cAttributes->find(name,decl,expr.type,expr.value,expr.intValue,expr.floatValue) == FALSE) {
							error(CODE_BADTOKEN,"Unable to find variable \"%s\"\n",name);
							result	=	FALSE;
						}
					} else {
						error(CODE_BADTOKEN,"Unable to find variable \"%s\"\n",name);
						result	=	FALSE;
					}
				}
			}
		}
	}



#line 252 "ifexpr.y"
typedef union slval {
	char	string[PARSER_MAX_STRING_SIZE];
	CExpr	expr;
	float	real;
} YYSTYPE;
#include <stdio.h>

#ifndef __cplusplus
#ifndef __STDC__
#define const
#endif
#endif



#define	YYFINAL		58
#define	YYFLAG		-32768
#define	YYNTBASE	30

#define YYTRANSLATE(x) ((unsigned)(x) <= 283 ? yytranslate[x] : 32)

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
     2,     2,     2,     2,     2,     1,     3,     4,     5,     6,
     7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
    17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
    27,    28,    29
};

#if YYDEBUG != 0
static const short yyprhs[] = {     0,
     0,     2,     5,    10,    12,    14,    18,    22,    26,    30,
    34,    38,    42,    46,    50,    54,    58,    62,    66,    70,
    74,    78,    81,    85,    90
};

static const short yyrhs[] = {    31,
     0,    22,    28,     0,    22,     3,    31,     4,     0,    29,
     0,    27,     0,    31,     5,    31,     0,    31,     6,    31,
     0,    31,     7,    31,     0,    31,     8,    31,     0,    31,
    10,    31,     0,    31,    12,    31,     0,    31,    11,    31,
     0,    31,    13,    31,     0,    31,    14,    31,     0,    31,
    18,    31,     0,    31,    17,    31,     0,    31,    16,    31,
     0,    31,    15,    31,     0,    31,    23,    31,     0,    31,
    19,    31,     0,    31,    20,    31,     0,    21,    31,     0,
     3,    31,     4,     0,    24,     3,    31,     4,     0,    25,
     3,    31,    26,    31,     4,     0
};

#endif

#if YYDEBUG != 0
static const short yyrline[] = { 0,
   306,   318,   326,   337,   342,   349,   358,   365,   372,   379,
   388,   395,   402,   415,   426,   437,   448,   459,   470,   480,
   489,   496,   502,   511,   521
};
#endif


#if YYDEBUG != 0 || defined (YYERROR_VERBOSE)

static const char * const yytname[] = {   "$","error","$undefined.","IF_OPEN",
"IF_CLOSE","IF_PLUS","IF_MINUS","IF_MUL","IF_DIV","IF_MULMUL","IF_AND","IF_POW",
"IF_OR","IF_EQUAL","IF_NEQUAL","IF_LESSE","IF_GREATERE","IF_LESS","IF_GREATER",
"IF_ANDAND","IF_OROR","IF_NOT","IF_DOLLAR","IF_MATCH","IF_DEFINED","IF_CONCAT",
"IF_COMMA","IF_TEXT_VALUE","IF_IDENTIFIER_VALUE","IF_FLOAT_VALUE","start","ifExpr", NULL
};
#endif

static const short yyr1[] = {     0,
    30,    31,    31,    31,    31,    31,    31,    31,    31,    31,
    31,    31,    31,    31,    31,    31,    31,    31,    31,    31,
    31,    31,    31,    31,    31
};

static const short yyr2[] = {     0,
     1,     2,     4,     1,     1,     3,     3,     3,     3,     3,
     3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
     3,     2,     3,     4,     6
};

static const short yydefact[] = {     0,
     0,     0,     0,     0,     0,     5,     4,     1,     0,    22,
     0,     2,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    23,     0,     0,     0,     6,     7,     8,     9,    10,    12,
    11,    13,    14,    18,    17,    16,    15,    20,    21,    19,
     3,    24,     0,     0,    25,     0,     0,     0
};

static const short yydefgoto[] = {    56,
     8
};

static const short yypact[] = {    29,
    29,    29,     2,     0,     1,-32768,-32768,   156,    77,   -21,
    29,-32768,    29,    29,    29,    29,    29,    29,    29,    29,
    29,    29,    29,    29,    29,    29,    29,    29,    29,    29,
-32768,    97,   117,    54,   288,    26,   308,   294,    20,   -21,
   313,   175,   194,   232,   213,   270,   251,    24,   268,-32768,
-32768,-32768,    29,   137,-32768,     6,     7,-32768
};

static const short yypgoto[] = {-32768,
    -1
};


#define	YYLAST		336


static const short yytable[] = {     9,
    10,    30,    13,    14,    11,    57,    58,     0,     0,    32,
     0,    33,    34,    35,    36,    37,    38,    39,    40,    41,
    42,    43,    44,    45,    46,    47,    48,    49,    50,    12,
    20,     1,    17,    18,    20,    19,    20,    21,    28,    29,
     0,     0,    30,     0,    28,    29,    30,     0,    30,     2,
     3,    54,     4,     5,     0,     6,     0,     7,    15,    16,
    17,    18,     0,    19,    20,    21,    22,    23,    24,    25,
    26,    27,    28,    29,     0,     0,    30,     0,     0,    53,
    31,    15,    16,    17,    18,     0,    19,    20,    21,    22,
    23,    24,    25,    26,    27,    28,    29,     0,     0,    30,
    51,    15,    16,    17,    18,     0,    19,    20,    21,    22,
    23,    24,    25,    26,    27,    28,    29,     0,     0,    30,
    52,    15,    16,    17,    18,     0,    19,    20,    21,    22,
    23,    24,    25,    26,    27,    28,    29,     0,     0,    30,
    55,    15,    16,    17,    18,     0,    19,    20,    21,    22,
    23,    24,    25,    26,    27,    28,    29,     0,     0,    30,
    15,    16,    17,    18,     0,    19,    20,    21,    22,    23,
    24,    25,    26,    27,    28,    29,     0,     0,    30,    15,
    16,    17,    18,     0,    19,    20,    21,     0,    23,    24,
    25,    26,    27,    28,    29,     0,     0,    30,    15,    16,
    17,    18,     0,    19,    20,    21,     0,     0,    24,    25,
    26,    27,    28,    29,     0,     0,    30,    15,    16,    17,
    18,     0,    19,    20,    21,     0,     0,    24,     0,    26,
    27,    28,    29,     0,     0,    30,    15,    16,    17,    18,
     0,    19,    20,    21,     0,     0,     0,     0,    26,    27,
    28,    29,     0,     0,    30,    15,    16,    17,    18,     0,
    19,    20,    21,     0,     0,     0,     0,    26,     0,    28,
    29,     0,     0,    30,    15,    16,    17,    18,    20,    19,
    20,    21,     0,     0,     0,     0,    28,     0,    28,    29,
    30,     0,    30,    16,    17,    18,     0,    19,    20,    21,
    17,     0,     0,    19,    20,    21,    28,    29,     0,     0,
    30,     0,    28,    29,     0,     0,    30,    19,    20,    21,
     0,     0,    19,    20,     0,     0,    28,    29,     0,     0,
    30,    28,    29,     0,     0,    30
};

static const short yycheck[] = {     1,
     2,    23,     3,     3,     3,     0,     0,    -1,    -1,    11,
    -1,    13,    14,    15,    16,    17,    18,    19,    20,    21,
    22,    23,    24,    25,    26,    27,    28,    29,    30,    28,
    11,     3,     7,     8,    11,    10,    11,    12,    19,    20,
    -1,    -1,    23,    -1,    19,    20,    23,    -1,    23,    21,
    22,    53,    24,    25,    -1,    27,    -1,    29,     5,     6,
     7,     8,    -1,    10,    11,    12,    13,    14,    15,    16,
    17,    18,    19,    20,    -1,    -1,    23,    -1,    -1,    26,
     4,     5,     6,     7,     8,    -1,    10,    11,    12,    13,
    14,    15,    16,    17,    18,    19,    20,    -1,    -1,    23,
     4,     5,     6,     7,     8,    -1,    10,    11,    12,    13,
    14,    15,    16,    17,    18,    19,    20,    -1,    -1,    23,
     4,     5,     6,     7,     8,    -1,    10,    11,    12,    13,
    14,    15,    16,    17,    18,    19,    20,    -1,    -1,    23,
     4,     5,     6,     7,     8,    -1,    10,    11,    12,    13,
    14,    15,    16,    17,    18,    19,    20,    -1,    -1,    23,
     5,     6,     7,     8,    -1,    10,    11,    12,    13,    14,
    15,    16,    17,    18,    19,    20,    -1,    -1,    23,     5,
     6,     7,     8,    -1,    10,    11,    12,    -1,    14,    15,
    16,    17,    18,    19,    20,    -1,    -1,    23,     5,     6,
     7,     8,    -1,    10,    11,    12,    -1,    -1,    15,    16,
    17,    18,    19,    20,    -1,    -1,    23,     5,     6,     7,
     8,    -1,    10,    11,    12,    -1,    -1,    15,    -1,    17,
    18,    19,    20,    -1,    -1,    23,     5,     6,     7,     8,
    -1,    10,    11,    12,    -1,    -1,    -1,    -1,    17,    18,
    19,    20,    -1,    -1,    23,     5,     6,     7,     8,    -1,
    10,    11,    12,    -1,    -1,    -1,    -1,    17,    -1,    19,
    20,    -1,    -1,    23,     5,     6,     7,     8,    11,    10,
    11,    12,    -1,    -1,    -1,    -1,    19,    -1,    19,    20,
    23,    -1,    23,     6,     7,     8,    -1,    10,    11,    12,
     7,    -1,    -1,    10,    11,    12,    19,    20,    -1,    -1,
    23,    -1,    19,    20,    -1,    -1,    23,    10,    11,    12,
    -1,    -1,    10,    11,    -1,    -1,    19,    20,    -1,    -1,
    23,    19,    20,    -1,    -1,    23
};
/* -*-C-*-  Note some compilers choke on comments on `#line' lines.  */
#line 3 "/usr/share/bison.simple"
/* This file comes from bison-1.28.  */

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
   Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

/* This is the parser code that is written into each bison parser
  when the %semantic_parser declaration is not specified in the grammar.
  It was written by Richard Stallman by simplifying the hairy parser
  used when %semantic_parser is specified.  */

#ifndef YYSTACK_USE_ALLOCA
#ifdef alloca
#define YYSTACK_USE_ALLOCA
#else /* alloca not defined */
#ifdef __GNUC__
#define YYSTACK_USE_ALLOCA
#define alloca __builtin_alloca
#else /* not GNU C.  */
#if (!defined (__STDC__) && defined (sparc)) || defined (__sparc__) || defined (__sparc) || defined (__sgi) || (defined (__sun) && defined (__i386))
#define YYSTACK_USE_ALLOCA
#include <alloca.h>
#else /* not sparc */
/* We think this test detects Watcom and Microsoft C.  */
/* This used to test MSDOS, but that is a bad idea
   since that symbol is in the user namespace.  */
#if (defined (_MSDOS) || defined (_MSDOS_)) && !defined (__TURBOC__)
#if 0 /* No need for malloc.h, which pollutes the namespace;
	 instead, just don't use alloca.  */
#include <malloc.h>
#endif
#else /* not MSDOS, or __TURBOC__ */
#if defined(_AIX)
/* I don't know what this was needed for, but it pollutes the namespace.
   So I turned it off.   rms, 2 May 1997.  */
/* #include <malloc.h>  */
 #pragma alloca
#define YYSTACK_USE_ALLOCA
#else /* not MSDOS, or __TURBOC__, or _AIX */
#if 0
#ifdef __hpux /* haible@ilog.fr says this works for HPUX 9.05 and up,
		 and on HPUX 10.  Eventually we can turn this on.  */
#define YYSTACK_USE_ALLOCA
#define alloca __builtin_alloca
#endif /* __hpux */
#endif
#endif /* not _AIX */
#endif /* not MSDOS, or __TURBOC__ */
#endif /* not sparc */
#endif /* not GNU C */
#endif /* alloca not defined */
#endif /* YYSTACK_USE_ALLOCA not defined */

#ifdef YYSTACK_USE_ALLOCA
#define YYSTACK_ALLOC alloca
#else
#define YYSTACK_ALLOC malloc
#endif

/* Note: there must be only one dollar sign in this file.
   It is replaced by the list of actions, each action
   as one case of the switch.  */

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		-2
#define YYEOF		0
#define YYACCEPT	goto yyacceptlab
#define YYABORT 	goto yyabortlab
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

/* Define __yy_memcpy.  Note that the size argument
   should be passed with type unsigned int, because that is what the non-GCC
   definitions require.  With GCC, __builtin_memcpy takes an arg
   of type size_t, but it can handle unsigned int.  */

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
     unsigned int count;
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
__yy_memcpy (char *to, char *from, unsigned int count)
{
  register char *t = to;
  register char *f = from;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#endif
#endif

#line 217 "/usr/share/bison.simple"

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

/* Prevent warning if -Wstrict-prototypes.  */
#ifdef __GNUC__
#ifdef YYPARSE_PARAM
int yyparse (void *);
#else
int yyparse (void);
#endif
#endif

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
  int yyfree_stacks = 0;

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
	  if (yyfree_stacks)
	    {
	      free (yyss);
	      free (yyvs);
#ifdef YYLSP_NEEDED
	      free (yyls);
#endif
	    }
	  return 2;
	}
      yystacksize *= 2;
      if (yystacksize > YYMAXDEPTH)
	yystacksize = YYMAXDEPTH;
#ifndef YYSTACK_USE_ALLOCA
      yyfree_stacks = 1;
#endif
      yyss = (short *) YYSTACK_ALLOC (yystacksize * sizeof (*yyssp));
      __yy_memcpy ((char *)yyss, (char *)yyss1,
		   size * (unsigned int) sizeof (*yyssp));
      yyvs = (YYSTYPE *) YYSTACK_ALLOC (yystacksize * sizeof (*yyvsp));
      __yy_memcpy ((char *)yyvs, (char *)yyvs1,
		   size * (unsigned int) sizeof (*yyvsp));
#ifdef YYLSP_NEEDED
      yyls = (YYLTYPE *) YYSTACK_ALLOC (yystacksize * sizeof (*yylsp));
      __yy_memcpy ((char *)yyls, (char *)yyls1,
		   size * (unsigned int) sizeof (*yylsp));
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

case 1:
#line 307 "ifexpr.y"
{
					// If no result set so far
					if (result == 2) {
					
						////////////////////////////////////////////////////////////////////
						// Compute the value of the expression
						if (yyvsp[0].expr.type == TYPE_STRING)	result	=	TRUE;
						else						result	=	(getFloat(yyvsp[0].expr) != 0);
					}
				;
    break;}
case 2:
#line 322 "ifexpr.y"
{
					// Find the variable here
					findExpr(yyval.expr,yyvsp[0].string);
				;
    break;}
case 3:
#line 331 "ifexpr.y"
{
					// FIXME: This is wrong. What are we supposed to do here ?
					
					// Find the variable here
					findExpr(yyval.expr,getString(yyvsp[-1].expr));
				;
    break;}
case 4:
#line 339 "ifexpr.y"
{					
					setFloat(yyval.expr,yyvsp[0].real);
				;
    break;}
case 5:
#line 344 "ifexpr.y"
{
					yyval.expr.type		=	TYPE_STRING;
					yyval.expr.value	=	NULL;
					strcpy(yyval.expr.stringValue,yyvsp[0].string);
				;
    break;}
case 6:
#line 355 "ifexpr.y"
{
					setFloat(yyval.expr,getFloat(yyvsp[-2].expr) + getFloat(yyvsp[0].expr));
				;
    break;}
case 7:
#line 362 "ifexpr.y"
{
					setFloat(yyval.expr,getFloat(yyvsp[-2].expr) - getFloat(yyvsp[0].expr));
				;
    break;}
case 8:
#line 369 "ifexpr.y"
{
					setFloat(yyval.expr,getFloat(yyvsp[-2].expr) * getFloat(yyvsp[0].expr));
				;
    break;}
case 9:
#line 376 "ifexpr.y"
{
					setFloat(yyval.expr,getFloat(yyvsp[-2].expr) / getFloat(yyvsp[0].expr));
				;
    break;}
case 10:
#line 385 "ifexpr.y"
{
					setInt(yyval.expr,getInt(yyvsp[-2].expr) & getInt(yyvsp[0].expr));
				;
    break;}
case 11:
#line 392 "ifexpr.y"
{
					setInt(yyval.expr,getInt(yyvsp[-2].expr) | getInt(yyvsp[0].expr));
				;
    break;}
case 12:
#line 399 "ifexpr.y"
{
					setInt(yyval.expr,getInt(yyvsp[-2].expr) ^ getInt(yyvsp[0].expr));
				;
    break;}
case 13:
#line 408 "ifexpr.y"
{
					if (yyvsp[-2].expr.type == TYPE_STRING || yyvsp[0].expr.type == TYPE_STRING) {
						setInt(yyval.expr,strcmp(getString(yyvsp[-2].expr),getString(yyvsp[0].expr)) == 0);
					} else {
						setInt(yyval.expr,getFloat(yyvsp[-2].expr) == getFloat(yyvsp[0].expr));
					}
				;
    break;}
case 14:
#line 419 "ifexpr.y"
{
					if (yyvsp[-2].expr.type == TYPE_STRING || yyvsp[0].expr.type == TYPE_STRING) {
						setInt(yyval.expr,strcmp(getString(yyvsp[-2].expr),getString(yyvsp[0].expr)) != 0);
					} else {
						setInt(yyval.expr,getFloat(yyvsp[-2].expr) != getFloat(yyvsp[0].expr));
					}
				;
    break;}
case 15:
#line 430 "ifexpr.y"
{
					if (yyvsp[-2].expr.type == TYPE_STRING || yyvsp[0].expr.type == TYPE_STRING) {
						setInt(yyval.expr,strcmp(getString(yyvsp[-2].expr),getString(yyvsp[0].expr)) > 0);
					} else {
						setInt(yyval.expr,getFloat(yyvsp[-2].expr) > getFloat(yyvsp[0].expr));
					}
				;
    break;}
case 16:
#line 441 "ifexpr.y"
{
					if (yyvsp[-2].expr.type == TYPE_STRING || yyvsp[0].expr.type == TYPE_STRING) {
						setInt(yyval.expr,strcmp(getString(yyvsp[-2].expr),getString(yyvsp[0].expr)) < 0);
					} else {
						setInt(yyval.expr,getFloat(yyvsp[-2].expr) < getFloat(yyvsp[0].expr));
					}
				;
    break;}
case 17:
#line 452 "ifexpr.y"
{
					if (yyvsp[-2].expr.type == TYPE_STRING || yyvsp[0].expr.type == TYPE_STRING) {
						setInt(yyval.expr,strcmp(getString(yyvsp[-2].expr),getString(yyvsp[0].expr)) >= 0);
					} else {
						setInt(yyval.expr,getFloat(yyvsp[-2].expr) >= getFloat(yyvsp[0].expr));
					}
				;
    break;}
case 18:
#line 463 "ifexpr.y"
{
					if (yyvsp[-2].expr.type == TYPE_STRING || yyvsp[0].expr.type == TYPE_STRING) {
						setInt(yyval.expr,strcmp(getString(yyvsp[-2].expr),getString(yyvsp[0].expr)) <= 0);
					} else {
						setInt(yyval.expr,getFloat(yyvsp[-2].expr) <= getFloat(yyvsp[0].expr));
					}
				;
    break;}
case 19:
#line 476 "ifexpr.y"
{
					// FIXME: Implement pattern matching
					setInt(yyval.expr,strcmp(getString(yyvsp[-2].expr),getString(yyvsp[0].expr)) == 0);
				;
    break;}
case 20:
#line 486 "ifexpr.y"
{
					setInt(yyval.expr,getInt(yyvsp[-2].expr) && getInt(yyvsp[0].expr));
				;
    break;}
case 21:
#line 493 "ifexpr.y"
{
					setInt(yyval.expr,getInt(yyvsp[-2].expr) || getInt(yyvsp[0].expr));
				;
    break;}
case 22:
#line 499 "ifexpr.y"
{
					setInt(yyval.expr,! getInt(yyvsp[0].expr));
				;
    break;}
case 23:
#line 508 "ifexpr.y"
{
					yyval.expr	=	yyvsp[-1].expr;
				;
    break;}
case 24:
#line 518 "ifexpr.y"
{
					setInt(yyval.expr,CRenderer::retrieveVariable(getString(yyvsp[-1].expr)) != NULL);
				;
    break;}
case 25:
#line 530 "ifexpr.y"
{
					yyval.expr.type		=	TYPE_STRING;
					yyval.expr.value	=	yyval.expr.stringValue;
					strcpy(yyval.expr.stringValue,getString(yyvsp[-3].expr));
					strcat(yyval.expr.stringValue,getString(yyvsp[-1].expr));
				;
    break;}
}
   /* the action file gets copied in in place of this dollarsign */
#line 543 "/usr/share/bison.simple"

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

 yyacceptlab:
  /* YYACCEPT comes here.  */
  if (yyfree_stacks)
    {
      free (yyss);
      free (yyvs);
#ifdef YYLSP_NEEDED
      free (yyls);
#endif
    }
  return 0;

 yyabortlab:
  /* YYABORT comes here.  */
  if (yyfree_stacks)
    {
      free (yyss);
      free (yyvs);
#ifdef YYLSP_NEEDED
      free (yyls);
#endif
    }
  return 1;
}
#line 538 "ifexpr.y"


#include "lex.if.cpp"


///////////////////////////////////////////////////////////////////////
// Function				:	ifParse
// Description			:	Parse an if statement
// Return Value			:	TRUE/FALSE
// Comments				:
int		CRendererContext::ifParse(const char *expr) {
	YY_BUFFER_STATE savedState	=	YY_CURRENT_BUFFER;		// Save the old buffer
	YY_BUFFER_STATE	newState;

	// Save the necessary info
	context			=	this;
	result			=	2;

	newState		=	if_scan_string(expr);				// Create a new buffer
	ifparse();												// Scan the buffer
	if_delete_buffer(newState);								// Ditch the buffer

	if_switch_to_buffer( savedState );						// Switch to the old buffer

	return result;
}

///////////////////////////////////////////////////////////////////////
// Function				:	dsoerror
// Description			:	Count the parse errors
// Return Value			:
// Comments				:
void	iferror(char *,...) {
	// What do we do in the case of an error ?
	warning(CODE_BADTOKEN,"Condition parse error\n");
}






