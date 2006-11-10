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
//  File				:	dataBlock.cpp
//  Classes				:	CDataBlock
//  Description			:	A datablock is something that holds memory that can
//							be cleared when needed. 
//
////////////////////////////////////////////////////////////////////////
#ifndef DATABLOCK_H
#define DATABLOCK_H


///////////////////////////////////////////////////////////////////////
// Class				:	CDataBlock
// Description			:	This class holds information about a particular texture block
// Comments				:
// Date last edited		:	7/7/2001
class	CDataBlock	{
public:
	void				*data;					// Where the block data is stored (NULL if the block has been paged out)
	int					size;					// Size of the block in bytes
	int					lastRefNumber;			// Last time this block was referenced
	CTextureBlock		*next;					// Pointer to the next used / empty block
	CTextureBlock		*prev;					// Pointer to the previous used / empty block
};


///////////////////////////////////////////////////////////////////////
// Class				:	CDataBlock
// Description			:	This class holds information about a particular texture block
// Comments				:
// Date last edited		:	7/7/2001
class	CDataBase	{
public:

						CDataBase();
		virtual			~CDataBase();

		void			allocateBlock(CDataBlock *block);

private:

		CDataBlock		*blocks;
		int				lastRef;
		int				usedMemory;
		int				maxMemory;
};


#endif




