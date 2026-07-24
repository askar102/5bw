@echo off
setlocal

echo ============================
echo   Building project...
echo ============================

rmdir -rf build CMakeFiles

cmake -S . -B build
if %errorlevel% neq 0 (
    echo CMake configure failed
    pause
    exit /b
)

cmake --build build
if %errorlevel% neq 0 (
    echo Build failed
    pause
    exit /b
)

echo ============================
echo   Trying to run ur fcking game...
echo ============================

build\5bw12.exe

echo ============================
echo   Game has closed
echo ============================
pause