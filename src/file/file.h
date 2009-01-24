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
//  File				:	file.cpp
//  Classes				:
//  Description			:	This file implements the default output device
//							that sends the image into a file
//
////////////////////////////////////////////////////////////////////////


#ifndef FILE_H
#define FILE_H

///////////////////////////////////////////////////////////////////////
// Class				:	CFileFramebuffer
// Description			:	Holds the framebuffer
// Comments				:
class CFileFramebuffer {
public:
	///////////////////////////////////////////////////////////////////////
	// Class				:	CFileFramebuffer
	// Method				:	CFileFramebuffer
	// Description			:	Ctor
	// Return Value			:	-
	// Comments				:
	CFileFramebuffer() { };

	///////////////////////////////////////////////////////////////////////
	// Class				:	CFileFramebuffer
	// Method				:	CFileFramebuffer
	// Description			:	Dtor
	// Return Value			:	-
	// Comments				:
	virtual ~CFileFramebuffer() { };
	
	///////////////////////////////////////////////////////////////////////
	// Class				:	CFileFramebuffer
	// Method				:	write
	// Description			:	Write image data to the file
	// Return Value			:	-
	// Comments				:
	virtual void write(int x,int y,int w,int h,float *data) { };
	
	///////////////////////////////////////////////////////////////////////
	// Class				:	CFileFramebuffer
	// Method				:	success
	// Description			:	Returns True if constructor succeeded with file creation
	// Return Value			:	-
	// Comments				:
	virtual bool success() { return false; };
};

#endif // FILE_H



