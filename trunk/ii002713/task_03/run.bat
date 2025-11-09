@echo off
REM Build Debug, run tests, main program and generate HTML docs

REM Set build directory inside src
set BUILD_DIR=%~dp0src\build

REM Create build folder if not exists
if not exist "%BUILD_DIR%" mkdir "%BUILD_DIR%"

REM Configure and build Debug
echo.
echo Building Debug configuration
cmake -S %~dp0src -B "%BUILD_DIR%" -G "Visual Studio 17 2022" -A x64 -DCMAKE_BUILD_TYPE=Debug
cmake --build "%BUILD_DIR%" --config Debug

REM Run Google Test
echo.
echo Running Google Tests
"%BUILD_DIR%\Debug\runTests_ii002713_task03.exe"
echo.
echo Google Tests finished

REM Run main program
echo.
echo Running main program (pid_sim)
"%BUILD_DIR%\Debug\pid_sim.exe"
echo.
echo Main program finished

REM Generate Doxygen HTML documentation
echo.
echo Generating Doxygen HTML documentation
cmake --build "%BUILD_DIR%" --target doc

REM Open HTML documentation in default browser
if exist "%~dp0doc\html\index.html" (
    start "" "%~dp0doc\html\index.html"
)

echo.
echo All done: Tests, main program, documentation
pause
