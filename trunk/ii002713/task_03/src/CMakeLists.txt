cmake_minimum_required(VERSION 3.14)
project(ii002713_task_03 LANGUAGES CXX)

# Настройки компиляции

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Строгие предупреждения
if (MSVC)
    add_compile_options(/W4 /permissive-)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Пути
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../test)
set(DOC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../doc)

# Библиотеки

add_library(model STATIC ${SRC_DIR}/model.cpp)
target_include_directories(model PUBLIC ${SRC_DIR})

add_library(pid STATIC ${SRC_DIR}/pid.cpp)
target_include_directories(pid PUBLIC ${SRC_DIR})

# Основная программа

add_executable(pid_sim ${SRC_DIR}/main.cpp)
target_link_libraries(pid_sim PRIVATE pid model)

# Google Test

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()
include(GoogleTest)

if (EXISTS ${TEST_DIR}/test_pid.cpp)
    add_executable(runTests_ii002713_task03 ${TEST_DIR}/test_pid.cpp)
    target_link_libraries(runTests_ii002713_task03 PRIVATE gtest_main pid model)
    gtest_discover_tests(runTests_ii002713_task03)
else()
    message(WARNING "Файл тестов не найден: ${TEST_DIR}/test_pid.cpp")
endif()


# Doxygen

find_package(Doxygen QUIET)
if (DOXYGEN_FOUND)
    set(DOXYFILE_IN ${DOC_DIR}/Doxyfile.in)
    set(DOXYFILE_OUT ${CMAKE_BINARY_DIR}/Doxyfile)

    configure_file(${DOXYFILE_IN} ${DOXYFILE_OUT} @ONLY)

    add_custom_target(doc
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYFILE_OUT}
        WORKING_DIRECTORY ${DOC_DIR}
        COMMENT "📚 Генерация документации Doxygen..."
        VERBATIM
    )
else()
    message(WARNING "Doxygen не найден. Цель 'doc' будет недоступна.")
endif()
