#!/bin/bash
#===============================================
# Build script for R-Type project on Linux
#===============================================

# Exit on any error
set -e

# Set build directory
BUILD_DIR=build

# Clean the build directory before starting
if [ -d "$BUILD_DIR" ]; then
    echo "Cleaning existing build directory..."
    rm -rf "$BUILD_DIR"
fi

# Create build directory
echo "Creating build directory..."
mkdir -p "$BUILD_DIR"

# Navigate to build directory
cd "$BUILD_DIR"

# Generate build files with CMake
echo "Configuring project with CMake..."
cmake ..

# Check if configuration was successful
if [ $? -ne 0 ]; then
    echo ""
    echo "ERROR: CMake configuration failed."
    exit 1
fi

# Build the project in Release configuration
echo "Building project..."
cmake --build . --config Release

# Check if build was successful
if [ $? -ne 0 ]; then
    echo ""
    echo "ERROR: Build failed."
    exit 1
fi

echo ""
echo "Build Successful!"
echo "Executables are in: $BUILD_DIR/"
echo ""
