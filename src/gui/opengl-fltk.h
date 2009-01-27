//////////////////////////////////////////////////////////////////////
//
//                             Pixie
//
// Copyright � 1999 - 2003, Okan Arikan
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
//  File				:	opengl-fltk.h
//  Classes				:
//  Description			:	Hardware resterizer
//
// !!! Work under progress !!!
////////////////////////////////////////////////////////////////////////

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Gl_Window.H>
#include <FL/gl.h>

#include "interface.h"

///////////////////////////////////////////////////////////////////////
// Class				:	CMainWindow
// Description			:	This class is responsible for drawing a view
// Comments				:
class	CMainWindow : public Fl_Gl_Window, public CInterface {
public:


						CMainWindow(CView *v) : Fl_Gl_Window(640,480,"View"), CInterface(v) {
							size_range(640,480);
							mode(FL_RGB | FL_DOUBLE | FL_DEPTH);
							
							end();
							show();						
							make_current();

							displayList	=	0;
						}

		virtual			~CMainWindow() {
							glDeleteLists(displayList,1);
							hide();
						}

		virtual	void	draw()	{
							// Compute the world to camera/camera to world matrices
							computeMatrices();
							
							// Background stuff
							if ((windowWidth > 0) && (windowHeight > 0)) {
								glViewport(0,0,CInterface::windowWidth,CInterface::windowHeight);
							}
							glClearColor(backgroundColor[0],backgroundColor[1],backgroundColor[2],0);
							glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

							// Projection matrix
							glMatrixMode(GL_PROJECTION);
							glLoadIdentity();
							glFrustum(	-CInterface::aspect*CInterface::fov*CInterface::clipNear,
										CInterface::aspect*CInterface::fov*CInterface::clipNear,
										-CInterface::fov*CInterface::clipNear,
										CInterface::fov*CInterface::clipNear,
										CInterface::clipNear,
										CInterface::clipFar);

							// Modelview matrix
							glMatrixMode(GL_MODELVIEW);
							glDisable(GL_CULL_FACE);
							glEnable(GL_DEPTH_TEST);
							glLoadMatrixf(worldToCamera);

							assert(glGetError() == GL_NO_ERROR);
							
							// Create a display list if not done already
							if (displayList == 0) {
								createDisplayList();
							}

							// Draw the scene							
							glCallList(displayList);

							if (TRUE) {
								glColor3f(0.0f,0.0f,0.0f);
								glScalef(0.2f,0.2f,0.2f);
								glBegin(GL_LINES);
								for (int i=0;i<=10;i++) {
									glVertex3f((float) -5,-1,(float)  (i-5));
									glVertex3f((float) 5,-1,(float)  (i-5));
									glVertex3f((float) (i-5),-1,(float) -5);
									glVertex3f((float) (i-5),-1,(float) 5);
								}
								glEnd();
							}
							
						}

protected:
	
	virtual void		reparse() {
							glDeleteLists(displayList,1);
							displayList	=	0;
							createDisplayList();
							redraw();
						}
	
	void				resize(int x,int y,int width,int height) {
							CInterface::resizeEvent(width,height);
							redraw();
						}

	int					handle(int event) {
							int	button	=	0;

							switch(event) {
							case FL_PUSH:
								if (Fl::event_button() == FL_LEFT_MOUSE)		button	=	INTERFACE_LEFT_BUTTON;
								else if (Fl::event_button() == FL_RIGHT_MOUSE)	button	=	INTERFACE_RIGHT_BUTTON;
								else if (Fl::event_button() == FL_MIDDLE_MOUSE)	button	=	INTERFACE_MID_BUTTON;

								CInterface::mousePressEvent(Fl::event_x(),Fl::event_y(),button);

								redraw();
								break;
							case FL_RELEASE:
								
								CInterface::mouseReleaseEvent(Fl::event_x(),Fl::event_y());

								redraw();
								break;
							case FL_DRAG:

								CInterface::mouseMoveEvent(Fl::event_x(),Fl::event_y());

								redraw();
								break;
							case FL_KEYDOWN:
								CInterface::keyPressEvent(Fl::event_key());
								break;
							case FL_KEYUP:
								CInterface::keyReleaseEvent(Fl::event_key());
								break;
							case FL_MOUSEWHEEL:
								zoom += Fl::event_dy()/40.0f;
								redraw();
								break;
							default:
								break;
							}
						
							return 0;
						}
						
	void				createDisplayList() {
							if (displayList == 0) {
								displayList	=	glGenLists(1);
							}
								
							glNewList(displayList,GL_COMPILE);
							glPushMatrix();
							glScalef(1/maxDim,1/maxDim,1/maxDim);
							glTranslatef(-mid[0],-mid[1],-mid[2]);
							view->draw();				
							glPopMatrix();
							glEndList();
						}

	unsigned int		displayList;
};
















///////////////////////////////////////////////////////////////////////
// Function				:	pglVisualize
// Description			:	Visualize some data
// Return Value			:	-
// Comments				:
void		pglVisualize(CView *view) {
	CMainWindow		mainWindow(view);

	Fl::run();
}

