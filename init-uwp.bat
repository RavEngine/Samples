@echo OFF
mkdir build
cd build
cmake -G "Visual Studio 16 2019" -Ax64 -DCMAKE_SYSTEM_NAME=WindowsStore -DCMAKE_SYSTEM_VERSION="10.0" ..