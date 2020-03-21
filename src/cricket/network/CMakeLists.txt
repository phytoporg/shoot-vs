cmake_minimum_required (VERSION 3.13)

file(GLOB LOCAL_SOURCES *.cpp)
set(SOURCES
    ${SOURCES}
    ${LOCAL_SOURCES}
    PARENT_SCOPE)
