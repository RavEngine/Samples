#!/bin/sh
cd ..
mkdir -p build && mkdir -p build/linuxarm && cd build/linuxarm && CC=/usr/bin/aarch64-linux-gnu-gcc CXX=/usr/bin/aarch64-linux-gnu-g++ cmake -G "Ninja" -Wno-dev -DCMAKE_BUILD_TYPE=Release -DTARGET_ARCH=aarch64 ../..
