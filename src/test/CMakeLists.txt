set(EXECUTABLE_NAME "${PROJECT_NAME}_test")

file(GLOB TEST_SOURCE_FILES
        "*.cpp")

add_executable(${EXECUTABLE_NAME} ${TEST_SOURCE_FILES})

target_link_libraries(${EXECUTABLE_NAME} "lib${PROJECT_NAME}")
target_link_libraries(${EXECUTABLE_NAME} libgtest)
target_link_libraries(${EXECUTABLE_NAME} libgmock)

enable_testing()
add_test(all-tests ${EXECUTABLE_NAME})
