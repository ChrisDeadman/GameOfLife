set(LIBRARY_NAME "lib${PROJECT_NAME}")

file(GLOB LIBMAIN_SOURCE_FILES
        "*.h"
        "*.cpp")

add_library(${LIBRARY_NAME} ${LIBMAIN_SOURCE_FILES})

set_property(
        TARGET ${LIBRARY_NAME} APPEND PROPERTY INTERFACE_INCLUDE_DIRECTORIES
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

################################
# Dependencies
################################

# -----------------
# Require pthread
# -----------------
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
if (THREADS_FOUND)
    target_link_libraries(${LIBRARY_NAME} Threads::Threads)
else ()
    message(SEND_ERROR "pthread library not found!")
endif ()

# -----------------
# Require SFML
# -----------------
find_package(SFML 2 REQUIRED graphics window network audio system)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${LIBRARY_NAME} ${SFML_LIBRARIES})
    target_link_libraries(${LIBRARY_NAME} ${SFML_DEPENDENCIES})
else ()
    message(SEND_ERROR "SFML library not found. Please set SFML_ROOT.")
endif ()
