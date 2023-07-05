cd ..
mkdir -p build && mkdir -p build/tvos && cd build/tvos && cmake -Wno-dev -G "Xcode" -DCMAKE_SYSTEM_NAME=tvOS ../..
