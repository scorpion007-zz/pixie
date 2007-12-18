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
//  File				:	interface.h
//  Classes				:	CInterface
//  Description			:	This class handles the user interface
//
////////////////////////////////////////////////////////////////////////
#ifndef INTERFACE_H
#define INTERFACE_H
#include "common/global.h"
#include "common/algebra.h"
#include "opengl.h"



const int	INTERFACE_LEFT_BUTTON	=	1;
const int	INTERFACE_MID_BUTTON	=	2;
const int	INTERFACE_RIGHT_BUTTON	=	4;

const int	INTERFACE_ALT_KEY		=	65513;
const int	INTERFACE_CTRL_KEY		=	65507;

///////////////////////////////////////////////////////////////////////
// Class				:	CInterface
// Description			:	Deals with the trackball interface
// Comments				:	-
class	CInterface {
public:
						CInterface(CView *v) {
							vector tmp;
														
							// Standard OpenGL camera
							initv(position,0,0,0);						// Inherited from CObject
							initq(orientation,0.08f,0.9f,0.2f,0.35f);	// A good orientation
							normalizeq(orientation);					// Make sure we're a quaternion

							// Set some misc attributes
							zoom				=	1;
							fov					=	0.6f;
							clipNear			=	0.001f;
							clipFar				=	1000.0f;
							initv(backgroundColor,0.5);
							antialiasedLines	=	TRUE;

							currentButton		=	0;
							cameraAction		=	FALSE;
							zoom				=	1;

							// The view we're drawing
							view				=	v;
							
							view->bound(bmin,bmax);
							
							addvv(mid,bmin,bmax);
							mulvf(mid,(float) 0.5);
							
							subvv(tmp,bmax,bmin);
							maxDim	=	max(tmp[0],tmp[1]);
							maxDim	=	max(tmp[2],maxDim);
							maxDim	*=	5;
						}

		virtual			~CInterface() {
						}

		virtual	void	draw()	{
						}
		
protected:

	virtual void		reparse() {
						}

	void				computeMatrices() {
							matrix	R,mtmp,T1,T2;
	
							//////////////////////////////////////////////////////////////
							// Compute the transformation matrices
							qtoR(R,orientation);
							translatem(T1,0,0,-zoom);
							translatem(T2,position[0],position[1],position[2]);

							// World to Camera = T1*R*T2
							mulmm(worldToCamera,T1,R,T2);

							transposem(mtmp,R);
							translatem(T1,0,0,zoom);
							translatem(T2,-position[0],-position[1],-position[2]);

							mulmm(cameraToWorld,T2,mtmp,T1);
							//////////////////////////////////////////////////////////////
						}

						////////////////////////////////////////////////////////////////////////////
						// Overloaded event handlers
	void				mouseMoveEvent(int x, int y) {

							// Dispatch the event if we hame camera action
							if (cameraAction) {

								switch(currentButton) {
									case INTERFACE_LEFT_BUTTON:
										{	// Rotate
											vector		to;
											vector		prod;
											quaternion	drag;

											toSphere(x,y,to);

											crossvv(prod,fromR,to);

											initq(drag,prod[0],prod[1],prod[2],dotvv(fromR,to));
											mulqq(orientation,drag,savedOrientation);
										}
										break;
									case INTERFACE_RIGHT_BUTTON:
										{	// Pan
											vector	d;

											d[0]		=	(float) x - fromT[0];
											d[1]		=	(float) -(y - fromT[1]);
											d[2]		=	0;

											mulmv(d,cameraToWorld,d);
											//mulvf(d,0.005f);
											mulvf(d,0.005f*zoom*zoom);
											addvv(position,savedPosition,d);
										}
										break;
									case INTERFACE_MID_BUTTON:
										{	// Zoom
											zoom		=	savedZoom - (x-fromZ[0])*0.005f*savedZoom;
										}
										break;
								}
							}
						}

	void				mousePressEvent(int x, int y,int button) {

							currentButton	=	button;

							// If no selection, do the camera thing
							if (cameraAction) {
							
								// Yes, depending on the button, dispatch the event
								switch(currentButton) {
									case INTERFACE_LEFT_BUTTON:
										// Rotate
										movqq(savedOrientation,orientation);
										toSphere(x,y,fromR);
										break;
									case INTERFACE_RIGHT_BUTTON:
										// Pan
										movvv(savedPosition,position);
										fromT[0]	=	(float) x;
										fromT[1]	=	(float) y;
										fromT[2]	=	(float) 0;
										break;
									case INTERFACE_MID_BUTTON:
										// Zoom
										savedZoom	=	zoom;
										fromZ[0]	=	(float) x;
										fromZ[1]	=	(float) y;
										fromZ[2]	=	(float) 0;
										break;
								}

								beginCalled	=	TRUE;
							}
							draw();
						}

	void				mouseReleaseEvent(int x, int y) {
							currentButton	=	0;
						}

	void				keyPressEvent(int key) {
							if (key == INTERFACE_ALT_KEY || key == INTERFACE_CTRL_KEY)	cameraAction	=	TRUE;
							else {
								if (view->keyDown(key) == TRUE)	reparse();
							}
						}

	void				keyReleaseEvent(int key) {
							if (key == INTERFACE_ALT_KEY || key == INTERFACE_CTRL_KEY)	cameraAction	=	FALSE;
						}

	void				resizeEvent(int w, int h) {
							windowWidth		=	w;
							windowHeight	=	h;
							radius			=	sqrtf((float) (w*w + h*h)) * 0.5f;
							aspect			=	(float) w / (float) h;
						}

	void				toSphere(int x,int y,float *P) {
							vector	d	=	{(x - windowWidth*0.5f), -(y - windowHeight*0.5f), 0};
							float	l;

							mulvf(d,1 / radius);
							movvv(P,d);

							l			=	dotvv(d,d);
							if (l > 1) {
								normalizev(P);
							} else {
								P[2]	=	sqrtf(1 - l);
							}
						}

	CView				*view;							// The view we're drawing
	vector				bmin,bmax;						// The bounding box
	float				maxDim;
	vector				mid;

	vector				position;						// The position the camera is looking at (in the world)
	quaternion			orientation;					// The orientation of the camera (in the world)
	float				zoom;							// The zoom amount (the distance between "position" and the center of projection)
	float				fov;							// Field of view
	float				clipNear,clipFar;				// Clipping planes
	vector				backgroundColor;				// The background color
	int					antialiasedLines;				// TRUE/FALSE
	int					windowWidth,windowHeight;

	int					currentButton;
	int					beginCalled;

	int					cameraAction;
	float				radius,aspect;					// Stuff for the crystal ball interface

	matrix				worldToCamera;					// World to camera transformation
	matrix				cameraToWorld;					// And its inverse

	quaternion			savedOrientation;				// Saved stuff
	vector				savedPosition;					// (during the manipulation)
	float				savedZoom;						// 

	vector				fromR;							// Clicked position (for rotating)
	vector				fromT;							// Clicked position (for translating)
	vector				fromZ;							// Clicked position (for zooming)

};

#endif

