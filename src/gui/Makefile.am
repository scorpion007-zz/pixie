
if BUILD_SHOW
 modules_LTLIBRARIES = gui.la
endif

#gui_la_SOURCES = opengl.cpp
#gui_la_LIBADD = ../common/libpixiecommon.la @QT_LIBS@
#gui_la_CXXFLAGS = $(AM_CXXFLAGS) @QT_CXXFLAGS@
#gui_la_LDFLAGS = -module -avoid-version @QT_LDFLAGS@
#
#INCLUDES = -I.. @QT_INCLUDES@

gui_la_SOURCES = opengl.cpp
gui_la_LIBADD = ../common/libpixiecommon.la @X_LIBS@
gui_la_CXXFLAGS = $(AM_CXXFLAGS) @X_CFLAGS@ @FLTK_CXXFLAGS@
gui_la_LDFLAGS = -module -avoid-version @FLTK_LDFLAGS@ @X_LDFLAGS@

INCLUDES = -I..

