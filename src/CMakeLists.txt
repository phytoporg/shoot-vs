cmake_minimum_required (VERSION 3.13)

project(ShootVs)

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/Paths.cmake)


find_package(SFML COMPONENTS graphics window system)
message(STATUS "SFML included at ${SFML_INCLUDE_DIR}")

option(BUILD_TESTS "Build the tests" ON)
if(BUILD_TESTS)
    message(STATUS "Building with tests")

    include(CTest)
    find_package(GTest REQUIRED)
    include(GoogleTest)
    enable_testing()

    set(gtestlib ${GTEST_LIBRARIES})
    set(gtestmain ${GTEST_MAIN_LIBRARIES})

    add_subdirectory(test)
else()
    message(STATUS "Not building tests")
endif()

add_subdirectory(cricket)
add_subdirectory(game)

