cmake_minimum_required (VERSION 3.13)

SET(TARGETNAME client_server_test)
file(GLOB SOURCES *.cpp)
add_executable(${TARGETNAME} ${SOURCES})

include_directories(${SRC_ROOT} ${GTEST_INCLUDE_DIR})
target_link_libraries(${TARGETNAME} ${gtestmain} ${gtestlib} pthread)

gtest_add_tests(TARGET "${TARGETNAME}")
