cmake_minimum_required(VERSION 3.14)
project(task_02)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Build the model library
add_library(model STATIC model.cpp)
target_include_directories(model PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Build the main executable
add_executable(task_02 task_02.cpp)
target_link_libraries(task_02 PRIVATE model)

# Fetch and configure GoogleTest
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Build the test executable
add_executable(runTests ../test/test.cpp)
target_link_libraries(runTests PRIVATE model gtest gtest_main)

# Register tests automatically
include(GoogleTest)
gtest_discover_tests(runTests)