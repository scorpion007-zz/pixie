lib_LTLIBRARIES = libri.la 

LIBRI_CURRENT_VERSION=0
LIBRI_REVISION_VERSION=0
LIBRI_AGE_VERSION=0

libri_la_LDFLAGS = -export-dynamic -version-info $(LIBRI_CURRENT_VERSION):$(LIBRI_REVISION_VERSION):$(LIBRI_AGE_VERSION)
libri_la_SOURCES = 		attributes.cpp \
				brickmap.cpp \
				bundles.cpp \
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
				pointHierarchy.cpp \
				polygons.cpp \
				ptcapi.cpp \
				quadrics.cpp \
				random.cpp \
				raytracer.cpp \
				refCounter.cpp \
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
				shaderPl.cpp \
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


BUILT_SOURCES =

## Additional rules for autogenerating flex products
if HAVE_FLEX

BUILT_SOURCES +=  lex.dso.cpp lex.rib.cpp lex.sl.cpp lex.var.cpp lex.if.cpp

lex.dso.cpp: dso.l
	@FLEX@ -i -Pdso -olex.dso.cpp dso.l

lex.rib.cpp: rib.l
	@FLEX@ -i -Prib -olex.rib.cpp rib.l

lex.sl.cpp: sdr.l
	@FLEX@ -Psl -olex.sl.cpp sdr.l

lex.var.cpp: variable.l
	@FLEX@ -Pvar -olex.var.cpp variable.l

lex.if.cpp: ifexpr.l
	@FLEX@ -Pif -olex.if.cpp ifexpr.l

endif
## Additional rules for autogenerating flex products


## Additional rules for autogenerating bison products
if HAVE_BISON

BUILT_SOURCES +=  dso.cpp rib.cpp sl.cpp variable.cpp ifexpr.cpp


dso.cpp: dso.y
	@BISON@ -p dso -o dso.cpp dso.y

rib.cpp: rib.y
	@BISON@ -p rib -o rib.cpp rib.y

sl.cpp: sdr.y
	@BISON@ -p sl -o sl.cpp sdr.y

variable.cpp: variable.y
	@BISON@ -p var -o variable.cpp variable.y

ifexpr.cpp: ifexpr.y
	@BISON@ -p if -o ifexpr.cpp ifexpr.y

endif
## Additional rules for autogenerating bison products
