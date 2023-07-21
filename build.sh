#!/bin/bash
# This file will install the required packages and build the project

# Check if package is installed
function check_package {
    if ! dpkg -s $1 > /dev/null 2>&1; then
        echo "Package $1 is not installed. Installing..."
        sudo apt install $1
    fi
}

# Check if package is installed
check_package "gcc"
check_package "cmake"
check_package "make"
check_package "libgtk-4-dev"

# Build the project
cd build
cmake ..
make

echo "Build complete, run ./run.sh to run the program"
