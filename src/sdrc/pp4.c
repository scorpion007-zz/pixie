/************************************************************************/
/*									*/
/*	File:	pp4.c							*/
/*									*/
/*	Token processing and related functions.				*/
/*									*/
/*	Written by:							*/
/*			Gary Oliver					*/
/*			3420 NW Elmwood Dr.				*/
/*			PO Box 826					*/
/*			Corvallis, Oregon 97339				*/
/*			(503)758-5549					*/
/*	Maintained by:							*/
/*			Kirk Bailey					*/
/*			Logical Systems					*/
/*			P.O. Box 1702					*/
/*			Corvallis, OR 97339				*/
/*			(503)753-9051					*/
/*									*/
/*	This program is hereby placed in the public domain.  In		*/
/*	contrast to other claims of "public domain", this means no	*/
/*	copyright is claimed and you may do anything you like with PP,	*/
/*	including selling it!  As a gesture of courtesy, please retain	*/
/*	the authorship information in the source code and		*/
/*	documentation.							*/
/*									*/
/*	Functions defined within this module:				*/
/*									*/
/*		addstr		Add a string to end of another string.	*/
/*		getnstoken	Get next non-space token.		*/
/*		gettoken	Get next token.				*/
/*		istype		Return boolean for char type mask.	*/
/*		memmov		Move bytes from place to place (MOVMEM)	*/
/*		pbcstr		Push back a copied string.		*/
/*		pbstr		Push back a string.			*/
/*		pushback	Push back a single character.		*/
/*		puttoken	Write a token to Output file.		*/
/*		type		Return type of token.			*/
/*									*/
/************************************************************************/

#include	"pp.h"
#include	"ppext.h"

/************************************************************************/
/*									*/
/*	addstr								*/
/*									*/
/*	Add a string to a buffer, test a limit and print a message	*/
/*	if the length of the new string would exceed the limit.		*/
/*									*/
/*	The error message will not be printed if a previous message	*/
/*	at the same address was printed.  A successful addstr() will	*/
/*	clear this state.  The logic will fail, however, if an error	*/
/*	is detected on one call, with a message printed, and then on	*/
/*	a next, unrelated call, the same msg is passed.  This can	*/
/*	be bypassed by insuring that the output buffer (old) is at	*/
/*	least twice (+1 byte) the size of the input (new) buffer.	*/
/*	For token building, the output buffer must be at least twice	*/
/*	(+1) the size of the token input buffer to insure that at	*/
/*	least ONE successful call to addstr can be made for each	*/
/*	time a string is to be built.					*/
/*									*/
/************************************************************************/

char *
addstr(old,limit,msg,new)
	char			*old;
	char			*limit;
	char			*msg;
	char			*new;
	{
	static	char		*origmsg = 0;

	register char		*o;
	register char		*n;

	if((old + strlen(new)) >= limit)
		{
		if(msg != origmsg)
			{
			/* Don't print multiple messages */
			non_fatal(msg,"");
			}

		origmsg = msg;
		return (old);
		}
	else
		{
		origmsg = NULL;		/* Clear the error condition */
		o = old;
		n = new;
		while((*o++ = *n++) != '\0')
			;		/* Copy strings */
		return (o-1);		/* Next char pos in output string */
		}
	}

/************************************************************************/
/*									*/
/*	getnstoken							*/
/*									*/
/*	Get next non-space token.					*/
/*									*/
/************************************************************************/

int
getnstoken(f)
	int			f;
	{
	register	int	t;

	while(istype(t = gettoken(f),C_W) && (t != '\n'))
		;			/* Skip space tokens but ! newlines */
	return (t);			/* Last token read */
	}

/************************************************************************/
/*									*/
/*	gettoken							*/
/*									*/
/*	Get alphanumeric string or single non-alpha for define		*/
/*									*/
/************************************************************************/

#ifdef	MSC_OPT
#pragma	optimize("e",off)		/* Disable global reg optimizing */
#pragma	optimize("g",off)		/* Disable global common subs */
#pragma	optimize("l",off)		/* Disable loop optimizations */
#endif	/* MSC_OPT */

