//////////////////////////////////////////////////////////////////////
//
//                             Pixie
//
// Copyright � 1999 - 2003, Okan Arikan
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
//  File				:	texture.cpp
//  Classes				:	CTexture
//  Description			:	Implementation !!!
//
////////////////////////////////////////////////////////////////////////
#include "texture.h"
#include "shading.h"
#include "stats.h"
#include "memory.h"
#include "error.h"
#include "renderer.h"
#include "tiff.h"

#include <stddef.h>		// Ensure NULL is defined before libtiff
#include <math.h>
#include <string.h>
#include <tiffio.h>

// FIXME: rand() is not thread safe
#define	urand()	(rand() / (float) RAND_MAX)





///////////////////////////////////////////////////////////////////////
// Class				:	CTextureBlock
// Description			:	This class holds information about a particular texture block
// Comments				:
class	CTextureBlock	{
public:
	void				*data;				// Where the block data is stored (NULL if the block has been paged out)
	int					size;				// Size of the block in bytes
	int					lastRefNumber;		// Last time this block was referenced
	CTextureBlock		*next;				// Pointer to the next used / empty block
	CTextureBlock		*prev;				// Pointer to the previous used / empty block
};


///////////////////////////////////////////////////////////////////////
//
//		Misc texture block management functions
//
///////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////
// function				:	tiffErrorHandler
// Description			:	Handle errors coming from the libtiff
// Return Value			:	-
// Comments				:
static	void	tiffErrorHandler(const char *module,const char *fmt,va_list ap) {
	char tmp[1024];

	vsprintf(tmp,fmt,ap);

	error(CODE_SYSTEM,tmp);
}

///////////////////////////////////////////////////////////////////////
// Function				:	textureQuickSort
// Description			:	Sort the textures in the order of increasing last ref number
// Return Value			:
// Comments				:
static	void	textureQuickSort(CTextureBlock **activeBlocks,int start,int end) {
	int				i,last;
	CTextureBlock	*cBlock;

	for (last=start,i=start+1;i<=end;i++) {
		if (activeBlocks[i]->lastRefNumber < activeBlocks[start]->lastRefNumber) {
			last++;
			cBlock					=	activeBlocks[last];
			activeBlocks[last]		=	activeBlocks[i];
			activeBlocks[i]			=	cBlock;
		}
	}

	cBlock				=	activeBlocks[last];
	activeBlocks[last]	=	activeBlocks[start];
	activeBlocks[start]	=	cBlock;

	// Speed is not an issue since this is not done very frequently, so recursion is OK
	if ((last-1) > start)
		textureQuickSort(activeBlocks,start,last-1);

	if (end > (last+1))
		textureQuickSort(activeBlocks,last+1,end);
}

///////////////////////////////////////////////////////////////////////
// Function				:	textureMemFlush
// Description			:	Try to deallocate some textures from memory
// Return Value			:
// Comments				:
static inline void	textureMemFlush(CTextureBlock *entry,int all) {
	
	// Do we have stuff to free ?
	if (CRenderer::textureUsedBlocks == NULL)	return;

	osLock(CRenderer::memoryMutex);
	memBegin(CRenderer::globalMemory);

	// Figure out how many blocks we have in memory
	int				i,j;
	CTextureBlock	**activeBlocks;
	CTextureBlock	*cBlock;
	for (cBlock=CRenderer::textureUsedBlocks,i=0;cBlock!=NULL;cBlock=cBlock->next) {
		if (cBlock->data != NULL) {
			i++;
		}
	}
	
	// Collect those blocks into an array
	activeBlocks	=	(CTextureBlock **) ralloc(i*sizeof(CTextureBlock *),CRenderer::globalMemory);
	for (cBlock=CRenderer::textureUsedBlocks,i=0;cBlock!=NULL;cBlock=cBlock->next) {
		if (cBlock->data != NULL) {
			if (cBlock != entry) {
				activeBlocks[i++]	=	cBlock;
			}
		}
	}

	// Sort the blocks from last used to the most recently used
	if (i > 1)	textureQuickSort(activeBlocks,0,i-1);

	// Free the memory
	if (all)	CRenderer::textureMaxMemory	=	0;
	for (j=0;(j<i) && (CRenderer::textureUsedMemory > (CRenderer::textureMaxMemory/2));j++) {
		cBlock							=	activeBlocks[j];

		stats.textureSize				-=	cBlock->size;
		stats.textureMemory				-=	cBlock->size;
		CRenderer::textureUsedMemory	-=	cBlock->size;
		delete [] (unsigned char *) cBlock->data;
		cBlock->data					=	NULL;
	}

	memEnd(CRenderer::globalMemory);
	osUnlock(CRenderer::memoryMutex);
}



///////////////////////////////////////////////////////////////////////
// Function				:	textureLoadBlock
// Description			:	Read a block of texture from disk
// Return Value			:	Pointer to the new texture
// Comments				:
static inline unsigned char	*textureAllocateBlock(CTextureBlock *entry) {
	stats.textureSize				+=	entry->size;
	stats.peakTextureSize			=	max(stats.textureSize,stats.peakTextureSize);
	stats.textureMemory				+=	entry->size;
	stats.transferredTextureData	+=	entry->size;
	CRenderer::textureUsedMemory	+=	entry->size;

	unsigned char *data				=	new unsigned char[entry->size];

	// If we exceeded the maximum texture memory, phase out the last texture
	if (CRenderer::textureUsedMemory > CRenderer::textureMaxMemory)
		textureMemFlush(entry,FALSE);

	return data;
}

///////////////////////////////////////////////////////////////////////
// Function				:	textureLoadBlock
// Description			:	Read a block of texture from disk
// Return Value			:	Pointer to the new texture
// Comments				:
static inline void	textureLoadBlock(CTextureBlock *entry,char *name,int x,int y,int w,int h,int dir) {
	void			*data	=	NULL;
	TIFF			*in;

	osLock(CRenderer::textureMutex);
	if (entry->data != NULL) {
		osUnlock(CRenderer::textureMutex);
		return;
	}

	// Update the state
	stats.numTextureMisses++;

	// Set the error handler so we don't crash
	TIFFSetErrorHandler(tiffErrorHandler);
	TIFFSetWarningHandler(tiffErrorHandler);

	// Open the file
	in		=	TIFFOpen(name,"r");

	if (in != NULL) {		// Error, we opened this file before
							// The stupid user must have deleted the 
							// file or unmounted the drive while in progress
		uint32	width,height;
		uint16	numSamples;
		int		pixelSize;
		int		i;
		uint16	bitspersample;
		int		tiled;

		TIFFSetDirectory(in,dir);

		// Get the texture properties
		TIFFGetFieldDefaulted(in,TIFFTAG_IMAGEWIDTH              ,&width);
		TIFFGetFieldDefaulted(in,TIFFTAG_IMAGELENGTH             ,&height);
		TIFFGetFieldDefaulted(in,TIFFTAG_SAMPLESPERPIXEL         ,&numSamples);
		TIFFGetFieldDefaulted(in,TIFFTAG_BITSPERSAMPLE           ,&bitspersample);
		tiled	=	TIFFIsTiled(in);

		if (bitspersample == 8) {
			pixelSize	=	numSamples*sizeof(unsigned char);
		} else if(bitspersample == 16){
			pixelSize	=	numSamples*sizeof(unsigned short);
		} else {
			assert(bitspersample == 32);
			pixelSize	=	numSamples*sizeof(float);
		}

		// Allocate space for the texture
		assert(entry->data == NULL);
		data		=	textureAllocateBlock(entry);		

		// Do we need to read the entire texture ?
		if ((x != 0) || (y != 0) || (w != (int) width) || (h != (int) height)) {
			// No , is the file tiled ?
			if (!tiled) {
				// No, read the required portion
				unsigned char	*tdata;

				osLock(CRenderer::memoryMutex);
				memBegin(CRenderer::globalMemory);
				
				tdata		=	(unsigned char *) ralloc(width*height*pixelSize,CRenderer::globalMemory);

				// Read the entire image
				assert((int) (pixelSize*width) == TIFFScanlineSize(in));
				for (i=0;i<(int) height;i++) {
					TIFFReadScanline(in,&tdata[pixelSize*i*width],i,0);
					if (i >= (y+h))	break;	// If we read the last required scanline, break
				}

				for (i=0;i<h;i++) {
					memcpy(&((unsigned char *) data)[i*pixelSize*w],&tdata[((y+i)*width + x)*pixelSize],w*pixelSize);
				}

				memEnd(CRenderer::globalMemory);
				osUnlock(CRenderer::memoryMutex);
			} else {
				uint32	tileWidth,tileHeight;

				TIFFGetFieldDefaulted(in,TIFFTAG_TILEWIDTH              ,&tileWidth);
				TIFFGetFieldDefaulted(in,TIFFTAG_TILELENGTH             ,&tileHeight);
				assert(tileWidth		==	(uint32) w);
				assert(tileHeight		==	(uint32) h);
				assert((x % tileWidth)	== 0);
				assert((y % tileHeight) == 0);

				TIFFReadTile(in,data,x,y,0,0);
			}
		} else {
			// We need to read the entire texture
			if (tiled) {
				uint32	tileWidth,tileHeight;

				TIFFGetFieldDefaulted(in,TIFFTAG_TILEWIDTH              ,&tileWidth);
				TIFFGetFieldDefaulted(in,TIFFTAG_TILELENGTH             ,&tileHeight);

				if ((x != 0) || (y != 0) || (w != (int) tileWidth) || (h != (int) tileHeight)) {
					error(CODE_BUG,"Tiled unmade texture\n");
				} else {
					TIFFReadTile(in,data,x,y,0,0);
				}
			} else {
				int	i;

				// Read the entire image
				assert((int) (pixelSize*width) == TIFFScanlineSize(in));
				for (i=0;i<(int) height;i++) {
					TIFFReadScanline(in,&((unsigned char *) data)[pixelSize*i*width],i,0);
				}
			}
		}


		TIFFClose(in);
	} else {
		// FIXME: Is this an error ?
	}

	entry->data	=	data;

	osUnlock(CRenderer::textureMutex);
}

