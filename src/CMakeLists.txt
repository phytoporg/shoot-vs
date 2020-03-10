cmake_minimum_required (VERSION 2.8)

project(ShootVs)

find_package(SFML COMPONENTS graphics window system)
message(STATUS "SFML included at ${SFML_INCLUDE_DIR}")

add_subdirectory(cricket)
add_subdirectory(game)

