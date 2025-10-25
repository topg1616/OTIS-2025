<p align="center">Министерство образования Республики Беларусь</p>
<p align="center">Учреждение образования</p>
<p align="center">“Брестский Государственный технический университет”</p>
<p align="center">Кафедра ИИТ</p>
<br><br><br><br><br><br><br>
<p align="center">Лабораторная работа №2</p>
<p align="center">По дисциплине “Общая теория интеллектуальных систем”</p>
<p align="center">Тема: “Модульное тестирование. Покрытие исходного кода тестами.”</p>
<br><br><br><br><br>
<p align="right">Выполнил:</p>
<p align="right">Студент 2 курса</p>
<p align="right">Группы ИИ-27</p>
<p align="right">Лыщенко К.В.</p>
<p align="right">Проверил:</p>
<p align="right">Дворанинович Д.А.</p>
<br><br><br><br><br>
<p align="center">Брест 2025</p>

# Общее задание #
Написать модульные тесты для программы, разработанной в лабораторной работе №1.

1. Использовать следующий фреймворк для модульного тестирования - [Google Test](https://google.github.io/googletest/).
2. Написать модульные тесты для основных функций программы. Разместить тесты в каталоге: **trunk\ii0xxyy\task_02\test**.
3. Исходный код модифицированной программы разместить в каталоге: **trunk\ii0xxyy\task_02\src**.
4. В файле `readme.md` отразить количество написанных тестов и процент покрытия кода тестами (использовать любой инструмент для анализа покрытия, например, [gcovr](https://gcovr.com/en/stable/)).
5. Также необходимо отразить выполнение работы в общем файле [`readme.md`](https://github.com/brstu/OTIS-2025/blob/main/README.md) в соответствующей строке (например, для студента под порядковым номером 1 - https://github.com/brstu/OTIS-2025/blob/b2d60c2765b369aed21af76af8fa4461da2c8da6/README.md?plain=1#L13).


## Код юнит-тестов [ test/test.cpp ]
```C++
#include <gtest/gtest.h>
#include <cmath>
#include "model.h"

// Тесты для линейной модели
TEST(LinearModelTest, BaseCase) {
    EXPECT_NEAR(Linear(0.1, 0.3, 0.5, 0.0), 0.15, 1e-6);
}

TEST(LinearModelTest, WithNonZeroY) {
    EXPECT_NEAR(Linear(0.2, 0.4, 2.0, 1.0), 1.0, 1e-6);
}

// Тесты для нелинейной модели
TEST(NonlinearModelTest, BaseCase) {
    NonlinearParams p{0.7, 0.9, 0.11, 0.13};
    double result = Nonlinear(p, 0.15, 0.0, 0.0, 0.0); // u, uPrev, y, yPrev
    double expected = p.c * 0.15 + p.d * std::sin(0.0);
    EXPECT_NEAR(result, expected, 1e-6);
}

TEST(NonlinearModelTest, WithPreviousValues) {
    NonlinearParams p{0.5, 0.2, 0.3, 0.1};
    double result = Nonlinear(p, 0.4, 0.3, 0.5, 0.2); // u, uPrev, y, yPrev
    double expected = 0.5 * 0.5 - 0.2 * (0.2 * 0.2) + 0.3 * 0.4 + 0.1 * std::sin(0.3);
    EXPECT_NEAR(result, expected, 1e-6);
}

```
## Результаты юнит-тестирования (GoogleTest)
[==========] Running 4 tests from 2 test suites.
[----------] Global test environment set-up.
[----------] 2 tests from LinearModelTest
[ RUN      ] LinearModelTest.BaseCase
[       OK ] LinearModelTest.BaseCase (0 ms)
[ RUN      ] LinearModelTest.WithNonZeroY
[       OK ] LinearModelTest.WithNonZeroY (0 ms)
[----------] 2 tests from LinearModelTest (26 ms total)

[----------] 2 tests from NonlinearModelTest
[ RUN      ] NonlinearModelTest.BaseCase
[       OK ] NonlinearModelTest.BaseCase (0 ms)
[ RUN      ] NonlinearModelTest.WithPreviousValues
[       OK ] NonlinearModelTest.WithPreviousValues (0 ms)
[----------] 2 tests from NonlinearModelTest (33 ms total)

[----------] Global test environment tear-down
[==========] 4 tests from 2 test suites ran. (116 ms total)
[  PASSED  ] 4 tests.

## Покрытие тестами (gcovr)
src/build/_deps/googletest-src/googletest/src/gtest_main.cc
                                               4       4   100%
src/model.cpp                                 25      25   100%
src/task_02.cpp                               11      11   100%
test/test.cpp                                 30      30   100%
------------------------------------------------------------------------------
TOTAL                                       6381    1374    21%
------------------------------------------------------------------------------