#!/bin/bash
# This file will install the required packages and build the project

# Check if package is installed
function check_packages {
    TO_INSTALL=""
    for pkg in "$@"; do
        if ! dpkg -s $pkg > /dev/null 2>&1; then
            TO_INSTALL="$TO_INSTALL $pkg"
        fi
    done

    if [ -n "$TO_INSTALL" ]; then
        echo "The following packages are not installed: $TO_INSTALL"
        echo "Installing missing packages..."
        sudo apt install $TO_INSTALL --fix-missing -y
    fi
}

# Check if package is installed (Ubuntu)
echo "Checking required packages..."
check_packages gcc cmake make libdrm-dev libgtk-4-dev

# Build the project
echo "Building the project..."
cd build
echo "> CMake .."
cmake ..
echo "> make"
make
cd ..

echo "Build complete, run ./run.sh to run the program"
