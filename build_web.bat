@echo off
setlocal

set EMS_PATH=C:\emscripten

echo --- Activate emscripten env...
cd %EMS_PATH%
call "%EMS_PATH%\emsdk_env.bat"

echo --- Returning back...
cd %~dp0


echo --- Remove old build folder...
if exist "build" ( rmdir /s /q "build" ) else echo --- Cant find 'build/' dir, skipping...

if exist "CMakeFiles" ( rmdir /s /q "CMakeFiles" ) else echo -- Cant find 'CMakeFiles/' dir, skipping...

if %errorlevel% neq 0 (
    echo Rmdir of 'build/' or 'CMakeFiles' failed
    pause
    exit /b
)

echo --- Configure emcmake... 
emcmake cmake .
if %errorlevel% neq 0 (
    echo CMake configure failed
    pause
    exit /b
)

echo --- Running ninja...
emcmake cmake -G "Ninja" -S . -B build
if %errorlevel% neq 0 (
    echo Ninja pipeline failed
    pause
    exit /b
)

echo --- Generate .obj files...
cmake --build build
if %errorlevel% neq 0 (
    echo Build failed
    pause
    exit /b
)


echo --- Build done!
