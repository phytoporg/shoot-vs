cmake_minimum_required (VERSION 3.13)

set(TARGET_NAME ShootVs)

file(GLOB SOURCES *.cpp)
add_executable (${TARGET_NAME} ${SOURCES})

target_include_directories(${TARGET_NAME} PUBLIC
    ..
    ${GLM_INCLUDE_DIR}
    ${SFLM_INCLUDE_DIR})
target_link_libraries(${TARGET_NAME} ${SFML_LIBRARIES} cricket stdc++fs)

