cmake_minimum_required (VERSION 2.8)

set(TARGET_NAME ShootVs)

file(GLOB SOURCES *.cpp)
add_executable (${TARGET_NAME} ${SOURCES})
target_link_libraries(${TARGET_NAME} ${SFML_LIBRARIES})
