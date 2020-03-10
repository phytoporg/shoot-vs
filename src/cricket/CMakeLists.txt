cmake_minimum_required (VERSION 2.8)

set(TARGET_NAME cricket)

file(GLOB SOURCES *.cpp)
add_library(${TARGET_NAME} ${SOURCES})

target_include_directories(${TARGET_NAME} PUBLIC
    ${GLM_INCLUDE_DIR}
    ${SFLM_INCLUDE_DIR})
