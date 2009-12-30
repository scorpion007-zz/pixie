file(GLOB pixiecommon_headers *.h)

add_library(pixiecommon SHARED os.cpp algebra.cpp ${pixiecommon_headers})
target_link_libraries(pixiecommon pthread dl)
install(TARGETS pixiecommon LIBRARY DESTINATION "${libdir}")

if(APPLE)
	# some Apple specific dependencies
	target_link_libraries(pixiecommon "-framework CoreServices")

	# install name for dylibs on Mac
	set_target_properties(pixiecommon PROPERTIES INSTALL_NAME_DIR "${CMAKE_INSTALL_PREFIX}/lib")
endif(APPLE)

