@echo off
REM =====================================================
REM Build script for R-Type project on Windows
REM Visual Studio 2026 - x64 - Release
REM Output binaries go directly into build\
REM =====================================================

setlocal enabledelayedexpansion

REM ---- Configuration ----
set BUILD_DIR=build
set CONFIG=Release
set ARCH=x64

REM ---- Clean build directory ----
if exist "%BUILD_DIR%" (
    echo Cleaning previous build...
    rmdir /s /q "%BUILD_DIR%"
)

REM ---- Create build directory ----
mkdir "%BUILD_DIR%"
cd "%BUILD_DIR%"

REM ---- Generate Visual Studio solution ----
echo Generating Visual Studio solution...
cmake .. -A %ARCH%

if errorlevel 1 (
    echo.
    echo ERROR: CMake configuration failed.
    pause
    exit /b 1
)

REM ---- Build (Release) ----
echo Building project (%CONFIG%)...
cmake --build . --config %CONFIG%

if errorlevel 1 (
    echo.
    echo ERROR: Build failed.
    pause
    exit /b 1
)

echo.
echo =====================================
echo Build Successful!
echo Executables are in: %CD%
echo =====================================
echo.

pause
