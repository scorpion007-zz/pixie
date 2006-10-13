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
//  File				:	rendererJobs.cpp
//  Classes				:	CRenderer
//  Description			:	Functions that deal with the actual rendering
//
////////////////////////////////////////////////////////////////////////
#include "renderer.h"
#include "shading.h"
#include "stats.h"
#include "error.h"

void			(*CRenderer::dispatchJob)(CJob &job)	=	NULL;



///////////////////////////////////////////////////////////////////////
// Class				:	CRenderer
// Method				:	beginRendering
// Description			:	Begin the rendering
// Return Value			:	-
// Comments				:	-
// Date last edited		:	6/21/2001
void			CRenderer::beginRendering() {
	int	i;

	for (i=0;i<numThreads;i++) {
		contexts[i]->renderingLoop();
	}
}





///////////////////////////////////////////////////////////////////////
// Class				:	CRenderer
// Method				:	dispatchReyes
// Description			:	Dispatch individual buckets
// Return Value			:	-
// Comments				:	-
// Date last edited		:	6/21/2001
void			CRenderer::dispatchReyes(CJob &job) {

	// If we have a client, ask for a bucket
	if (netClient != INVALID_SOCKET) {
		T32	netBuffer[3];

		// Receive the bucket to render from the client
		rcRecv(netClient,(char *) netBuffer,3*sizeof(T32));

		// Process the render order
		if (netBuffer[0].integer == NET_RENDER_BUCKET) {
			job.type				=	CJob::BUCKET;
			job.xBucket				=	netBuffer[1].integer;
			job.yBucket				=	netBuffer[2].integer;
			return;
		} else if (netBuffer[0].integer == NET_FINISH_FRAME) {
			// We have finished the frame, so terminate
			netBuffer[0].integer	=	NET_ACK;
			rcSend(netClient,(char *) netBuffer,1*sizeof(T32));
			
			// send end of frame channel data
			sendFrameDataChannels();
			
			job.type				=	CJob::TERMINATE;
			return;
		} else {
			error(CODE_BUG,"Unrecognised network request\n");
		}
	}

	// We do not have a client, if we're not done, dispatch the first bucket

	// If we're done, tell the hider to terminate
	if (hiderFlags & (HIDER_DONE | HIDER_BREAK)) {
		job.type	=	CJob::TERMINATE;
	} else {
		// Otherwise, dispatch a bucket
		job.type	=	CJob::BUCKET;
		job.xBucket	=	currentXBucket;
		job.yBucket	=	currentYBucket;

		// Advance the bucket
		CRenderer::currentXBucket++;
		if (CRenderer::currentXBucket == CRenderer::xBuckets) {		
			CRenderer::currentXBucket	=	0;
			CRenderer::currentYBucket++;
		}

		if ((CRenderer::currentXBucket == 0) && (CRenderer::currentYBucket == CRenderer::yBuckets)) {
			CRenderer::hiderFlags |=	HIDER_DONE | HIDER_BREAK;
		}
	}
}



///////////////////////////////////////////////////////////////////////
// Class				:	CRenderer
// Method				:	getJob
// Description			:	This function is used by the hiders to request a job
// Return Value			:	-
// Comments				:	-
// Date last edited		:	6/21/2001
void			CRenderer::dispatchPhoton(CJob &job) {
}


