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

// This is the portion of Pixie that draws a triangle into the zbuffer

const	float			*v0			=	cPrimitive->v0;
const	float			*v0c		=	v0 + 3;
const	float			*v1			=	(float *) (cPrimitive->data[0].pointer);
const	float			*v1c		=	v1 + 3;
const	float			*v2			=	(float *) (cPrimitive->data[1].pointer);
const	float			*v2c		=	v2 + 3;
const	int				*xbound,*ybound;
int		xmin,xmax,ymin,ymax,x,y;
float	a;
float					xcent,ycent;

xbound	=	cPrimitive->xbound;
ybound	=	cPrimitive->ybound;

xmin	=	xbound[0] - left;
ymin	=	ybound[0] - top;
xmax	=	xbound[1] - left;
ymax	=	ybound[1] - top;

xmin	=	max(xmin,0);
ymin	=	max(ymin,0);
xmax	=	min(xmax,xres);
ymax	=	min(ymax,yres);

a					=	area(v0[COMP_X],v0[COMP_Y],v1[COMP_X],v1[COMP_Y],v2[COMP_X],v2[COMP_Y]);

// A small hack
const float	t		=	a * -0.01f;

if (a > 0) {

	if (grid->flags & (RASTER_DRAW_BACK | RASTER_SHADE_BACKFACE)) {
		for (		ycent=top+	ymin+0.5001011f,y=ymin;y<=ymax;y++,ycent++) {
			for (	xcent=left+	xmin+0.5001011f,x=xmin;x<=xmax;x++,xcent++) {
				float		u,v,z;
				float		*sample;

				u			=	area(xcent,ycent,v0[COMP_X],v0[COMP_Y],v1[COMP_X],v1[COMP_Y]);
				if (u < t)	continue;

				v			=	area(xcent,ycent,v1[COMP_X],v1[COMP_Y],v2[COMP_X],v2[COMP_Y]);
				if (v < t)	continue;

				if ((u+v) > a) continue;

				u			/=	a;
				v			/=	a;

				sample		=	&fb[y][x*SAMPLES_PER_PIXEL];
				z			=	v0[2]*v + v1[2]*(1-u-v) + v2[2]*u;

				if (z < sample[0] || (grid->flags & RASTER_SHADE_HIDDEN)) {
					if (z > clipMin) {
						if (grid->flags & RASTER_UNSHADED) {
							shadeGrid(grid,FALSE);
						}

						sample[0]	=	z;
						if (grid->flags & RASTER_MATTE ) {
							initv(sample,0);
						} else {
							sample[1]	=	v0c[0]*v + v1c[0]*(1-u-v) + v2c[0]*u;
							sample[2]	=	v0c[1]*v + v1c[1]*(1-u-v) + v2c[1]*u;
							sample[3]	=	v0c[2]*v + v1c[2]*(1-u-v) + v2c[2]*u;
						}

						// Update the occlusion cache
						COcclusionNode	*cNode	=	getNode(x,y);

						touchNode(cNode,z);
					}
				}
			}
		}
	}
} else {
	if (grid->flags & (RASTER_DRAW_FRONT | RASTER_SHADE_BACKFACE)) {
		for (		ycent=top+	ymin+0.5001011f,y=ymin;y<=ymax;y++,ycent++) {
			for (	xcent=left+	xmin+0.5001011f,x=xmin;x<=xmax;x++,xcent++) {
				float		u,v,z;
				float		*sample;

				u			=	area(xcent,ycent,v0[COMP_X],v0[COMP_Y],v1[COMP_X],v1[COMP_Y]);
				if (u > t)	continue;

				v			=	area(xcent,ycent,v1[COMP_X],v1[COMP_Y],v2[COMP_X],v2[COMP_Y]);
				if (v > t)	continue;

				if ((u+v) < a) continue;

				u			/=	a;
				v			/=	a;

				sample		=	&fb[y][x*SAMPLES_PER_PIXEL];
				z			=	v0[2]*v + v1[2]*(1-u-v) + v2[2]*u;

				if (z < sample[0] || (grid->flags & RASTER_SHADE_HIDDEN)) {
					if (z > clipMin) {
						if (grid->flags & RASTER_UNSHADED) {
							shadeGrid(grid,FALSE);
						}

						sample[0]	=	z;
						if (grid->flags & RASTER_MATTE ) {
							initv(sample,0);
						} else {
							sample[1]	=	v0c[0]*v + v1c[0]*(1-u-v) + v2c[0]*u;
							sample[2]	=	v0c[1]*v + v1c[1]*(1-u-v) + v2c[1]*u;
							sample[3]	=	v0c[2]*v + v1c[2]*(1-u-v) + v2c[2]*u;
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



#undef t
