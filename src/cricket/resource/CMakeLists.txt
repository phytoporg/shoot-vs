cmake_minimum_required (VERSION 2.8)

file(GLOB LOCAL_SOURCES *.cpp)
set(SOURCES
    ${SOURCES}
    ${LOCAL_SOURCES}
    PARENT_SCOPE)
