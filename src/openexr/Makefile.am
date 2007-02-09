if BUILD_OPENEXR
 displays_LTLIBRARIES = openexr.la 
endif

openexr_la_SOURCES = openexr.cpp
openexr_la_LIBADD = ../common/libpixiecommon.la @OPENEXR_LIBS@
openexr_la_LDFLAGS = -module -avoid-version @OPENEXR_LDFLAGS@

INCLUDES = -I.. @OPENEXR_INCLUDES@

