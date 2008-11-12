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
//  File				:	rendererJobs.cpp
//  Classes				:	CRenderer
//  Description			:	Functions that deal with the actual rendering
//
////////////////////////////////////////////////////////////////////////
#include "renderer.h"
#include "shading.h"
#include "stats.h"
#include "error.h"

void			(*CRenderer::dispatchJob)(int thread,CJob &job)	=	NULL;





///////////////////////////////////////////////////////////////////////
// Class				:	CRenderer
// Method				:	dispatchReyes
// Description			:	Dispatch individual buckets
// Return Value			:	-
// Comments				:	-
void			CRenderer::dispatchReyes(int thread,CJob &job) {

	// If we have a client, ask for a bucket
	if (netClient != INVALID_SOCKET) {
		T32	netBuffer[3];

		// Receive the bucket to render from the client
		osLock(networkMutex);
		rcRecv(netClient,netBuffer,3*sizeof(T32));
		
		// Process the render order
		if (netBuffer[0].integer == NET_RENDER_BUCKET) {
			job.type				=	CJob::BUCKET;
			job.xBucket				=	netBuffer[1].integer;
			job.yBucket				=	netBuffer[2].integer;

		} else if (netBuffer[0].integer == NET_FINISH_FRAME) {
			// We have finished the frame, so terminate
			netBuffer[0].integer	=	NET_ACK;
			rcSend(netClient,netBuffer,1*sizeof(T32));
			
			// send end of frame channel data
			sendFrameDataChannels();
			
			job.type				=	CJob::TERMINATE;
		} else {
			error(CODE_BUG,"Unrecognized network request\n");
			job.type				=	CJob::TERMINATE;
		}

		osUnlock(networkMutex);
		return;
	}

	// We do not have a client




	// Lock the bucket info
	osLock(jobMutex);

	// If we're done, tell the hider to terminate
	if (hiderFlags & (HIDER_DONE | HIDER_BREAK)) {
		job.type	=	CJob::TERMINATE;
	} else {
		int	x,y;

		// Find the bucket for this thread to render
		x	=	contexts[thread]->currentXBucket;
		y	=	contexts[thread]->currentYBucket;
		while(TRUE) {

			// Has this bucket been assigned to soneone ?
			if (jobAssignment[y*xBuckets+x]	== -1) {
				int	i;

				// Nop, allocate the next stride of buckets to this thread
				for (i=0;i<threadStride;i++) {
					if ((y*xBuckets+x+i) < (xBuckets*yBuckets))	jobAssignment[y*xBuckets+x+i] = thread;
				}

				break;

			// Has it been assigned to me?
			} else if (jobAssignment[y*xBuckets+x]	== thread) {
				break;

			// OK, it has been assigned to someone else ... Skip this bucket
			} else {
				x++;
				if (x >= xBuckets) {
					x = 0;
					y++;
					if (y >= yBuckets) break;
				}
			}
		}


		// Did we find the bucket ?
		if (y < yBuckets) {
			job.type	=	CJob::BUCKET;
			job.xBucket	=	x;
			job.yBucket	=	y;
		} else {
			job.type	=	CJob::TERMINATE;
			numActiveThreads--;
		}

		// Did we finish the scene ?
		if (numActiveThreads == 0) {
			CRenderer::hiderFlags |=	HIDER_DONE | HIDER_BREAK;
		}
	}

	// Release the bucket info
	osUnlock(jobMutex);
}



///////////////////////////////////////////////////////////////////////
// Class				:	CRenderer
// Method				:	getJob
// Description			:	This function is used by the hiders to request a job
// Return Value			:	-
// Comments				:	-
void			CRenderer::dispatchPhoton(int thread,CJob &job) {

	// Lock
	osLock(jobMutex);

	if (currentPhoton < numEmitPhotons) {

		// There are still photons to trace
		job.type		=	CJob::PHOTON_BUNDLE;
		job.numPhotons	=	min(1000,numEmitPhotons-currentPhoton);	// Shoot 1000 photons at a time
		currentPhoton	+=	job.numPhotons;
		
		if (CRenderer::flags & OPTIONS_FLAGS_PROGRESS)	{
			stats.progress		=	(currentPhoton*100) / (float) (numEmitPhotons);
			if (currentPhoton == numEmitPhotons)	info(CODE_PROGRESS,"Done %d photons            	            \r\n",numEmitPhotons);
			else									info(CODE_PROGRESS,"Done %%%3.2f %d photons\r",stats.progress,currentPhoton);
		}

	} else {

		// We're finished, terminate
		job.type		=	CJob::TERMINATE;
	}

	// Unlock
	osUnlock(jobMutex);
}







