#!/bin/bash
set -e

echo "--- Removing old build folders..."
rm -rf build CMakeFiles

echo "--- Configure emcmake..."
emcmake cmake .

echo "--- Running ninja..."
emcmake cmake -G "Ninja" -S . -B build

echo "--- Generate .obj files..."
cmake --build build

echo "--- Build done!"