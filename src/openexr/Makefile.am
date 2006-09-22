if BUILD_OPENEXR
 displays_LTLIBRARIES = openexr.la 
endif

openexr_la_SOURCES = openexr.cpp
openexr_la_LIBADD = ../common/libcommon.la @OPENEXR_LIBS@
openexr_la_LDFLAGS = -module -avoid-version

INCLUDES = -I.. @OPENEXR_INCLUDES@


