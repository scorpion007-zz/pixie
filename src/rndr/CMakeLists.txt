set(rndr_sources rndr.cpp)

add_executable(rndr ${rndr_sources})
target_link_libraries(rndr ri pixiecommon)
install(TARGETS rndr RUNTIME DESTINATION "${bindir}")
