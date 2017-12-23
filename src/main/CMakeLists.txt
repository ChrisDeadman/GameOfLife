set(EXECUTABLE_NAME ${PROJECT_NAME})

file(GLOB MAIN_SOURCE_FILES
        "*.h"
        "*.cpp")

add_executable(${EXECUTABLE_NAME} ${MAIN_SOURCE_FILES})

configure_file(${CMAKE_SOURCE_DIR}/data/opensans/OpenSans-Regular.ttf OpenSans-Regular.ttf COPYONLY)

target_link_libraries(${EXECUTABLE_NAME} "lib${PROJECT_NAME}")

# -----------------
# Require SDL2
# -----------------
find_package(SDL2 REQUIRED)
if (SDL2_INCLUDE_DIR)
    include_directories(${SDL2_INCLUDE_DIR})
else ()
    message(SEND_ERROR "SDL2 library not found!")
endif ()

# -----------------
# Require SDL2 TTF
# -----------------
find_package(SDL2_TTF REQUIRED)
if (SDL2_TTF_INCLUDE_DIRS)
    include_directories(${SDL2_TTF_INCLUDE_DIRS})
else ()
    message(SEND_ERROR "SDL2 library not found!")
endif ()
