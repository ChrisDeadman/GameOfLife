set(EXECUTABLE_NAME ${PROJECT_NAME})

file(GLOB MAIN_SOURCE_FILES
        "*.h"
        "*.cpp")

add_executable(${EXECUTABLE_NAME} ${MAIN_SOURCE_FILES})

target_link_libraries(${EXECUTABLE_NAME} "lib${PROJECT_NAME}")
