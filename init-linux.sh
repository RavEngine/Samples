#!/bin/sh

mkdir -p build && cd build && cmake -G "Ninja" -Wno-dev -DCMAKE_BUILD_TYPE=Release ..
