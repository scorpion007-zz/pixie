//////////////////////////////////////////////////////////////////////
//
//                             Pixie
//
// Copyright © 1999 - 2003, Okan Arikan
//
// Contact: okan@cs.utexas.edu
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
		fprintf(stdout,"\t\tpoint cloud\tp:show points\n");
		fprintf(stdout,"\t\t\t\td:show discs\n");
		fprintf(stdout,"\t\tirradiance\tp:show points\n");
		fprintf(stdout,"\t\t\t\td:show discs\n");
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




