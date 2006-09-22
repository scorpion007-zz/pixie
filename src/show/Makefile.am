if BUILD_SHOW
bin_PROGRAMS = show
endif

EXTRA_DIST = *.h show.dsp

show_SOURCES = cacheView.cpp \
				radView.cpp \
				interface.cpp \
				meshView.cpp \
				photonView.cpp \
				pointCloudView.cpp \
				imageView.cpp \
				show.cpp

show_LDADD = @X_LIBS@ @FLTK_LDFLAGS@ @X_LDFLAGS@ @TIFF_LIBS@ ../common/libcommon.la ../ri/libri.la
show_CXXFLAGS = @X_CFLAGS@ @FLTK_CXXFLAGS@

INCLUDES = -I..

