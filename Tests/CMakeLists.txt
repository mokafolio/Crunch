add_executable (CrunchTests CrunchTests.cpp)
target_link_libraries(CrunchTests ${CRUNCHDEPS})
add_custom_target(check COMMAND CrunchTests)
