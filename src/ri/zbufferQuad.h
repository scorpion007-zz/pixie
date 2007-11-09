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

// This is the portion of Pixie that draws a quad into the zbuffer
int			i,j;
const int	*bounds		=	grid->bounds;
const float	*vertices	=	grid->vertices;
const	int	xres		=	sampleWidth - 1;
const	int	yres		=	sampleHeight - 1;
const	int	udiv		=	grid->udiv;
const	int	vdiv		=	grid->vdiv;
const	int	flags		=	grid->flags;



// Iterate over every quad
for (j=0;j<vdiv;j++) {
	for (i=0;i<udiv;i++,bounds+=4,vertices+=numVertexSamples) {

		// Trivial rejects
		if (bounds[1] < left)		continue;
		if (bounds[3] < top)		continue;
		if (bounds[0] >= right)		continue;
		if (bounds[2] >= bottom)	continue;

		// Extract the quad corners
		const float	*v0	=	vertices;
		const float	*v1	=	vertices + numVertexSamples;
		const float	*v2	=	v1 + udiv*numVertexSamples;
		const float	*v3	=	v2 + numVertexSamples;

		int	xmin	=	bounds[0] - left;	// Convert the bound into the current bucket
		int	ymin	=	bounds[2] - top;
		int	xmax	=	bounds[1] - left;
		int	ymax	=	bounds[3] - top;

		xmin		=	max(xmin,0);		// Clamp the bound in the current bucket
		ymin		=	max(ymin,0);
		xmax		=	min(xmax,xres);
		ymax		=	min(ymax,yres);


		// This macro is used to check whether the sample is inside the quad or not
#define	checkPixel(__op)																						\
		float			aleft,atop,aright,abottom;																\
																												\
		if ((atop		= area(xcent,ycent,v0[COMP_X],v0[COMP_Y],v1[COMP_X],v1[COMP_Y])) __op 0)	continue;	\
		if ((aright		= area(xcent,ycent,v1[COMP_X],v1[COMP_Y],v3[COMP_X],v3[COMP_Y])) __op 0)	continue;	\
		if ((abottom	= area(xcent,ycent,v3[COMP_X],v3[COMP_Y],v2[COMP_X],v2[COMP_Y])) __op 0)	continue;	\
		if ((aleft		= area(xcent,ycent,v2[COMP_X],v2[COMP_Y],v0[COMP_X],v0[COMP_Y])) __op 0)	continue;	\
																												\
		const float u	=	aleft / (aleft + aright);															\
		const float v	=	atop / (atop + abottom);															\
		const float	z	=	(v0[COMP_Z]*(1-u) + v1[COMP_Z]*u)*(1-v) + (v2[COMP_Z]*(1-u) + v3[COMP_Z]*u)*v;


#define	recordPixel()														\
		float	*sample		=	&fb[y][x*SAMPLES_PER_PIXEL];				\
		if (z < sample[0] || (flags & RASTER_SHADE_HIDDEN)) {				\
			if (z > CRenderer::clipMin) {							\
				if (flags & RASTER_UNSHADED) {								\
					shadeGrid(grid,FALSE);									\
					rasterDrawPrimitives(grid);								\
					return;													\
				}															\
																			\
				sample[0]	=	z;											\
				if (flags & RASTER_MATTE ) {								\
					initv(sample,0);										\
				} else {													\
					sample[1]	=	(v0[3]*(1-u) + v1[3]*u)*(1-v) + (v2[3]*(1-u) + v3[3]*u)*v;		\
					sample[2]	=	(v0[4]*(1-u) + v1[4]*u)*(1-v) + (v2[4]*(1-u) + v3[4]*u)*v;		\
					sample[3]	=	(v0[5]*(1-u) + v1[5]*u)*(1-v) + (v2[5]*(1-u) + v3[5]*u)*v;		\
				}															\
																			\
				COcclusionNode	*cNode	=	getNode(x,y);					\
																			\
				touchNode(cNode,z);											\
			}																\
		}



		float a	= area(v0[COMP_X],v0[COMP_Y],v1[COMP_X],v1[COMP_Y],v2[COMP_X],v2[COMP_Y]);
		if (fabsf(a) < C_EPSILON)  a = area(v1[COMP_X],v1[COMP_Y],v3[COMP_X],v3[COMP_Y],v2[COMP_X],v2[COMP_Y]);
		if (a > 0) {

			if (flags & (RASTER_DRAW_BACK | RASTER_SHADE_BACKFACE)) {

				float	xcent,ycent;
				int		x,y;
				for (		ycent=top+	ymin+0.5001011f,y=ymin;y<=ymax;y++,ycent++) {
					for (	xcent=left+	xmin+0.5001011f,x=xmin;x<=xmax;x++,xcent++) {

						checkPixel(<);

						recordPixel();
						
					}
				}
			}
		} else {
			if (flags & (RASTER_DRAW_FRONT | RASTER_SHADE_BACKFACE)) {

				float	xcent,ycent;
				int		x,y;
				for (		ycent=top+	ymin+0.5001011f,y=ymin;y<=ymax;y++,ycent++) {
					for (	xcent=left+	xmin+0.5001011f,x=xmin;x<=xmax;x++,xcent++) {
						
						checkPixel(>);

						recordPixel();
					}
				}
			}
		}

		
	}

	vertices	+=	numVertexSamples;
}

