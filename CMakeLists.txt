cmake_minimum_required(VERSION 2.6)

project(Pixie)

set(PIXIE_VERSION_MAJOR "2")
set(PIXIE_VERSION_MINOR "2")
set(PIXIE_VERSION_PATCH "6")
set(PIXIE_VERSION ${PIXIE_VERSION_MAJOR}.${PIXIE_VERSION_MINOR}.${PIXIE_VERSION_PATCH})

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake")


set(PIXIE_INSTALL_PREFIX "/usr/local/Pixie" CACHE PATH "Prefix prepended to install directories")
set(CMAKE_INSTALL_PREFIX "${PIXIE_INSTALL_PREFIX}" CACHE INTERNAL "Prefix prepended to install directories" FORCE)

# ###########################################################################
# ########## Options 
# ###########################################################################
option(USE_FLEX_BISON "" ON)
option(BUILD_SHOW "Build the show program" ON)
option(INSTALL_SELFCONTAINED "Build for a selfcontained setup (overrides custom directory settings)" ON)
if(APPLE)
	option(USE_STAGING_TIFF_LIB "Set this option to ON to build with the TIFF libs from xcode subdir. Set to OFF to build with system installed libs instead (Fink/MacPorts)" OFF)
	option(USE_STAGING_OPENEXR_LIB "Set this option to ON to build with the OpenEXR libs from xcode subdir. Set to OFF to build with system installed libs instead (Fink/MacPorts)" OFF)
endif(APPLE)

if(USE_FLEX_BISON)
	include(CMake/PixieUseFlex.cmake)
	include(CMake/PixieUseBison.cmake)
endif(USE_FLEX_BISON)


# ###########################################################################
# ########## User Overridable Variables
# ###########################################################################
if(APPLE)
	# this is required for Snow Leopard, gcc being configured as 64-bit by default
	set(PIXIE_C_FLAGS "-arch i386" CACHE STRING "var")
	set(PIXIE_CXX_FLAGS "-arch i386" CACHE STRING "var")
else(APPLE)
	set(PIXIE_C_FLAGS CACHE STRING "Pixie custom cflags")
	set(PIXIE_CXX_FLAGS CACHE STRING "Pixie custom cxxflags")
endif(APPLE)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${PIXIE_C_FLAGS}" CACHE INTERNAL "Pixie custom cflags" FORCE)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${PIXIE_CXX_FLAGS}" CACHE INTERNAL "Pixie custom cxxflags" FORCE)

# ###########################################################################
# ########## Making config.h for various platform
# ###########################################################################
include(CheckIncludeFiles)
include(CheckFunctionExists)
include(CheckLibraryExists)

set(CMAKE_REQUIRED_INCLUDES math.h)
set(CMAKE_REQUIRED_LIBRARIES m)

# check some include files
check_include_files(malloc.h 						HAVE_MALLOC_H)
check_include_files(stdint.h 						HAVE_STDINT_H)
check_include_files("sys/param.h;sys/mount.h" 		HAVE_SYS_MOUNT_H)
check_include_files(sys/time.h 						HAVE_SYS_TIME_H)

# check libs
check_library_exists(dl			dlopen			"" 	HAVE_DL)
check_library_exists(m			sin				"" 	HAVE_M)
check_library_exists(pthread 	pthread_create 	"" 	HAVE_PTHREAD)

# check functions
check_function_exists(random 						HAVE_RANDOM)
check_function_exists(gettimeofday 					HAVE_GETTIMEOFDAY)
check_function_exists(sqrtf 						HAVE_SQRTF)
check_function_exists(cosf							HAVE_COSF)
check_function_exists(sinf							HAVE_SINF)
check_function_exists(tanf							HAVE_TANF)
check_function_exists(atan2f						HAVE_ATAN2F)
check_function_exists(powf							HAVE_POWF)
check_function_exists(logf							HAVE_LOGF)
check_function_exists(fmodf							HAVE_FMODF)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config-cmake.h.in ${CMAKE_CURRENT_BINARY_DIR}/config.h)
include_directories(${CMAKE_CURRENT_BINARY_DIR})
add_definitions(-DHAVE_CMAKE_CONFIG_H)

# ###########################################################################
# ########## Global Libraries Deps
# ###########################################################################
# Finding some dependency
if(USE_STAGING_TIFF_LIB)
	# on Apple systems, we can use the staging libs. Other option is to use macports / fink versions instead...
	include_directories(xcode/PixieLibs/libtiff/STAGING/libtiff-i386/include)
	find_library(pixietiff_lib pixietiff xcode/PixieLibs/libtiff/STAGING/libtiff NO_DEFAULT_PATH)
	#message(STATUS "found ${pixietiff_lib}" )
	find_library(pixietiffjpeg_lib jpeg xcode/PixieLibs/libtiff/STAGING/libjpeg/lib NO_DEFAULT_PATH)
	#message(STATUS "found ${pixietiffjpeg_lib}" )
	set(pixietiff_libs ${pixietiff_lib} ${pixietiffjpeg_lib})
else(USE_STAGING_TIFF_LIB)
	find_package(TIFF REQUIRED)
	if(TIFF_FOUND)
		include_directories(${TIFF_INCLUDE_DIR})
		set(pixietiff_libs ${TIFF_LIBRARIES})
	else(TIFF_FOUND)
		message(FATAL_ERROR "Could not find TIFF library")
	endif(TIFF_FOUND)
endif(USE_STAGING_TIFF_LIB)

# ###########################################################################
# ########## Installation of built products
# ###########################################################################

if(INSTALL_SELFCONTAINED)
	set(datadir "share")
	set(libdir "lib")
	set(bindir "bin")
	set(includedir "include")
	set(mandir "man")
	set(docdir "doc")
	set(shaderdir "shaders")
	set(ribdir "ribs")
	set(texturedir "textures")
	set(proceduraldir "procedurals")
	set(displaysdir "displays")
	set(modulesdir "modules")
else(INSTALL_SELFCONTAINED)
	set(datadir "share")
	set(libdir "lib")
	set(bindir "bin")
	set(includedir "include/Pixie")
	set(mandir "man")
	set(docdir "${datadir}/Pixie/doc")
	set(shaderdir "${datadir}/Pixie/shaders")
	set(ribdir "${datadir}/Pixie/ribs")
	set(texturedir "${datadir}/Pixie/textures")
	set(proceduraldir "${libdir}/Pixie/procedurals")
	set(displaysdir "${libdir}/Pixie/displays")
	set(modulesdir "${libdir}/Pixie/modules")
endif(INSTALL_SELFCONTAINED)


# install doc
set(doc_files AUTHORS ChangeLog COPYING DEVNOTES INSTALL LICENSE NEWS README)
install(FILES ${doc_files} DESTINATION "${docdir}")

# install man pages
file(GLOB man_files man/*.1)
install(FILES ${man_files} DESTINATION "${mandir}/man1")

#install shaders
file(GLOB shader_files shaders/*.sl)
install(FILES ${shader_files} DESTINATION "${shaderdir}")
file(GLOB shader_files shaders/*.sdr)
install(FILES ${shader_files} DESTINATION "${shaderdir}")


# ###########################################################################
# ########## Find rules/targets in subdirs
# ###########################################################################
add_subdirectory(src)
