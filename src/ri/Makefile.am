lib_LTLIBRARIES = libri.la 

LIBRI_CURRENT_VERSION=0
LIBRI_REVISION_VERSION=0
LIBRI_AGE_VERSION=0

libri_la_LDFLAGS = -export-dynamic -version-info $(LIBRI_CURRENT_VERSION):$(LIBRI_REVISION_VERSION):$(LIBRI_AGE_VERSION)
libri_la_SOURCES = 		attributes.cpp \
				brickmap.cpp \
				bundles.cpp \
				cache.cpp \
				curves.cpp \
				bsplinePatchgrid.cpp \
				delayed.cpp \
				depository.cpp \
				dlobject.cpp \
				dso.cpp \
				error.cpp \
				execute.cpp \
				executeMisc.cpp \
				fileResource.cpp \
				hcshader.cpp \
				hierarchy.cpp \
				implicitSurface.cpp \
				init.cpp \
				instance.cpp \
				irradiance.cpp \
				linsys.cpp \
				memory.cpp \
				noise.cpp \
				object.cpp \
				occlusion.cpp \
				options.cpp \
				output.cpp \
				patches.cpp \
				patchgrid.cpp \
				photon.cpp \
				photonMap.cpp \
				pl.cpp \
				points.cpp \
				pointCloud.cpp \
				polygons.cpp \
				quadrics.cpp \
				radiance.cpp \
				random.cpp \
				raytracer.cpp \
				remoteChannel.cpp \
				renderer.cpp \
				reyes.cpp \
				ri.cpp \
				rib.cpp \
				riInterface.cpp \
				ribOut.cpp \
				shader.cpp \
				shading.cpp \
                                show.cpp \
				sl.cpp \
				stats.cpp \
				stochastic.cpp \
				subdivision.cpp \
				subdivisionCreator.cpp \
				surface.cpp \
				tesselate.cpp \
				texmake.cpp \
				texture.cpp \
				texture3d.cpp \
				trace.cpp \
				variable.cpp \
				xform.cpp	\
				zbuffer.cpp

libri_la_LIBADD = ../common/libcommon.la @TIFF_LIBS@ @ZLIB_LIBS@

INCLUDES = -I..

includedir = $(prefix)/include

include_HEADERS = ri.h dsply.h shadeop.h implicit.h dlo.h