int
gettoken(f)
	int			f;
	{
	register char		ch;
	register int		comment_level;
	register int		fail;
	register int		nt;
	register int		numstate;
	register char		*p;
	register int		t;
	register int		tmask;

/*	Define numstate values:						*/
#define	F_INTPART	0		/* numstate for integer part	*/
#define	F_FRAC		1		/* fractional part		*/
#define	F_EXPSIGN	2		/* exponent sign test		*/
#define	F_EXP		3		/* exponent digits		*/
#define	F_LAST		4		/* after occurrance of f|F|l|L	*/

#if	DEBUG
	if(Debug) printf("gettoken: ");
#endif	/* DEBUG */

	p = Token;
	t = nextch();
	Token[0] = t;

	Tokenfile = Filelevel;		/* Remember file number and	*/
	Tokenline = LLine;		/* Line number for this token	*/

	if(istype(t,C_L|C_D|C_W))
		{
		if(istype(t,C_L))
			{
			for(p = &Token[1]; p < &Token[TOKENSIZE]; p++)
				{
				t = nextch();
				*p = t;
				if(! istype(t,C_L|C_D))
					break;
				}
			}
		else if(istype(t,C_D))
			{
			if(t == '0')
				{
				/* Possible octal/hex numeric token */
				t = nextch();	/* Get next one */
				*++p = t;	/* Store into token buffer */

				if((t == 'x') || (t == 'X'))
					tmask = C_X;	/* Only hex digits */
				else if(istype(t,C_D))
/* 0..9 (8 & 9 are "octal" digits) */	tmask = C_D;
				else
					tmask = 0;	/* Not part of #'s */

				while((p < &Token[TOKENSIZE]) && (tmask != 0))
					{
					t = nextch();
					*++p = t;
					if(! istype(t,tmask))
						tmask = 0;
					}

				if((t == 'l') || (t == 'L') || (t == 'u') ||
					(t == 'U'))
					{
/*
 *	Last was a numeric terminator -- look ahead one char.
 */
					t = nextch();
/* Get next token for later refetch */	*++p = t;
					}
				}
			else
				{
				numstate = F_INTPART;
				fail = FALSE;
				for(p = &Token[1]; p < &Token[TOKENSIZE] &&
					(! fail); /*none*/ )
					{
					t = nextch();
					*p = t;
					switch(numstate)
						{
						case F_INTPART:
					if(istype(t,C_D))
						break;
					else if(t == '.')
						{
						numstate = F_FRAC;
						break;
						}
/*
 *	Fall thru to fraction test.  If t is not 'e|E', it will bail out.
 */

						case F_FRAC:
					if(istype(t,C_D))
/* Fraction ok so far */			break;
					else if((t == 'e') || (t == 'E'))
						{
/* Test sign */					numstate = F_EXPSIGN;
						break;
						}
					else if((t == 'l') || (t == 'L') ||
						(t == 'f') || (t == 'F'))
						{
						numstate = F_LAST;
						break;
						}

					fail = TRUE;	/* Failure */
					continue;

						case F_EXPSIGN:
					if((t == '+') || (t == '-') ||
						istype(t,C_D))
						{
						numstate = F_EXP;
						break;
						}
					fail = TRUE;
/* Error here -- loop fails */		continue;

						case F_EXP:
					if(istype(t,C_D))
						break;	/* Digits ok */

					if((t == 'f') || (t == 'F'))
						{
						numstate = F_LAST;
/* Dummy state to end it */			break;
						}
					fail = TRUE;
/* Error -- loop will fail */		continue;
				    
						case F_LAST:
					fail = TRUE;	/* Force failure */
					continue;	/* after an f|F|l|L */
						}
/* Advance char pointer into Token */	++p;
					}
				}
			}
		else
			{
			/* Must be some type of whitespace */
			while(istype((t = nextch()),C_W))
				;
			if(t == '\n')
				{
				/* Just forget we saw any of the above space */
				p = Token;	/* Reset token pointer */
				Token[0] = '\n';
				}
			else
				{
				p = Token + 1;	/* Leave only one in buffer */
				Token[0] = ' ';	/* Make it a single space */
				/* t = token to pushback */
				}
			}
		}
	else
		{
		if(t == '\\')
			{
			if((t = nextch()) == '\n')
				{
				Token[0] = ' ';	/* Generic whitespace token */
				Token[1] = '\0';
				return (' ');
				}
			pushback(t);
			t = '\\';	/* Return an escape char */
			}
		else if(((t == '"') || (t == '\'')) && (f & GT_STR))
			{
#if	DEBUG
			if(Debug) printf(" in quote");
#endif	/* DEBUG */

			for(p = &Token[1]; p < &Token[TOKENSIZE]; p++)
				{
				if((*p = nextch()) != '\\')
					{
					if((*p == t) || (*p == '\n'))
						break;
/*
 *	BUG: if a closing " or ' is missing from the string, the termination
 *	upon \n returns the \n as part of the string -- not as the NEXT token
 *	fetched.  This confuses readline() among others.  26-Jul-85 GO.
 */
					}
				else
					{
/*
 *	Fetched a '\\', see if next char is newline, and ignore both if it is.
 */
					if((ch = nextch()) != '\n')
						*++p = ch;
					else
						{
						/* Unrecord the saved '\\' */
						--p;
						}
					}
				}
			if(p >= &Token[TOKENSIZE])
				non_fatal("Token too long","");

			p[1] = '\0';
			return(t);
			}
		else if((t == '<') && (f == GT_ANGLE))
			{
#if	DEBUG
			if(Debug) printf(" in angle bracket");
#endif	/* DEBUG */

			for(p = &Token[1]; p < &Token[TOKENSIZE]; p++)
				{
				*p = nextch();
				if((*p == '>') || (*p == '\n'))
					break;
				}
			if(p >= &Token[TOKENSIZE])
				non_fatal("Token too long","");

			p[1] = '\0';
			return(t);
			}
		else
			{
			if(t == '/')
				{
/* Regular C comments */	if((nt = nextch()) == '*')
					{
					comment_level = 1;
					t = ' ';
					Token[0] = t;
#if	DEBUG
					if(Debug) printf(" in comment");
#endif	/* DEBUG */
					do
						{
						while((t != '*') && (t != '/')
							&& (t != EOF))
							{
							t = nextch();
							}
						if(t == EOF)
							{
						non_fatal("EOF in comment","");
							return (EOF);
							}
						nt = nextch();
						if((t == '/') && (nt == '*'))
							{
							if(! A_crecurse)
								{
					warning("\"/*\" found in comment","");
								}
							else
								{
							comment_level++;
								}
							}
						if((t == '*') && (nt == '/'))
							comment_level--;
						if(comment_level > 0)
							t = nt;
						}
					while(comment_level > 0) ;
					t = Token[0];
					}
/* Optional C++ comments */	else if(A_eolcomment && (nt == '/'))
					{
					t = ' ';
					Token[0] = t;
#if	DEBUG
					if(Debug) printf(" in eol comment");
#endif	/* DEBUG */
					while((t != '\n') && (t != EOF))
						t = nextch();
					if(t == EOF)
						{
						non_fatal("EOF in comment","");

						return (EOF);
						}
					else
						pushback(t);

					t = Token[0];
					}
				else
					pushback(nt);
				}
			}
		if(istype(t,C_M))
			{
			/* One of several meta token chars */
			switch(t)
				{
				case LINE_TOKEN:
					sprintf(Token,"%d",LLine);
					break;

				case FILE_TOKEN:
					sprintf(Token, "\"%s\"",
						Filestack[Filelevel]->f_name);
					break;

				case TIME_TOKEN:
					sprintf(Token,"\"%s\"",_Time);
					break;

				case DATE_TOKEN:
					sprintf(Token,"\"%s\"",Date);
					break;

				case NOW_TOKEN:
					sprintf(Token,"%u",Unique);
					break;

				case NEXT_TOKEN:
					sprintf(Token,"%u",++Unique);
					break;

				case PREV_TOKEN:
					sprintf(Token,"%u",--Unique);
					break;

				default:
					Token[0] = t;
					Token[1] = '\0';
					break;
				}
			return (type(Token[0] & 0xFF));
			}
		}

	if(p >= &Token[TOKENSIZE])
		non_fatal("Token too long","");

	if(p > Token)
		{
		--p;
		pushback(t);		/* Push back previous token value */
		t = type(Token[0] & 0xFF);
		}

	p[1] = '\0';			/* Null terminated */

#if	DEBUG
	if(Debug) printf(" returning: <%s> type: %c\n",Token,t);
#endif	/* DEBUG */

	return(t);
	}

