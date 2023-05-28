cd ..
mkdir -p build && mkdir -p build/ios && cd build/ios && cmake -Wno-dev -G "Xcode" -DENABLE_VISIBILITY=ON -DCMAKE_SYSTEM_NAME=iOS ../..
