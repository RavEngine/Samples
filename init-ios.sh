mkdir -p build && cd build && cmake -Wno-dev -G "Xcode" -DCMAKE_TOOLCHAIN_FILE=../RavEngine/deps/ios/ios.toolchain.cmake -DPLATFORM=OS64COMBINED ..
