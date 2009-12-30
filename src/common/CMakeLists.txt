file(GLOB pixiecommon_headers *.h)

add_library(pixiecommon STATIC os.cpp algebra.cpp ${pixiecommon_headers})
target_link_libraries(pixiecommon)
install(TARGETS pixiecommon LIBRARY DESTINATION "${libdir}"
				ARCHIVE DESTINATION "{$libdir}"
				RUNTIME DESTINATION "{$bindir}")

if(UNIX)
	target_link_libraries(pixiecommon pthread dl)
endif(UNIX)

if(APPLE)
	# some Apple specific dependencies
	target_link_libraries(pixiecommon "-framework CoreServices")

	# install name for dylibs on Mac
	set_target_properties(pixiecommon PROPERTIES INSTALL_NAME_DIR "${CMAKE_INSTALL_PREFIX}/lib")
endif(APPLE)

