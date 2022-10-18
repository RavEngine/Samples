@echo OFF
cd ..
mkdir build
cd build
mkdir uwparm
cd uwparm
cmake -AARM64 -DCMAKE_SYSTEM_NAME=WindowsStore -DCMAKE_SYSTEM_VERSION="10.0" -Wno-dev ..\..
cd ..\..
