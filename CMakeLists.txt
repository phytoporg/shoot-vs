cmake_minimum_required (VERSION 2.8)
project(ShootVs)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_LIST_DIR}/cmake)
find_package(SFML COMPONENTS graphics window system)
add_subdirectory(src)
