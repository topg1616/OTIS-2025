cmake_minimum_required(VERSION 3.14)
project(task_02)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fprofile-arcs -ftest-coverage")

# Model library
add_library(model STATIC model.cpp)
target_include_directories(model PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Main executable
add_executable(task_02 ${CMAKE_CURRENT_SOURCE_DIR}/task_02.cpp)
target_link_libraries(task_02 PRIVATE model)

# GoogleTest setup
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Test executable
add_executable(runTests ${CMAKE_CURRENT_SOURCE_DIR}/../test/test.cpp)
target_link_libraries(runTests PRIVATE model gtest gtest_main)

target_compile_options(runTests PRIVATE --coverage -g -O0)
target_link_options(runTests PRIVATE --coverage)

# Register tests
include(GoogleTest)
gtest_discover_tests(runTests)