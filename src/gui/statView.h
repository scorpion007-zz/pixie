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
//  File				:	statView.h
//  Classes				:	CStatView
//  Description			:	This class visualizes the statistics during the view
//
////////////////////////////////////////////////////////////////////////
#ifndef STATVIEW_H
#define STATVIEW_H

#include <QDialog>
#include <QTabWidget>

#include "common/global.h"
#include "ri/stats.h"


///////////////////////////////////////////////////////////////////////
// Class				:	CTimeMemory
// Description			:	Holds info about time and memory
// Comments				:
class CTimeMemory : public QWidget {
    Q_OBJECT
public:
					CTimeMemory(QWidget *parent = 0) { }

	void			update(CStatistics *stats);

	QLabel			memory;
	QLabel			startTime;
	QLabel			overhead;
	QLabel			renderTime;
};

///////////////////////////////////////////////////////////////////////
// Class				:	CNumbers
// Description			:	Numbers of various items
// Comments				:
class CNumbers : public QWidget {
    Q_OBJECT
public:
					CNumbers(QWidget *parent = 0) { }

	void			update(CStatistics *stats);

	QLabel			numAttributes;
	QLabel			numXforms;
	QLabel			numOptions;
	QLabel			numShaders;
	QLabel			numShaderInstances;
	QLabel			numOutDevices;
	QLabel			numGprimCores;
	QLabel			numVariableDatas;
	QLabel			numVertexDatas;
	QLabel			numParameters;
	QLabel			numParameterLists;
	QLabel			numPls;
	QLabel			numObjects;
	QLabel			numGprims;
	QLabel			numSurfaces;
	QLabel			numPeakSurfaces;
	QLabel			numComposites;
	QLabel			numDelayeds;
	QLabel			numInstances;
	QLabel			numTextures;
	QLabel			numEnvironments;
};


///////////////////////////////////////////////////////////////////////
// Class				:	CStatView
// Description			:	This is the main statistics view class
// Comments				:
class CStatView : public QDialog {
    Q_OBJECT
public:
					CStatView(CStatistics *stats,QWidget *parent = 0);

private:
    CTimeMemory		*timeMemory;			// Time and memory usage information
	CStatistics		*stats;
};


#endif