///////////////////////////////////////////////////////////////////////
// Class				:	CRenderer
// Method				:	advanceBucket
// Description			:	Advance the bucket for network parallel rendering
// Return Value			:	TRUE if we're still rendering, FALSE otherwise
// Comments				:
// Date last edited		:	7/4/2001
int				CRenderer::advanceBucket(int index,int &x,int &y,int &nx,int &ny) {

	nx = xBuckets;
	ny = yBuckets;
	
// Advance bucket indices
#define	advance(__x,__y)									\
		__x++;												\
		if (__x == xBuckets) {								\
			__x	=	0;										\
			__y++;											\
			if (__y == yBuckets)	{						\
				return FALSE;								\
			}												\
		}

// Find the server index assigned to this job
#define	bucket(__x,__y)		jobAssignment[__y*xBuckets + __x]

	if (jobAssignment == FALSE) {
		int	i;

		jobAssignment	=	new int[xBuckets*yBuckets];

		// Create the job assignment
		for (i=0;i<xBuckets*yBuckets;i++)	jobAssignment[i]	=	-1;

	}

	// Are we just starting ?
	if ((x == -1) || (y == -1)) {
		x	=	0;			// Begin from the start
		y	=	0;
	} else {
		advance(x,y);		// Advance the bucket by one
	}
	
	// Scan forward from (cx,cy) to find the first bucket to render
	while(TRUE) {

		// Has the bucket been assigned before ?
		if (bucket(x,y) == -1) {
			int	left	=	(x / netXBuckets)*netXBuckets;
			int	right	=	min((left + netXBuckets),xBuckets);
			int	top		=	(y / netYBuckets)*netYBuckets;
			int	bottom	=	min((top + netYBuckets),yBuckets);
			int	i,j;

			// The bucket is not assigned ...
			// Assign the meta block to this processor
			for (i=left;i<right;i++) {
				for (j=top;j<bottom;j++) {
					bucket(i,j)	=	index;
				}
			}

			assert(bucket(x,y) == index);

			// We found the job !!!
			return TRUE;
		} else if (bucket(x,y) != index) {

			// This bucket has been pre-allocated to another server, skip over
			advance(x,y);
		} else {

			// This bucket has been pre-allocated to us, proceed
			return TRUE;
		}
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	CRenderer
// Method				:	rendererThread
// Description			:	This function actually manages the servers
// Return Value			:
// Comments				:
// Date last edited		:	8/25/2002
void		CRenderer::rendererThread(void *w) {
	int		index			=	(int) w;	// This is the server index, 1 thread for every server
	int		done			=	FALSE;
	T32		netBuffer[3];
	int		x,y,nx,ny;

	// Make sure the server needs all the files it needs
	while(TRUE) {

		// Expect the ready message
		rcRecv(netServers[index],(char *) netBuffer,1*sizeof(T32));

		if (netBuffer[0].integer == NET_READY)	break;

		// Server needs something, process the request
		processServerRequest(netBuffer[0],index);
	}

	// At this point, the server should be ready to render...

	// Dispatch buckets
	x	=	-1;
	y	=	-1;
	while(done==FALSE){
		T32		header[5];
		float	*buffer;

		// Find the needed bucket
		osDownMutex(commitMutex);

		// Get the current bucket and advance the bucket
		if (advanceBucket(index,x,y,nx,ny) == FALSE) {
			done	=	TRUE;
		}

		// Release the bucket
		osUpMutex(commitMutex);

		if (done == FALSE) {

			// Dispatch the job
			netBuffer[0].integer	=	NET_RENDER_BUCKET;
			netBuffer[1].integer	=	x;
			netBuffer[2].integer	=	y;
			rcSend(netServers[index],(char *) netBuffer,3*sizeof(T32));

			while(TRUE) {
				// Expect the ready message
				rcRecv(netServers[index],(char *) netBuffer,1*sizeof(T32));

				if (netBuffer[0].integer == NET_READY)	break;

				// Server needs something, process the request
				processServerRequest(netBuffer[0],index);
			}

			// Receive the result
			rcRecv(netServers[index],(char *) &header,5*sizeof(T32));		// Receive the response header
			rcSend(netServers[index],(char *) &netBuffer,1*sizeof(T32));	// Echo the message back

			buffer					=	new float[header[4].integer];
																			// Receive the framebuffer
			rcRecv(netServers[index],(char *) buffer,header[4].integer*sizeof(T32));

			// Commit the bucket
			osDownMutex(commitMutex);
			
			commit(header[0].integer,header[1].integer,header[2].integer,header[3].integer,buffer);
			recvBucketDataChannels(netServers[index],x,y);
	
			numNetrenderedBuckets++;
			stats.progress		=	(numNetrenderedBuckets*100) / (float) (nx*ny);
			if (flags & OPTIONS_FLAGS_PROGRESS)	info(CODE_PROGRESS,"Done %%%3.2f\r",stats.progress);
			
			osUpMutex(commitMutex);

			delete[] buffer;
		}

		if(done == TRUE){
			// We finished rendering this frame
			// Advance the server to the next frame
			netBuffer[0].integer	=	NET_FINISH_FRAME;
			netBuffer[1].integer	=	0;
			netBuffer[2].integer	=	0;
			rcSend(netServers[index],(char *) netBuffer,3*sizeof(T32));
			rcRecv(netServers[index],(char *) netBuffer,1*sizeof(T32));	// Expect ACK
			
			osDownMutex(commitMutex);
			
			recvFrameDataChannels(netServers[index]);
	
			stats.progress	=	100;
			if (flags & OPTIONS_FLAGS_PROGRESS)	info(CODE_PROGRESS,"Done               \r");

			osUpMutex(commitMutex);
		}
	}
}



///////////////////////////////////////////////////////////////////////
// Class				:	CRenderer
// Method				:	processServerRequest
// Description			:	Process a server request
// Return Value			:	-
// Comments				:
// Date last edited		:	8/25/2002
void			CRenderer::processServerRequest(T32 req,int index) {
	if (req.integer == NET_SEND_FILE) {
		// The server is missing a file, so send it over
		char		*fileName;
		char		fileLocation[OS_MAX_PATH_LENGTH];
		int			start,size;
		int			nameLength;
		T32			buffer[3];
		TSearchpath	*search;

		// Receive the length of the fileName
		rcRecv(netServers[index],(char *) buffer,3*sizeof(T32));
		start		=	buffer[0].integer;
		size		=	buffer[1].integer;
		nameLength	=	buffer[2].integer;

		fileName	=	(char *) alloca(nameLength);
		rcRecv(netServers[index],(char *) fileName,nameLength,FALSE);
		
		// Figure out what type of file it is
		if (strstr(fileName,".sdr") != NULL)		search	=	shaderPath;
		else if (strstr(fileName,".dll") != NULL)	search	=	proceduralPath;
		else if (strstr(fileName,".so") != NULL)	search	=	proceduralPath;
		else if (strstr(fileName,".rib") != NULL)	search	=	archivePath;
		else if (strstr(fileName,".tif") != NULL)	search	=	texturePath;
		else if (strstr(fileName,".tiff") != NULL)	search	=	texturePath;
		else if (strstr(fileName,".tex") != NULL)	search	=	texturePath;
		else if (strstr(fileName,".tx") != NULL)	search	=	texturePath;
		else if (strstr(fileName,".ptc") != NULL)	search	=	texturePath;
		else if (strstr(fileName,".bm") != NULL)	search	=	texturePath;
		else										search	=	NULL;

		if (locateFile(fileLocation,fileName,search)) {
			sendFile(index,fileLocation,start,size);
		} else {
			// Unable to find file
			T32	response;

			response.integer	=	NET_NACK;
			rcSend(netServers[index],(char *) &response,sizeof(T32));
		}
	} else if (req.integer == NET_CREATE_CHANNEL) {
		// This must be atomic
		osDownMutex(commitMutex);
		processChannelRequest(index,netServers[index]);
		osUpMutex(commitMutex);
	} else {
		error(CODE_BUG,"Unknown server request\n");
	}
}