//////////////////////////////////////////////////////////////////////
// Function				:	texturRegisterBlock
// Description			:	Add a block into the list of used blocks
// Return Value			:	Pointer to the new block
// Comments				:
static inline void	textureRegisterBlock(CTextureBlock *cEntry,int size) {
	
	cEntry->prev						=	NULL;
	cEntry->next						=	CRenderer::textureUsedBlocks;
	if (CRenderer::textureUsedBlocks != NULL)
		CRenderer::textureUsedBlocks->prev	=	cEntry;
	CRenderer::textureUsedBlocks		=	cEntry;

	cEntry->data						=	NULL;
	cEntry->lastRefNumber				=	CRenderer::textureRefNumber;
	cEntry->size						=	size;
}

//////////////////////////////////////////////////////////////////////
// Function				:	texturUnregisterBlock
// Description			:	Remove the block
// Return Value			:	Pointer to the new block
// Comments				:
static inline void	textureUnregisterBlock(CTextureBlock *cEntry) {
	
	if (cEntry->next != NULL)	cEntry->next->prev						=	cEntry->prev;
	if (cEntry->prev != NULL)	cEntry->prev->next						=	cEntry->next;
	else						CRenderer::textureUsedBlocks			=	cEntry->next;

	if (cEntry->data != NULL) {
		stats.textureSize	-=	cEntry->size;
		stats.textureMemory	-=	cEntry->size;
		CRenderer::textureUsedMemory	-=	cEntry->size;
		delete [] (unsigned char *) cEntry->data;
	}
}






















///////////////////////////////////////////////////////////////////////
//
//		Class declerations
//
///////////////////////////////////////////////////////////////////////

// Texture wrapping modes
typedef enum {
	TEXTURE_PERIODIC	=	0,
	TEXTURE_BLACK,
	TEXTURE_CLAMP
} TTextureMode;



///////////////////////////////////////////////////////////////////////
// Class				:	CTextureLayer
// Description			:	This class encapsulates a single 2D texture layer in a file
// Comments				:
class	CTextureLayer  {
public:
						CTextureLayer(const char *name,short directory,int width,int height,short numSamples,int fileWidth,int fileHeight,TTextureMode sMode,TTextureMode tMode) {
							this->directory		=	directory;
							this->width			=	width;
							this->height		=	height;
							this->numSamples	=	numSamples;
							this->fileWidth		=	fileWidth;
							this->fileHeight	=	fileHeight;
							this->name			=	strdup(name);
							this->sMode			=	sMode;
							this->tMode			=	tMode;
						}

	virtual				~CTextureLayer() {
							free(name);
						}

	void				lookup(float *r,float s,float t,const CTextureLookup *lookup) { 
							s		*=	width;					// To the pixel space
							t		*=	height;
							int		si	=	(int) floor(s);		// The integer pixel coordinates
							int		ti	=	(int) floor(t);
							float	ds	=	s - si;
							float	dt	=	t - ti;

							if (si >= width)	si	=  (sMode == TEXTURE_PERIODIC) ? (si - width)  : (width-1);
							if (ti >= height)	ti	=  (tMode == TEXTURE_PERIODIC) ? (ti - height) : (height-1);

							float	res[4*3];
							lookupPixel(res,si,ti,lookup);

							float	tmp;

							tmp		=	(1-ds)*(1-dt);				// Bilinear interpolation
							r[0]	=	res[0]*tmp;
							r[1]	=	res[1]*tmp;
							r[2]	=	res[2]*tmp;

							tmp		=	ds*(1-dt);
							r[0]	+=	res[3]*tmp;
							r[1]	+=	res[4]*tmp;
							r[2]	+=	res[5]*tmp;

							tmp		=	(1-ds)*dt;
							r[0]	+=	res[6]*tmp;
							r[1]	+=	res[7]*tmp;
							r[2]	+=	res[8]*tmp;

							tmp		=	ds*dt;
							r[0]	+=	res[9]*tmp;
							r[1]	+=	res[10]*tmp;
							r[2]	+=	res[11]*tmp;
						}

	float				lookupz(float s,float t,float z,const CTextureLookup *lookup) {
							s		*=	width;						// To the pixel space
							t		*=	height;
							int		si		=	(int) floor(s);				// The integer pixel coordinates
							int		ti		=	(int) floor(t);
							float	ds		=	s - si;
							float	dt		=	t - ti;

							if (si >= width)	si	=  (sMode == TEXTURE_PERIODIC) ? (si - width)  : (width-1);
							if (ti >= height)	ti	=  (tMode == TEXTURE_PERIODIC) ? (ti - height) : (height-1);

							float	res[4*3];
							lookupPixel(res,si,ti,lookup);

							float	r		=	0;

							if (z > res[0]) {
								r		+=	(1-ds)*(1-dt);
							}

							if (z > res[3]) {
								r		+=	ds*(1-dt);
							}

							if (z > res[6]) {
								r		+=	(1-ds)*dt;
							}

							if (z > res[9]) {
								r		+=	ds*dt;
							}

							return r;
						}

	char				*name;															// The filename of the texture
	short				directory;														// The directory index in the tiff file
	short				numSamples;														// The number of samples in the texture
	int					width,height;													// The image info
	int					fileWidth,fileHeight;											// The physical size in the file
	TTextureMode		sMode,tMode;													// The wrap modes
protected:
	// This function must be overriden by the child class
	virtual	void		lookupPixel(float *,int,int,const CTextureLookup *)		=	0;		// Lookup 4 pixel values
};



