file(GLOB rgbe_headers *.h)
file(GLOB rgbe_sources *.cpp)

add_library(rgbe MODULE ${rgbe_sources} ${rgbe_headers})
set_target_properties(rgbe PROPERTIES PREFIX "")
install(TARGETS rgbe LIBRARY DESTINATION "${displaysdir}")
