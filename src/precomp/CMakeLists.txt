set(precomp_sources precomp.cpp)

add_executable(precomp ${precomp_sources})
target_link_libraries(precomp pixiecommon)

# no install, right?
#install(TARGETS rndr RUNTIME DESTINATION bin)
