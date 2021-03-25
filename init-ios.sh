mkdir -p build && cd build && cmake -Wno-dev -G "Xcode" -DCMAKE_TOOLCHAIN_FILE=../RavEngine/deps/ios/ios.toolchain.cmake -DENABLE_ARC=OFF -DDEPLOYMENT_TARGET=14.0 -DPLATFORM=OS64COMBINED ..
