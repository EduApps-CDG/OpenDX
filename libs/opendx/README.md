# libopendx.so
Here goes everything that's not part of DirectX library.
Some examples are:
* DLL files that DirectX depends on will be turned into `libopendx.so`
such as kernel32.dll.
* Essential external functions and definitions needed to mantain software
compatibility such as functions contained in `<windows.h>`. But the headers
will be found in [`/prod_include`](../../prod_include).

All of these examples will be built in a single library and that's what
`libopendx.so` does.

The main file is [`./opendx.cpp`](./opendx.cpp)