///////////////////////////////////////////////////////////////////////
// Class				:	CBasicTexture
// Description			:	Thic class holds a basic uncached texture
// Comments				:
template <class T> class CBasicTexture : public CTextureLayer {
public:
					///////////////////////////////////////////////////////////////////////
					// Class				:	CBasicTexture
					// Method				:	CBasicTexture
					// Description			:	Ctor
					// Return Value			:	-
					// Comments				:
					CBasicTexture(const char *name,short directory,int width,int height,short numSamples,int fileWidth,int fileHeight,TTextureMode sMode,TTextureMode tMode,double Mult) : CTextureLayer(name,directory,width,height,numSamples,fileWidth,fileHeight,sMode,tMode) {
						textureRegisterBlock(&dataBlock,width*height*numSamples*sizeof(T));
						M				=	Mult;
					}

					///////////////////////////////////////////////////////////////////////
					// Class				:	CBasicTexture
					// Method				:	~CBasicTexture
					// Description			:	Dtor
					// Return Value			:	-
					// Comments				:
					~CBasicTexture() {
						textureUnregisterBlock(&dataBlock);
					}

protected:
					// The pixel lookup
			void	lookupPixel(float *res,int x,int y,const CTextureLookup *l) {

						if (dataBlock.data == NULL) {
							// The data is cached out
							textureLoadBlock(&dataBlock,name,0,0,fileWidth,fileHeight,directory);
						}

						// Texture cache management
						CRenderer::textureRefNumber++;
						dataBlock.lastRefNumber	=	CRenderer::textureRefNumber;

						int	xi		=	x+1;
						int	yi		=	y+1;
						
						assert(x >= 0);
						assert(y >= 0);
						assert(x < width);
						assert(y < height);

						// these must be after the xi,yi calculation
						//if (x < 0)			x  = (smode == TEXTURE_PERIODIC) ? (x + width)   : 0;
						//f (y < 0)			y  = (tmode == TEXTURE_PERIODIC) ? (y + height)  : 0;
						if (xi >= width)	xi = (sMode == TEXTURE_PERIODIC) ? (xi - width)  : (width - 1);
						if (yi >= height)	yi = (tMode == TEXTURE_PERIODIC) ? (yi - height) : (height - 1);

						const T		*data;

						if (l->lookupFloat) {
#define access(__x,__y)											\
							data	=	&((T *) dataBlock.data)[(__y*fileWidth+__x)*numSamples+l->channel];	\
							res[0]	=	(float) (data[0]*M);	\
							res[1]	=	l->fill;				\
							res[2]	=	l->fill;				\
							res		+=	3;

							access(x,y);
							access(xi,y);
							access(x,yi);
							access(xi,yi);
#undef access

						} else {
#define access(__x,__y)											\
							data	=	&((T *) dataBlock.data)[(__y*fileWidth+__x)*numSamples+l->channel];	\
							res[0]	=	(float) (data[0]*M);	\
							res[1]	=	(float) (data[1]*M);	\
							res[2]	=	(float) (data[2]*M);	\
							res		+=	3;

							access(x,y);
							access(xi,y);
							access(x,yi);
							access(xi,yi);
#undef access
						}
					}

private:
	CTextureBlock	dataBlock;
	double			M;
};

///////////////////////////////////////////////////////////////////////
// Class				:	CTiledTexture
// Description			:	Thi class holds info about a tiled texture (tiled textures are cached in tiles)
// Comments				:
template <class T> class CTiledTexture : public CTextureLayer {
public:
				///////////////////////////////////////////////////////////////////////
				// Class				:	CTiledTexture
				// Method				:	CTiledTexture
				// Description			:	Ctor
				// Return Value			:	-
				// Comments				:
				CTiledTexture(const char *name,short directory,int width,int height,short numSamples,int fileWidth,int fileHeight,TTextureMode sMode,TTextureMode tMode,int tileSize,int tileSizeShift,double Mult) : CTextureLayer(name,directory,width,height,numSamples,fileWidth,fileHeight,sMode,tMode) {
					this->tileSize		=	tileSize;
					this->tileSizeShift	=	tileSizeShift;

					xTiles				=	(int) ceil((float) width / (float) tileSize);
					yTiles				=	(int) ceil((float) height / (float) tileSize);

					const int	tileLength	=	tileSize*tileSize*numSamples*sizeof(T);
					int			i,j;

					dataBlocks			=	new CTextureBlock*[yTiles];
					for (i=0;i<yTiles;i++) {
						dataBlocks[i]	=	new CTextureBlock[xTiles];

						for (j=0;j<xTiles;j++) {
							textureRegisterBlock(dataBlocks[i] + j,tileLength);
						}
					}

					M					=	Mult;
				}

				///////////////////////////////////////////////////////////////////////
				// Class				:	CTiledTexture
				// Method				:	~CTiledTexture
				// Description			:	Dtor
				// Return Value			:	-
				// Comments				:
				~CTiledTexture() {
					int i,j;

					for (i=0;i<yTiles;i++) {
						for (j=0;j<xTiles;j++) {
							textureUnregisterBlock(&dataBlocks[i][j]);
						}

						delete [] dataBlocks[i];
					}

					delete [] dataBlocks;
				}

protected:

					// Pixel lookup
	void			lookupPixel(float *res,int x,int y,const CTextureLookup *l) {
						int					xTile;
						int					yTile;
						CTextureBlock		*block;
						const T				*data;
						const int			t		=	tileSize - 1;

						int	xi		=	x+1;
						int	yi		=	y+1;
						
						// these must be after the xi,yi calculation
						assert(x >= 0);
						assert(y >= 0);
						assert(x < width);
						assert(y < height);

						//if (x < 0)			x  = (smode == TEXTURE_PERIODIC) ? (x + width)   : 0;
						//if (y < 0)			y  = (tmode == TEXTURE_PERIODIC) ? (y + height)  : 0;
						if (xi >= width)	xi = (sMode == TEXTURE_PERIODIC) ? (xi - width)  : (width - 1);
						if (yi >= height)	yi = (tMode == TEXTURE_PERIODIC) ? (yi - height) : (height - 1);

						if (l->lookupFloat) {
#define	access(__x,__y)																\
							xTile	=	__x >> tileSizeShift;						\
							yTile	=	__y >> tileSizeShift;						\
							block	=	dataBlocks[yTile] + xTile;					\
																					\
							if (block->data == NULL) {								\
								textureLoadBlock(block,name,xTile << tileSizeShift,yTile << tileSizeShift,tileSize,tileSize,directory);		\
							}														\
																					\
							CRenderer::textureRefNumber++;							\
							block->lastRefNumber	=	CRenderer::textureRefNumber;	\
																					\
							data	=	&((T *) block->data)[(((__y & t) << tileSizeShift)+(__x & t))*numSamples+l->channel];	\
							res[0]	=	(float) (data[0]*M);						\
							res[1]	=	l->fill;									\
							res[2]	=	l->fill;									\
							res		+=	3;

							access(x,y);
							access(xi,y);
							access(x,yi);
							access(xi,yi);

#undef access

						} else {
#define	access(__x,__y)																\
							xTile	=	__x >> tileSizeShift;						\
							yTile	=	__y >> tileSizeShift;						\
							block	=	dataBlocks[yTile] + xTile;					\
																					\
							if (block->data == NULL) {								\
								textureLoadBlock(block,name,xTile << tileSizeShift,yTile << tileSizeShift,tileSize,tileSize,directory);		\
							}														\
																					\
							CRenderer::textureRefNumber++;							\
							block->lastRefNumber	=	CRenderer::textureRefNumber;	\
																					\
							data	=	&((T *) block->data)[(((__y & t) << tileSizeShift)+(__x & t))*numSamples+l->channel];	\
							res[0]	=	(float) (data[0]*M);						\
							res[1]	=	(float) (data[1]*M);						\
							res[2]	=	(float) (data[2]*M);						\
							res		+=	3;

							access(x,y);
							access(xi,y);
							access(x,yi);
							access(xi,yi);

#undef access
						}
					}

						

	CTextureBlock	**dataBlocks;
	int				xTiles,yTiles;
	int				tileSize,tileSizeShift;
	double			M;
};











///////////////////////////////////////////////////////////////////////
// Class				:	CMadeTexture
// Description			:	A previously made texture
// Comments				:
class	CMadeTexture : public CTexture {
public:
						CMadeTexture(const char *name) : CTexture(name) {
							numLayers	=	0;
							layers		=	NULL;
						}

	virtual				~CMadeTexture() {
							if (layers != NULL) {
								int	i;

								for (i=0;i<numLayers;i++)
									delete layers[i];
								delete [] layers;
							}
						}

	float				lookupz(float s,float t,float z,const CTextureLookup *lookup) {
							assert(numLayers > 0);
							return layers[0]->lookupz(s,t,z,lookup);
						}

	void				lookup(float *result,float s,float t,const CTextureLookup *l) {

							// Do the s mode
							switch(layers[0]->sMode) {
							case TEXTURE_PERIODIC:
								s	=	fmodf(s,1);
								if (s < 0)	s	+=	1;
								break;
							case TEXTURE_BLACK:
								if ((s < 0) || (s > 1)) {
									initv(result,l->fill,l->fill,l->fill);
									return;
								}
								break;
							case TEXTURE_CLAMP:
								if (s < 0)		s	=	0;
								if (s > 1)		s	=	1;
								break;
							}

							// Do the t mode
							switch(layers[0]->tMode) {
							case TEXTURE_PERIODIC:
								t	=	fmodf(t,1);
								if (t < 0)	t	+=	1;
								break;
							case TEXTURE_BLACK:
								if ((t < 0) || (t > 1)) {
									initv(result,l->fill,l->fill,l->fill);
									return;
								}
								break;
							case TEXTURE_CLAMP:
								if (t < 0)		t	=	0;
								if (t > 1)		t	=	1;
								break;
							}

							layers[0]->lookup(result,s,t,l);
						}

