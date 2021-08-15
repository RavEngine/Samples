@echo OFF

cd ..
mkdir build
cd build
mkdir win
cd win
cmake -Wno-dev ..\..
cd ..\..
