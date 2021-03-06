set(CMAKE_CXX_STANDARD 14)

include(ExternalProject)
set(DEPENDENCIES)

set(PROJECT_ARCHITECTURE x64)

include (${PROJECT_SOURCE_DIR}/cmake/External-googletest.cmake)

ExternalProject_Add(ShootVs
    DEPENDS ${DEPENDENCIES}
    DOWNLOAD_COMMAND ""
    SOURCE_DIR ${PROJECT_SOURCE_DIR}
    BINARY_DIR ShootVs-build
    LIST_SEPARATOR ${SEPARATOR}
    CMAKE_ARGS
        -DUSE_SUPERBUILD=OFF
        -DCMAKE_CXX_STANDARD=${CMAKE_CXX_STANDARD}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -DCMAKE_CXX_FLAGS_RELEASE=${CMAKE_CXX_FLAGS_RELEASE}
        -DCMAKE_SHARED_LINKER_FLAGS_RELEASE=${CMAKE_SHARED_LINKER_FLAGS_RELEASE}
        -DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX}
        -DGTEST_ROOT:PATH=${GTEST_ROOT}
        -DCMAKE_PREFIX_PATH:PATH=${CMAKE_PREFIX_PATH}
        -DCMAKE_MODULES_PATH:PATH=${CMAKE_MODULES_PATH}
    INSTALL_COMMAND ""
)

