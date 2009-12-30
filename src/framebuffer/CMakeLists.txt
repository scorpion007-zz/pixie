file(GLOB framebuffer_headers *.h)

find_package( X11 REQUIRED )

if(X11_FOUND)
	add_library(framebuffer MODULE framebuffer.cpp fbx.cpp ${framebuffer_headers})
	target_link_libraries(framebuffer pixiecommon ${X11_LIBRARIES})
	set_target_properties(framebuffer PROPERTIES PREFIX "")
	install(TARGETS framebuffer LIBRARY DESTINATION "${displaysdir}")
else(X11_FOUND)
	message(FATAL_ERROR "Could not find X11 libs, cannot build framebuffer.so")
endif(X11_FOUND)