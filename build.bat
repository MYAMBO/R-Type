@echo off
REM ==============================================
REM Build script for R-Type project on Windows
REM (Updated for Visual Studio 2026 and x64)
REM ==============================================

REM Set build directory
set BUILD_DIR=build

REM Clean the build directory before starting
if exist %BUILD_DIR% rmdir /s /q %BUILD_DIR%

REM Create build directory
mkdir %BUILD_DIR%

REM Navigate to build directory
cd %BUILD_DIR%

REM Generate Visual Studio solution with CMake
REM Using auto-detection (no -G) and specifying 64-bit architecture (-A x64)
cmake .. -A x64

REM Check if configuration was successful
if errorlevel 1 (
    echo.
    echo ERROR: CMake configuration failed.
    pause
    exit /b 1
)

REM Build the solution in Release configuration
cmake --build . --config Release

REM Check if build was successful
if errorlevel 1 (
    echo.
    echo ERROR: Build failed.
    pause
    exit /b 1
)

echo.
echo Build Successful!
echo Executables are likely in: %BUILD_DIR%\Release
echo.

REM Optional: pause to see output
pause
