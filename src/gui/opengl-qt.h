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
//  File				:	opengl-qt.h
//  Classes				:
//  Description			:	Hardware resterizer
//
// !!! Work under progress !!!
////////////////////////////////////////////////////////////////////////
#include <QMainWindow>
#include <QGLWidget>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QPaintEvent>
#include <QResizeEvent>
#include <QApplication>

#include "interface.h"


///////////////////////////////////////////////////////////////////////
// Class				:	CMainWindow
// Description			:	This class is responsible for drawing a view
// Comments				:
class	CMainWindow : public QMainWindow, public CInterface {
public:

						CMainWindow(CView *v) : QMainWindow() , CInterface(v) {
						}

		virtual			~CMainWindow() {
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
							glLoadMatrixf(worldToCamera);

							assert(glGetError() == GL_NO_ERROR);
							
							// Create a display list if not done already
							if (displayList == 0) {
								displayList	=	glGenLists(1);
								glNewList(displayList,GL_COMPILE);
								glPushMatrix();
								glScalef(1/maxDim,1/maxDim,1/maxDim);
								glTranslatef(-mid[0],-mid[1],-mid[2]);
								view->draw();				
								glPopMatrix();
								glEndList();
							}

							// Draw the scene
							glCallList(displayList);

							if (TRUE) {
								glScalef(0.2f,0.2f,0.2f);
								glBegin(GL_LINES);
								for (int i=0;i<=10;i++) {
									glVertex3f(-5,-1,i-5);
									glVertex3f(5,-1,i-5);
									glVertex3f(i-5,-1,-5);
									glVertex3f(i-5,-1,5);
								}
								glEnd();
							}
						}

protected:
						////////////////////////////////////////////////////////////////////////////
						// Overloaded event handlers
	void				mouseMoveEvent(QMouseEvent *event) {
							int	button	=	0;

							switch(event->button()) {
								case Qt::LeftButton:
									button	=	INTERFACE_LEFT_BUTTON;
									break;
								case Qt::RightButton:
									button	=	INTERFACE_RIGHT_BUTTON;
									break;
								case Qt::MidButton:
									button	=	INTERFACE_MID_BUTTON;
									break;
							}

							CInterface::mouseMoveEvent(event->x(),event->y(),button);

							glArea.repaint();
						}

	void				mousePressEvent(QMouseEvent *event) {
							int	button	=	0;

							switch(event->button()) {
								case Qt::LeftButton:
									button	=	INTERFACE_LEFT_BUTTON;
									break;
								case Qt::RightButton:
									button	=	INTERFACE_RIGHT_BUTTON;
									break;
								case Qt::MidButton:
									button	=	INTERFACE_MID_BUTTON;
									break;
							}

							CInterface::mousePressEvent(event->x(),event->y(),button);

							glArea.repaint();
						}

	void				mouseReleaseEvent(QMouseEvent *event) {
							CInterface::mouseReleaseEvent(event->x(),event->y());

							glArea.repaint();
						}

	void				keyPressEvent(QKeyEvent *event) {
							CInterface::keyPressEvent(event->key());
						}

	void				keyReleaseEvent(QKeyEvent *event) {
							CInterface::keyReleaseEvent(event->key());
						}

	void				resizeEvent(QResizeEvent *event) {
							CInterface::resizeEvent(width(),height());
						}

	void				paintEvent(QPaintEvent *event) {
							draw();
						}

	QGLWidget			glArea;
};



///////////////////////////////////////////////////////////////////////
// Function				:	pglVisualize
// Description			:	Visualize some data
// Return Value			:	-
// Comments				:
void		pglVisualize(CView *view) {
	int		argc	=	1;
	char	*argv[]	=	{	"View"	};

	QApplication	app(argc,argv);
	CMainWindow		mainWindow(view);

	app.exec();
}
