cmake_minimum_required(VERSION 3.14)
project(task_02)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Включаем флаги покрытия
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage -O0 -g")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fprofile-arcs -ftest-coverage")

# Модель
add_library(model STATIC model.cpp)
target_include_directories(model PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(model PRIVATE gcov)

# Основной исполняемый файл
add_executable(task_02 ${CMAKE_CURRENT_SOURCE_DIR}/task_02.cpp)
target_link_libraries(task_02 PRIVATE model gcov)

# GoogleTest setup
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Тесты
add_executable(runTests_ii002713 ${CMAKE_CURRENT_SOURCE_DIR}/../test/test.cpp)
target_link_libraries(runTests_ii002713
    PRIVATE
        model
        gtest
        gtest_main
        gcov
)

target_compile_options(runTests_ii002713 PRIVATE -fprofile-arcs -ftest-coverage -O0 -g)
target_link_options(runTests_ii002713 PRIVATE -fprofile-arcs -ftest-coverage)

# Регистрация тестов
include(GoogleTest)
gtest_discover_tests(runTests_ii002713)
