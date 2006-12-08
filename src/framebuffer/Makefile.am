if BUILD_FRAMEBUFFER
displays_LTLIBRARIES = framebuffer.la
endif

framebuffer_la_SOURCES = framebuffer.cpp fbx.cpp
framebuffer_la_LIBADD = ../common/libpixiecommon.la @X_LIBS@
framebuffer_la_LDFLAGS = -module -avoid-version @X_LDFLAGS@
framebuffer_la_CXXFLAGS = @X_CFLAGS@

INCLUDES = -I..

