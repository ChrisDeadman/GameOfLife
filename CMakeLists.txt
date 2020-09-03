cmake_minimum_required(VERSION 3.6)

set(PROJECT_NAME "gameOfLife")

project(${PROJECT_NAME})

if (CMAKE_BUILD_TYPE MATCHES "")
    set(CMAKE_BUILD_TYPE "RELEASE")
endif()

message("CMAKE_BUILD_TYPE is '${CMAKE_BUILD_TYPE}'")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-Ofast")

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

set(EXTERNAL_PROJECTS_PREFIX ${CMAKE_BINARY_DIR}/external-projects)

set(EXTERNAL_PROJECTS_INSTALL_PREFIX ${EXTERNAL_PROJECTS_PREFIX}/installed)

option(test "Build all tests." OFF)

add_subdirectory(src/libmain)
add_subdirectory(src/main)

if (test)
    add_subdirectory(src/libgtest)
    add_subdirectory(src/test)
endif ()
