set(GTEST_LIBRARY_NAME "libgtest")
set(GMOCK_LIBRARY_NAME "libgmock")

include(ExternalProject)

ExternalProject_Add(
        gtest
        URL https://github.com/google/googletest/archive/master.zip
        PREFIX ${CMAKE_CURRENT_BINARY_DIR}/gtest
        # Disable install step
        INSTALL_COMMAND ""
)

# Get gtest source and binary directories from CMake project
ExternalProject_Get_Property(gtest source_dir binary_dir)

################################
# libgtest
################################
add_library(${GTEST_LIBRARY_NAME} IMPORTED STATIC GLOBAL)
add_dependencies(${GTEST_LIBRARY_NAME} gtest)

set(GTEST_INCLUDE_DIRECTORY "${source_dir}/googletest/include")

file(MAKE_DIRECTORY ${GTEST_INCLUDE_DIRECTORY})

set_target_properties(
        ${GTEST_LIBRARY_NAME} PROPERTIES
        "IMPORTED_LOCATION" "${binary_dir}/googlemock/gtest/libgtest.a"
        "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
)

set_property(
        TARGET ${GTEST_LIBRARY_NAME} APPEND PROPERTY INTERFACE_INCLUDE_DIRECTORIES
        $<BUILD_INTERFACE:${GTEST_INCLUDE_DIRECTORY}>
)

################################
# libgmock
################################
add_library(${GMOCK_LIBRARY_NAME} IMPORTED STATIC GLOBAL)
add_dependencies(${GMOCK_LIBRARY_NAME} gmock)

set(GMOCK_INCLUDE_DIRECTORY "${source_dir}/googlemock/include")

file(MAKE_DIRECTORY ${GMOCK_INCLUDE_DIRECTORY})

set_target_properties(
        ${GMOCK_LIBRARY_NAME} PROPERTIES
        "IMPORTED_LOCATION" "${binary_dir}/googlemock/libgmock.a"
        "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
)

set_property(
        TARGET ${GMOCK_LIBRARY_NAME} APPEND PROPERTY INTERFACE_INCLUDE_DIRECTORIES
        $<BUILD_INTERFACE:${GMOCK_INCLUDE_DIRECTORY}>
)
