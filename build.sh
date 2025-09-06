#!/bin/bash
# This file will install the required packages and build the project
# Feel free to contribute it to suit your distro.

set -e

INSTALL_CMD="sudo apt install -y --fix-missing"
PACKAGES=();
UBUNTU_PACKAGES=(
    gcc
    cmake
    make
    libdrm-dev
    libgtk-4-dev
    rpm # For cpack RPM generation ("rpm-build" in some distros)
);
ARCH_PACKAGES=(
    base-devel
    gdb
    gcc
    cmake
    make
    libdrm
    gtk4
    rpm-tools # For cpack RPM generation ("rpm-build" in some distros)
);
DISTRO="ubuntu" #default

# Check if package is installed
function check_packages {
    TO_INSTALL=""
    if [ "$DISTRO" == "ubuntu" ]; then
        for pkg in "$@"; do
            if ! dpkg -s $pkg > /dev/null 2>&1; then
                TO_INSTALL="$TO_INSTALL $pkg"
            fi
        done
    elif [ "$DISTRO" == "arch" ]; then
        for pkg in "$@"; do
            if ! pacman -Qi $pkg > /dev/null 2>&1; then
                TO_INSTALL="$TO_INSTALL $pkg"
            fi
        done
    fi

    if [ -n "$TO_INSTALL" ]; then
        echo "The following packages are not installed: $TO_INSTALL"
        echo "Installing missing packages..."
        $INSTALL_CMD $TO_INSTALL
    fi
}

#check distro (ID)
if [ -f /etc/os-release ]; then
    . /etc/os-release
    DISTRO=$ID
    #Arch based distros
    if [[ "$ID" == "arch" || "$ID_LIKE" == *"arch"* ]]; then
        INSTALL_CMD="sudo pacman -Syu --needed --noconfirm"
        PACKAGES=("${ARCH_PACKAGES[@]}")
    elif [[ "$ID" == "ubuntu" || "$ID_LIKE" == *"debian"* ]]; then
        INSTALL_CMD="sudo apt install -y --fix-missing"
        PACKAGES=("${UBUNTU_PACKAGES[@]}")
    else
        echo "Distro $ID is not directly supported. Attempting to use Ubuntu packages."
        INSTALL_CMD="sudo apt install -y --fix-missing"
        PACKAGES=("${UBUNTU_PACKAGES[@]}")
    fi
else
    echo "Cannot determine the operating system. Exiting."
    exit 1
fi

# Check if package is installed
echo "Checking required packages for $DISTRO..."
check_packages "${PACKAGES[@]}"

# Build the project
echo "Building the project..."
cd build
echo "> CMake .."
cmake ..
echo "> make"
make
cd ..

echo "Build complete, run ./run.sh to run the program"