	void				lookup4(float *result,const float *u,const float *v,const CTextureLookup *lookup) {
							int				i;
							float			totalContribution	=	0;
							CTextureLayer	*layer0,*layer1;
							float			offset;
							float			l;
							float			diag;
							const float		cs	=	((u[0] + u[1] + u[2] + u[3]) * 0.25f);
							const float		ct	=	((v[0] + v[1] + v[2] + v[3]) * 0.25f);
							float			ds,dt,d;

							const int		width	=	layers[0]->width;
							const int		height	=	layers[0]->height;

							// Compute the tri-linear level
							ds			=	(u[0] - cs)*width;
							dt			=	(v[0] - ct)*height;
							diag		=	ds*ds + dt*dt;

							ds			=	(u[1] - cs)*width;
							dt			=	(v[1] - ct)*height;
							d			=	ds*ds + dt*dt;
							diag		=	min(d,diag);

							ds			=	(u[2] - cs)*width;
							dt			=	(v[2] - ct)*height;
							d			=	ds*ds + dt*dt;
							diag		=	min(d,diag);

							ds			=	(u[3] - cs)*width;
							dt			=	(v[3] - ct)*height;
							d			=	ds*ds + dt*dt;
							diag		=	min(d,diag);

							diag		+=	lookup->blur*lookup->blur*width*height;

																	// Find the layer that we want to probe
							l			=	(logf(diag)*0.5f*(1/logf(2.0f)));
							l			=	max(l,0);

							i			=	(int) floor(l);
							if (i >= (numLayers-1)) i =	numLayers-2;

							layer0		=	layers[i];
							layer1		=	layers[i+1];	
							offset		=	l - i;
							offset		=	min(offset,1);

							initv(result,0,0,0);					// Result is black
							for (i=lookup->numSamples;i>0;i--) {
								float			r[2];
								float			s,t;
								vector			C,CC0,CC1;
								float			contribution;

								generator.get(r);

								s					=	(u[0]*(1-r[0]) + u[1]*r[0])*(1-r[1])	+
														(u[2]*(1-r[0]) + u[3]*r[0])*r[1];
								t					=	(v[0]*(1-r[0]) + v[1]*r[0])*(1-r[1])	+
														(v[2]*(1-r[0]) + v[3]*r[0])*r[1];

								contribution		=	lookup->filter(r[0]-0.5f,r[1]-0.5f,1,1);
								totalContribution	+=	contribution;

								// Do the s mode
								switch(layers[0]->sMode) {
								case TEXTURE_PERIODIC:
									s	=	fmodf(s,1);
									if (s < 0)	s	+=	1;
									break;
								case TEXTURE_BLACK:
									if ((s < 0) || (s > 1)) {
										continue;
									}
									break;
								case TEXTURE_CLAMP:
									if (s < 0)		s	=	0;
									if (s > 1)		s	=	1;
									break;
								}

								// Do the t mode
								switch(layers[0]->tMode) {
								case TEXTURE_PERIODIC:
									t	=	fmodf(t,1);
									if (t < 0)	t	+=	1;
									break;
								case TEXTURE_BLACK:
									if ((t < 0) || (t > 1)) {
										continue;
									}
									break;
								case TEXTURE_CLAMP:
									if (t < 0)		t	=	0;
									if (t > 1)		t	=	1;
									break;
								}

												// lookup (s,t) and add it to the result
								layer0->lookup(CC0,s,t,lookup);
								layer1->lookup(CC1,s,t,lookup);
								interpolatev(C,CC0,CC1,offset);

								result[0]		+=	C[0]*contribution;
								result[1]		+=	C[1]*contribution;
								result[2]		+=	C[2]*contribution;
							}

							const	float	tmp	=	1 / totalContribution;
							mulvf(result,tmp);
						}

	
	// textureinfo support
	void				getResolution(float *r) 	{ r[0] = (float) layers[0]->width; r[1] = (float) layers[0]->height; }
	int 				getNumChannels()			{ return layers[0]->numSamples; }

	short				numLayers;					// The number of layers
	CTextureLayer		**layers;					// The actual layers
	CSobol<2>			generator;
};

///////////////////////////////////////////////////////////////////////
// Class				:	CRegularTexture
// Description			:	A regular texture
// Comments				:
class	CRegularTexture : public CTexture {
public:
						CRegularTexture(const char *name) : CTexture(name) {
							layer	=	NULL;
						}

	virtual				~CRegularTexture() {
							if (layer != NULL) delete  layer;
						}

	float				lookupz(float s,float t,float z,const CTextureLookup *lookup) {
							assert(layer != NULL);
							return layer->lookupz(s,t,z,lookup);
						}


	void				lookup(float *result,float s,float t,const CTextureLookup *l) {
							// Do the s mode
							switch(layer->sMode) {
							case TEXTURE_PERIODIC:
								s	=	fmodf(s,1);
								if (s < 0)	s	+=	1;
								break;
							case TEXTURE_BLACK:
								if ((s < 0) || (s > 1)) {
									initv(result,l->fill,l->fill,l->fill);
									return;
								}
								break;
							case TEXTURE_CLAMP:
								if (s < 0)		s	=	0;
								if (s > 1)		s	=	1;
								break;
							}

							// Do the t mode
							switch(layer->tMode) {
							case TEXTURE_PERIODIC:
								t	=	fmodf(t,1);
								if (t < 0)	t	+=	1;
								break;
							case TEXTURE_BLACK:
								if ((t < 0) || (t > 1)) {
									initv(result,l->fill,l->fill,l->fill);
									return;
								}
								break;
							case TEXTURE_CLAMP:
								if (t < 0)		t	=	0;
								if (t > 1)		t	=	1;
								break;
							}

							layer->lookup(result,s,t,l);
						}

	void				lookup4(float *result,const float *u,const float *v,const CTextureLookup *lookup) {
							int			i;
							float		totalContribution	=	0;

							initv(result,0,0,0);		// Result is black
							for (i=lookup->numSamples;i>0;i--) {
								float			s,t;
								vector			C;
								float			contribution;
								float			r[2];

								generator.get(r);

								s					=	(u[0]*(1-r[0]) + u[1]*r[0])*(1-r[1])	+
														(u[2]*(1-r[0]) + u[3]*r[0])*r[1];
								t					=	(v[0]*(1-r[0]) + v[1]*r[0])*(1-r[1])	+
														(v[2]*(1-r[0]) + v[3]*r[0])*r[1];
								contribution		=	lookup->filter(r[0]-(float) 0.5,r[1]-(float) 0.5,1,1);
								totalContribution	+=	contribution;

								if (lookup->blur > 0) {
									generator.get(r);
									s				+=	lookup->blur*(r[0] - 0.5f);
									t				+=	lookup->blur*(r[1] - 0.5f);
								}

								// Do the s mode
								switch(layer->sMode) {
								case TEXTURE_PERIODIC:
									s	=	fmodf(s,1);
									if (s < 0)	s	+=	1;
									break;
								case TEXTURE_BLACK:
									if ((s < 0) || (s > 1)) {
										continue;
									}
									break;
								case TEXTURE_CLAMP:
									if (s < 0)		s	=	0;
									if (s > 1)		s	=	1;
									break;
								}

								// Do the t mode
								switch(layer->tMode) {
								case TEXTURE_PERIODIC:
									t	=	fmodf(t,1);
									if (t < 0)	t	+=	1;
									break;
								case TEXTURE_BLACK:
									if ((t < 0) || (t > 1)) {
										continue;
									}
									break;
								case TEXTURE_CLAMP:
									if (t < 0)		t	=	0;
									if (t > 1)		t	=	1;
									break;
								}
												// lookup (s,t) and add it to the result
								layer->lookup(C,s,t,lookup);

								result[0]		+=	C[0]*contribution;
								result[1]		+=	C[1]*contribution;
								result[2]		+=	C[2]*contribution;
							}

							const float	tmp	=	1 / totalContribution;
							mulvf(result,tmp);
						}
	
