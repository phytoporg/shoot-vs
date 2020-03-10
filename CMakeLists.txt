cmake_minimum_required (VERSION 2.8)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_LIST_DIR}/cmake)

#
# Handle superbuild first
# Leveraging the superbuild pattern illustrated at Sarcasm/cmake-superbuild
#
option (USE_SUPERBUILD "Whether or not a superbuild should be invoked" ON)
option (DEPS_ONLY "Only build dependencies and skip Watcher step" OFF)

if (USE_SUPERBUILD)
    project(SUPERBUILD NONE)
    include(cmake/Superbuild.cmake)
    return()
elseif(NOT DEPS_ONLY)
    project(Watchers CXX C)
endif()

add_subdirectory(src)
