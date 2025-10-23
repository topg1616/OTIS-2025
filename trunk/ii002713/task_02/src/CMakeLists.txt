cmake_minimum_required(VERSION 3.14)
project(task_02)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# === Модель проекта ===
add_library(model STATIC model.cpp)
target_include_directories(model PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# === GoogleTest ===
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
    )
    
# Настройка CRT, чтобы избежать ошибок MTd / MDd
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
# Подключение GoogleTest
FetchContent_MakeAvailable(googletest)

enable_testing()

# === Тесты ===
add_executable(runTests ../test/test.cpp)
target_link_libraries(runTests PRIVATE model gtest gtest_main)
include(GoogleTest)
gtest_discover_tests(runTests)