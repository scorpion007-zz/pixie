file(GLOB file_headers *.h)

add_library(file MODULE file.cpp file_tiff.cpp file_png.cpp ${file_headers})
target_link_libraries(file ${pixietiff_libs} pixiecommon)

if(UNIX)
	target_link_libraries(file z)
endif(UNIX)

if(WIN32)
	target_link_libraries(file zlib)
endif(WIN32)


set_target_properties(file PROPERTIES PREFIX "") # otherwise CMake create a libxxxx.so file, here we don't want the lib prefix
install(TARGETS file LIBRARY DESTINATION "${displaysdir}")