#ifdef	MSC_OPT
#pragma	optimize("e",on)		/* Enable global reg optimizing */
#pragma	optimize("g",on)		/* Enable global common subs */
#pragma	optimize("l",on)		/* Enable loop optimizing */
#endif	/* MSC_OPT */

#if	!PP
/************************************************************************/
/*									*/
/*	istype								*/
/*									*/
/*	Return TRUE if char is of type specified.			*/
/*									*/
/*	This function is here in case the macro capability cannot be	*/
/*	exercized. (Bootstrapping the Preprocessor.)			*/
/*									*/
/************************************************************************/

int
istype(c,v)
	int			c;
	int			v;
	{
	return ((typetab+1)[c]&v);
	}
#endif	/* !PP */

#ifndef	memmov
/************************************************************************/
/*									*/
/*	memmov								*/
/*									*/
/*	Move a block of memory from one byte location to another.	*/
/*									*/
/************************************************************************/

void
memmov(f,t,l)
	register	char	*f;
	register	char	*t;
	register unsigned	l;
	{    
	while(l--)
		*t++ = *f++;
	}
#endif	/* memmov */

/************************************************************************/
/*									*/
/*	pbcstr								*/
/*									*/
/*	Push back a copy of a string so that it is the first to be	*/
/*	refetched.  Note that we put two copies of the starting string	*/
/*	address on the stack:  The first is used as the working		*/
/*	pointer, the second serves to remember the string beginning for	*/
/*	later freeing.							*/
/*									*/
/************************************************************************/

