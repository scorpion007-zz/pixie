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
				debug.cpp \
				delayed.cpp \
				displayChannel.cpp \
				dlobject.cpp \
				dso.cpp \
				error.cpp \
				execute.cpp \
				executeMisc.cpp \
				fileResource.cpp \
				hcshader.cpp \
				ifexpr.cpp \
				implicitSurface.cpp \
				init.cpp \
				irradiance.cpp \
				linsys.cpp \
				memory.cpp \
				noise.cpp \
				object.cpp \
				occlusion.cpp \
				options.cpp \
				patches.cpp \
				patchgrid.cpp \
				photon.cpp \
				photonMap.cpp \
				pl.cpp \
				points.cpp \
				pointCloud.cpp \
				polygons.cpp \
				ptcapi.cpp \
				quadrics.cpp \
				random.cpp \
				raytracer.cpp \
				remoteChannel.cpp \
				renderer.cpp \
				rendererClipping.cpp \
				rendererContext.cpp \
				rendererDeclerations.cpp \
				rendererDisplay.cpp \
				rendererFiles.cpp \
				rendererJobs.cpp \
				rendererMutexes.cpp \
				rendererNetwork.cpp \
				resource.cpp \
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
				texmake.cpp \
				texture.cpp \
				texture3d.cpp \
				trace.cpp \
				variable.cpp \
				xform.cpp	\
				zbuffer.cpp

libri_la_LIBADD = ../common/libpixiecommon.la @TIFF_LIBS@ @ZLIB_LIBS@

INCLUDES = -I..

includedir = $(prefix)/include

include_HEADERS = ri.h dsply.h shadeop.h implicit.h dlo.h ptcapi.h