	// textureinfo support
	void				getResolution(float *r) 	{ r[0] = (float) layer->width; r[1] = (float) layer->height; }
	int 				getNumChannels()			{ return layer->numSamples; }
	
	CTextureLayer		*layer;						// There's only one layer
	CSobol<2>			generator;
};


///////////////////////////////////////////////////////////////////////
// Class				:	CShadow
// Description			:	A single sided shadow map
// Comments				:
class	CShadow : public CEnvironment{
public:

						CShadow(const char *name,float *toNDC,CTexture *side) : CEnvironment(name) {
							movmm(this->toNDC,toNDC);
							this->side	=	side;
						}

	virtual				~CShadow() {
							if (side != NULL)	delete side;
						}

	void				lookup(float *result,const float *D0,const float *D1,const float *D2,const float *D3,const CTextureLookup *lookup) {
							int			i;
							float		totalContribution	=	0;
							float		r[4];

							result[0]	=	0;
							for (i=lookup->numSamples;i>0;i--) {
								float	x,y;
								float	s,t;
								float	C;
								float	contribution;
								float	tmp[4],cP[4];

								generator.get(r);

								x					=	r[0];	// Assume x,y are gaussian samples
								y					=	r[1];
								contribution		=	lookup->filter(x - 0.5f,y - 0.5f,1,1);
								totalContribution	+=	contribution;

								cP[COMP_X]			=	(D0[COMP_X]*(1-x) + D1[COMP_X]*x)*(1-y) + (D2[COMP_X]*(1-x) + D3[COMP_X]*x)*y;
								cP[COMP_Y]			=	(D0[COMP_Y]*(1-x) + D1[COMP_Y]*x)*(1-y) + (D2[COMP_Y]*(1-x) + D3[COMP_Y]*x)*y;
								cP[COMP_Z]			=	(D0[COMP_Z]*(1-x) + D1[COMP_Z]*x)*(1-y) + (D2[COMP_Z]*(1-x) + D3[COMP_Z]*x)*y;
								cP[3]				=	1;

								mulmp4(tmp,toNDC,cP);
								s					=	tmp[0] / tmp[3];
								t					=	tmp[1] / tmp[3];

								// Blur the result
								s					+=	2*(r[2]-0.5f)*lookup->blur;
								t					+=	2*(r[3]-0.5f)*lookup->blur;


								if ((s < 0) || (s > 1) || (t < 0) || (t > 1)) {
									continue;
								}

								C	=	side->lookupz(s,t,tmp[2]-lookup->shadowBias,lookup);

								result[0]			+=	C*contribution;
							}

							result[0]	/=	totalContribution;
							result[1]	=	result[0];
							result[2]	=	result[0];
						}
	
	// textureinfo support
	void				getResolution(float *r) 	{ side->getResolution(r); }
	char* 				getTextureType()			{ return "shadow"; }
	int 				getNumChannels()			{ return side->getNumChannels(); }
	int 				getViewMatrix(float *m)		{ movmm(m,toNDC); return TRUE; }
	int 				getProjectionMatrix(float*)	{ return FALSE; }

private:
	CTexture			*side;
	matrix				toNDC;
	CSobol<4>			generator;
};



///////////////////////////////////////////////////////////////////////
// Class				:	CDeepShadow
// Description			:	A deep shadow map
// Comments				:
class	CDeepShadow : public CEnvironment{

	// Holds a deep tile
	class	CDeepTile {
	public:
		float			**data;
		float			**lastData;
		CTextureBlock	block;
	};

public:

						CDeepShadow(const char *name,const char *fn,const float *toWorld,FILE *in) : CEnvironment(name) {
							int		i,k;
							matrix	mtmp;
							int		*tileSizes;

							fileName	=	strdup(fn);

							// Read the header
							fread(&header,sizeof(CDeepShadowHeader),1,in);
							mulmm(mtmp,header.toNDC,toWorld);
							movmm(header.toNDC,mtmp);

							// Read the tile end indices
							tileIndices		=	new int[header.xTiles*header.yTiles];
							fread(tileIndices,sizeof(int),header.xTiles*header.yTiles,in);

							// new-style tsm file
							tileSizes	=	new int[header.xTiles*header.yTiles];
							fread(tileSizes,sizeof(int),header.xTiles*header.yTiles,in);
							
							// Save the index start
							fileStart		=	ftell(in);
							
							// Init the tiles
							tiles	=	new CDeepTile*[header.yTiles];
							for (k=0,i=0;i<header.yTiles;i++) {
								int	j;

								tiles[i]	=	new CDeepTile[header.xTiles];

								for (j=0;j<header.xTiles;j++,k++) {
									CDeepTile	*cTile	=	tiles[i]+j;
									int			size;

									size				=	tileSizes[k];

									textureRegisterBlock(&(cTile->block),size);
									cTile->data			=	new float*[header.tileSize*header.tileSize];
									cTile->lastData		=	new float*[header.tileSize*header.tileSize];
								}
							}

							delete[] tileSizes;
								
							fclose(in);
						}

	virtual				~CDeepShadow() {
							int	i,j;

							for (j=0;j<header.yTiles;j++) {
								for (i=0;i<header.xTiles;i++) {
									textureUnregisterBlock(&(tiles[j][i].block));
									delete [] tiles[j][i].lastData;
									delete [] tiles[j][i].data;
								}
								delete [] tiles[j];
							}
							delete [] tiles;

							delete [] tileIndices;

							free(fileName);
						}

	void				lookup(float *result,const float *D0,const float *D1,const float *D2,const float *D3,const CTextureLookup *lookup) {
							int			i;
							float		totalContribution	=	0;

							result[0]	=	0;
							result[1]	=	0;
							result[2]	=	0;
							for (i=lookup->numSamples;i>0;i--) {
								float		x,y;		// Assume x,y are gaussian samples
								float		s,t,w;
								float		contribution;
								float		tmp[4],cP[4];
								int			px,py;
								int			bx,by;
								CDeepTile	*cTile;
								float		*cPixel;

								x					=	urand();
								y					=	urand();
								contribution		=	lookup->filter(x - 0.5f,y - 0.5f,1,1);
								totalContribution	+=	contribution;

								cP[COMP_X]			=	(D0[COMP_X]*(1 - x) + D1[COMP_X]*x)*(1-y) + (D2[COMP_X]*(1 - x) + D3[COMP_X]*x)*y;
								cP[COMP_Y]			=	(D0[COMP_Y]*(1 - x) + D1[COMP_Y]*x)*(1-y) + (D2[COMP_Y]*(1 - x) + D3[COMP_Y]*x)*y;
								cP[COMP_Z]			=	(D0[COMP_Z]*(1 - x) + D1[COMP_Z]*x)*(1-y) + (D2[COMP_Z]*(1 - x) + D3[COMP_Z]*x)*y;
								cP[3]				=	1;

								mulmp4(tmp,header.toNDC,cP);
								s					=	tmp[0] / tmp[3];
								t					=	tmp[1] / tmp[3];
								if ((s < 0) || (s >= 1) || (t < 0) || (t >= 1)) {
									continue;
								}

								s					*=	header.xres;
								t					*=	header.yres;
								w					=	tmp[2] - lookup->shadowBias;

								px					=	(int) floor(s);
								py					=	(int) floor(t);
								bx					=	px >> header.tileShift;
								by					=	py >> header.tileShift;
								px					=	px & ((1 << header.tileShift) - 1);
								py					=	py & ((1 << header.tileShift) - 1);

								cTile				=	tiles[by]+bx;

								if (cTile->block.data == NULL)	loadTile(bx,by);

								cPixel				=	cTile->lastData[py*header.tileSize+px];

								while(TRUE) {
									if (cPixel[0] > w)		cPixel	-=	4;
									else if (cPixel[4] < w)	cPixel	+=	4;
									else {
										const float	alpha	=	(w - cPixel[0]) / (cPixel[4] - cPixel[0]);

										result[0]			+=	(1-((1-alpha)*cPixel[1] + alpha*cPixel[5]))*contribution;
										result[1]			+=	(1-((1-alpha)*cPixel[2] + alpha*cPixel[6]))*contribution;
										result[2]			+=	(1-((1-alpha)*cPixel[3] + alpha*cPixel[7]))*contribution;

										cTile->lastData[py*header.tileSize+px]	=	cPixel;

										break;
									}
								}

								//	0	-	z
								//	1	-	r
								//	2	-	g
								//	3	-	b

								//	4	-	z
								//	5	-	r
								//	6	-	g
								//	7	-	b
							}

							result[0]	/=	totalContribution;
							result[1]	/=	totalContribution;
							result[2]	/=	totalContribution;
						}
	
