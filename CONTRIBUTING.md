# Contributing
This guide shows how to prepare your environment to contribute for OpenDX's DirectX reimplementation.

## Dependencies
If you-re using Ubuntu or Arch Linux, `./build.sh` should detect and try to install the dependencies for you. You're free to modify `build.sh` according to your distro packages in a pull request.

But if you want to do it manually. Here is the list of dependencies:
| Dependency | Version |
|:-|-:|
|[`gcc`](https://packages.ubuntu.com/lunar/gcc)|`12.2.0`|
|[`cmake`](https://packages.ubuntu.com/lunar/cmake)|`3.25.1`|
|[`make`](https://packages.ubuntu.com/lunar/make)|`4.3`|
|[`libgtk-4-dev`](https://packages.ubuntu.com/lunar/libgtk-4-dev)|`4.10.1`|
|[`libdrm-dev`](https://packages.ubuntu.com/lunar/libdrm-dev)|`4.10.1`|

## Building and running
These are the same universal steps for cmake:

**Build:**
```sh
./build.sh
```

**Run:**
```sh
#setup env vars such as PATH and LD_LIBRARY_PATH
source ./setpath.sh

#commands available to run:
dxdiag
sample
```
