#!/bin/bash
# This file will install the required packages and build the project

# Check if package is installed
function check_package($package) {
    if ! dpkg -s $package > /dev/null 2>&1; then
        echo "Package $1 is not installed. Installing..."
        #sudo apt-get install $1
    fi
}

# Check if package is installed
check_package "gcc"
check_package "make"
check_package "libgtk+-3.0-dev"

# Build the project
cd build
cmake ..
make

echo "Build complete, run ./run.sh to run the program"