	// textureinfo support
	void				getResolution(float *r) 	{ r[0] = (float) header.xres; r[1] = (float) header.yres; }
	char* 				getTextureType()			{ return "shadow"; }
	int 				getNumChannels()			{ return 4; }
	int 				getViewMatrix(float *m)		{ movmm(m,header.toNDC); return TRUE; }
	int 				getProjectionMatrix(float*)	{ return FALSE; }
	
private:
	void				loadTile(int x,int y) {

							CDeepTile	*cTile	=	tiles[y]+x;

							osLock(CRenderer::textureMutex);
							if (cTile->block.data != NULL) {
								osUnlock(CRenderer::textureMutex);
								return;
							}

							int			index	=	y*header.xTiles+x;
							FILE		*in		=	fopen(fileName,"rb");
							float		**cData;
							float		**cLastData;
							float		*data,*dataStart;
							int			i;
							int			startIndex;

							assert(in != NULL);

							startIndex	=	tileIndices[index];

							dataStart	=	data	=	(float *) textureAllocateBlock(&(cTile->block));
							fseek(in,startIndex,SEEK_SET);
							fread(data,sizeof(unsigned char),cTile->block.size,in);
							fclose(in);

							cLastData		=	cTile->lastData;
							cData			=	cTile->data;
							for (i=header.tileSize*header.tileSize;i>0;i--) {
								cData[0]		=	data;
								cLastData[0]	=	data;
								cData++;
								cLastData++;

								if (i != 1) {
									data		+=	4;
									while(*data != -C_INFINITY)	data	+=	4;
								}
							}

							cTile->block.data	=	dataStart;
							osUnlock(CRenderer::textureMutex);
						}

	char				*fileName;				// The name of the file
	CDeepTile			**tiles;				// Array of tiles
	int					*tileIndices;			// The tile offset index in the file
	CDeepShadowHeader	header;					// The header
	int					fileStart;				// The offset in the file
};



///////////////////////////////////////////////////////////////////////
// Class				:	CCubicEnvironment
// Description			:	A Cubic environment map
// Comments				:
class	CCubicEnvironment : public CEnvironment{
public:

						CCubicEnvironment(const char *name,CTexture **s) : CEnvironment(name) {
							sides[0]		=	s[0];
							sides[1]		=	s[1];
							sides[2]		=	s[2];
							sides[3]		=	s[3];
							sides[4]		=	s[4];
							sides[5]		=	s[5];
						}

	virtual				~CCubicEnvironment() {
							if (sides[0] != NULL)		delete sides[0];
							if (sides[1] != NULL)		delete sides[1];
							if (sides[2] != NULL)		delete sides[2];
							if (sides[3] != NULL)		delete sides[3];
							if (sides[4] != NULL)		delete sides[4];
							if (sides[5] != NULL)		delete sides[5];
						}

						typedef enum {
							PX		=	0,
							NX,
							PY,
							NY,
							PZ,
							NZ,
						} ESide;

	
						typedef enum {
							XYZ		=	0,
							XZY,
							YXZ,
							YZX,
							ZXY,
							ZYX
						} EOrder;


	void				lookup(float *result,const float *D0,const float *D1,const float *D2,const float *D3,const CTextureLookup *lookup) {
							EOrder		order;
							CTexture	*side;
							float		u,v;
							vector		D;
							int			i;
							float		totalContribution	=	0;
							float		r[2];
							vector		C;

							result[0]	=	0;
							result[1]	=	0;
							result[2]	=	0;

							if (dotvv(D0,D0) == 0)	return;

							for (i=lookup->numSamples;i>0;i--) {
								float	x,y;
								float	t;
								float	contribution;

								generator.get(r);

								x					=	r[0];	// Assume x,y are gaussian samples
								y					=	r[1];
								contribution		=	lookup->filter(x - (float) 0.5,y - (float) 0.5,1,1);
								totalContribution	+=	contribution;

								D[0]				=	(D0[0]*(1-x) + D1[0]*x)*(1-y) + (D2[0]*(1-x) + D3[0]*x)*y;
								D[1]				=	(D0[1]*(1-x) + D1[1]*x)*(1-y) + (D2[1]*(1-x) + D3[1]*x)*y;
								D[2]				=	(D0[2]*(1-x) + D1[2]*x)*(1-y) + (D2[2]*(1-x) + D3[2]*x)*y;

								// Find the side of the cube that we're looking at
								if (fabs(D[COMP_Y]) > fabs(D[COMP_X])) {
									if (fabs(D[COMP_Z]) > fabs(D[COMP_Y])) {
										order	=	ZYX;
									} else {
										if (fabs(D[COMP_Z]) > fabs(D[COMP_X]))
											order	=	YZX;
										else
											order	=	YXZ;
									}
								} else if (fabs(D[COMP_Z]) > fabs(D[COMP_Y])) {
									if (fabs(D[COMP_Z]) > fabs(D[COMP_X]))
										order	=	ZXY;
									else
										order	=	XZY;
								} else {
									order		=	XYZ;
								}

								switch(order) {
								case XYZ:
								case XZY:
									if (D[COMP_X] > 0)	{	
										side	=	sides[PX];	
										t		=	1 / D[COMP_X];
										u		=	(-D[COMP_Z]*t+1)*0.5f;
										v		=	(-D[COMP_Y]*t+1)*0.5f;
									} else {
										side	=	sides[NX];
										t		=	-1 / D[COMP_X];
										u		=	(D[COMP_Z]*t+1)*0.5f;
										v		=	(-D[COMP_Y]*t+1)*0.5f;
									}
									break;
								case YXZ:
								case YZX:
									if (D[COMP_Y] > 0) {
										side	=	sides[PY];	
										t		=	1 / D[COMP_Y];
										u		=	(D[COMP_X]*t+1)*0.5f;
										v		=	(D[COMP_Z]*t+1)*0.5f;
									} else	{
										side	=	sides[NY];	
										t		=	-1 / D[COMP_Y];
										u		=	(D[COMP_X]*t+1)*0.5f;
										v		=	(-D[COMP_Z]*t+1)*0.5f;
									}
									break;
								case ZXY:
								case ZYX:
									if (D[COMP_Z] > 0) {
										side	=	sides[PZ];
										t		=	1 / D[COMP_Z];
										u		=	(D[COMP_X]*t+1)*0.5f;
										v		=	(-D[COMP_Y]*t+1)*0.5f;
									} else {
										side	=	sides[NZ];
										t		=	-1 / D[COMP_Z];
										u		=	(-D[COMP_X]*t+1)*0.5f;
										v		=	(-D[COMP_Y]*t+1)*0.5f;
									}

									break;
								}


								side->lookup(C,u,v,lookup);

								result[0]	+=	C[0]*contribution;
								result[1]	+=	C[1]*contribution;
								result[2]	+=	C[2]*contribution;
							}

							mulvf(result,1 / totalContribution);
						}

	// textureinfo support
	void				getResolution(float *r) 	{ sides[0]->getResolution(r); }
	char* 				getTextureType()			{ return "environment"; }
	int 				getNumChannels()			{ return sides[0]->getNumChannels(); }
	int 				getViewMatrix(float *m)		{ return FALSE; }
	int 				getProjectionMatrix(float*)	{ return FALSE; }
	
	CTexture			*sides[6];
	CSobol<2>			generator;
};


///////////////////////////////////////////////////////////////////////
// Class				:	CSphericalEnvironment
// Description			:	A Spherical environment map
// Comments				:	RenderMan does not support cylinderical env. maps yet so this class is not used
class	CSphericalEnvironment : public CEnvironment{
public:

						CSphericalEnvironment(const char *name,CTexture *s) : CEnvironment(name) {
							side	=	s;
						}

	virtual				~CSphericalEnvironment() {
							delete side;
						}

