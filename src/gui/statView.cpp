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
//  File				:	statView.cpp
//  Classes				:	CStatView
//  Description			:	This class visualizes the statistics during the view
//
////////////////////////////////////////////////////////////////////////
#include <QtGui>

#include "statView.h"

///////////////////////////////////////////////////////////////////////
// Class				:	CStatView
// Method				:	CStatView
// Description			:	Ctor
// Return Value			:	-
// Comments				:
CStatView::CStatView(CStatistics *s,QWidget *parent) : QDialog(parent) {

	// Create the tab widget
	stats		=	s;
	tabWidget	=	new CTabWidget;
    tabWidget->addTab(new QTabWidget(stats), tr("General"));

	// Create the buttons
    QPushButton *okButton		= new QPushButton(tr("OK"));
    QPushButton *cancelButton	= new QPushButton(tr("Cancel"));
    connect(okButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(reject()));

	// Create the layouts
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addStretch(1);
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(tabWidget);
    mainLayout->addLayout(buttonLayout);
    setLayout(mainLayout);

    setWindowTitle(tr("Statistics"));
}




///////////////////////////////////////////////////////////////////////
// Class				:	CTimeMemory
// Method				:	update
// Description			:	Update the tabs
// Return Value			:	-
// Comments				:
void		CTimeMemory::update(CStatistics *stats) {
}


///////////////////////////////////////////////////////////////////////
// Class				:	CNumbers
// Method				:	update
// Description			:	Update the tabs
// Return Value			:	-
// Comments				:
void		CNumbers::update(CStatistics *stats) {
	QGridLayout		*layout	=	new QGridLayout;

	layout->addWidget(new QLabel("Num. Attributes"),1,1);
	layout->addWidget(&numAttributes,1,2);

	layout->addWidget(new QLabel("Num. Options"),1,1);
	layout->addWidget(&numOptions,1,2);

	setLayout(layout);
}
