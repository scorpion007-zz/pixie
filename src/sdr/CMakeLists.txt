file(GLOB sdr_headers *.h)

if(USE_FLEX_BISON)
	# this is to make sure generated bison cpp's include the correct lex.xxx.cpp
	include_directories(BEFORE ${CMAKE_CURRENT_BINARY_DIR})
	include_directories(AFTER .)

	# define flex targets
	flex_file(sdr.l lex.sdr.cpp sdr)

	# define bison targets (they depend on flex ones, via prefix - third arg)
	bison_file(sdr.y sdr_generated.cpp sdr)
	
	# add the generated bison cpp's
	set(sdr_sources sdr_generated.cpp)
else(USE_FLEX_BISON)
	# add the ones from the source tree
	set(sdr_sources sdr.cpp)
endif(USE_FLEX_BISON)

add_library(sdr SHARED ${sdr_sources} ${sdr_headers})
target_link_libraries(sdr pixiecommon)
install(TARGETS sdr LIBRARY DESTINATION "${libdir}"
			ARCHIVE DESTINATION "{$libdir}"
			RUNTIME DESTINATION "{$bindir}")
install(FILES sdr.h DESTINATION "${includedir}")

if(APPLE)
	set_target_properties(sdr PROPERTIES INSTALL_NAME_DIR "${CMAKE_INSTALL_PREFIX}/lib")
endif(APPLE)