	void				lookup(float *result,const float *D0,const float *D1,const float *D2,const float *D3,const CTextureLookup *lookup) {
							float		u[4],v[4];
							float		m;

							m					=	2*sqrtf(D0[COMP_X]*D0[COMP_X] + D0[COMP_Y]*D0[COMP_Y] + (D0[COMP_Z]+1)*(D0[COMP_Z]+1));
							u[0]				=	D0[COMP_X] / m + 0.5f;
							v[0]				=	D0[COMP_Y] / m + 0.5f;

							m					=	2*sqrtf(D1[COMP_X]*D1[COMP_X] + D1[COMP_Y]*D1[COMP_Y] + (D1[COMP_Z]+1)*(D1[COMP_Z]+1));
							u[1]				=	D1[COMP_X] / m + 0.5f;
							v[1]				=	D1[COMP_Y] / m + 0.5f;

							m					=	2*sqrtf(D2[COMP_X]*D2[COMP_X] + D2[COMP_Y]*D2[COMP_Y] + (D2[COMP_Z]+1)*(D2[COMP_Z]+1));
							u[2]				=	D2[COMP_X] / m + 0.5f;
							v[2]				=	D2[COMP_Y] / m + 0.5f;

							m					=	2*sqrtf(D3[COMP_X]*D3[COMP_X] + D3[COMP_Y]*D3[COMP_Y] + (D3[COMP_Z]+1)*(D3[COMP_Z]+1));
							u[3]				=	D3[COMP_X] / m + 0.5f;
							v[3]				=	D3[COMP_Y] / m + 0.5f;

							side->lookup4(result,u,v,lookup);
						}

	// textureinfo support
	void				getResolution(float *r) 	{ side->getResolution(r); }
	char* 				getTextureType()			{ return "environment"; }
	int 				getNumChannels()			{ return side->getNumChannels(); }
	int 				getViewMatrix(float *m)		{ return FALSE; }
	int 				getProjectionMatrix(float*)	{ return FALSE; }
	
	CTexture			*side;
};

///////////////////////////////////////////////////////////////////////
// Class				:	CCylindericalEnvironment
// Description			:	A Cylinderical environment map
// Comments				:
class	CCylindericalEnvironment : public CEnvironment{
public:

						CCylindericalEnvironment(const char *name,CTexture *s) : CEnvironment(name) {
							side	=	s;
						}

	virtual				~CCylindericalEnvironment() {
							delete side;
						}

	void				lookup(float *result,const float *D0,const float *D1,const float *D2,const float *D3,const CTextureLookup *lookup) {
							float		u[4],v[4];
							double		a,b,c;
							vector		D,Dsamp;

							if (dotvv(D0,D0) > 0) {
								normalizev(D,D0);
								movvv(Dsamp,D);
								u[0]				=	(atan2f(D[COMP_Z],D[COMP_X]) +(float)  C_PI) * (1.0f / (2.0f* (float) C_PI));
								v[0]				=	acosf(D[COMP_Y]) * (1.0f / (float) C_PI);
								
								c = (D[COMP_X]*D[COMP_X]+D[COMP_Z]*D[COMP_Z])*2.0*C_PI;
								a = -D[COMP_Z]/c;
								b = D[COMP_X]/c;
								c = -1.0f/(C_PI*sqrt(1.0f-D[COMP_Y]*D[COMP_Y] + C_EPSILON));
										
								normalizev(D,D1);
								subvv(D,Dsamp);
								u[1]				=	u[0] + (float) (a*D[COMP_X] + b*D[COMP_Z]);
								v[1]				=	v[0] + (float) (c*D[COMP_Y]);

								normalizev(D,D2);
								subvv(D,Dsamp);
								u[2]				=	u[0] + (float) (a*D[COMP_X] + b*D[COMP_Z]);
								v[2]				=	v[0] + (float) (c*D[COMP_Y]);
								
								normalizev(D,D3);
								subvv(D,Dsamp);
								u[3]				=	u[0] + (float) (a*D[COMP_X] + b*D[COMP_Z]);
								v[3]				=	v[0] + (float) (c*D[COMP_Y]);
								
								side->lookup4(result,u,v,lookup);
							} else {
								initv(result,0,0,0);
							}
						}

	// textureinfo support
	void				getResolution(float *r) 	{ side->getResolution(r); }
	char* 				getTextureType()			{ return "environment"; }
	int 				getNumChannels()			{ return side->getNumChannels(); }
	int 				getViewMatrix(float *m)		{ return FALSE; }
	int 				getProjectionMatrix(float*)	{ return FALSE; }
	
	CTexture			*side;
};
































































///////////////////////////////////////////////////////////////////////
// Function				:	readTexture
// Description			:	Read the pyramid layers
// Return Value			:	TRUE on success
// Comments				:
template <class T> static CTexture	*readMadeTexture(const char *name,const char *aname,TIFF *in,int dstart,int width,int height,char *smode,char *tmode,T enforcer) {
	CMadeTexture			*cTexture;
	int						i,j;
	uint32					fileWidth,fileHeight;
	uint32					tileWidth,tileHeight;
	uint16					numSamples;
	int						cwidth,cheight;
	TTextureMode			sMode,tMode;
	int						tileSize,tileSizeShift;
	double					M;

	fileWidth				=	0;
	fileHeight				=	0;
	numSamples				=	0;

	TIFFSetDirectory(in,dstart);
	TIFFGetFieldDefaulted(in,TIFFTAG_IMAGEWIDTH              ,&fileWidth);
	TIFFGetFieldDefaulted(in,TIFFTAG_IMAGELENGTH             ,&fileHeight);
	TIFFGetFieldDefaulted(in,TIFFTAG_SAMPLESPERPIXEL         ,&numSamples);
	TIFFGetFieldDefaulted(in,TIFFTAG_TILEWIDTH				 ,&tileWidth);
	TIFFGetFieldDefaulted(in,TIFFTAG_TILELENGTH		         ,&tileHeight);

	assert(tileWidth == tileHeight);

	tileSize		=	tileWidth;

	if (strcmp(smode,RI_PERIODIC) == 0) {
		sMode	=	TEXTURE_PERIODIC;
	} else if (strcmp(smode,RI_CLAMP) == 0) {
		sMode	=	TEXTURE_CLAMP;
	} else if ((strcmp(smode,RI_BLACK) == 0) || (strcmp(smode,RI_NONPERIODIC) == 0)) {
		sMode	=	TEXTURE_BLACK;
	} else {
		error(CODE_BADTOKEN,"Unknown texture wrap mode (\"%s\")\n",smode);
		sMode	=	TEXTURE_BLACK;
	}

	if (strcmp(tmode,RI_PERIODIC) == 0) {
		tMode	=	TEXTURE_PERIODIC;
	} else if (strcmp(tmode,RI_CLAMP) == 0) {
		tMode	=	TEXTURE_CLAMP;
	} else if ((strcmp(smode,RI_BLACK) == 0) || (strcmp(smode,RI_NONPERIODIC) == 0)) {
		tMode	=	TEXTURE_BLACK;
	} else {
		error(CODE_BADTOKEN,"Unknown texture wrap mode (\"%s\")\n",tmode);
		tMode	=	TEXTURE_BLACK;
	}

	cTexture	=	new CMadeTexture(aname);

	for (i=1,j=0;i != tileSize;i = i << 1,j++);
	tileSizeShift		=	j;

	if (sizeof(T) == sizeof(float)) {
		M		=	1;
	} else if(sizeof(T) == sizeof(unsigned short)) {
		M		= 	1.0/65535.0;
	} else {
		M		=	1.0/255.0;
	}

	// This is the number of levels we have for the texture
	int	pyramidSize		=	tiffNumLevels(fileWidth,fileHeight);

	cTexture->numLayers	=	pyramidSize;
	cTexture->layers	=	new CTextureLayer*[pyramidSize];

	cwidth				=	width;
	cheight				=	height;
	for (i=0;i<pyramidSize;i++) {
		TIFFSetDirectory(in,dstart);
		TIFFGetFieldDefaulted(in,TIFFTAG_IMAGEWIDTH              ,&fileWidth);
		TIFFGetFieldDefaulted(in,TIFFTAG_IMAGELENGTH             ,&fileHeight);
		cTexture->layers[i]	=	new CTiledTexture<T>(name,dstart,cwidth,cheight,numSamples,fileWidth,fileHeight,sMode,tMode,tileSize,tileSizeShift,M);
		dstart++;

		cwidth				=	cwidth >> 1;
		cheight				=	cheight >> 1;
	}

	return cTexture;
}