///////////////////////////////////////////////////////////////////////
// Class				:	CRenderer
// Method				:	advanceBucket
// Description			:	Advance the bucket for network parallel rendering
// Return Value			:	TRUE if we're still rendering, FALSE otherwise
// Comments				:
int				CRenderer::advanceBucket(int index,int &x,int &y) {


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
// Method				:	serverThread
// Description			:	This function actually manages the servers
// Return Value			:
// Comments				:
void		CRenderer::serverThread(void *w) {
	int		index			=	(int) (uintptr_t) w;	// This is the server index, 1 thread for every server
	int		done			=	FALSE;
	T32		netBuffer[3];
	int		x,y;

	// Make sure the server needs all the files it needs
	while(TRUE) {

		// Expect the ready message
		rcRecv(netServers[index],netBuffer,1*sizeof(T32));

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
		osLock(jobMutex);

		// Get the current bucket and advance the bucket
		if (advanceBucket(index,x,y) == FALSE) {
			done	=	TRUE;
		}

		// Release the bucket
		osUnlock(jobMutex);

		if (done == FALSE) {

			// Dispatch the job
			netBuffer[0].integer	=	NET_RENDER_BUCKET;
			netBuffer[1].integer	=	x;
			netBuffer[2].integer	=	y;
			rcSend(netServers[index],netBuffer,3*sizeof(T32));

			while(TRUE) {
				// Expect the ready message
				rcRecv(netServers[index],netBuffer,1*sizeof(T32));

				if (netBuffer[0].integer == NET_READY)	break;

				// Server needs something, process the request
				processServerRequest(netBuffer[0],index);
			}

			// Receive the result
			rcRecv(netServers[index],&header,5*sizeof(T32));		// Receive the response header
			rcSend(netServers[index],&netBuffer,1*sizeof(T32));		// Echo the message back

			buffer					=	new float[header[4].integer];
																			// Receive the framebuffer
			rcRecv(netServers[index],buffer,header[4].integer*sizeof(T32));

			// Commit the bucket
			osLock(commitMutex);
			
			commit(header[0].integer,header[1].integer,header[2].integer,header[3].integer,buffer);
			recvBucketDataChannels(netServers[index],x,y);
			
			osUnlock(commitMutex);

			delete[] buffer;
		}

		if(done == TRUE){
			// We finished rendering this frame
			// Advance the server to the next frame
			netBuffer[0].integer	=	NET_FINISH_FRAME;
			netBuffer[1].integer	=	0;
			netBuffer[2].integer	=	0;
			rcSend(netServers[index],netBuffer,3*sizeof(T32));
			rcRecv(netServers[index],netBuffer,1*sizeof(T32));	// Expect ACK
			
			osLock(commitMutex);
			
			recvFrameDataChannels(netServers[index]);
			
			osUnlock(commitMutex);
		}
	}
}



///////////////////////////////////////////////////////////////////////
// Class				:	CRenderer
// Method				:	processServerRequest
// Description			:	Process a server request
// Return Value			:	-
// Comments				:
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
		rcRecv(netServers[index],buffer,3*sizeof(T32));
		start		=	buffer[0].integer;
		size		=	buffer[1].integer;
		nameLength	=	buffer[2].integer;

		fileName	=	(char *) alloca(nameLength);
		rcRecv(netServers[index],fileName,nameLength,FALSE);
		
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
			rcSend(netServers[index],&response,sizeof(T32));
		}
	} else if (req.integer == NET_CREATE_CHANNEL) {
		// This must be atomic
		osLock(commitMutex);
		processChannelRequest(index,netServers[index]);
		osUnlock(commitMutex);
	} else {
		error(CODE_BUG,"Unknown server request\n");
	}
}

