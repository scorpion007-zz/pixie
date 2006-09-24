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
//  File				:	opengl
//  Classes				:
//  Description			:	Hardware resterizer
//
// !!! Work under progress !!!
////////////////////////////////////////////////////////////////////////

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Gl_Window.H>
#include <FL/gl.h>

#include <GL/glu.h>

#include "common/os.h"
#include "common/algebra.h"
#include "opengl.h"


///////////////////////////////////////////////////////////////////////
// Class				:	CMainWindow
// Description			:	This class is responsible for drawing a view
// Comments				:
// Date last edited		:	9/21/2006
class	CMainWindow : public Fl_Gl_Window {
public:



						CMainWindow(CView *v) : Fl_Gl_Window(640,480,"View") {
							
							size_range(640,480);
							mode(FL_RGB | FL_DOUBLE | FL_DEPTH);
							
							// Standard OpenGL camera
							initv(position,0,0,0);						// Inherited from CObject
							initq(orientation,0.08f,0.9f,0.2f,0.35f);	// A good orientation
							normalizeq(orientation);					// Make sure we're a quaternion

							// Set some misc attributes
							zoom				=	2;
							fov					=	0.6f;
							clipNear			=	0.001f;
							clipFar				=	1000.0f;
							initv(backgroundColor,0.5);
							antialiasedLines	=	TRUE;
							drawGround			=	TRUE;

							currentButton		=	0;

							// The view we're drawing
							view				=	v;
							
							end();
							show();						
							make_current();
						}

		virtual			~CMainWindow() {
							hide();
						}

		virtual	void	draw()	{
							glViewport(0,0,w(),h());
							glMatrixMode(GL_PROJECTION);
							glLoadIdentity();
							//glFrustum(-clipNear,clipNear,-clipNear,clipNear,clipNear*fov,clipFar);

							glMatrixMode(GL_MODELVIEW);
							glLoadIdentity();
							glTranslatef(0,0,-5);
							//glScalef(1,1,-0.1);
							glPointSize(5);
							
							glClearColor(backgroundColor[0],backgroundColor[1],backgroundColor[2],1);
							
							glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
							view->draw();							
						}

protected:
	int					handle(int event) {
							switch(event) {
							case FL_PUSH:
								currentButton	|=	Fl::event_button();
								mousePressEvent(Fl::event_x(),Fl::event_y());
								break;
							case FL_RELEASE:
								currentButton	&=	~(Fl::event_button() & (FL_BUTTON1|FL_BUTTON2|FL_BUTTON3));
								beginCalled		=	FALSE;
								break;
							case FL_DRAG:
								mouseMoveEvent(Fl::event_x(),Fl::event_y());
								break;
							case FL_KEYDOWN:
								if (Fl::event_key() == FL_Alt_L) cameraAction		=	TRUE;
								break;
							case FL_KEYUP:
								if (Fl::event_key() == FL_Alt_L) cameraAction		=	FALSE;
								break;
							default:
								break;
							}
						
							return 0;
						}

						////////////////////////////////////////////////////////////////////////////
						// Overloaded event handlers
	void				mouseMoveEvent(int x, int y) {

							// Dispatch the event if we hame camera action
							if (cameraAction) {

								switch(currentButton) {
									case FL_BUTTON1:
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
									case FL_BUTTON2:
										{	// Pan
											vector	d;

											d[0]		=	(float) x - fromT[0];
											d[1]		=	(float) -(y - fromT[1]);
											d[2]		=	0;

											mulmv(d,cameraToWorld,d);
											mulvf(d,0.005f);
											addvv(position,savedPosition,d);
										}
										break;
									case FL_BUTTON3:
										{	// Zoom
											zoom		=	savedZoom - (x-fromZ[0])*0.005f;
										}
										break;
								}
							}
							draw();
						}

	void				mousePressEvent(int x, int y) {

							// If no selection, do the camera thing
							if (cameraAction) {

								// Yes, depending on the button, dispatch the event
								switch(currentButton) {
									case FL_BUTTON1:
										// Rotate
										movqq(savedOrientation,orientation);
										toSphere(x,y,fromR);
										break;
									case FL_BUTTON2:
										// Pan
										movvv(savedPosition,position);
										fromT[0]	=	(float) x;
										fromT[1]	=	(float) y;
										fromT[2]	=	(float) 0;
										break;
									case FL_BUTTON3:
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

	void				resize(int x,int y,int w, int h) {
							Fl_Gl_Window::resize(x,y,w,h);
							radius		=	sqrtf((float) (w*w + h*h)) * 0.5f;
							aspect		=	(float) w / (float) h;
						}

	void				toSphere(int x,int y,float *P) {
							vector	d	=	{(x - w()*0.5f), -(y - h()*0.5f), 0};
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

	vector				position;						// The position the camera is looking at (in the world)
	quaternion			orientation;					// The orientation of the camera (in the world)
	float				zoom;							// The zoom amount (the distance between "position" and the center of projection)
	float				fov;							// Field of view
	float				clipNear,clipFar;				// Clipping planes
	vector				backgroundColor;				// The background color
	int					antialiasedLines;				// TRUE/FALSE
	int					drawGround;						// TRUE/FALSE

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
















///////////////////////////////////////////////////////////////////////
// Function				:	pglVisualize
// Description			:	Visualize some data
// Return Value			:	-
// Comments				:
// Date last edited		:	9/21/2006
void		pglVisualize(CView *view) {
	int		argc	=	1;
	char	*argv[]	=	{	"View"	};

	CMainWindow		mainWindow(view);

	Fl::run();
}


///////////////////////////////////////////////////////////////////////
// Function				:	pglTriangles
// Description			:	Draw triangles with OpenGL
// Return Value			:	-
// Comments				:
// Date last edited		:	9/21/2006
void		pglTriangles(int n,const int *indices,const float *P,const float *C) {
	int	i;

	glBegin(GL_TRIANGLES);
	for (i=n;i>0;i--) {
		glColor3fv(C + indices[0]*3);
		glVertex3fv(P + indices[0]*3);
		glColor3fv(C + indices[1]*3);
		glVertex3fv(P + indices[1]*3);
		glColor3fv(C + indices[2]*3);
		glVertex3fv(P + indices[2]*3);
	}
	glEnd();
}



///////////////////////////////////////////////////////////////////////
// Function				:	pglTriangles
// Description			:	Draw triangles with OpenGL
// Return Value			:	-
// Comments				:
// Date last edited		:	9/21/2006
void		pglPoints(int n,const float *P,const float *C) {
	int	i;

	glBegin(GL_POINTS);
	for (i=n;i>0;i--,P+=3,C+=3) {
		glColor3fv(C);
		glVertex3fv(P);
	}
	glEnd();
}
