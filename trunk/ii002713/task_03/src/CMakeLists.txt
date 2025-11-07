cmake_minimum_required(VERSION 3.14)
project(ii002713_task_03 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Пути
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../test)
set(DOC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../doc)

# Библиотеки

# Модель
add_library(model STATIC model.cpp)
target_include_directories(model PUBLIC ${SRC_DIR})

# PID-регулятор
add_library(pid STATIC pid.cpp)
target_include_directories(pid PUBLIC ${SRC_DIR})

# Основная программа
add_executable(pid_sim main.cpp)
target_link_libraries(pid_sim PRIVATE pid model)

# Google Test
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(runTests ${TEST_DIR}/test_pid.cpp)
target_link_libraries(runTests PRIVATE gtest_main pid model)

add_test(NAME all_tests COMMAND runTests)

# Doxygen
find_package(Doxygen QUIET)
if (DOXYGEN_FOUND)
    set(DOXYFILE_IN ${DOC_DIR}/Doxyfile.in)
    set(DOXYFILE_OUT ${CMAKE_BINARY_DIR}/Doxyfile)
    configure_file(${DOXYFILE_IN} ${DOXYFILE_OUT} @ONLY)

    add_custom_target(doc
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYFILE_OUT}
        WORKING_DIRECTORY ${DOC_DIR}
        COMMENT "Генерация документации Doxygen"
        VERBATIM)
endif()
