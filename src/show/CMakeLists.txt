
if(BUILD_SHOW)
	add_executable(show show.cpp)
	target_link_libraries(show ri pixiecommon)
	install(TARGETS show RUNTIME DESTINATION "${bindir}")
endif(BUILD_SHOW)
