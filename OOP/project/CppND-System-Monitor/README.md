# CppND-System-Monitor

My implementation of the system monitor developed from the starter code available at [https://github.com/udacity/CppND-System-Monitor](https://github.com/udacity/CppND-System-Monitor). See also  [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213). 

## Make
This project uses [Make](https://www.gnu.org/software/make/). The Makefile has four targets:
* `build` compiles the source code and generates an executable
* `format` applies [ClangFormat](https://clang.llvm.org/docs/ClangFormat.html) to style the source code
* `debug` compiles the source code and generates an executable, including debugging symbols
* `clean` deletes the `build/` directory, including all of the build artifacts

## Build instructions
From the command line, navigate to the current directory, i.e. `CppND-System-Monitor/CppND-System-Monitor`. Make sure you are using g++ version 8 or later. Then, type `make build`. The executable `monitor` will be created in the directory `./build/`. 

## Filesystem
Notice that the file `./CMakeList` sets c++17 as standard and links stdc++fs in order for the header \<filesystem\> to be used.
In the folder `../mytests/filesystem` a small program tests the utilization of \<filesystem\>.

## ncurses
[ncurses](https://www.gnu.org/software/ncurses/) is a library that facilitates text-based graphical output in the terminal. This project relies on ncurses for display output.