void
pbcstr(s)
	char			*s;
	{
	char			*cp;
	unsigned	int	length;

	if((cp = malloc((unsigned) (length = (strlen(s) + 1)))) == NULL)
		out_of_memory();
	memmov(s,cp,length);		/* Make a copy of memory */

	if(Pbbufp++ >= &Pbbuf[PUSHBACKSIZE-1])
		fatal("Pushback buffer overflow","");
	Pbbufp->pb_type = PB_STRING;
	Pbbufp->pb_val.pb_str = cp;

	if(Pbbufp++ >= &Pbbuf[PUSHBACKSIZE-1])
		fatal("Pushback buffer overflow","");
	Pbbufp->pb_type = PB_STRING;
	Pbbufp->pb_val.pb_str = cp;

	Nextch = gchpb;
	}

/************************************************************************/
/*									*/
/*	pbstr								*/
/*									*/
/*	Push back a string so it is first to be re-fetched.		*/
/*									*/
/************************************************************************/

void
pbstr(in)
	char			*in;
	{
	register	int	i;

	for(i = strlen(in) - 1; i >= 0; i--)
		pushback(in[i] & 0xFF);
	}

/************************************************************************/
/*									*/
/*	pushback							*/
/*									*/
/*	Push back a character so it is first to be re-fetched.		*/
/*									*/
/************************************************************************/

void
pushback(c)
	int			c;
	{
	if(Pbbufp++ >= &Pbbuf[PUSHBACKSIZE-1])
		fatal("Pushback buffer overflow","");

	Pbbufp->pb_type = PB_CHAR;
	Pbbufp->pb_val.pb_char = c;

	Nextch = gchpb;
	}

/************************************************************************/
/*									*/
/*	puttoken							*/
/*									*/
/*	Write token to output file.					*/
/*									*/
/************************************************************************/

void
puttoken(s)
	char			s[];
	{
	register	int	ch;
	register	char	*str;
	static	int		lastoutc = '\n';	/* Last char written */

	str = s;

#if	DEBUG
if (Debug) printf("puttoken: <%s>\n", str);
#endif	/* DEBUG */

	if(istype(*str & 0xFF,C_N))	/* Ignore null tokens */
		return;

	if(Lineopt)
		{
		/* Get line numbers in sync before emitting token */

#if	(TARGET == T_QC) OR (TARGET == T_QCX)
		if(!Do_asm && (((*str != '\n') && (Outline != LLine)) ||
			Do_name))
#else	/* !((TARGET == T_QC) OR (TARGET == T_QCX)) */
		if(((*str != '\n') && (Outline != LLine)) || Do_name)
#endif	/* (TARGET == T_QC) OR (TARGET == T_QCX) */
			{
			do_line(lastoutc == '\n');	/* True if at BOL */
			lastoutc = '\n';	/* We're at BOL now... */
			}

		while((ch = *str++) != '\0')
			{
			if(ch == '\n')
				{
				if(lastoutc != '\n')
					{
					putc(lastoutc = '\n',Output);
					Outline++;
					}
/*
 *	No character written if lastoutc WAS a newline.
 */
				}
			else
				putc(lastoutc = ch,Output);
			}
		}
	else
		{
		while((ch = *str++) != '\0')
			putc(ch,Output);	/* if!line mode output token */
		}
	}

/************************************************************************/
/*									*/
/*	type								*/
/*									*/
/*	Return token type of character.					*/
/*									*/
/************************************************************************/

int
type(c)
	int			c;
	{
	if(istype(c,C_L))
		return(LETTER);
	else if(istype(c,C_D))
		return(NUMBER);
	else
		return(c);
	}

