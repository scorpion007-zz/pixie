
if BUILD_SHOW
 modules_LTLIBRARIES = opengl.la
endif

#opengl_la_SOURCES = opengl.cpp
#opengl_la_LIBADD = ../common/libcommon.la @QT_LIBS@
#opengl_la_CXXFLAGS = $(AM_CXXFLAGS) @QT_CXXFLAGS@
#opengl_la_LDFLAGS = -module -avoid-version @QT_LDFLAGS@
#
#INCLUDES = -I.. @QT_INCLUDES@

opengl_la_SOURCES = opengl-fltk.cpp
opengl_la_LIBADD = ../common/libcommon.la @FLTK_LIBS@ @X_LIBS@
opengl_la_CXXFLAGS = $(AM_CXXFLAGS) @X_CFLAGS@ @FLTK_CXXFLAGS@
opengl_la_LDFLAGS = -module -avoid-version @FLTK_LDFLAGS@ @X_LDFLAGS@

INCLUDES = -I..
