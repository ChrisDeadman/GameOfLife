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
# Require SDL2
# -----------------
find_package(SDL2 REQUIRED)
if (SDL2_INCLUDE_DIR)
    include_directories(${SDL2_INCLUDE_DIR})
    target_link_libraries(${LIBRARY_NAME} ${SDL2_LIBRARY})
else ()
    message(SEND_ERROR "SDL2 library not found!")
endif ()

# -----------------
# Require SDL2 TTF
# -----------------
find_package(SDL2_TTF REQUIRED)
if (SDL2_TTF_INCLUDE_DIRS)
    include_directories(${SDL2_TTF_INCLUDE_DIRS})
    message(${SDL2_TTF_LIBRARIES})
    target_link_libraries(${LIBRARY_NAME} ${SDL2_TTF_LIBRARIES})
else ()
    message(SEND_ERROR "SDL2 library not found!")
endif ()
