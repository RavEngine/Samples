#!/bin/sh
cd ..
mkdir -p build && mkdir -p build/web && cd build/web && cmake -DCMAKE_TOOLCHAIN_FILE=../../../emsdk/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake ../..
