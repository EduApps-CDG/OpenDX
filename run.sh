# Run dxdiag from build directory
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:./build/opendx/lib
export PATH=$PATH:./build/opendx/bin
cd build/opendx
gdb -x ../../.gdbinit