///////////////////////////////////////////////////////////////////////
// Function				:	readTexture
// Description			:	read a regular texture
// Return Value			:	The texture
// Comments				:
template <class T> static CTexture	*readTexture(const char *name,const char *aname,TIFF *in,int &dstart,T enforcer) {
	uint32				width,height;
	uint16				numSamples;
	CRegularTexture		*cTexture;
	double				M;

	TIFFSetDirectory(in,dstart);
	width				=	0;
	height				=	0;
	TIFFGetFieldDefaulted(in,TIFFTAG_IMAGEWIDTH              ,&width);
	TIFFGetFieldDefaulted(in,TIFFTAG_IMAGELENGTH             ,&height);
	TIFFGetFieldDefaulted(in,TIFFTAG_SAMPLESPERPIXEL         ,&numSamples);

	if (sizeof(T) == sizeof(float)) {
		M		=	1;
	} else if(sizeof(T) == sizeof(unsigned short)) {
		M		= 	1.0/65535.0;
	} else {
		M		=	1.0/255.0;
	}

	cTexture			=	new CRegularTexture(aname);
	cTexture->layer		=	new CBasicTexture<T>(name,dstart,width,height,numSamples,width,height,TEXTURE_BLACK,TEXTURE_BLACK,M);
	dstart++;

	return cTexture;
}

///////////////////////////////////////////////////////////////////////
// Function				:	textureLoad
// Description			:	Load a texture from disk
// Return Value			:	Pointer to the new texture
// Comments				:
static	CTexture	*texLoad(const char *name,const char *aname,TIFF *in,int &dstart,int unMade = FALSE) {
	CTexture		*cTexture = NULL;
	uint16			bitspersample;

	// Get the bits per sample from the file
	TIFFSetDirectory(in,dstart);
	TIFFGetFieldDefaulted(in,TIFFTAG_BITSPERSAMPLE              ,&bitspersample);

	// Is this a made texture file ?
	if (unMade == FALSE) {
		char			*smode,*tmode,*mode,tmp[128];
		uint32			width,height;

		width	=	0;
		height	=	0;
		mode	=	NULL;
		if (	(TIFFGetField(in,TIFFTAG_PIXAR_IMAGEFULLWIDTH       ,&width)	== 1) &&
				(TIFFGetField(in,TIFFTAG_PIXAR_IMAGEFULLLENGTH      ,&height)	== 1)) {

			if (TIFFGetField(in,TIFFTAG_PIXAR_WRAPMODES ,&mode)		== 1) {
				strcpy(tmp,mode);
				smode	=	tmp;
				tmode	=	strchr(smode,',');
				assert(tmode != NULL);
				*tmode++	=	'\0';
			} else {
				smode	=	RI_BLACK;
				tmode	=	RI_BLACK;
			}


			if (bitspersample == 8) {
				cTexture	=	readMadeTexture<unsigned char>(name,aname,in,dstart,width,height,smode,tmode,1);
			} else if (bitspersample == 16) {
				cTexture	=	readMadeTexture<unsigned short>(name,aname,in,dstart,width,height,smode,tmode,1);
			} else {
				cTexture	=	readMadeTexture<float>(name,aname,in,dstart,width,height,smode,tmode,1);
			}
		
		}
	} else {

		if (bitspersample == 8) {
			cTexture	=	readTexture<unsigned char>(name,aname,in,dstart,1);
		} else if (bitspersample == 16) {
			cTexture	=	readTexture<unsigned short>(name,aname,in,dstart,1);
		} else {
			cTexture	=	readTexture<float>(name,aname,in,dstart,1);
		}
	}


	assert(cTexture != NULL);

	return cTexture;
}




///////////////////////////////////////////////////////////////////////
// Function				:	textureLoad
// Description			:	Load a texture from disk
// Return Value			:	Pointer to the new texture
// Comments				:
CTexture		*CRenderer::textureLoad(const char *name,TSearchpath *path) {
	TIFF			*in;
	CTexture		*cTexture	=	NULL;
	char			fn[OS_MAX_PATH_LENGTH];
	int				directory	=	0;

	if (CRenderer::locateFile(fn,name,path) == FALSE) {
		return NULL;
	}

	// Set the error handler so we don't crash
	TIFFSetErrorHandler(tiffErrorHandler);
	TIFFSetWarningHandler(tiffErrorHandler);

	// Open the texture
	in			=	TIFFOpen(fn,"r");

	if (in != NULL) {
		char	*textureFormat = NULL;

		if (TIFFGetField(in,TIFFTAG_PIXAR_TEXTUREFORMAT,&textureFormat) == 1) {
			
			if (strcmp(textureFormat,TIFF_TEXTURE) == 0)
				// This seems like a made texture
				cTexture	=	texLoad(fn,name,in,directory);
			else
				// This seems like a texture made by another software
				cTexture	=	texLoad(fn,name,in,directory);
		} else {
			// This seems like an unmade texture
			cTexture		=	texLoad(fn,name,in,directory);
		}

		TIFFClose(in);
	}

	return cTexture;
}


///////////////////////////////////////////////////////////////////////
// Function				:	environmentLoad
// Description			:	Load an environment from disk
// Return Value			:	Pointer to the new environment
// Comments				:
CEnvironment		*CRenderer::environmentLoad(const char *name,TSearchpath *path,float *toWorld) {
	TIFF			*in;
	char			fileName[OS_MAX_PATH_LENGTH];
	CEnvironment	*cTexture	=	NULL;
	FILE			*tmpin;

	if (CRenderer::locateFile(fileName,name,path) == FALSE) {
		return NULL;
	}

	// Check if the file is a transparency shadow map
	tmpin		=	ropen(fileName,"rb",fileTransparencyShadow,TRUE);
	if (tmpin != NULL) {
		return	new CDeepShadow(name,fileName,toWorld,tmpin);
	}

	// Set the error handler so we don't crash
	TIFFSetErrorHandler(tiffErrorHandler);
	TIFFSetWarningHandler(tiffErrorHandler);

	// Open the texture
	in			=	TIFFOpen(fileName,"r");

	if (in != NULL) {
		char				*textureFormat = NULL;

		if (TIFFGetField(in,TIFFTAG_PIXAR_TEXTUREFORMAT ,&textureFormat) == 1) {

			if (strcmp(textureFormat,TIFF_CUBIC_ENVIRONMENT) == 0) {
				// We're loading a cubic environment 
				int			directory	=	0;
				int			i;
				CTexture	*sides[6];

				for (i=0;i<6;i++)	sides[i]	=	texLoad(fileName,name,in,directory);

				cTexture	=	new CCubicEnvironment(name,sides);
			} else if (strcmp(textureFormat,TIFF_SPHERICAL_ENVIRONMENT) == 0) {
				int			directory	=	0;
				CTexture	*side;

				side		=	texLoad(fileName,name,in,directory);

				cTexture	=	new CSphericalEnvironment(name,side);
			} else if (strcmp(textureFormat,TIFF_CYLINDER_ENVIRONMENT) == 0) {
				int			directory	=	0;
				CTexture	*side;

				side		=	texLoad(fileName,name,in,directory);

				cTexture	=	new CCylindericalEnvironment(name,side);
			} else if (strcmp(textureFormat,TIFF_SHADOW) == 0)	{
				CTexture	*side;
				int			directory	=	0;
				matrix		worldToCamera,worldToScreen,trans;
				float		*tmp;

				TIFFGetField(in,TIFFTAG_PIXAR_MATRIX_WORLDTOCAMERA,	&tmp);	movmm(worldToCamera,tmp);
				TIFFGetField(in,TIFFTAG_PIXAR_MATRIX_WORLDTOSCREEN,	&tmp);	movmm(worldToScreen,tmp);

				side		=	texLoad(fileName,name,in,directory);

				// Compute the transformation matrix to the light space
				mulmm(trans,worldToScreen,toWorld);

				cTexture	=	new CShadow(name,trans,side);
			}
		} 
	}

	return cTexture;
}

///////////////////////////////////////////////////////////////////////
// Function				:	textureSetMaxMemory
// Description			:	Set the maximum texture memory
// Return Value			:	-
// Comments				:
void			CRenderer::textureSetMaxMemory(int mm) {

	// Flush all the memory
	textureMemFlush(NULL,TRUE);
	assert(CRenderer::textureUsedMemory == 0);

	// Reset the texture memory
	CRenderer::textureMaxMemory	=	mm;
}