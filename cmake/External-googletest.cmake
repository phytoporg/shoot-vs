cmake_minimum_required(VERSION 3.7)

include(ExternalProject)

find_package(GTest)
if (NOT GTest_FOUND)
    message("Could not find GTest package. Pulling from git repository and building from scratch.")

    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

    ExternalProject_Add(GOOGLETEST
        PREFIX googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG master
        SOURCE_DIR ${CMAKE_CURRENT_BINARY_DIR}/googletest/src/googletest
        STEP_TARGETS build
        EXCLUDE_FROM_ALL TRUE
        INSTALL_COMMAND cmake -E echo "Skipping install step."
        CMAKE_ARGS
            -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
            -DCMAKE_CXX_FLAGS_RELEASE=${CMAKE_CXX_FLAGS_RELEASE}
            -DCMAKE_SHARED_LINKER_FLAGS_RELEASE=${CMAKE_SHARED_LINKER_FLAGS_RELEASE}
            -Dgtest_force_shared_crt:BOOL=ON
            -DCMAKE_DEBUG_POSTFIX=d
            -DBUILD_SHARED_LIBS=1
            -DCMAKE_CXX_STANDARD=14
    )

    list(APPEND DEPENDENCIES GOOGLETEST)
endif()
