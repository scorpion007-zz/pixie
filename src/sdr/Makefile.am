lib_LTLIBRARIES = libsdr.la 

LIBSDR_CURRENT_VERSION=0
LIBSDR_REVISION_VERSION=0
LIBSDR_AGE_VERSION=0

libsdr_la_LDFLAGS = -export-dynamic -version-info $(LIBSDR_CURRENT_VERSION):$(LIBSDR_REVISION_VERSION):$(LIBSDR_AGE_VERSION)

libsdr_la_SOURCES = sdr.cpp

libsdr_la_LIBADD = ../common/libpixiecommon.la

INCLUDES = -I..

includedir = $(prefix)/include

include_HEADERS = sdr.h

BUILT_SOURCES =

## Additional rules for autogenerating flex products
if HAVE_FLEX

BUILT_SOURCES += lex.sdr.cpp

lex.sdr.cpp: sdr.l
	@FLEX@ -Psdr -olex.sdr.cpp sdr.l

endif
## Additional rules for autogenerating flex products


## Additional rules for autogenerating bison products
if HAVE_BISON

BUILT_SOURCES += sdr.cpp

sdr.cpp: sdr.y
	@BISON@ -p sdr -o sdr.cpp sdr.y

endif
## Additional rules for autogenerating bison products