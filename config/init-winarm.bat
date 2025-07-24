@echo OFF

cd ..
mkdir build
cd build
mkdir winarm
cd winarm
cmake -Wno-dev -AARM64 ..\..
cd ..\..
PAUSE
