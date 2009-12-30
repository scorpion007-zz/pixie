
# Finding EXR dependency
if(USE_STAGING_OPENEXR_LIB)
	find_library(exr_libHalf NAMES Half PATHS ../../xcode/PixieLibs/OpenEXR/STAGING/OpenEXR/lib NO_DEFAULT_PATH)
	find_library(exr_libIlmImf NAMES IlmImf PATHS ../../xcode/PixieLibs/OpenEXR/STAGING/OpenEXR/lib NO_DEFAULT_PATH)
	find_library(exr_libIex NAMES Iex PATHS ../../xcode/PixieLibs/OpenEXR/STAGING/OpenEXR/lib NO_DEFAULT_PATH)
	set(exr_libs  ${exr_libHalf} ${exr_libIex} ${exr_libIlmImf})
	include_directories(../../xcode/PixieLibs/OpenEXR/STAGING/OpenEXR/include/OpenEXR)
	message(STATUS "Found EXR: ${exr_libs}")
else(USE_STAGING_OPENEXR_LIB)
	find_package(OpenEXR)
	set(exr_libs  ${OPENEXR_LIBRARIES})
	include_directories(${OPENEXR_INCLUDE_DIR})
endif(USE_STAGING_OPENEXR_LIB)

# Declare EXR include dir

# Decalre Target
file(GLOB openexr_headers *.h)
add_library(openexr MODULE openexr.cpp ${openexr_headers})
set_target_properties(openexr PROPERTIES PREFIX "")
target_link_libraries(openexr pixiecommon ${exr_libs})

install(TARGETS openexr LIBRARY DESTINATION "${displaysdir}")