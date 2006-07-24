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

// This is the portion of Pixie that draws a point into the zbuffer

const float	*v0			=	cPrimitive->v0;
const float	*v0c		=	v0+3;
int			xmin,xmax,ymin,ymax,x,y;
const float	radius		=	(cPrimitive->data[0].real*cPrimitive->data[0].real);
float		xcent,ycent;

xmin				=	cPrimitive->xbound[0]-left;
ymin				=	cPrimitive->ybound[0]-top;
xmax				=	cPrimitive->xbound[1]-left;
ymax				=	cPrimitive->ybound[1]-top;

xmin				=	max(xmin,0);
ymin				=	max(ymin,0);
xmax				=	min(xmax,xres);
ymax				=	min(ymax,yres);

for (		ycent=top+ymin+  0.5f,y=ymin;y<=ymax;y++,ycent++) {
	for (	xcent=left+xmin+ 0.5f,x=xmin;x<=xmax;x++,xcent++) {
		float		z;
		float		*sample;
		float		dx,dy;

		dx				=	xcent - v0[0];
		dy				=	ycent - v0[1];

		if ((dx*dx + dy*dy) < radius) {
			sample		=	&fb[y][x*SAMPLES_PER_PIXEL];
			z			=	v0[2];

			if (z < sample[0] || (grid->flags & RASTER_SHADE_HIDDEN)) {
				if (z > clipMin) {
					if (grid->flags & RASTER_UNSHADED) {
						shadeGrid(grid,FALSE);
					}

					sample[0]	=	z;
					if (grid->flags & RASTER_MATTE ) {
						initv(sample,0);
					} else {
						sample[1]	=	v0c[0];
						sample[2]	=	v0c[1];
						sample[3]	=	v0c[2];
					}
					
					// Update the occlusion cache
					COcclusionNode	*cNode	=	getNode(x,y);

					touchNode(cNode,z);
				}
			}
		}
	}
}




