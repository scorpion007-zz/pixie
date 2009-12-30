file(GLOB ri_headers *.h)

# for flex and bison files that depend on ri/ files
include_directories(.)

set(ri_sources
	attributes.cpp 
	brickmap.cpp 
	bundles.cpp 
	curves.cpp 
	bsplinePatchgrid.cpp 
	debug.cpp 
	delayed.cpp 
	displayChannel.cpp 
	dlobject.cpp 
#	dso.cpp 
	error.cpp 
	execute.cpp 
	executeMisc.cpp 
	fileResource.cpp 
	hcshader.cpp 
#	ifexpr.cpp 
	implicitSurface.cpp 
	init.cpp 
	irradiance.cpp 
	linsys.cpp 
	memory.cpp 
	noise.cpp 
	object.cpp 
	occlusion.cpp 
	options.cpp 
	patches.cpp 
	patchgrid.cpp 
	photon.cpp 
	photonMap.cpp 
	pl.cpp 
	points.cpp 
	pointCloud.cpp 
	pointHierarchy.cpp 
	polygons.cpp 
	ptcapi.cpp 
	quadrics.cpp 
	random.cpp 
	raytracer.cpp 
	refCounter.cpp 
	remoteChannel.cpp 
	renderer.cpp 
	rendererClipping.cpp 
	rendererContext.cpp 
	rendererDeclerations.cpp 
	rendererDisplay.cpp 
	rendererFiles.cpp 
	rendererJobs.cpp 
	rendererMutexes.cpp 
	rendererNetwork.cpp 
	resource.cpp 
	reyes.cpp 
	ri.cpp 
#	rib.cpp 
	riInterface.cpp 
	ribOut.cpp 
	shader.cpp 
	shaderPl.cpp 
	shading.cpp 
	show.cpp 
#	sl.cpp 
	stats.cpp 
	stochastic.cpp 
	subdivision.cpp 
	subdivisionCreator.cpp 
	surface.cpp 
	texmake.cpp 
	texture.cpp 
	texture3d.cpp 
	trace.cpp 
#	variable.cpp 
	xform.cpp	
	zbuffer.cpp
)

if(USE_FLEX_BISON)
	# this is to make sure generated bison cpp's include the correct lex.xxx.cpp
	include_directories(BEFORE ${CMAKE_CURRENT_BINARY_DIR})

	# define flex targets
	flex_file(dso.l lex.dso.cpp dso)
	flex_file(rib.l lex.rib.cpp rib)
	flex_file(sdr.l lex.sl.cpp sl)
	flex_file(variable.l lex.var.cpp var)
	flex_file(ifexpr.l lex.if.cpp if)

	# define bison targets (they depend on flex ones, via prefix - third arg)
	bison_file(dso.y dso_generated.cpp dso)
	bison_file(rib.y rib_generated.cpp rib)
	bison_file(sdr.y sl_generated.cpp sl)
	bison_file(variable.y variable_generated.cpp var)
	bison_file(ifexpr.y ifexpr_generated.cpp if)
	
	# add the generated bison cpp's
	set(ri_sources ${ri_sources} dso_generated.cpp rib_generated.cpp sl_generated.cpp variable_generated.cpp ifexpr_generated.cpp)
else(USE_FLEX_BISON)
	# add the ones from the source tree
	set(ri_sources ${ri_sources} dso.cpp rib.cpp sl.cpp variable.cpp ifexpr.cpp)
endif(USE_FLEX_BISON)


add_library(ri SHARED ${ri_sources} ${ri_headers})
target_link_libraries(ri ${pixietiff_libs} pixiecommon)
install(TARGETS ri LIBRARY DESTINATION "${libdir}"
			ARCHIVE DESTINATION "{$libdir}"
			RUNTIME DESTINATION "{$bindir}")
install(FILES dlo.h dsply.h implicit.h ptcapi.h ri.h shadeop.h DESTINATION "${includedir}")

if(WIN32)
	target_link_libraries(ri zlib ws2_32)
endif(WIN32)

if(UNIX)
	target_link_libraries(ri z)
endif(UNIX)

if(APPLE)
	set_target_properties(ri PROPERTIES INSTALL_NAME_DIR "${CMAKE_INSTALL_PREFIX}/lib")
endif(APPLE)

