add_executable(sdrinfo sdrinfo.cpp)
target_link_libraries(sdrinfo sdr pixiecommon)
install(TARGETS sdrinfo RUNTIME DESTINATION "${bindir}")