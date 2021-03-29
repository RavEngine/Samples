#!/bin/sh

#export CC=/usr/bin/clang;
#export CXX=/usr/bin/clang++;
./init-linux.sh
cd build;
cmake --build . --config release --target install
