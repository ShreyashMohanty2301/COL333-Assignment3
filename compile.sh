#!/bin/bash

# This script compiles all the necessary C++ source files into a single executable.

echo "Compiling C++ source files..."

# List all your .cpp files here.
# -std=c++17 sets the C++ standard.
# -O2 is a standard optimization level.
# -Wall enables all compiler warnings.
# -o maincode names the output executable 'maincode'.
make

echo "Compilation successful. Executable 'maincode' created."