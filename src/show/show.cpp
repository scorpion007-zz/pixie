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
//  File				:	show.cpp
//  Classes				:	-
//  Description			:	The main show file
//
////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common/global.h"
#include "common/os.h"
#include "ri/ri.h"



///////////////////////////////////////////////////////////////////////
// Function				:	main
// Description			:	Da main function for show
// Return Value			:	1 on failure, 0 on success
// Comments				:
int	main(int argc,char *argv[]) {

	if (argc == 1) {
		fprintf(stdout,"Usage: show <options> <file_name>[,mode]\n");
		fprintf(stdout,"\tKeys:\tbrickmap\tm:more detailed level\n");
		fprintf(stdout,"\t\t\t\tl:less detailed level\n");
		fprintf(stdout,"\t\t\t\tb:show boxes\n");
		fprintf(stdout,"\t\t\t\td:show discs\n");
		fprintf(stdout,"\t\t\t\tp:show points\n");
		fprintf(stdout,"\t\t\t\tq:previous channel\n");
		fprintf(stdout,"\t\t\t\tw:next channel\n");
		fprintf(stdout,"\t\tpoint cloud\tp:show points\n");
		fprintf(stdout,"\t\t\t\td:show discs\n");
		fprintf(stdout,"\t\t\t\tq:previous channel\n");
		fprintf(stdout,"\t\t\t\tw:next channel\n");
		fprintf(stdout,"\t\tirradiance\tp:show points\n");
		fprintf(stdout,"\t\t\t\td:show discs\n\n");
		fprintf(stdout,"\tMouse:\tleft\t\trotate\n");
		fprintf(stdout,"\t\tmiddle\t\tzoom\n");
		fprintf(stdout,"\t\tright\t\tpan\n");
		return 1;
	} else {
		char	tmp[OS_MAX_PATH_LENGTH+6];

		sprintf(tmp,"show:%s",argv[1]);

		// This is how we show things
		RiBegin(RI_NULL);
		RiHider(tmp,RI_NULL);
		RiWorldBegin();				// Force fake rendering (show the window)
		RiWorldEnd();
		RiEnd();

		return	0;
	}
}

