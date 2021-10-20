#!/bin/sh

#export CC=/usr/bin/clang;
#export CXX=/usr/bin/clang++;
./init-linux.sh
cd ../build/linux
cmake --build . --config debug --target install
