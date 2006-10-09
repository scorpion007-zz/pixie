/************************************************************************/
/*									*/
/*	File:	pp5.c							*/
/*									*/
/*	Conditional processing.						*/
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
/*	Functions contained within this module:				*/
/*									*/
/*		doelse		Process #else/#elif directive.		*/
/*		doendif		Process #endif directive.		*/
/*		doif		Process #if directive.			*/
/*		doifs		Do work for #ifdef/#ifndef stuff.	*/
/*									*/
/************************************************************************/

#include	"pp.h"
#include	"ppext.h"

/************************************************************************/
/*									*/
/*	doelse								*/
/*									*/
/*	Process #else/#elif statement.					*/
/*									*/
/************************************************************************/

void
doelse(elif)
	int			elif;	/* TRUE if #elif; FALSE if #else */
	{
#if	DEBUG
	if(Debug) printf("doelse: %d\n",Iflevel);
#endif	/* DEBUG */
	if(Iflevel)
		{
		/* We are processing an if */
		if(Ifstack[Iflevel].i_else)
			non_fatal("\"#else\" already encountered","");
		else
			{
			if(Ifstate == IFTRUE)
				Ifstate = Ifstack[Iflevel].i_state = IFNEVER;
			else if(Ifstate == IFFALSE)
				{
				if(elif)
					{
/*
 *	Note that we first need to pretend that we are in a TRUE branch so
 *	that routines which "eval" causes to be called will correctly process
 *	the "elif" expression (in particular "_docall").
 */
					Ifstate = Ifstack[Iflevel].i_state =
						IFTRUE;
					Ifstate = Ifstack[Iflevel].i_state =
						eval() ? IFTRUE : IFFALSE;
					}
				else
					{
					Ifstate = Ifstack[Iflevel].i_state =
						IFTRUE;
					}
				}
			/* If have seen an #else */
			Ifstack[Iflevel].i_else = !elif;
			}
		}
	else
		{
		if(elif)
			non_fatal("\"#elif\" outside of \"#if\"","");
		else
			non_fatal("\"#else\" outside of \"#if\"","");
		}
	}

/************************************************************************/
/*									*/
/*	doendif								*/
/*									*/
/*	Process #endif statement.					*/
/*									*/
/************************************************************************/

void
doendif()
	{
#if	DEBUG
	if(Debug) printf("doendif: %d\n",Iflevel);
#endif	/* DEBUG */
	if(Iflevel)
		Ifstate = Ifstack[--Iflevel].i_state;	/* Pop stack */
	else
		non_fatal("\"#endif\" outside of \"#if\"","");
	}

/************************************************************************/
/*									*/
/*	doif								*/
/*									*/
/*	Process #if statement.						*/
/*									*/
/************************************************************************/

void
doif()
	{
	if(Iflevel >= IFSTACKSIZE)
		non_fatal("\"#if\" stack overflow","");
	else
		{
		if(Ifstate == IFTRUE)
			{
			Ifstate = Ifstack[++Iflevel].i_state =
				eval() ? IFTRUE : IFFALSE;
			}
		else
			{
			Ifstate = Ifstack[++Iflevel].i_state =
				IFNEVER;  /* NO #else */
			scaneol();	/* Just absorb the rest */
			}
		Ifstack[Iflevel].i_else = FALSE;	/* No #else seen */
		}
	}

/************************************************************************/
/*									*/
/*	doifs								*/
/*									*/
/*	Process some kind of #ifxdef statement.				*/
/*									*/
/*	Lookup token and set Ifstack to inform output routine to	*/
/*	emit code or not.						*/
/*									*/
/************************************************************************/

void
doifs(t)
	int			t;	/* Type of if TRUE if #ifdef */
	{
	register int		iftype;

	if(Ifstate == IFTRUE)
		{
		/* Get next non-space token */
		if(getnstoken(GT_STR) == LETTER)
			{
#if	DEBUG
			if(Debug) printf("doifs: %d %s",t,Token);
#endif	/* DEBUG */
			iftype = (lookup(Token,NULL) ? TRUE : FALSE) ^
				(t ? FALSE : TRUE) ? IFTRUE : IFFALSE;
			}
		else
			{
			iftype = IFFALSE;
			illegal_symbol();
			}
		}
	else
		iftype = IFNEVER;	/* Inside false #if -- No #else */

	if(Iflevel >= IFSTACKSIZE)
		non_fatal("\"#if\" stack overflow","");
	else
		{
		Ifstate = Ifstack[++Iflevel].i_state = iftype;
		Ifstack[Iflevel].i_else = FALSE;
		}

#if	DEBUG
	if(Debug) printf("doifs: %d %d %d\n",t,iftype,Iflevel);
#endif	/* DEBUG */
	}

