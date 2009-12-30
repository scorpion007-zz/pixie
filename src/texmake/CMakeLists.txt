
add_executable(texmake texmake.cpp)
target_link_libraries(texmake ri pixiecommon)
install(TARGETS texmake RUNTIME DESTINATION "${bindir}")