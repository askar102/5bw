@echo off
setlocal

echo ============================
echo   I fck your mother I building project plz wait me
echo ============================

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
echo   Game has closed alright
echo ============================
pause