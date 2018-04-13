cmake_minimum_required(VERSION 3.9)

#Project Name
project(ISAE_ML)

#The version number
set(ISAE_ML_VERSION_MAJOR 0)
set(ISAE_ML_VERSION_MINOR 1)

#Configure a header file to pass CMAKE settings to source code
configure_file(
        "${PROJECT_SOURCE_DIR}/src/Config.hpp.in"
        "${PROJECT_BINARY_DIR}/Config.hpp"
)

# add the binary tree to the search path for include files
# so that we will find Config.h
include_directories("${PROJECT_BINARY_DIR}")

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_STANDARD 11)
set(DIST_DIR "${CMAKE_PROJECT_NAME}")

option(GPU "Use of CUDA Library" ON)
option(OPENCV "Use of OpenCV Library" ON)

if (GPU)
    message(STATUS "Use of CUDA activated")
    add_definitions(-DGPU=1)
endif ()

if (OPENCV)
    message(STATUS "Use of OPENCV activated")
    add_definitions(-DOPENCV=1)
endif ()

add_subdirectory(src)
add_subdirectory(examples)
add_subdirectory(doc)

add_subdirectory(tests)
enable_testing()

file(
        GLOB
        unit_tests
        tests/*.cpp
)

foreach (t ${unit_tests})
    get_filename_component(testName ${t} NAME_WE)
    add_test(NAME ${testName}
            COMMAND ${testName}
            )

endforeach (t)


add_custom_target(dist
        COMMAND rm -rf ${DIST_DIR}
        COMMAND mkdir ${DIST_DIR}
        COMMAND cp -r ${CMAKE_SOURCE_DIR}/* ${DIST_DIR} || true
        COMMAND rm -rf ${DIST_DIR}/build
        COMMAND mkdir ${DIST_DIR}/build
        COMMAND tar --exclude="*~" --exclude="._*" -zcvf ${DIST_DIR}.tar.gz ${DIST_DIR}
        COMMAND rm -rf ${DIST_DIR}
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR})

INCLUDE(CPack)

