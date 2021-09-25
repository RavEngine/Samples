cd ..
mkdir -p build && mkdir -p build/ios-sim && cd build/ios-sim && cmake -Wno-dev -G "Xcode" -DCMAKE_TOOLCHAIN_FILE=../../RavEngine/deps/ios/ios.toolchain.cmake -DENABLE_ARC=OFF -DDEPLOYMENT_TARGET=14.0 -DPLATFORM=SIMULATOR64 ../..
