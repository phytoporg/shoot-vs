cmake_minimum_required (VERSION 2.8)

set(TARGET_NAME cricket)

file(GLOB SOURCES *.cpp) # <-- try and eliminate this
add_subdirectory(game)
add_subdirectory(input)
add_subdirectory(network)
add_subdirectory(resource)
add_subdirectory(utility)

add_library(${TARGET_NAME} ${SOURCES})
target_include_directories(${TARGET_NAME} PUBLIC
    .
    ${GLM_INCLUDE_DIR}
    ${SFLM_INCLUDE_DIR})
