cmake_minimum_required (VERSION 2.8)

set(TARGET_NAME ShootVs)

file(GLOB SOURCES *.cpp)
add_executable (${TARGET_NAME} ${SOURCES})

target_include_directories(${TARGET_NAME} PUBLIC
    ${SFLM_INCLUDE_DIR})

target_link_libraries(${TARGET_NAME} ${SFML_LIBRARIES})
