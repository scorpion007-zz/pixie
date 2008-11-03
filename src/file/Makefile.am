displays_LTLIBRARIES = file.la 

file_la_SOURCES = file.cpp file_tiff.cpp file_png.cpp
file_la_LIBADD = ../common/libpixiecommon.la @TIFF_LIBS@ @PNG_LIBS@
file_la_LDFLAGS = -module -avoid-version

INCLUDES = -I..

