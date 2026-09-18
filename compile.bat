@echo off
cd /d "%~dp0"

if exist build rmdir /s /q build
mkdir build
cd /d build

cmake .. -G "MinGW Makefiles"
cmake --build . -j7