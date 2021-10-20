#!/bin/sh
cd ..
mkdir -p build && mkdir -p build/linux && cd build/linux && cmake -G "Ninja" -Wno-dev -DCMAKE_BUILD_TYPE=Debug ../..
