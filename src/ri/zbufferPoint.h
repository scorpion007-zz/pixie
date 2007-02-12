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

// This is the portion of Pixie that draws a point into the zbuffer

int			i;
const int	*bounds		=	grid->bounds;
const float	*vertices	=	grid->vertices;
const float	*sizes		=	grid->sizes;
const	int	xres		=	sampleWidth - 1;
const	int	yres		=	sampleHeight - 1;

// Iterate over every quad
for (i=grid->numVertices;i>0;i--,vertices+=numVertexSamples,bounds+=4,sizes+=2) {

	// Trivial rejects
	if (bounds[1] < left)		continue;
	if (bounds[3] < top)		continue;
	if (bounds[0] >= right)		continue;
	if (bounds[2] >= bottom)	continue;

	int	xmin	=	bounds[0] - left;	// Convert the bound into the current bucket
	int	ymin	=	bounds[2] - top;
	int	xmax	=	bounds[1] - left;
	int	ymax	=	bounds[3] - top;

	xmin		=	max(xmin,0);		// Clamp the bound in the current bucket
	ymin		=	max(ymin,0);
	xmax		=	min(xmax,xres);
	ymax		=	min(ymax,yres);


	float	xcent,ycent;
	int		x,y;
	for (		ycent=top+ymin+  0.5f,y=ymin;y<=ymax;y++,ycent++) {
		for (	xcent=left+xmin+ 0.5f,x=xmin;x<=xmax;x++,xcent++) {

			const float dx				=	xcent - vertices[0];
			const float dy				=	ycent - vertices[1];

			if ((dx*dx + dy*dy) < sizes[0]*sizes[0]) {
				float		*sample		=	&fb[y][x*SAMPLES_PER_PIXEL];
				const float	z			=	vertices[2];

				if (z < sample[0] || (CRenderer::flags & RASTER_SHADE_HIDDEN)) {
					if (z > CRenderer::clipMin) {
						if (CRenderer::flags & RASTER_UNSHADED) {
							shadeGrid(grid,FALSE);
							rasterDrawPrimitives(grid);
							return;
						}

						sample[0]	=	z;
						if (CRenderer::flags & RASTER_MATTE ) {
							initv(sample,0);
						} else {
							sample[1]	=	vertices[3];
							sample[2]	=	vertices[4];
							sample[3]	=	vertices[5];
						}
						
						// Update the occlusion cache
						COcclusionNode	*cNode	=	getNode(x,y);

						touchNode(cNode,z);
					}
				}
			}
		}
	}
}

