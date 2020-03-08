cmake_minimum_required (VERSION 2.8)
project(ShootVs)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_LIST_DIR}/cmake)
find_package(SFML COMPONENTS graphics window system)
message(STATUS "SFML included at ${SFML_INCLUDE_DIR}")

find_package(GLM REQUIRED)
message(STATUS "GLM included at ${GLM_INCLUDE_DIR}")

add_subdirectory(src)
