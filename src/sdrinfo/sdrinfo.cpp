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
//  File				:	sdrinfo.cpp
//  Classes				:	-
//  Description			:	sdr info probram
//
////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common/global.h"
#include "common/os.h"
#include "sdr/sdr.h"

///////////////////////////////////////////////////////////////////////
// Function				:	main
// Description			:	The god
// Return Value			:	-
// Comments				:
int main(int argc, char* argv[]) {
	char	tmp[1024];

	if (argc > 1) {
		TSdrShader		*cShader;
		TSdrParameter	*cParameter;
		const char		*pixieHome	=	osEnvironment("PIXIEHOME");
		const char		*shaders	=	osEnvironment("SHADERS");

		sprintf(tmp,".");

		if (pixieHome != NULL) {
			strcat(tmp,":");
			strcat(tmp,pixieHome);
			strcat(tmp,"/shaders");
		}

		if (shaders != NULL) {
			strcat(tmp,":");
			strcat(tmp,shaders);
		}


		osFixSlashes(tmp);
		cShader	=	sdrGet(argv[1],tmp);

		if (cShader == NULL) {
			fprintf(stderr,"Failed to find shader \"%s\"\n",argv[1]);
			exit(1);
		}

		switch(cShader->type) {
		case SHADER_SURFACE:
			fprintf(stdout,"surface ");
			break;
		case SHADER_DISPLACEMENT:
			fprintf(stdout,"displacement ");
			break;
		case SHADER_VOLUME:
			fprintf(stdout,"volume ");
			break;
		case SHADER_LIGHT:
			fprintf(stdout,"light ");
			break;
		case SHADER_IMAGER:
			fprintf(stdout,"imager ");
			break;
		}

		fprintf(stdout,"\"%s\"\n",cShader->name);

		for (cParameter=cShader->parameters;cParameter!=NULL;cParameter=cParameter->next) {
			fprintf(stdout,"\t\"%s\" ",cParameter->name);

			if (cParameter->writable) {
				fprintf(stdout,"\"output ");
			} else {
				fprintf(stdout,"\"");
			}
			
			switch(cParameter->container) {
			case CONTAINER_CONSTANT:
				fprintf(stdout,"constant ");
				break;
			case CONTAINER_UNIFORM:
				fprintf(stdout,"uniform ");
				break;
			case CONTAINER_VARYING:
				fprintf(stdout,"varying ");
				break;
			case CONTAINER_VERTEX:
				fprintf(stdout,"vertex ");
				break;
			}

			switch(cParameter->type) {
			case TYPE_FLOAT:
				fprintf(stdout,"float");
				break;
			case TYPE_VECTOR:
				fprintf(stdout,"vector");
				break;
			case TYPE_NORMAL:
				fprintf(stdout,"normal");
				break;
			case TYPE_POINT:
				fprintf(stdout,"point");
				break;
			case TYPE_COLOR:
				fprintf(stdout,"color");
				break;
			case TYPE_MATRIX:
				fprintf(stdout,"matrix");
				break;
			case TYPE_STRING:
				fprintf(stdout,"string");
				break;
			}

			if (cParameter->numItems > 1) {
				fprintf(stdout,"[%d]",cParameter->numItems);
			}

			fprintf(stdout,"\"\n");

			fprintf(stdout,"\t\tDefault value: ");

			UDefaultVal *currentDefault = &cParameter->defaultValue;
			if (cParameter->numItems > 1)
				currentDefault = currentDefault->array;
			
			for(int i=0;i<cParameter->numItems;i++){
				switch(cParameter->type) {
				case TYPE_FLOAT:
					fprintf(stdout,"%g ",currentDefault->scalar);
					break;
				case TYPE_VECTOR:
				case TYPE_NORMAL:
				case TYPE_POINT:
				case TYPE_COLOR:
					if (cParameter->space != NULL) {
						fprintf(stdout,"\"%s\" ",cParameter->space);
					}

					if (currentDefault->vector != NULL) {
						fprintf(stdout,"[%g %g %g] ",currentDefault->vector[0],currentDefault->vector[1],currentDefault->vector[2]);
					} else {
						fprintf(stdout,"[0 0 0] ");
					}
					break;
				case TYPE_MATRIX:
					if (currentDefault->matrix != NULL) {
						fprintf(stdout,"[%g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g] "
							,currentDefault->matrix[0]
							,currentDefault->matrix[1]
							,currentDefault->matrix[2]
							,currentDefault->matrix[3]
							,currentDefault->matrix[4]
							,currentDefault->matrix[5]
							,currentDefault->matrix[6]
							,currentDefault->matrix[7]
							,currentDefault->matrix[8]
							,currentDefault->matrix[9]
							,currentDefault->matrix[10]
							,currentDefault->matrix[11]
							,currentDefault->matrix[12]
							,currentDefault->matrix[13]
							,currentDefault->matrix[14]
							,currentDefault->matrix[15]);
					} else {
						fprintf(stdout,"[0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0] ");
					}
					break;
				case TYPE_STRING:
					if (currentDefault->string != NULL) {
						fprintf(stdout,"\"%s\" ",currentDefault->string);
					} else {
						fprintf(stdout,"NULL ");
					}
					break;
				}
				currentDefault++;
			}
			fprintf(stdout,"\n");
		}

		sdrDelete(cShader);
	}

	return 0;
}

